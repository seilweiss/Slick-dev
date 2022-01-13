#pragma once

#include "core/asset.h"
#include "core/assetmanager.h"
#include "core/modelinstance.h"

#include "render/clump.h"

#include "hiphop/assets/model_asset.h"

namespace Slick {

    namespace Assets {

        class ModelAsset : public Core::Asset
        {
            Q_OBJECT

        public:
            ModelAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);
            ~ModelAsset();

            Render::Clump* clump() { return &m_clump; }

            Core::ModelInstance* createInstance();

            void setup();

            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::ModelAsset m_model;
            Render::Clump m_clump;
            QList<Core::ModelInstance*> m_instances;
        };

        class ModelManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            ModelManager(Core::Scene* scene) : Core::AssetManager(scene) {}

            void setup();

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::MODL; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new ModelAsset(asset, sceneFile); }
        };

    }

}
