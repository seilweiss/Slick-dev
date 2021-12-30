#pragma once

#include "core/asset.h"

namespace Slick {

    namespace Core {

        class AssetManager : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(Scene* scene READ scene)

        public:
            AssetManager(Scene* scene);

            Scene* scene() const { return m_scene; }

            QList<Asset*>& assets() { return m_assets; }
            const QList<Asset*>& assets() const { return m_assets; }

            void addAsset(Asset* asset) { m_assets.append(asset); }

            virtual bool supports(HipHop::Asset asset) const = 0;
            virtual Asset* createAsset(HipHop::Asset asset, SceneFile* sceneFile) = 0;

        private:
            Scene* m_scene;
            QList<Asset*> m_assets;
        };

    }

}
