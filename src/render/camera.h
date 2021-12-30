#pragma once

#include <glm/glm.hpp>

#include <QObject>

namespace Slick {

    namespace Render {

        class Context;

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

        class Camera
        {
        public:
            Camera(Context* context);

            void begin();
            void end();

            bool begun() const { return m_begun; }

            Context* context() const { return m_context; }

            Projection projection() const { return m_proj; }
            void setProjection(const Projection& projection);

            glm::mat4 projectionMatrix() const { return m_projMatrix; }

            glm::mat4 viewMatrix() const { return m_viewMatrix; }
            void setViewMatrix(const glm::mat4& mat);

        private:
            Context* m_context;
            Projection m_proj;
            glm::mat4 m_projMatrix;
            glm::mat4 m_viewMatrix;
            bool m_begun;

            void calcProjMatrix();
        };

    }

}
