#pragma once

#include "Render/Viewport.h"
#include "Core/Scene.h"

namespace Slick {

    class SceneEditorViewport : public Render::Viewport
    {
        Q_OBJECT

    public:
        SceneEditorViewport(QWindow* parent = nullptr);

        Scene* scene() const { return m_scene; }
        void setScene(Scene* scene);

    protected:
        virtual void update(float dt) override;
        virtual void render(Render::Context& context) override;

    private:
        Scene* m_scene;
    };

}
