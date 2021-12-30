#include "assets/cameraasset.h"

#include "core/scene.h"
#include "util/mathutils.h"
#include "render/camera.h"

namespace Slick {

    namespace Assets {

        namespace {

            class CamPositionProxy : public Inspector::Proxy<Core::Vector3>
            {
            public:
                CamPositionProxy(CameraAsset* asset) : Inspector::Proxy<Core::Vector3>(nullptr), m_asset(asset) {}

                virtual Core::Vector3 data() const override
                {
                    return m_asset->position();
                }

                virtual void setData(const Core::Vector3& pos) const override
                {
                    m_asset->setPosition(pos);
                }

            private:
                CameraAsset* m_asset;
            };

            class CamRotationProxy : public Inspector::Proxy<Core::Vector3>
            {
            public:
                CamRotationProxy(CameraAsset* asset) : Inspector::Proxy<Core::Vector3>(nullptr), m_asset(asset) {}

                virtual Core::Vector3 data() const override
                {
                    return m_asset->rotation();
                }

                virtual void setData(const Core::Vector3& rot) const override
                {
                    m_asset->setRotation(rot);
                }

            private:
                CameraAsset* m_asset;
            };

            class CamScaleProxy : public Inspector::Proxy<Core::Vector3>
            {
            public:
                CamScaleProxy(CameraAsset* asset) : Inspector::Proxy<Core::Vector3>(nullptr), m_asset(asset) {}

                virtual Core::Vector3 data() const override
                {
                    return m_asset->scale();
                }

                virtual void setData(const Core::Vector3& scale) const override
                {
                    m_asset->setScale(scale);
                }

            private:
                CameraAsset* m_asset;
            };

        }

        CameraAsset::CameraAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            BaseAsset(asset, sceneFile),
            m_cam(asset),
            m_viewMatrix(1.0f)
        {
            setEditor(&m_cam);
        }

        void CameraAsset::setup()
        {
            glm::mat4 mat(1.0f);

            mat[0][0] = -m_cam.right.x;
            mat[0][1] = -m_cam.right.y;
            mat[0][2] = -m_cam.right.z;
            mat[1][0] = m_cam.up.x;
            mat[1][1] = m_cam.up.y;
            mat[1][2] = m_cam.up.z;
            mat[2][0] = -m_cam.at.x;
            mat[2][1] = -m_cam.at.y;
            mat[2][2] = -m_cam.at.z;
            mat[3][0] = m_cam.pos.x;
            mat[3][1] = m_cam.pos.y;
            mat[3][2] = m_cam.pos.z;

            glm::vec3 pos;
            glm::vec3 rot;
            glm::vec3 scale;

            Util::decomposeMatrix(mat, pos, rot, scale);

            m_pos = Core::Vector3(pos.x, pos.y, pos.z);
            m_rot = Core::Vector3(rot.x, rot.y, rot.z);
            m_scale = Core::Vector3(scale.x, scale.y, scale.z);

            m_viewMatrix = mat;
        }

        void CameraAsset::apply()
        {
            Render::Context* context = scene()->renderContext();

            context->camera()->setViewMatrix(m_viewMatrix);

            Render::Projection proj = context->camera()->projection();
            proj.fov = glm::radians(m_cam.fov);
            context->camera()->setProjection(proj);
        }

        void CameraAsset::inspect(Inspector::Root* root)
        {
            BaseAsset::inspect(root);

            auto transformGroup = root->addGroup("transform", tr("Transform"));
            auto positionProp = transformGroup->addVectorInput("position", tr("Position"), new CamPositionProxy(this));
            auto rotationProp = transformGroup->addVectorInput("rotation", tr("Rotation"), new CamRotationProxy(this));
            auto scaleProp = transformGroup->addVectorInput("scale", tr("Scale"), new CamScaleProxy(this));

            auto cameraGroup = root->addGroup("camera", tr("Camera"));
            //auto previewProp = cameraGroup->addCheckBox("preview", tr("Preview"), &m_preview);
            auto fovProp = cameraGroup->addNumberInput("fov", tr("FOV"), &m_cam.fov);

            rotationProp->setConvertRadiansToDegrees(true);

            positionProp->setHelpText(tr("The camera's position."));
            rotationProp->setHelpText(tr("The camera's rotation."));
            scaleProp->setHelpText(tr("The camera's scale."));
            //previewProp->setHelpText(tr("Preview the camera in the editor viewport."));
            fovProp->setHelpText(tr("The camera's field-of-view."));

            connect(positionProp, &Inspector::Property::dataChanged, this, &CameraAsset::makeDirty);
            connect(rotationProp, &Inspector::Property::dataChanged, this, &CameraAsset::makeDirty);
            connect(scaleProp, &Inspector::Property::dataChanged, this, &CameraAsset::makeDirty);

            inspectLinks(root);
        }

        void CameraAsset::setPosition(const Core::Vector3& pos)
        {
            m_pos = pos;
            updateMatrix();
        }

        void CameraAsset::setRotation(const Core::Vector3& rot)
        {
            m_rot = rot;
            updateMatrix();
        }

        void CameraAsset::setScale(const Core::Vector3& scale)
        {
            m_scale = scale;
            updateMatrix();
        }

        void CameraAsset::updateMatrix()
        {
            glm::mat4 mat(1.0f);
            mat = glm::translate(mat, glm::vec3(m_pos.x, m_pos.y, m_pos.z));
            mat *= glm::mat4_cast(glm::quat(glm::vec3(m_rot.x, m_rot.y, m_rot.z)));
            mat = glm::scale(mat, glm::vec3(m_scale.x, m_scale.y, m_scale.z));

            m_cam.right = HipHop::Vec3(-mat[0][0], -mat[0][1], -mat[0][2]);
            m_cam.up = HipHop::Vec3(mat[1][0], mat[1][1], mat[1][2]);
            m_cam.at = HipHop::Vec3(-mat[2][0], -mat[2][1], -mat[2][2]);
            m_cam.pos = HipHop::Vec3(mat[3][0], mat[3][1], mat[3][2]);

            m_viewMatrix = mat;
        }

        void CameraManager::setup()
        {
            for (auto asset : assets())
            {
                ((CameraAsset*)asset)->setup();
            }
        }

        void CameraManager::update()
        {
            Render::Context* context = scene()->renderContext();

            m_isPreviewing = (m_previewCam != nullptr);

            if (m_isPreviewing != m_wasPreviewing)
            {
                if (m_isPreviewing && !m_wasPreviewing)
                {
                    m_saveEditorCamMatrix = context->camera()->viewMatrix();
                    m_saveEditorCamFov = context->camera()->projection().fov;
                }
                else if (!m_isPreviewing)
                {
                    context->camera()->setViewMatrix(m_saveEditorCamMatrix);

                    Render::Projection proj = context->camera()->projection();
                    proj.fov = m_saveEditorCamFov;
                    context->camera()->setProjection(proj);
                }
            }

            if (m_previewCam)
            {
                m_previewCam->apply();
            }

            m_wasPreviewing = m_isPreviewing;
        }

        void CameraManager::setPreviewCamera(Assets::CameraAsset* camera)
        {
            if (m_previewCam)
            {
                m_previewCam->disconnect(this);
            }

            m_previewCam = camera;

            if (m_previewCam)
            {
                connect(m_previewCam, &QObject::destroyed, this, [=]
                {
                    m_previewCam = nullptr;
                    emit previewCameraChanged(nullptr);
                });
            }

            emit previewCameraChanged(camera);
        }

    }

}
