#include "core/modelbucketmanager.h"

#include "core/scene.h"
#include "core/modelinstance.h"

#include "render/atomic.h"

namespace Slick {

    namespace Core {

        ModelBucketManager::ModelBucketManager(Scene* scene) :
            QObject(scene),
            m_scene(scene),
            m_enabled(false),
            m_opaqueBuckets(),
            m_alphaBuckets()
        {
        }

        void ModelBucketManager::begin()
        {
            m_opaqueBuckets.clear();
            m_alphaBuckets.clear();
            m_enabled = true;
        }

        void ModelBucketManager::add(ModelInstance* model)
        {
            bool opaque = true;
            HipHop::PipeInfo* pipeInfo = model->pipeInfo();

            if (pipeInfo &&
                    (pipeInfo->BlendSrc != HipHop::PipeInfo::BlendNA ||
                     pipeInfo->BlendDst != HipHop::PipeInfo::BlendNA))
            {
                opaque = false;
            }
            else if (model->color()[3] != 1.0f)
            {
                opaque = false;
            }

            if (opaque)
            {
                OpaqueBucket bucket;
                bucket.model = model;

                m_opaqueBuckets.append(bucket);
            }
            else
            {
                Render::Atomic* atomic = model->data();
                glm::mat4 oldmat = atomic->frame()->matrix();

                atomic->frame()->setMatrix(model->matrix());

                glm::vec3 center = atomic->worldBoundingSphereCenter();
                float radius = atomic->worldBoundingSphereRadius();
                glm::mat4 cammat = m_scene->renderContext()->camera()->viewMatrix();

                float camdot =
                        cammat[2][0] * (center.x - cammat[3][0]) +
                        cammat[2][1] * (center.y - cammat[3][1]) +
                        cammat[2][2] * (center.z - cammat[3][2]);

                AlphaBucket bucket;
                bucket.model = model;
                bucket.sortValue = radius > 25.0f ? camdot + radius : camdot;
                bucket.layer = pipeInfo ? pipeInfo->AlphaLayer : 19;

                m_alphaBuckets.append(bucket);

                atomic->frame()->setMatrix(oldmat);
            }
        }

        void ModelBucketManager::renderOpaque()
        {
            m_enabled = false;

            for (OpaqueBucket& bucket : m_opaqueBuckets)
            {
                bucket.model->renderSingle();
            }
        }

        void ModelBucketManager::renderAlpha()
        {
            m_enabled = false;

            std::sort(m_alphaBuckets.begin(), m_alphaBuckets.end(), [=](const AlphaBucket& a, const AlphaBucket& b)
            {
                if (a.layer > b.layer)
                {
                    return false;
                }

                if (a.layer < b.layer)
                {
                    return true;
                }

                if (a.sortValue < b.sortValue)
                {
                    return false;
                }

                if (a.sortValue > b.sortValue)
                {
                    return true;
                }

                return false;
            });

            for (AlphaBucket& bucket : m_alphaBuckets)
            {
                bucket.model->renderSingle();
            }
        }

    }

}
