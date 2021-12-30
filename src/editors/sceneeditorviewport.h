#pragma once

#include "render/viewport.h"
#include "core/scene.h"

namespace Slick {

    namespace Editors {

        class SceneEditorViewport : public Render::Viewport
        {
            Q_OBJECT

        public:
            SceneEditorViewport(QWindow* parent = nullptr);

            Core::Scene* scene() const { return m_scene; }
            void setScene(Core::Scene* scene);

        signals:
            void doneRendering();

        protected:
            virtual void update() override;
            virtual void render() override;

        private:
            Core::Scene* m_scene;
        };

    }

}
