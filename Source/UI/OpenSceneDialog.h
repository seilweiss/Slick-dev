#pragma once

#include <QDialog>

#include "hiphop.h"

class QHBoxLayout;
class QVBoxLayout;
class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QComboBox;
class QTableWidget;
class QTableWidgetItem;

namespace Slick {

    class OpenSceneDialog : public QDialog
    {
        Q_OBJECT

    public:
        OpenSceneDialog(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        QString hipPath() const;
        QString hopPath() const;
        QStringList locHipPaths() const;
        HipHop::Game game() const;
        HipHop::Platform platform() const;
        HipHop::Language language() const;
        HipHop::Region region() const;
        QString sceneName() const { return m_sceneName; }

        void accept() override;

    private:
        struct HipHopGroup
        {
            QHBoxLayout* layout;
            QCheckBox* checkBox;
            QLabel* label;
            QLineEdit* lineEdit;
            QPushButton* browseButton;
            bool valid;

            HipHopGroup(OpenSceneDialog* dialog, const QString& text);

            void update();
            void setPath(const QString& path);
        };

        struct InfoGroup
        {
            QHBoxLayout* layout;
            QLabel* label;
            QComboBox* comboBox;
            bool valid;

            InfoGroup(OpenSceneDialog* dialog, const QString& text);

            void update();
        };

        struct LocGroup
        {
            struct Item
            {
                QTableWidgetItem* pathItem;
                QPushButton* browseButton;
            };

            OpenSceneDialog* dialog;
            QVBoxLayout* layout;
            QLabel* label;
            QTableWidget* tableWidget;
            QPushButton* addButton;
            QPushButton* removeButton;
            bool valid;

            LocGroup(OpenSceneDialog* dialog, const QString& text);

            void update();
            void addPath(const QString& path);
            void setPaths(const QStringList& paths);
            Item createItem(const QString& path);
        };

        HipHopGroup m_hip;
        HipHopGroup m_hop;
        LocGroup m_loc;
        InfoGroup m_game;
        InfoGroup m_platform;
        InfoGroup m_language;
        InfoGroup m_region;
        QString m_sceneName;
        QPushButton* m_okButton;
        QPushButton* m_cancelButton;
        bool m_dontUpdateWidgets;

        void addGame(HipHop::Game game);
        void addPlatform(HipHop::Platform platform);
        void addLanguage(HipHop::Language language);
        void addRegion(HipHop::Region region);

    private slots:
        void updateWidgets();
        void browse();
    };

}
