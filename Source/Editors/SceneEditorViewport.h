#pragma once

#include "Core/Viewport.h"
#include "Core/Scene.h"

namespace Slick {

    class SceneEditorViewport : public Viewport
    {
        Q_OBJECT

    public:
        SceneEditorViewport(RenderContext* context, QWindow* parent = nullptr);

        Scene* scene() const { return m_scene; }
        void setScene(Scene* scene);

    signals:
        void doneRendering();

    protected:
        virtual void update() override;
        virtual void render() override;

    private:
        Scene* m_scene;
    };

}
