#include "mainwindow.h"

#include "panels/toolbarpanel.h"
#include "panels/editorpanel.h"
#include "panels/projectpanel.h"
#include "panels/scenepanel.h"
#include "panels/inspectorpanel.h"
#include "panels/debugpanel.h"

#include "editors/texteditor.h"
#include "editors/hiphopeditor.h"
#include "editors/sceneeditor.h"

#include "tools/hashgenerator.h"

#include <QApplication>
#include <QScreen>
#include <QDockWidget>
#include <QMenuBar>
#include <QMessageBox>
#include <QCloseEvent>

namespace Slick {

    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          m_projectDock(new QDockWidget(tr("Project"))),
          m_sceneDock(new QDockWidget(tr("Scene"))),
          m_inspectorDock(new QDockWidget(tr("Inspector"))),
          m_toolbarDock(new QDockWidget(tr("Toolbar"))),
          m_debugDock(new QDockWidget(tr("Debug"))),
          m_newProjectAction(new QAction(tr("Project..."), this)),
          m_newSceneAction(new QAction(tr("Scene..."), this)),
          m_newHipHopFileAction(new QAction(tr("HIP/HOP File"), this)),
          m_newTextFileAction(new QAction(tr("Text File"), this)),
          m_openProjectAction(new QAction(tr("Project..."), this)),
          m_openSceneAction(new QAction(tr("Scene..."), this)),
          m_openHipHopFileAction(new QAction(tr("HIP/HOP File..."), this)),
          m_openTextFileAction(new QAction(tr("Text File..."), this)),
          m_closeEditorAction(new QAction(tr("Close"), this)),
          m_closeAllAction(new QAction(tr("Close All"), this)),
          m_closeProjectAction(new QAction(tr("Close Project"), this)),
          m_saveAction(new QAction(tr("Save"), this)),
          m_saveAsAction(new QAction(tr("Save As..."), this)),
          m_saveAllAction(new QAction(tr("Save All"), this)),
          m_saveProjectAction(new QAction(tr("Save Project"), this)),
          m_saveProjectAsAction(new QAction(tr("Save Project As..."), this)),
          m_quitAction(new QAction(tr("Quit"), this)),
          m_undoAction(new QAction(tr("Undo"), this)),
          m_redoAction(new QAction(tr("Redo"), this)),
          m_toggleProjectVisibleAction(new QAction(tr("Project"), this)),
          m_toggleSceneVisibleAction(new QAction(tr("Scene"), this)),
          m_toggleInspectorVisibleAction(new QAction(tr("Inspector"), this)),
          m_toggleToolbarVisibleAction(new QAction(tr("Toolbar"), this)),
          m_toggleDebugVisibleAction(new QAction(tr("Debug"), this)),
          m_toggleExpandEditorAction(new QAction(tr("Expand Editor"), this)),
          m_playSceneAction(new QAction(tr("Play Scene"), this)),
          m_stopSceneAction(new QAction(tr("Stop Scene"), this)),
          m_emulatorMenu(new QMenu(tr("Emulator"))),
          m_manageEmulatorsAction(new QAction(tr("Manage Emulators..."), this)),
          m_newScriptAction(new QAction(tr("New Script"), this)),
          m_openScriptAction(new QAction(tr("Open Script..."), this)),
          m_runScriptAction(new QAction(tr("Run Script"), this)),
          m_hashGeneratorAction(new QAction(tr("Hash Generator..."), this)),
          m_hashLookupAction(new QAction(tr("Hash Lookup..."), this)),
          m_optionsAction(new QAction(tr("Options..."), this)),
          m_viewManualAction(new QAction(tr("Manual"), this)),
          m_viewWikiAction(new QAction(tr("Wiki"), this)),
          m_aboutSlickAction(new QAction(tr("About Slick..."), this)),
          m_aboutQtAction(new QAction(tr("About Qt..."), this)),
          m_fileMenu(menuBar()->addMenu(tr("File"))),
          m_editMenu(menuBar()->addMenu(tr("Edit"))),
          m_viewMenu(menuBar()->addMenu(tr("View"))),
          m_playMenu(menuBar()->addMenu(tr("Play"))),
          m_scriptsMenu(menuBar()->addMenu(tr("Scripts"))),
          m_toolsMenu(menuBar()->addMenu(tr("Tools"))),
          m_helpMenu(menuBar()->addMenu(tr("Help"))),
          m_prevEditor(nullptr),
          m_projectVisible(true),
          m_sceneVisible(true),
          m_inspectorVisible(true),
          m_toolbarVisible(true),
          m_debugVisible(false),
          m_editorExpanded(false),
          m_updatingPanels(false)
    {
        resize(screen()->availableSize() * 0.75);

        setupLayout();
        setupActions();
        setupMenus();
        setupPanels();

        updatePanels();
        updateMenus();
    }

