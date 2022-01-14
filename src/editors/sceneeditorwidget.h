#pragma once

#include "core/editorwidget.h"
#include "core/scene.h"

class QLabel;
class QCheckBox;
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
            QCheckBox* m_letterBoxCheckBox;
            QComboBox* m_aspectRatioComboBox;
            QComboBox* m_previewCamComboBox;
            bool m_previewCamChangedByMe;

            void refreshPreviewCam();
        };

    }

}
