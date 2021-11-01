#pragma once

#include <QDialog>

class QLineEdit;

namespace Slick {

    class HashGeneratorTool : public QDialog
    {
        Q_OBJECT

    public:
        static HashGeneratorTool* instance(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())
        {
            static HashGeneratorTool* theInstance = new HashGeneratorTool(parent, f);
            return theInstance;
        }

    private:
        HashGeneratorTool(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        QLineEdit* m_textLineEdit;
        QLineEdit* m_hashLineEdit;
        QPushButton* m_addToLookupTableButton;

    private slots:
        void textChanged(const QString& text);
    };

}
