#pragma once

#include "rws/core/core_common.h"

namespace Rws { class TextureNative; }

namespace Slick {

    namespace Render {

        class Context;

        class Texture
        {
        public:
            Texture(Context* context, Rws::TextureNative* data = nullptr);

            Rws::TextureNative* data() const { return m_data; }
            void setData(Rws::TextureNative* data);

            Rws::TextureFilterMode filterMode() const { return m_filterMode; }
            void setFilterMode(Rws::TextureFilterMode mode);

            Rws::TextureAddressMode addressingU() const { return m_addressingU; }
            void setAddressingU(Rws::TextureAddressMode mode);

            Rws::TextureAddressMode addressingV() const { return m_addressingV; }
            void setAddressingV(Rws::TextureAddressMode mode);

            void bind();
            void unbind();

            void destroy();

        private:
            Context* m_context;
            Rws::TextureNative* m_data;
            uint32_t m_id;
            Rws::TextureFilterMode m_filterMode;
            Rws::TextureAddressMode m_addressingU;
            Rws::TextureAddressMode m_addressingV;
            int m_filterMin;
            int m_filterMag;
            int m_wrapS;
            int m_wrapT;
        };

    }

}
