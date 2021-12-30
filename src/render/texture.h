#pragma once

#include "render/context.h"

namespace Rws { class TextureNative; }

namespace Slick {

    namespace Render {

        class Texture
        {
        public:
            Texture(Context* context, Rws::TextureNative* data = nullptr);

            Rws::TextureNative* data() const { return m_data; }
            void setData(Rws::TextureNative* data);

            void bind();
            void unbind();

            void destroy();

        private:
            Context* m_context;
            Rws::TextureNative* m_data;
            uint32_t m_id;
        };

    }

}
