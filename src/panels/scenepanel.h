#pragma once

#include "core/scene.h"

#include <QWidget>

class QTabWidget;
class QPushButton;
class QLineEdit;
class QComboBox;
class QTableWidget;

namespace Slick {

    namespace Panels {

        class ScenePanel : public QWidget
        {
            Q_OBJECT
            Q_PROPERTY(Core::Scene* scene READ scene WRITE setScene NOTIFY sceneChanged)

        public:
            static ScenePanel* instance()
            {
                static ScenePanel* theInstance = new ScenePanel;
                return theInstance;
            }

            Core::Scene* scene() const;
            void setScene(Core::Scene* scene);

            QList<Core::Asset*> selectedAssets() const;

        signals:
            void sceneChanged(Core::Scene* scene);
            void assetsSelected(const QList<Core::Asset*>& assets);

        private:
            ScenePanel(QWidget* parent = nullptr);
        };

        namespace ScenePanelPrivate {

            class SceneWidget : public QWidget
            {
                Q_OBJECT
                Q_PROPERTY(Core::Scene* scene READ scene WRITE setScene)

            public:
                SceneWidget(QWidget* parent = nullptr);

                Core::Scene* scene() const { return m_scene; }
                void setScene(Core::Scene* scene);

                QList<Core::Asset*> selectedAssets() const;

            signals:
                void assetsSelected(const QList<Core::Asset*>& assets);

            private:
                Core::Scene* m_scene;
                QTabWidget* m_fileTabWidget;
            };

            class SceneFileWidget : public QWidget
            {
                Q_OBJECT
                Q_PROPERTY(Core::SceneFile* file READ file WRITE setFile)

            public:
                SceneFileWidget(QWidget* parent = nullptr);

                Core::SceneFile* file() const { return m_file; }
                void setFile(Core::SceneFile* file);

                QList<Core::Asset*> selectedAssets() const { return m_selectedAssets; }

            signals:
                void assetsSelected(const QList<Core::Asset*>& assets);

            private:
                Core::SceneFile* m_file;
                QPushButton* m_createAssetButton;
                QLineEdit* m_filterAssetsLineEdit;
                QComboBox* m_filterTypesComboBox;
                QTableWidget* m_assetsTableWidget;
                QList<Core::Asset*> m_selectedAssets;

            private slots:
                void updateFilter();
                void onItemSelectionChanged();
            };

        }

    }

}
