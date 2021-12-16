#pragma once

#include "Core/RenderContext.h"

#include <glm/glm.hpp>

#include <QObject>

namespace Slick {

    struct Projection
    {
        enum Type
        {
            Perspective,
            Ortho
        };

        Type type;
        float nearClip;
        float farClip;

        union
        {
            struct
            {
                float aspect;
                float fov;
            };

            struct
            {
                float left;
                float right;
                float bottom;
                float top;
            };
        };
    };

    class Camera : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(RenderContext* context READ context)
        Q_PROPERTY(Projection projection READ projection WRITE setProjection)
        Q_PROPERTY(glm::mat4 projectionMatrix READ projectionMatrix)
        Q_PROPERTY(glm::mat4 viewMatrix READ viewMatrix WRITE setViewMatrix)

    public:
        Camera(RenderContext* context);

        void begin();
        void end();

        bool begun() const { return m_begun; }

        RenderContext* context() const { return m_context; }

        Projection projection() const { return m_proj; }
        void setProjection(const Projection& projection);

        glm::mat4 projectionMatrix() const { return m_projMatrix; }

        glm::mat4 viewMatrix() const { return m_viewMatrix; }
        void setViewMatrix(const glm::mat4& mat);

    private:
        RenderContext* m_context;
        Projection m_proj;
        glm::mat4 m_projMatrix;
        glm::mat4 m_viewMatrix;
        bool m_begun;

        void calcProjMatrix();
    };

}
