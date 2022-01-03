#pragma once

#include "render/texture.h"

#include <glm/glm.hpp>

namespace Rws { class Material; }

namespace Slick {

    namespace Render {

        class Context;

        class Material
        {
        public:
            Material(Context* context, Rws::Material* data = nullptr);

            Rws::Material* data() const { return m_data; }
            void setData(Rws::Material* data);

            Texture* texture() const { return m_texture; }
            void setTexture(Texture* texture) { m_texture = texture; }

            glm::vec4 color() const { return m_color; }
            void setColor(const glm::vec4& color) { m_color = color; }

            float ambient() const { return m_ambient; }
            void setAmbient(float ambient) { m_ambient = ambient; }

            float diffuse() const { return m_diffuse; }
            void setDiffuse(float diffuse) { m_diffuse = diffuse; }

            float specular() const { return m_specular; }
            void setSpecular(float specular) { m_specular = specular; }

            void bind();
            void unbind();

        private:
            Context* m_context;
            Rws::Material* m_data;
            Texture* m_texture;
            glm::vec4 m_color;
            float m_ambient;
            float m_diffuse;
            float m_specular;
        };

    }

}
