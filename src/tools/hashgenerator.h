#pragma once

#include <QDialog>

class QLineEdit;

namespace Slick {

    namespace Tools {

        class HashGenerator : public QDialog
        {
            Q_OBJECT

        public:
            static HashGenerator* instance(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())
            {
                static HashGenerator* theInstance = new HashGenerator(parent, f);
                return theInstance;
            }

        private:
            HashGenerator(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

            QLineEdit* m_textLineEdit;
            QLineEdit* m_hashLineEdit;
            QPushButton* m_addToLookupTableButton;

        private slots:
            void textChanged(const QString& text);
        };

    }

}
