#pragma once

#include "Editors/IEditor.h"
#include "Editors/EditorTypes.h"

#include "hiphop.h"

class QComboBox;
class QLineEdit;
class QTableWidget;

namespace Slick {

    class HipHopEditorWidget;

    class HipHopEditor : public IEditor
    {
        Q_OBJECT
        Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
        Q_PROPERTY(HipHop::File file READ file)

    public:
        HipHopEditor(QObject* parent = nullptr);

        virtual int type() const override { return EditorType_HipHop; }
        virtual IEditorWidget* createWidget() override;
        virtual SaveResult save() override;
        virtual SaveResult saveAs() override;
        virtual OpenResult open() override;

        QString path() const { return m_path; }
        void setPath(const QString& path) { m_path = path; emit pathChanged(path); }

        HipHop::File& file() { return m_file; }

        static QString filter();
        static QString getOpenFileName();
        static QString getSaveFileName(HipHopEditor* editor = nullptr);

    signals:
        void pathChanged(const QString& path);

    private:
        QString m_path;
        HipHop::File m_file;
        HipHop::FileStream m_stream;
        HipHopEditorWidget* m_widget;
    };

    class HipHopEditorWidget : public IEditorWidget
    {
        Q_OBJECT

    public:
        HipHopEditorWidget(HipHopEditor* editor, QWidget* parent = nullptr);

        void load();

    private:
        HipHopEditor* m_editor;
        QComboBox* m_layerComboBox;
        QComboBox* m_layerTypeComboBox;
        QComboBox* m_assetTypeComboBox;
        QLineEdit* m_assetSearchLineEdit;
        QTableWidget* m_assetTableWidget;

        void resetTable();
        void refresh();
    };

}
