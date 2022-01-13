#pragma once

#include "hiphop/assets/pipe_info_table_asset.h"

#include <glm/glm.hpp>

namespace Slick {

    namespace Assets { class LightKitAsset; }
    namespace Render { class Atomic; }

    namespace Core {

        class Scene;

        class ModelInstance
        {
        public:
            ModelInstance(Scene* scene);

            Scene* scene() const { return m_scene; }

            ModelInstance* next() const { return m_next; }
            void setNext(ModelInstance* next) { m_next = next; }

            Render::Atomic* data() const { return m_data; }
            void setData(Render::Atomic* data) { m_data = data; }

            Assets::LightKitAsset* lightKit() const { return m_lightKit; }
            void setLightKit(Assets::LightKitAsset* lightKit) { m_lightKit = lightKit; }

            glm::mat4 matrix() const { return m_mat; }
            void setMatrix(const glm::mat4& mat) { m_mat = mat; }

            glm::vec4 color() const { return m_color; }
            void setColor(const glm::vec4& color) { m_color = color; }

            bool visible() const { return m_visible; }
            void setVisible(bool visible) { m_visible = visible; }

            HipHop::PipeInfo* pipeInfo() const { return m_pipeInfo; }
            void setPipeInfo(HipHop::PipeInfo* pipeInfo) { m_pipeInfo = pipeInfo; }

            void render();
            void renderSingle();

        private:
            Scene* m_scene;
            ModelInstance* m_next;
            Render::Atomic* m_data;
            Assets::LightKitAsset* m_lightKit;
            glm::mat4 m_mat;
            glm::vec4 m_color;
            bool m_visible;
            HipHop::PipeInfo* m_pipeInfo;
        };

    }

}
