#pragma once

#include "core/asset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/lightkit_asset.h"

namespace Slick {

    namespace Assets {

        class LightKitAsset : public Core::Asset
        {
            Q_OBJECT

        public:
            LightKitAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            HipHop::LightKitAsset* serializer() { return &m_lightKit; }

            bool lightPreviewEnabled(int index) const { return m_lightPreviews[index]; }
            void setLightPreviewEnabled(int index, bool enabled) { m_lightPreviews[index] = enabled; }

            Core::Vector3 lightPosition(int index) const { return m_lightPositions[index]; }
            void setLightPosition(int index, const Core::Vector3& pos);

            Core::Vector3 lightRotation(int index) const { return m_lightRotations[index]; }
            void setLightRotation(int index, const Core::Vector3& pos);

            Core::Vector3 lightScale(int index) const { return m_lightScales[index]; }
            void setLightScale(int index, const Core::Vector3& pos);

            void setup();
            void bind();

            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::LightKitAsset m_lightKit;
            QList<bool> m_lightPreviews;
            QList<Core::Vector3> m_lightPositions;
            QList<Core::Vector3> m_lightRotations;
            QList<Core::Vector3> m_lightScales;

            void updateLightMatrix(int index);
        };

        class LightKitManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            LightKitManager(Core::Scene* scene) : Core::AssetManager(scene), m_currentLightKit(nullptr) {}

            void setup();
            void bind(LightKitAsset* lightKit);

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::LKIT; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new LightKitAsset(asset, sceneFile); }

        private:
            LightKitAsset* m_currentLightKit;
        };

    }

}
