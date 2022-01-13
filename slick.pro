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
    src/assets/animlistasset.cpp \
    src/assets/baseasset.cpp \
    src/assets/boulderasset.cpp \
    src/assets/buttonasset.cpp \
    src/assets/cameraasset.cpp \
    src/assets/conditionalasset.cpp \
    src/assets/counterasset.cpp \
    src/assets/dispatcherasset.cpp \
    src/assets/entasset.cpp \
    src/assets/envasset.cpp \
    src/assets/fogasset.cpp \
    src/assets/groupasset.cpp \
    src/assets/jspasset.cpp \
    src/assets/lightkitasset.cpp \
    src/assets/markerasset.cpp \
    src/assets/modelasset.cpp \
    src/assets/motionasset.cpp \
    src/assets/pipeinfotableasset.cpp \
    src/assets/platformasset.cpp \
    src/assets/playerasset.cpp \
    src/assets/simpleobjectasset.cpp \
    src/assets/textasset.cpp \
    src/assets/textureasset.cpp \
    src/assets/texturepreview.cpp \
    src/assets/timerasset.cpp \
    src/core/asset.cpp \
    src/core/assetmanager.cpp \
    src/core/editor.cpp \
    src/core/editorwidget.cpp \
    src/core/modelbucketmanager.cpp \
    src/core/modelinstance.cpp \
    src/core/scene.cpp \
    src/core/scenefile.cpp \
    src/core/scrfxmanager.cpp \
    src/core/skydomemanager.cpp \
    src/dialogs/editorlist.cpp \
    src/dialogs/openscene.cpp \
    src/editors/hiphopeditor.cpp \
    src/editors/hiphopeditorwidget.cpp \
    src/editors/sceneeditor.cpp \
    src/editors/sceneeditorviewport.cpp \
    src/editors/sceneeditorwidget.cpp \
    src/editors/texteditor.cpp \
    src/editors/texteditorwidget.cpp \
    src/inspector/group.cpp \
    src/inspector/groupitem.cpp \
    src/inspector/properties/buttonproperty.cpp \
    src/inspector/properties/labelproperty.cpp \
    src/inspector/property.cpp \
    src/inspector/root.cpp \
    src/inspector/properties/assetinputproperty.cpp \
    src/inspector/properties/checkboxproperty.cpp \
    src/inspector/properties/colorinputproperty.cpp \
    src/inspector/properties/comboboxproperty.cpp \
    src/inspector/properties/eventinputproperty.cpp \
    src/inspector/properties/numberinputproperty.cpp \
    src/inspector/properties/textinputproperty.cpp \
    src/inspector/properties/vectorinputproperty.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/panels/editorpanel.cpp \
    src/panels/inspectorpanel.cpp \
    src/panels/inspectorpanelprivate.cpp \
    src/panels/projectpanel.cpp \
    src/panels/scenepanel.cpp \
    src/panels/toolbarpanel.cpp \
    src/render/atomic.cpp \
    src/render/camera.cpp \
    src/render/cameracontroller.cpp \
    src/render/clump.cpp \
    src/render/context.cpp \
    src/render/controllers/firstpersoncameracontroller.cpp \
    src/render/frame.cpp \
    src/render/geometry.cpp \
    src/render/material.cpp \
    src/render/texture.cpp \
    src/render/viewport.cpp \
    src/tools/hashgenerator.cpp \
    src/util/expandwidget.cpp

HEADERS += \
    src/assets/animlistasset.h \
    src/assets/baseasset.h \
    src/assets/baseassetprivate.h \
    src/assets/boulderasset.h \
    src/assets/buttonasset.h \
    src/assets/cameraasset.h \
    src/assets/conditionalasset.h \
    src/assets/counterasset.h \
    src/assets/dispatcherasset.h \
    src/assets/entasset.h \
    src/assets/envasset.h \
    src/assets/fogasset.h \
    src/assets/groupasset.h \
    src/assets/jspasset.h \
    src/assets/lightkitasset.h \
    src/assets/markerasset.h \
    src/assets/modelasset.h \
    src/assets/motionasset.h \
    src/assets/pipeinfotableasset.h \
    src/assets/platformasset.h \
    src/assets/playerasset.h \
    src/assets/simpleobjectasset.h \
    src/assets/textasset.h \
    src/assets/textureasset.h \
    src/assets/texturepreview.h \
    src/assets/timerasset.h \
    src/core/asset.h \
    src/core/assetmanager.h \
    src/core/color.h \
    src/core/editor.h \
    src/core/editorwidget.h \
    src/core/modelbucketmanager.h \
    src/core/modelinstance.h \
    src/core/scene.h \
    src/core/scenefile.h \
    src/core/scrfxmanager.h \
    src/core/skydomemanager.h \
    src/core/vector.h \
    src/dialogs/editorlist.h \
    src/dialogs/openscene.h \
    src/editors/hiphopeditor.h \
    src/editors/hiphopeditorwidget.h \
    src/editors/sceneeditor.h \
    src/editors/sceneeditorviewport.h \
    src/editors/sceneeditorwidget.h \
    src/editors/texteditor.h \
    src/editors/texteditorwidget.h \
    src/inspector/datasource.h \
    src/inspector/group.h \
    src/inspector/groupitem.h \
    src/inspector/listsource.h \
    src/inspector/object.h \
    src/inspector/properties/assetinputproperty.h \
    src/inspector/properties/buttonproperty.h \
    src/inspector/properties/checkboxproperty.h \
    src/inspector/properties/colorinputproperty.h \
    src/inspector/properties/combobox.h \
    src/inspector/properties/comboboxproperty.h \
    src/inspector/properties/doublespinbox.h \
    src/inspector/properties/eventinputproperty.h \
    src/inspector/properties/intspinbox.h \
    src/inspector/properties/labelproperty.h \
    src/inspector/properties/numberinputproperty.h \
    src/inspector/properties/textinputproperty.h \
    src/inspector/properties/vectorinputproperty.h \
    src/inspector/properties/wheelignorer.h \
    src/inspector/property.h \
    src/inspector/proxy.h \
    src/inspector/root.h \
    src/mainwindow.h \
    src/panels/editorpanel.h \
    src/panels/inspectorpanel.h \
    src/panels/inspectorpanelprivate.h \
    src/panels/projectpanel.h \
    src/panels/scenepanel.h \
    src/panels/toolbarpanel.h \
    src/render/atomic.h \
    src/render/camera.h \
    src/render/cameracontroller.h \
    src/render/clump.h \
    src/render/context.h \
    src/render/controllers/firstpersoncameracontroller.h \
    src/render/frame.h \
    src/render/geometry.h \
    src/render/material.h \
    src/render/texture.h \
    src/render/viewport.h \
    src/tools/hashgenerator.h \
    src/util/expandwidget.h \
    src/util/expandwidgetprivate.h \
    src/util/hiphoputils.h \
    src/util/mathutils.h \
    src/util/stringutils.h \
    src/util/widgetutils.h \
    src/version.h

INCLUDEPATH += \
    C:/dev/hiphop/include \
    C:/dev/rws/include \
    C:/dev/glm \
    src

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
