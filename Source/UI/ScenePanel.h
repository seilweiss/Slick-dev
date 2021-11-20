#pragma once

#include "Core/Scene.h"

#include <QWidget>

class QTabWidget;
class QPushButton;
class QLineEdit;
class QComboBox;
class QTableWidget;

namespace Slick {

    class ScenePanel : public QWidget
    {
        Q_OBJECT
        Q_PROPERTY(Scene* scene READ scene WRITE setScene NOTIFY sceneChanged)

    public:
        static ScenePanel* instance()
        {
            static ScenePanel* theInstance = new ScenePanel;
            return theInstance;
        }

        Scene* scene() const;
        void setScene(Scene* scene);

    signals:
        void sceneChanged(Scene* scene);

    private:
        ScenePanel(QWidget* parent = nullptr);
    };

    namespace ScenePanelPrivate {

        class SceneWidget : public QWidget
        {
            Q_OBJECT
            Q_PROPERTY(Scene* scene READ scene WRITE setScene)

        public:
            SceneWidget(QWidget* parent = nullptr);

            Scene* scene() const { return m_scene; }
            void setScene(Scene* scene);

        private:
            Scene* m_scene;
            QTabWidget* m_fileTabWidget;
        };

        class SceneFileWidget : public QWidget
        {
            Q_OBJECT
            Q_PROPERTY(SceneFile* file READ file WRITE setFile)

        public:
            SceneFileWidget(QWidget* parent = nullptr);

            SceneFile* file() const { return m_file; }
            void setFile(SceneFile* file);

        private:
            SceneFile* m_file;
            QPushButton* m_createAssetButton;
            QLineEdit* m_filterAssetsLineEdit;
            QComboBox* m_filterTypesComboBox;
            QTableWidget* m_assetsTableWidget;

        private slots:
            void updateFilter();
        };

    }

}
