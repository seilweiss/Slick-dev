#pragma once

#include "Core/Asset.h"
#include "Render/Clump.h"

#include "hiphop/assets/jsp_asset.h"

namespace Slick {

    namespace Assets {

        class JSPAsset : public Asset
        {
            Q_OBJECT

        public:
            JSPAsset(HipHop::Asset asset, SceneFile* sceneFile);

            Render::Clump* clump() const { return m_clump; }

            virtual void render(Render::Context& context) override;

        private:
            Render::Clump* m_clump;
            HipHop::JSPAsset m_jsp;
        };

    }

}