    MainWindow::~MainWindow()
    {
    }

    bool MainWindow::newProject()
    {
        return true;
    }

    bool MainWindow::newScene()
    {
        Panels::EditorPanel::instance()->addEditor(new Editors::SceneEditor);

        return true;
    }

    bool MainWindow::newHipHopFile()
    {
        Panels::EditorPanel::instance()->addEditor(new Editors::HipHopEditor);

        return true;
    }

    bool MainWindow::newTextFile()
    {
        Panels::EditorPanel::instance()->addEditor(new Editors::TextEditor);

        return true;
    }

    bool MainWindow::openProject()
    {
        return true;
    }

    bool MainWindow::openScene()
    {
        Editors::SceneEditor* editor = new Editors::SceneEditor;

        if (!Panels::EditorPanel::instance()->openEditor(editor))
        {
            delete editor;
            return false;
        }

        return true;
    }

    bool MainWindow::openHipHopFile()
    {
        Editors::HipHopEditor* editor = new Editors::HipHopEditor;

        if (!Panels::EditorPanel::instance()->openEditor(editor))
        {
            delete editor;
            return false;
        }

        return true;
    }

    bool MainWindow::openTextFile()
    {
        Editors::TextEditor* editor = new Editors::TextEditor;

        if (!Panels::EditorPanel::instance()->openEditor(editor))
        {
            delete editor;
            return false;
        }

        return true;
    }

    bool MainWindow::closeEditor()
    {
        return Panels::EditorPanel::instance()->closeEditor();
    }

    bool MainWindow::closeAll()
    {
        return Panels::EditorPanel::instance()->closeAll();
    }

    bool MainWindow::closeProject()
    {
        return true;
    }

    bool MainWindow::save()
    {
        bool success = Panels::EditorPanel::instance()->saveEditor();

        if (success)
        {
            updateMenus();
        }

        return success;
    }

    bool MainWindow::saveAs()
    {
        bool success = Panels::EditorPanel::instance()->saveEditorAs();

        if (success)
        {
            updateMenus();
        }

        return success;
    }

    bool MainWindow::saveAll()
    {
        bool success = Panels::EditorPanel::instance()->saveAll();

        if (success)
        {
            updateMenus();
        }

        return success;
    }

    bool MainWindow::saveProject()
    {
        return true;
    }

    bool MainWindow::saveProjectAs()
    {
        return true;
    }

    void MainWindow::undo()
    {

    }

    void MainWindow::redo()
    {

    }

    void MainWindow::toggleProjectVisible()
    {
        m_projectVisible = !m_projectVisible;
        updatePanels();
    }

    void MainWindow::toggleSceneVisible()
    {
        m_sceneVisible = !m_sceneVisible;
        updatePanels();
    }

    void MainWindow::toggleInspectorVisible()
    {
        m_inspectorVisible = !m_inspectorVisible;
        updatePanels();
    }

    void MainWindow::toggleToolbarVisible()
    {
        m_toolbarVisible = !m_toolbarVisible;
        updatePanels();
    }

    void MainWindow::toggleDebugVisible()
    {
        m_debugVisible = !m_debugVisible;
        updatePanels();
    }

    void MainWindow::toggleExpandEditor()
    {
        m_editorExpanded = !m_editorExpanded;
        updatePanels();
    }

    bool MainWindow::playScene()
    {
        return true;
    }

    bool MainWindow::stopScene()
    {
        return true;
    }

