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
    Source/Assets/AnimListAsset.cpp \
    Source/Assets/BoulderAsset.cpp \
    Source/Assets/ButtonAsset.cpp \
    Source/Assets/CounterAsset.cpp \
    Source/Assets/EnvAsset.cpp \
    Source/Assets/FogAsset.cpp \
    Source/Assets/GroupAsset.cpp \
    Source/Assets/JSPAsset.cpp \
    Source/Assets/LightKitAsset.cpp \
    Source/Assets/MarkerAsset.cpp \
    Source/Assets/ModelAsset.cpp \
    Source/Assets/PlayerAsset.cpp \
    Source/Assets/SimpleObjectAsset.cpp \
    Source/Assets/TextAsset.cpp \
    Source/Assets/TimerAsset.cpp \
    Source/CameraControllers/FirstPersonCameraController.cpp \
    Source/Core/Asset.cpp \
    Source/Core/BaseAsset.cpp \
    Source/Core/Camera.cpp \
    Source/Core/CameraController.cpp \
    Source/Core/Editor.cpp \
    Source/Core/EditorWidget.cpp \
    Source/Core/EntAsset.cpp \
    Source/Core/Inspector.cpp \
    Source/Core/InspectorGroup.cpp \
    Source/Core/InspectorGroupItem.cpp \
    Source/Core/InspectorProperty.cpp \
    Source/Core/MotionAsset.cpp \
    Source/Core/RenderContext.cpp \
    Source/Core/Scene.cpp \
    Source/Core/SceneFile.cpp \
    Source/Core/Viewport.cpp \
    Source/Editors/HipHopEditor.cpp \
    Source/Editors/HipHopEditorWidget.cpp \
    Source/Editors/SceneEditor.cpp \
    Source/Editors/SceneEditorViewport.cpp \
    Source/Editors/SceneEditorWidget.cpp \
    Source/Editors/TextEditor.cpp \
    Source/Editors/TextEditorWidget.cpp \
    Source/InspectorProperties/AssetInputProperty.cpp \
    Source/InspectorProperties/CheckBoxProperty.cpp \
    Source/InspectorProperties/ColorInputProperty.cpp \
    Source/InspectorProperties/ComboBoxProperty.cpp \
    Source/InspectorProperties/EventInputProperty.cpp \
    Source/InspectorProperties/NumberInputProperty.cpp \
    Source/InspectorProperties/TextInputProperty.cpp \
    Source/InspectorProperties/VectorInputProperty.cpp \
    Source/RW/ClumpRenderer.cpp \
    Source/RW/Frame.cpp \
    Source/RW/AtomicRenderer.cpp \
    Source/RW/GeometryRenderer.cpp \
    Source/UI/EditorMessageBox.cpp \
    Source/UI/EditorPanel.cpp \
    Source/UI/ExpanderWidget.cpp \
    Source/UI/HashGeneratorTool.cpp \
    Source/UI/InspectorPanel.cpp \
    Source/UI/InspectorPanelPrivate.cpp \
    Source/UI/MainWindow.cpp \
    Source/UI/OpenSceneDialog.cpp \
    Source/UI/ProjectPanel.cpp \
    Source/UI/ScenePanel.cpp \
    Source/UI/ToolbarPanel.cpp \
    Source/main.cpp

HEADERS += \
    Source/Assets/AnimListAsset.h \
    Source/Assets/BoulderAsset.h \
    Source/Assets/ButtonAsset.h \
    Source/Assets/CounterAsset.h \
    Source/Assets/EnvAsset.h \
    Source/Assets/FogAsset.h \
    Source/Assets/GroupAsset.h \
    Source/Assets/JSPAsset.h \
    Source/Assets/LightKitAsset.h \
    Source/Assets/MarkerAsset.h \
    Source/Assets/ModelAsset.h \
    Source/Assets/PlayerAsset.h \
    Source/Assets/SimpleObjectAsset.h \
    Source/Assets/TextAsset.h \
    Source/Assets/TimerAsset.h \
    Source/CameraControllers/FirstPersonCameraController.h \
    Source/Core/Asset.h \
    Source/Core/BaseAsset.h \
    Source/Core/BaseAssetPrivate.h \
    Source/Core/Camera.h \
    Source/Core/CameraController.h \
    Source/Core/Editor.h \
    Source/Core/EditorWidget.h \
    Source/Core/EntAsset.h \
    Source/Core/Inspectable.h \
    Source/Core/Inspector.h \
    Source/Core/InspectorDataSource.h \
    Source/Core/InspectorGroup.h \
    Source/Core/InspectorGroupItem.h \
    Source/Core/InspectorListSource.h \
    Source/Core/InspectorProperty.h \
    Source/Core/InspectorProxy.h \
    Source/Core/InspectorState.h \
    Source/Core/InspectorTypes.h \
    Source/Core/MotionAsset.h \
    Source/Core/RenderContext.h \
    Source/Core/Scene.h \
    Source/Core/SceneFile.h \
    Source/Core/Slick.h \
    Source/Core/Util.h \
    Source/Core/Viewport.h \
    Source/Editors/HipHopEditor.h \
    Source/Editors/HipHopEditorWidget.h \
    Source/Editors/SceneEditor.h \
    Source/Editors/SceneEditorViewport.h \
    Source/Editors/SceneEditorWidget.h \
    Source/Editors/TextEditor.h \
    Source/Editors/TextEditorWidget.h \
    Source/InspectorProperties/AssetInputProperty.h \
    Source/InspectorProperties/CheckBoxProperty.h \
    Source/InspectorProperties/ColorInputProperty.h \
    Source/InspectorProperties/ComboBoxProperty.h \
    Source/InspectorProperties/EventInputProperty.h \
    Source/InspectorProperties/InspectorPropertiesCommon.h \
    Source/InspectorProperties/NumberInputProperty.h \
    Source/InspectorProperties/TextInputProperty.h \
    Source/InspectorProperties/VectorInputProperty.h \
    Source/RW/Frame.h \
    Source/RW/AtomicRenderer.h \
    Source/RW/ClumpRenderer.h \
    Source/RW/GeometryRenderer.h \
    Source/UI/EditorMessageBox.h \
    Source/UI/EditorPanel.h \
    Source/UI/ExpanderWidget.h \
    Source/UI/ExpanderWidgetPrivate.h \
    Source/UI/HashGeneratorTool.h \
    Source/UI/InspectorPanel.h \
    Source/UI/InspectorPanelPrivate.h \
    Source/UI/MainWindow.h \
    Source/UI/OpenSceneDialog.h \
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
    Icons/icons.qrc \
    Images/images.qrc \
    Themes/breeze/breeze.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
