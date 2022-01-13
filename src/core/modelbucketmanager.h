#pragma once

#include <QObject>

namespace Slick {

    namespace Core {

        class Scene;
        class ModelInstance;

        class ModelBucketManager : public QObject
        {
        public:
            ModelBucketManager(Scene* scene);

            bool isEnabled() const { return m_enabled; }

            void begin();
            void add(ModelInstance* model);
            void renderOpaque();
            void renderAlpha();

        private:
            struct OpaqueBucket
            {
                ModelInstance* model;
            };

            struct AlphaBucket
            {
                ModelInstance* model;
                float sortValue;
                int layer;
            };

            Scene* m_scene;
            bool m_enabled;
            QList<OpaqueBucket> m_opaqueBuckets;
            QList<AlphaBucket> m_alphaBuckets;
        };

    }

}
