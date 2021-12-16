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

        QVector<Asset*> selectedAssets() const;

    signals:
        void sceneChanged(Scene* scene);
        void assetsSelected(const QVector<Asset*>& assets);

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

            QVector<Asset*> selectedAssets() const;

        signals:
            void assetsSelected(const QVector<Asset*>& assets);

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

            QVector<Asset*> selectedAssets() const { return m_selectedAssets; }

        signals:
            void assetsSelected(const QVector<Asset*>& assets);

        private:
            SceneFile* m_file;
            QPushButton* m_createAssetButton;
            QLineEdit* m_filterAssetsLineEdit;
            QComboBox* m_filterTypesComboBox;
            QTableWidget* m_assetsTableWidget;
            QVector<Asset*> m_selectedAssets;

        private slots:
            void updateFilter();
            void onItemSelectionChanged();
        };

    }

}
