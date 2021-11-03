#pragma once

#include "Editors/IEditor.h"
#include "Editors/EditorTypes.h"

#include "hiphop.h"

namespace Slick {

    class SceneEditorWidget;

    class SceneEditor : public IEditor
    {
        Q_OBJECT

    public:
        SceneEditor(QObject* parent = nullptr);

        virtual int type() const override { return EditorType_Scene; }
        virtual IEditorWidget* createWidget() override;
        virtual SaveResult save() override;
        virtual SaveResult saveAs() override;
        virtual OpenResult open() override;

    private:
        SceneEditorWidget* m_widget;
    };

    class SceneEditorWidget : public IEditorWidget
    {
        Q_OBJECT

    public:
        SceneEditorWidget(SceneEditor* editor, QWidget* parent = nullptr);

    private:
        SceneEditor* m_editor;
    };

}
