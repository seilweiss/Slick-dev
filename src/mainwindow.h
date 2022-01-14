#pragma once

#include "core/asset.h"

#include <QMainWindow>

namespace Slick {

    namespace Core { class Editor; }

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        static MainWindow* instance()
        {
            static MainWindow* theInstance = new MainWindow;
            return theInstance;
        }

        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    public slots:
        bool newProject();
        bool newScene();
        bool newHipHopFile();
        bool newTextFile();
        bool openProject();
        bool openScene();
        bool openHipHopFile();
        bool openTextFile();
        bool closeEditor();
        bool closeAll();
        bool closeProject();
        bool save();
        bool saveAs();
        bool saveAll();
        bool saveProject();
        bool saveProjectAs();
        void undo();
        void redo();
        void toggleProjectVisible();
        void toggleSceneVisible();
        void toggleInspectorVisible();
        void toggleToolbarVisible();
        void toggleDebugVisible();
        void toggleExpandEditor();
        bool playScene();
        bool stopScene();
        void manageEmulators();
        bool newScript();
        bool openScript();
        bool runScript();
        void hashGenerator();
        void hashLookup();
        void options();
        void viewManual();
        void viewWiki();
        void aboutSlick();
        void aboutQt();

    protected:
        void closeEvent(QCloseEvent* event);

    private:
        void setupActions();
        void setupMenus();
        void setupPanels();
        void setupLayout();
        void updateMenus();
        void updatePanels();

    private slots:
        void onPanelDockVisibilityChanged();
        void onAssetsSelected(const QList<Core::Asset*>& assets);

    private:
        QDockWidget* m_projectDock;
        QDockWidget* m_sceneDock;
        QDockWidget* m_inspectorDock;
        QDockWidget* m_toolbarDock;
        QDockWidget* m_debugDock;
        QAction* m_newProjectAction;
        QAction* m_newSceneAction;
        QAction* m_newHipHopFileAction;
        QAction* m_newTextFileAction;
        QAction* m_openProjectAction;
        QAction* m_openSceneAction;
        QAction* m_openHipHopFileAction;
        QAction* m_openTextFileAction;
        QAction* m_closeEditorAction;
        QAction* m_closeAllAction;
        QAction* m_closeProjectAction;
        QAction* m_saveAction;
        QAction* m_saveAsAction;
        QAction* m_saveAllAction;
        QAction* m_saveProjectAction;
        QAction* m_saveProjectAsAction;
        QAction* m_quitAction;
        QAction* m_undoAction;
        QAction* m_redoAction;
        QAction* m_toggleProjectVisibleAction;
        QAction* m_toggleSceneVisibleAction;
        QAction* m_toggleInspectorVisibleAction;
        QAction* m_toggleToolbarVisibleAction;
        QAction* m_toggleDebugVisibleAction;
        QAction* m_toggleExpandEditorAction;
        QAction* m_playSceneAction;
        QAction* m_stopSceneAction;
        QMenu* m_emulatorMenu;
        QAction* m_manageEmulatorsAction;
        QAction* m_newScriptAction;
        QAction* m_openScriptAction;
        QAction* m_runScriptAction;
        QAction* m_hashGeneratorAction;
        QAction* m_hashLookupAction;
        QAction* m_optionsAction;
        QAction* m_viewManualAction;
        QAction* m_viewWikiAction;
        QAction* m_aboutSlickAction;
        QAction* m_aboutQtAction;
        QMenu* m_fileMenu;
        QMenu* m_editMenu;
        QMenu* m_viewMenu;
        QMenu* m_playMenu;
        QMenu* m_scriptsMenu;
        QMenu* m_toolsMenu;
        QMenu* m_helpMenu;
        Core::Editor* m_prevEditor;
        bool m_projectVisible;
        bool m_sceneVisible;
        bool m_inspectorVisible;
        bool m_toolbarVisible;
        bool m_debugVisible;
        bool m_editorExpanded;
        bool m_updatingPanels;
    };

}
