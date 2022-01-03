#pragma once

#include <glm/glm.hpp>

namespace Slick {

    namespace Render {

        class Context;

        class Frame
        {
        public:
            Frame(Context* context);

            Frame* parent() const { return m_parent; }
            void setParent(Frame* parent) { m_parent = parent; }

            glm::mat4 matrix() const { return m_mat; }
            void setMatrix(const glm::mat4& mat) { m_mat = mat; }

            void bind();
            void unbind();

        private:
            Context* m_context;
            Frame* m_parent;
            glm::mat4 m_mat;
        };

    }

}
