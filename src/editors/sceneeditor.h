#pragma once

#include "core/editor.h"
#include "core/scene.h"

#include "hiphop.h"

namespace Slick {

    namespace Editors {

        class SceneEditorWidget;

        class SceneEditor : public Core::Editor
        {
            Q_OBJECT

        public:
            SceneEditor(QObject* parent = nullptr);

            virtual Core::EditorWidget* createWidget() override;
            virtual OpenResult open() override;
            virtual SaveResult save(bool saveAs) override;
            virtual void enter() override;
            virtual void exit() override;

            Core::Scene* scene() const { return m_scene; }

        private:
            Core::Scene* m_scene;
        };

    }

}
