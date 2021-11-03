#pragma once

#include <QDialog>

class QCheckBox;
class QLineEdit;
class QPushButton;
class QComboBox;

namespace Slick {

    class OpenSceneDialog : public QDialog
    {
        Q_OBJECT

    public:
        OpenSceneDialog(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    private:
        QCheckBox* m_hipCheckBox;
        QCheckBox* m_hopCheckBox;
        QLineEdit* m_hipPathLineEdit;
        QLineEdit* m_hopPathLineEdit;
        QPushButton* m_hipBrowseButton;
        QPushButton* m_hopBrowseButton;
        QComboBox* m_gameComboBox;
        QComboBox* m_platformComboBox;
        QComboBox* m_languageComboBox;
        QComboBox* m_regionComboBox;
        QPushButton* m_okButton;
        QPushButton* m_cancelButton;

    private slots:
        void updateWidgets();
        void getHipHopFilename();
    };

}
