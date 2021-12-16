#pragma once

#include "Core/Asset.h"

#include "hiphop/assets/text_asset.h"

namespace Slick {

    namespace Assets {

        class TextAsset : public Asset
        {
            Q_OBJECT

        public:
            TextAsset(HipHop::Asset asset, SceneFile* sceneFile);

        protected:
            virtual void doSave() override;

        private:
            HipHop::TextAsset m_text;
        };

    }

}
