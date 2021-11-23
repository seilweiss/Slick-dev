QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG(debug, debug|release) {
    LIBS += \
        -L"C:/dev/hiphop/lib/Debug" -lhiphop \
        -L"C:/dev/rws/lib/Debug/x64" -lrws
} else {
    LIBS += \
        -L"C:/dev/hiphop/lib/Release" -lhiphop \
        -L"C:/dev/rws/lib/Release/x64" -lrws
}

SOURCES += \
    Source/Assets/JSPAsset.cpp \
    Source/Core/Asset.cpp \
    Source/Core/Editor.cpp \
    Source/Core/EditorWidget.cpp \
    Source/Core/Scene.cpp \
    Source/Core/SceneFile.cpp \
    Source/Editors/HipHopEditor.cpp \
    Source/Editors/HipHopEditorWidget.cpp \
    Source/Editors/SceneEditor.cpp \
    Source/Editors/SceneEditorViewport.cpp \
    Source/Editors/SceneEditorWidget.cpp \
    Source/Editors/TextEditor.cpp \
    Source/Editors/TextEditorWidget.cpp \
    Source/Render/Camera.cpp \
    Source/Render/Clump.cpp \
    Source/Render/Geometry.cpp \
    Source/Render/Viewport.cpp \
    Source/UI/EditorMessageBox.cpp \
    Source/UI/EditorPanel.cpp \
    Source/UI/HashGeneratorTool.cpp \
    Source/UI/InspectorPanel.cpp \
    Source/UI/MainWindow.cpp \
    Source/UI/OpenSceneDialog.cpp \
    Source/UI/ProjectPanel.cpp \
    Source/UI/ScenePanel.cpp \
    Source/UI/ToolbarPanel.cpp \
    Source/main.cpp

HEADERS += \
    Source/Assets/JSPAsset.h \
    Source/Core/Asset.h \
    Source/Core/Editor.h \
    Source/Core/EditorWidget.h \
    Source/Core/Scene.h \
    Source/Core/SceneFile.h \
    Source/Core/Util.h \
    Source/Editors/HipHopEditor.h \
    Source/Editors/HipHopEditorWidget.h \
    Source/Editors/SceneEditor.h \
    Source/Editors/SceneEditorViewport.h \
    Source/Editors/SceneEditorWidget.h \
    Source/Editors/TextEditor.h \
    Source/Editors/TextEditorWidget.h \
    Source/Render/Camera.h \
    Source/Render/Clump.h \
    Source/Render/Context.h \
    Source/Render/Geometry.h \
    Source/Render/Viewport.h \
    Source/UI/EditorMessageBox.h \
    Source/UI/EditorPanel.h \
    Source/UI/HashGeneratorTool.h \
    Source/UI/InspectorPanel.h \
    Source/UI/MainWindow.h \
    Source/UI/OpenSceneDialog.h \
    Source/UI/PanelLayout.h \
    Source/UI/ProjectPanel.h \
    Source/UI/ScenePanel.h \
    Source/UI/ToolbarPanel.h

INCLUDEPATH += \
    C:/dev/hiphop/include \
    C:/dev/rws/include \
    C:/dev/glm \
    Source

DEFINES += \
    HIPHOP_USE_RWS

RESOURCES += \
    Themes/breeze/breeze.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
