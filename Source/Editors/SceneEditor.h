#pragma once

#include "Core/Editor.h"
#include "Core/Scene.h"

#include "hiphop.h"

namespace Slick {

    class SceneEditorWidget;

    class SceneEditor : public Editor
    {
        Q_OBJECT

    public:
        SceneEditor(QObject* parent = nullptr);

        virtual EditorWidget* createWidget() override;
        virtual OpenResult open() override;
        virtual SaveResult save(bool saveAs) override;
        virtual void enter() override;
        virtual void exit() override;

        Scene* scene() const { return m_scene; }

    private:
        Scene* m_scene;
    };

}
