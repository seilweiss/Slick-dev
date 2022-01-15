#pragma once

#include "assets/entasset.h"
#include "assets/motionasset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/button_asset.h"

namespace Slick {

    namespace Assets {

        class ButtonAsset : public EntAsset
        {
            Q_OBJECT

        public:
            ButtonAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            HipHop::ButtonAsset* serializer() { return &m_button; }

            virtual void setup() override;
            virtual void update() override;
            virtual void render() override;
            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::ButtonAsset m_button;
            MotionAsset* m_motion;
        };

        class ButtonManager : public Core::AssetManager
        {
            Q_OBJECT
            Q_PROPERTY(float redMultiplier READ redMultiplier)
            Q_PROPERTY(float greenMultiplier READ greenMultiplier)
            Q_PROPERTY(float blueMultiplier READ blueMultiplier)

        public:
            ButtonManager(Core::Scene* scene) :
                Core::AssetManager(scene),
                m_redMultiplier(1.0f),
                m_greenMultiplier(1.0f),
                m_blueMultiplier(1.0f),
                m_colorMultiplier(1.0f),
                m_colorMultiplierSign(1)
            {
            }

            float redMultiplier() const { return m_redMultiplier; }
            float greenMultiplier() const { return m_greenMultiplier; }
            float blueMultiplier() const { return m_blueMultiplier; }

            void setup();
            void update();
            void render();

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::BUTN; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new ButtonAsset(asset, sceneFile); }

        private:
            float m_redMultiplier;
            float m_greenMultiplier;
            float m_blueMultiplier;
            float m_colorMultiplier;
            int m_colorMultiplierSign;
        };

    }

}
