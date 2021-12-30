#pragma once

#include "core/editorwidget.h"

#include "hiphop.h"

class QComboBox;
class QLineEdit;
class QTableWidget;

namespace Slick {

    namespace Editors {

        class HipHopEditorWidget : public Core::EditorWidget
        {
            Q_OBJECT

        public:
            HipHopEditorWidget(QWidget* parent = nullptr);

            void setFile(HipHop::File* file);

        private:
            HipHop::File* m_file;
            QComboBox* m_layerComboBox;
            QComboBox* m_layerTypeComboBox;
            QComboBox* m_assetTypeComboBox;
            QLineEdit* m_assetSearchLineEdit;
            QTableWidget* m_assetTableWidget;

            void resetTable();
            void refresh();
        };

    }

}
