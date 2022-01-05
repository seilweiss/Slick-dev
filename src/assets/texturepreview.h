#pragma once

#include "render/viewport.h"
#include "assets/textureasset.h"

namespace Slick {

    namespace Assets {

        class TexturePreview : public Render::Viewport
        {
            Q_OBJECT

        public:
            TexturePreview(TextureAsset* asset, QWindow* parent = nullptr);

        protected:
            virtual void render() override;

        private:
            TextureAsset* m_asset;
        };

    }

}