    void MainWindow::manageEmulators()
    {

    }

    bool MainWindow::newScript()
    {
        return true;
    }

    bool MainWindow::openScript()
    {
        return true;
    }

    bool MainWindow::runScript()
    {
        return true;
    }

    void MainWindow::hashGenerator()
    {
        Tools::HashGenerator* tool = Tools::HashGenerator::instance(this);
        tool->show();
        tool->raise();
        tool->activateWindow();
    }

    void MainWindow::hashLookup()
    {

    }

    void MainWindow::options()
    {

    }

    void MainWindow::viewManual()
    {

    }

    void MainWindow::viewWiki()
    {

    }

    void MainWindow::aboutSlick()
    {
        QMessageBox messageBox;
        messageBox.setWindowTitle(tr("About Slick"));
        messageBox.setIconPixmap(QPixmap(":/images/slick-compact.svg").scaledToWidth(150, Qt::SmoothTransformation));
        messageBox.setTextFormat(Qt::RichText);
        messageBox.setText("<b style=\"font-size: 25px\">Slick</b><br>" SLICK_VERSION);
        messageBox.setInformativeText(tr("Copyright (C) 2022 Seil Weiss<br><br>"
                                         "Source code: <a href=https://github.com/seilweiss/Slick-dev>github.com/seilweiss/Slick-dev</a><br><br>"
                                         "Logo design by Joey Ballentine: <a href=https://github.com/JoeyBallentine>github.com/JoeyBallentine</a><br>"
                                         "Icons by Font Awesome: <a href=https://fontawesome.com>fontawesome.com</a><br><br>"
                                         "Heavy Iron Modding Wiki: <a href=https://heavyironmodding.org>heavyironmodding.org</a><br>"
                                         "Heavy Iron Modding Discord: <a href=https://discord.gg/9eAE6UB>discord.gg/9eAE6UB</a>"));
        messageBox.setStandardButtons(QMessageBox::Ok);
        messageBox.setDefaultButton(QMessageBox::Ok);
        messageBox.exec();
    }

    void MainWindow::aboutQt()
    {
        QMessageBox::aboutQt(this);
    }

