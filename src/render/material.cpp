#include "render/material.h"

#include "render/context.h"

#include "rws_core.h"
#include "rws_world.h"

#include <glm/gtc/type_ptr.hpp>

namespace Slick {

    namespace Render {

        Material::Material(Context* context, Rws::Material* data) :
            m_context(context),
            m_data(nullptr),
            m_texture(nullptr),
            m_color(1.0f),
            m_ambient(1.0f),
            m_diffuse(1.0f),
            m_specular(1.0f),
            m_useColorMaterial(false)
        {
            setData(data);
        }

        void Material::setData(Rws::Material* data)
        {
            m_data = data;

            Rws::MaterialStruct* matStruct = m_data->GetStruct();

            if (matStruct)
            {
                m_color = glm::vec4(matStruct->color.red / 255.0f, matStruct->color.green / 255.0f, matStruct->color.blue / 255.0f, matStruct->color.alpha / 255.0f);
                m_ambient = matStruct->surfaceProps.ambient;
                m_diffuse = matStruct->surfaceProps.diffuse;
                m_specular = matStruct->surfaceProps.specular;
            }
        }

        void Material::bind()
        {
            m_context->glPushAttrib(GL_LIGHTING_BIT);

            if (m_useColorMaterial)
            {
                m_context->glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
                m_context->glEnable(GL_COLOR_MATERIAL);
            }
            else
            {
                m_context->glDisable(GL_COLOR_MATERIAL);

                float ambient[4] = { m_ambient * m_color[0], m_ambient * m_color[1], m_ambient * m_color[2], m_ambient * m_color[3] };
                float diffuse[4] = { m_diffuse * m_color[0], m_diffuse * m_color[1], m_diffuse * m_color[2], m_diffuse * m_color[3] };

                m_context->glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
                m_context->glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
            }

            float specular[4] = { 0, 0, 0, 0 }; // RW doesn't actually support specular

            m_context->glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

            if (m_texture)
            {
                m_texture->bind();
            }
        }

        void Material::unbind()
        {
            if (m_texture)
            {
                m_texture->unbind();
            }

            m_context->glPopAttrib();
        }

    }

}
