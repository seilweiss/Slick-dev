#pragma once

#include "core/editorwidget.h"
#include "core/scene.h"

class QLabel;
class QComboBox;

namespace Slick {

    namespace Render { class Camera; }

    namespace Editors {

        class SceneEditorViewport;

        class SceneEditorWidget : public Core::EditorWidget
        {
            Q_OBJECT

        public:
            SceneEditorWidget(QWidget* parent = nullptr);

            void setScene(Core::Scene* scene);

            SceneEditorViewport* viewport() const { return m_viewport; }

        private:
            Core::Scene* m_scene;
            SceneEditorViewport* m_viewport;
            QLabel* m_statsLabel;
            QComboBox* m_previewCamComboBox;
            bool m_previewCamChangedByMe;

            void updateStats();
            void refreshPreviewCam();
        };

    }

}