    void MainWindow::closeEvent(QCloseEvent* event)
    {
        if (closeAll())
        {
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }

    void MainWindow::setupActions()
    {
        m_newProjectAction->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_N);
        m_newSceneAction->setShortcut(Qt::CTRL | Qt::Key_N);
        m_openProjectAction->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_O);
        m_openSceneAction->setShortcut(Qt::CTRL | Qt::Key_O);
        m_saveAction->setShortcut(Qt::CTRL | Qt::Key_S);
        m_saveAllAction->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_S);
        m_quitAction->setShortcuts(QKeySequence::Quit);
        m_undoAction->setShortcuts(QKeySequence::Undo);
        m_redoAction->setShortcuts(QKeySequence::Redo);
        m_viewManualAction->setShortcuts(QKeySequence::HelpContents);

        m_toggleProjectVisibleAction->setCheckable(true);
        m_toggleSceneVisibleAction->setCheckable(true);
        m_toggleInspectorVisibleAction->setCheckable(true);
        m_toggleToolbarVisibleAction->setCheckable(true);
        m_toggleDebugVisibleAction->setCheckable(true);
        m_toggleExpandEditorAction->setCheckable(true);

        connect(m_newProjectAction, &QAction::triggered, this, &MainWindow::newProject);
        connect(m_newSceneAction, &QAction::triggered, this, &MainWindow::newScene);
        connect(m_newHipHopFileAction, &QAction::triggered, this, &MainWindow::newHipHopFile);
        connect(m_newTextFileAction, &QAction::triggered, this, &MainWindow::newTextFile);
        connect(m_openProjectAction, &QAction::triggered, this, &MainWindow::openProject);
        connect(m_openSceneAction, &QAction::triggered, this, &MainWindow::openScene);
        connect(m_openHipHopFileAction, &QAction::triggered, this, &MainWindow::openHipHopFile);
        connect(m_openTextFileAction, &QAction::triggered, this, &MainWindow::openTextFile);
        connect(m_closeEditorAction, &QAction::triggered, this, &MainWindow::closeEditor);
        connect(m_closeProjectAction, &QAction::triggered, this, &MainWindow::closeProject);
        connect(m_closeAllAction, &QAction::triggered, this, &MainWindow::closeAll);
        connect(m_saveAction, &QAction::triggered, this, &MainWindow::save);
        connect(m_saveAsAction, &QAction::triggered, this, &MainWindow::saveAs);
        connect(m_saveAllAction, &QAction::triggered, this, &MainWindow::saveAll);
        connect(m_saveProjectAction, &QAction::triggered, this, &MainWindow::saveProject);
        connect(m_saveProjectAsAction, &QAction::triggered, this, &MainWindow::saveProjectAs);
        connect(m_quitAction, &QAction::triggered, this, &MainWindow::close);
        connect(m_undoAction, &QAction::triggered, this, &MainWindow::undo);
        connect(m_redoAction, &QAction::triggered, this, &MainWindow::redo);
        connect(m_toggleProjectVisibleAction, &QAction::triggered, this, &MainWindow::toggleProjectVisible);
        connect(m_toggleSceneVisibleAction, &QAction::triggered, this, &MainWindow::toggleSceneVisible);
        connect(m_toggleInspectorVisibleAction, &QAction::triggered, this, &MainWindow::toggleInspectorVisible);
        connect(m_toggleToolbarVisibleAction, &QAction::triggered, this, &MainWindow::toggleToolbarVisible);
        connect(m_toggleDebugVisibleAction, &QAction::triggered, this, &MainWindow::toggleDebugVisible);
        connect(m_toggleExpandEditorAction, &QAction::triggered, this, &MainWindow::toggleExpandEditor);
        connect(m_playSceneAction, &QAction::triggered, this, &MainWindow::playScene);
        connect(m_stopSceneAction, &QAction::triggered, this, &MainWindow::stopScene);
        connect(m_newScriptAction, &QAction::triggered, this, &MainWindow::newScript);
        connect(m_openScriptAction, &QAction::triggered, this, &MainWindow::openScript);
        connect(m_runScriptAction, &QAction::triggered, this, &MainWindow::runScript);
        connect(m_hashGeneratorAction, &QAction::triggered, this, &MainWindow::hashGenerator);
        connect(m_hashLookupAction, &QAction::triggered, this, &MainWindow::hashLookup);
        connect(m_optionsAction, &QAction::triggered, this, &MainWindow::options);
        connect(m_viewManualAction, &QAction::triggered, this, &MainWindow::viewManual);
        connect(m_viewWikiAction, &QAction::triggered, this, &MainWindow::viewWiki);
        connect(m_aboutSlickAction, &QAction::triggered, this, &MainWindow::aboutSlick);
        connect(m_aboutQtAction, &QAction::triggered, this, &MainWindow::aboutQt);
    }

    void MainWindow::setupMenus()
    {
        QMenu* fileNewMenu = m_fileMenu->addMenu(tr("New"));
        fileNewMenu->addAction(m_newProjectAction);
        fileNewMenu->addAction(m_newSceneAction);
        fileNewMenu->addSeparator();
        fileNewMenu->addAction(m_newHipHopFileAction);
        fileNewMenu->addAction(m_newTextFileAction);

        QMenu* fileOpenMenu = m_fileMenu->addMenu(tr("Open"));
        fileOpenMenu->addAction(m_openProjectAction);
        fileOpenMenu->addAction(m_openSceneAction);
        fileOpenMenu->addSeparator();
        fileOpenMenu->addAction(m_openHipHopFileAction);
        fileOpenMenu->addAction(m_openTextFileAction);

        m_fileMenu->addSeparator();
        m_fileMenu->addAction(m_closeEditorAction);
        m_fileMenu->addAction(m_closeAllAction);
        m_fileMenu->addAction(m_closeProjectAction);
        m_fileMenu->addSeparator();
        m_fileMenu->addAction(m_saveAction);
        m_fileMenu->addAction(m_saveAsAction);
        m_fileMenu->addAction(m_saveAllAction);
        m_fileMenu->addAction(m_saveProjectAction);
        m_fileMenu->addAction(m_saveProjectAsAction);
        m_fileMenu->addSeparator();
        m_fileMenu->addAction(m_quitAction);

        m_editMenu->addAction(m_undoAction);
        m_editMenu->addAction(m_redoAction);

        m_viewMenu->addAction(m_toggleProjectVisibleAction);
        m_viewMenu->addAction(m_toggleSceneVisibleAction);
        m_viewMenu->addAction(m_toggleInspectorVisibleAction);
        m_viewMenu->addAction(m_toggleToolbarVisibleAction);
        m_viewMenu->addAction(m_toggleDebugVisibleAction);
        m_viewMenu->addSeparator();
        m_viewMenu->addAction(m_toggleExpandEditorAction);

        m_playMenu->addAction(m_playSceneAction);
        m_playMenu->addAction(m_stopSceneAction);
        m_playMenu->addSeparator();
        m_playMenu->addMenu(m_emulatorMenu);

        m_scriptsMenu->addAction(m_newScriptAction);
        m_scriptsMenu->addAction(m_openScriptAction);
        m_scriptsMenu->addAction(m_runScriptAction);

        m_toolsMenu->addAction(m_hashGeneratorAction);
        m_toolsMenu->addAction(m_hashLookupAction);
        m_toolsMenu->addSeparator();
        m_toolsMenu->addAction(m_optionsAction);

        m_helpMenu->addAction(m_viewManualAction);
        m_helpMenu->addAction(m_viewWikiAction);
        m_helpMenu->addSeparator();
        m_helpMenu->addAction(m_aboutSlickAction);
        m_helpMenu->addAction(m_aboutQtAction);
    }

    void MainWindow::setupPanels()
    {
        connect(Panels::EditorPanel::instance(), &Panels::EditorPanel::editorChanged, this, [=](Core::Editor* editor)
        {
            m_prevEditor = editor;

            updatePanels();
        });

        connect(m_projectDock, &QDockWidget::visibilityChanged, this, &MainWindow::onPanelDockVisibilityChanged);
        connect(m_sceneDock, &QDockWidget::visibilityChanged, this, &MainWindow::onPanelDockVisibilityChanged);
        connect(m_inspectorDock, &QDockWidget::visibilityChanged, this, &MainWindow::onPanelDockVisibilityChanged);
        connect(m_toolbarDock, &QDockWidget::visibilityChanged, this, &MainWindow::onPanelDockVisibilityChanged);
        connect(m_debugDock, &QDockWidget::visibilityChanged, this, &MainWindow::onPanelDockVisibilityChanged);

        connect(Panels::ScenePanel::instance(), &Panels::ScenePanel::assetsSelected, this, &MainWindow::onAssetsSelected);
    }

    void MainWindow::onPanelDockVisibilityChanged()
    {
        if (!m_updatingPanels)
        {
            m_projectVisible = m_projectDock->isVisible();
            m_sceneVisible = m_sceneDock->isVisible();
            m_inspectorVisible = m_inspectorDock->isVisible();
            m_toolbarVisible = m_toolbarDock->isVisible();
            m_debugVisible = m_debugDock->isVisible();

            updateMenus();
        }
    }

    void MainWindow::onAssetsSelected(const QList<Core::Asset*>& assets)
    {
        Panels::InspectorPanel::instance()->clear();

        for (Core::Asset* asset : assets)
        {
            Panels::InspectorPanel::instance()->addObject(asset, false);
        }

        Panels::InspectorPanel::instance()->refresh();
    }

    void MainWindow::setupLayout()
    {
        m_projectDock->setWidget(Panels::ProjectPanel::instance());
        m_projectDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
        addDockWidget(Qt::BottomDockWidgetArea, m_projectDock);

        m_sceneDock->setWidget(Panels::ScenePanel::instance());
        m_sceneDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
        addDockWidget(Qt::LeftDockWidgetArea, m_sceneDock);

        m_debugDock->setWidget(Panels::DebugPanel::instance());
        m_debugDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
        addDockWidget(Qt::RightDockWidgetArea, m_debugDock);

        m_inspectorDock->setWidget(Panels::InspectorPanel::instance());
        m_inspectorDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
        addDockWidget(Qt::RightDockWidgetArea, m_inspectorDock);

        m_toolbarDock->setWidget(Panels::ToolbarPanel::instance());
        m_toolbarDock->setTitleBarWidget(new QWidget);
        m_toolbarDock->setFeatures(QDockWidget::DockWidgetClosable);
        addDockWidget(Qt::TopDockWidgetArea, m_toolbarDock);

        setCorner(Qt::TopLeftCorner, Qt::TopDockWidgetArea);
        setCorner(Qt::TopRightCorner, Qt::TopDockWidgetArea);
        setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
        setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

        setCentralWidget(Panels::EditorPanel::instance());

        resizeDocks({ m_projectDock }, { height() / 5 }, Qt::Vertical);
        resizeDocks({ m_sceneDock }, { width() / 5 }, Qt::Horizontal);
        resizeDocks({ m_inspectorDock }, { width() / 5 }, Qt::Horizontal);
    }

    void MainWindow::updateMenus()
    {
        qDebug("Update menus");

        Core::Editor* editor = Panels::EditorPanel::instance()->editor();

        if (editor)
        {
            m_closeEditorAction->setEnabled(true);
            m_saveAction->setEnabled(true);
            m_saveAsAction->setEnabled(true);

            m_closeEditorAction->setText(tr("Close %1").arg(editor->title()));
            m_saveAction->setText(tr("Save %1").arg(editor->title()));
            m_saveAsAction->setText(tr("Save %1 As...").arg(editor->title()));
        }
        else
        {
            m_closeEditorAction->setEnabled(false);
            m_saveAction->setEnabled(false);
            m_saveAsAction->setEnabled(false);

            m_closeEditorAction->setText(tr("Close"));
            m_saveAction->setText(tr("Save"));
            m_saveAsAction->setText(tr("Save As..."));
        }

        if (Panels::EditorPanel::instance()->editorCount() > 0)
        {
            m_saveAllAction->setEnabled(true);
            m_closeAllAction->setEnabled(true);
        }
        else
        {
            m_saveAllAction->setEnabled(false);
            m_closeAllAction->setEnabled(false);
        }

        m_toggleProjectVisibleAction->setChecked(m_projectVisible);
        m_toggleSceneVisibleAction->setChecked(m_sceneVisible);
        m_toggleInspectorVisibleAction->setChecked(m_inspectorVisible);
        m_toggleToolbarVisibleAction->setChecked(m_toolbarVisible);
        m_toggleDebugVisibleAction->setChecked(m_debugVisible);
        m_toggleExpandEditorAction->setChecked(m_editorExpanded);

        m_playSceneAction->setEnabled(false);
        m_playSceneAction->setShortcut(Qt::Key_F5);
        m_stopSceneAction->setEnabled(false);
        m_stopSceneAction->setShortcut(QKeySequence());

        m_emulatorMenu->clear();

        {
            QAction* action = m_emulatorMenu->addAction(tr("Dolphin (C:\\Users\\seilc\\Documents\\Dolphin-x64\\Dolphin.exe)"));
            action->setCheckable(true);
            action->setChecked(true);
        }

        m_emulatorMenu->addSeparator();
        m_emulatorMenu->addAction(m_manageEmulatorsAction);

        m_runScriptAction->setEnabled(false);
    }

    void MainWindow::updatePanels()
    {
        qDebug("Update panels");

        m_updatingPanels = true;

        m_projectDock->setVisible(m_projectVisible && !m_editorExpanded);
        m_sceneDock->setVisible(m_sceneVisible && !m_editorExpanded);
        m_inspectorDock->setVisible(m_inspectorVisible && !m_editorExpanded);
        m_toolbarDock->setVisible(m_toolbarVisible);
        m_debugDock->setVisible(m_debugVisible);

        Editors::SceneEditor* sceneEditor = qobject_cast<Editors::SceneEditor*>(Panels::EditorPanel::instance()->editor());
        Panels::DebugPanel::instance()->setRenderContext(sceneEditor ? sceneEditor->scene()->renderContext() : nullptr);

        updateMenus();

        m_updatingPanels = false;

        qDebug("Done updating panels");
    }
}
