#include "render/texture.h"

#include "render/context.h"

#include "rws_core.h"

namespace Slick {

    namespace Render {

        namespace {

            GLenum makeMinFilter(Rws::TextureFilterMode mode)
            {
                switch (mode)
                {
                case Rws::FILTER_NEAREST: return GL_NEAREST;
                case Rws::FILTER_LINEAR: return GL_LINEAR;
                case Rws::FILTER_MIPNEAREST: return GL_NEAREST_MIPMAP_NEAREST;
                case Rws::FILTER_MIPLINEAR: return GL_NEAREST_MIPMAP_LINEAR; // Is this right???
                case Rws::FILTER_LINEARMIPNEAREST: return GL_LINEAR_MIPMAP_NEAREST;
                case Rws::FILTER_LINEARMIPLINEAR: return GL_LINEAR_MIPMAP_LINEAR;
                default: return GL_LINEAR;
                }
            }

            GLenum makeMagFilter(Rws::TextureFilterMode mode)
            {
                switch (mode)
                {
                case Rws::FILTER_NEAREST: return GL_NEAREST;
                case Rws::FILTER_LINEAR: return GL_LINEAR;
                case Rws::FILTER_MIPNEAREST: return GL_NEAREST;
                case Rws::FILTER_MIPLINEAR: return GL_LINEAR;
                case Rws::FILTER_LINEARMIPNEAREST: return GL_NEAREST;
                case Rws::FILTER_LINEARMIPLINEAR: return GL_LINEAR;
                default: return GL_LINEAR;
                }
            }

            Rws::TextureFilterMode makeRwFilter(GLenum mode)
            {
                switch (mode)
                {
                case GL_NEAREST: return Rws::FILTER_NEAREST;
                case GL_LINEAR: return Rws::FILTER_LINEAR;
                case GL_NEAREST_MIPMAP_NEAREST: return Rws::FILTER_MIPNEAREST;
                case GL_NEAREST_MIPMAP_LINEAR: return Rws::FILTER_MIPLINEAR; // Is this right???
                case GL_LINEAR_MIPMAP_NEAREST: return Rws::FILTER_LINEARMIPNEAREST;
                case GL_LINEAR_MIPMAP_LINEAR: return Rws::FILTER_LINEARMIPLINEAR;
                default: return Rws::FILTER_LINEAR;
                }
            }

            GLenum makeWrap(Rws::TextureAddressMode mode)
            {
                switch (mode)
                {
                case Rws::ADDRESS_WRAP: return GL_REPEAT;
                case Rws::ADDRESS_MIRROR: return GL_MIRRORED_REPEAT;
                case Rws::ADDRESS_CLAMP: return GL_CLAMP;
                case Rws::ADDRESS_BORDER: return GL_CLAMP_TO_BORDER;
                default: return GL_REPEAT;
                }
            }

            Rws::TextureAddressMode makeRwAddress(GLenum mode)
            {
                switch (mode)
                {
                case GL_REPEAT: return Rws::ADDRESS_WRAP;
                case GL_MIRRORED_REPEAT: return Rws::ADDRESS_MIRROR;
                case GL_CLAMP: return Rws::ADDRESS_CLAMP;
                case GL_CLAMP_TO_BORDER: return Rws::ADDRESS_BORDER;
                default: return Rws::ADDRESS_WRAP;
                }
            }

        }

        Texture::Texture(Context* context, Rws::TextureNative* data) :
            m_context(context),
            m_data(nullptr),
            m_id(0)
        {
            setFilterMode(Rws::FILTER_LINEAR);
            setAddressingU(Rws::ADDRESS_WRAP);
            setAddressingV(Rws::ADDRESS_WRAP);

            setData(data);
        }

        void Texture::setData(Rws::TextureNative* data)
        {
            destroy();

            m_data = data;

            if (m_data)
            {
                m_context->glGenTextures(1, &m_id);
                m_context->glBindTexture(GL_TEXTURE_2D, m_id);
                m_context->glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                m_context->glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
                m_context->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_data->width, m_data->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data->texels.data());
                m_context->glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

                setFilterMode(m_data->filtering);
                setAddressingU(m_data->addressingU);
                setAddressingV(m_data->addressingV);
            }
        }

        void Texture::bind()
        {
            if (m_id != 0)
            {
                m_context->glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
                m_context->glEnable(GL_TEXTURE_2D);

                m_context->glBindTexture(GL_TEXTURE_2D, m_id);
                m_context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin);
                m_context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMag);
                m_context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapS);
                m_context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapT);
            }
        }

        void Texture::unbind()
        {
            if (m_id != 0)
            {
                m_context->glPopAttrib();
            }
        }

        void Texture::destroy()
        {
            if (m_id != 0)
            {
                m_context->glDeleteTextures(1, &m_id);
                m_id = 0;
            }
        }

        void Texture::setFilterMode(Rws::TextureFilterMode mode)
        {
            m_filterMode = mode;
            m_filterMin = makeMinFilter(mode);
            m_filterMag = makeMagFilter(mode);
        }

        void Texture::setAddressingU(Rws::TextureAddressMode mode)
        {
            m_addressingU = mode;
            m_wrapS = makeWrap(mode);
        }

        void Texture::setAddressingV(Rws::TextureAddressMode mode)
        {
            m_addressingV = mode;
            m_wrapT = makeWrap(mode);
        }

    }

}
