#pragma once

#include "assets/baseasset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/cam_asset.h"

#include <glm/glm.hpp>

namespace Slick {

    namespace Assets {

        class CameraAsset : public BaseAsset
        {
            Q_OBJECT

        public:
            CameraAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            virtual void inspect(Inspector::Root* root) override;

            Core::Vector3 position() const { return m_pos; }
            void setPosition(const Core::Vector3& pos);

            Core::Vector3 rotation() const { return m_rot; }
            void setRotation(const Core::Vector3& rot);

            Core::Vector3 scale() const { return m_scale; }
            void setScale(const Core::Vector3& scale);

            void setup();
            void apply();

        private:
            HipHop::CamAsset m_cam;
            glm::mat4 m_viewMatrix;
            Core::Vector3 m_pos;
            Core::Vector3 m_rot;
            Core::Vector3 m_scale;

            void updateMatrix();
        };

        class CameraManager : public Core::AssetManager
        {
            Q_OBJECT
            Q_PROPERTY(Assets::CameraAsset* previewCamera READ previewCamera WRITE setPreviewCamera NOTIFY previewCameraChanged)

        public:
            CameraManager(Core::Scene* scene) :
                Core::AssetManager(scene),
                m_previewCam(nullptr),
                m_isPreviewing(false),
                m_wasPreviewing(false),
                m_saveEditorCamMatrix(1.0f),
                m_saveEditorCamFov(0.0f)
            {
            }

            Assets::CameraAsset* previewCamera() const { return m_previewCam; }
            void setPreviewCamera(Assets::CameraAsset* camera);

            void setup();
            void update();

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::CAM; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new CameraAsset(asset, sceneFile); }

        signals:
            void previewCameraChanged(Assets::CameraAsset* camera);

        private:
            Assets::CameraAsset* m_previewCam;
            bool m_isPreviewing;
            bool m_wasPreviewing;
            glm::mat4 m_saveEditorCamMatrix;
            float m_saveEditorCamFov;
        };

    }

}
