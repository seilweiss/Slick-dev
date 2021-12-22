#pragma once

#include "Core/EntAsset.h"

#include "hiphop/assets/player_asset.h"

namespace Slick {

    namespace Assets {

        class PlayerAsset : public EntAsset
        {
            Q_OBJECT

        public:
            PlayerAsset(HipHop::Asset asset, SceneFile* sceneFile);

            virtual void setup() override;
            virtual void inspect(Inspector* inspector) override;

        private:
            HipHop::PlayerAsset m_player;
        };

    }

}
