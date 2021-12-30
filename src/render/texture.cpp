#include "render/texture.h"

#include "rws_core.h"

namespace Slick {

    namespace Render {

        Texture::Texture(Context* context, Rws::TextureNative* data) :
            m_context(context),
            m_data(nullptr),
            m_id(0)
        {
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
                m_context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                m_context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                m_context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                m_context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                m_context->glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
                m_context->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_data->width, m_data->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data->texels.data());
                m_context->glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            }
        }

        void Texture::bind()
        {
            if (m_id != 0)
            {
                m_context->glPushAttrib(GL_ENABLE_BIT);
                m_context->glEnable(GL_TEXTURE_2D);
                m_context->glBindTexture(GL_TEXTURE_2D, m_id);
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

    }

}
