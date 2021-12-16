#pragma once

#include "Core/RenderContext.h"

#include <glm/glm.hpp>

namespace Slick {

    class Frame
    {
    public:
        Frame();

        Frame* parent() const { return m_parent; }
        void setParent(Frame* parent) { m_parent = parent; }

        glm::mat4 matrix() const { return m_mat; }
        void setMatrix(const glm::mat4& mat) { m_mat = mat; }

        void bind(RenderContext* context);
        void unbind(RenderContext* context);

    private:
        Frame* m_parent;
        glm::mat4 m_mat;
    };

}
