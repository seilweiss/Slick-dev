#pragma once

#include "Core/EditorWidget.h"

#include "hiphop.h"

class QComboBox;
class QLineEdit;
class QTableWidget;

namespace Slick {

    class HipHopEditorWidget : public EditorWidget
    {
        Q_OBJECT

    public:
        HipHopEditorWidget(QWidget* parent = nullptr);

        void loadFile(HipHop::File* file);

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
