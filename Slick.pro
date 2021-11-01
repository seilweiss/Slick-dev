QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += \
    -L"C:/dev/hiphop/lib/Release" -lhiphop \
    -L"C:/dev/rws/lib/Release/x64" -lrws

SOURCES += \
    Source/Editors/IEditor.cpp \
    Source/Editors/TextEditor.cpp \
    Source/UI/EditorMessageBox.cpp \
    Source/UI/EditorPanel.cpp \
    Source/UI/HashGeneratorTool.cpp \
    Source/UI/InspectorPanel.cpp \
    Source/UI/ScenePanel.cpp \
    Source/UI/ToolbarPanel.cpp \
    Source/main.cpp \
    Source/UI/ProjectPanel.cpp \
    Source/UI/MainWindow.cpp

HEADERS += \
    Source/Editors/IEditor.h \
    Source/Editors/TextEditor.h \
    Source/UI/EditorMessageBox.h \
    Source/UI/EditorPanel.h \
    Source/UI/HashGeneratorTool.h \
    Source/UI/InspectorPanel.h \
    Source/UI/MainWindow.h \
    Source/UI/ProjectPanel.h \
    Source/UI/ScenePanel.h \
    Source/UI/ToolbarPanel.h

INCLUDEPATH += \
    C:/dev/hiphop/include \
    C:/dev/rws/include \
    Source

DEFINES += \
    HIPHOP_USE_RWS

RESOURCES += \
    Themes/breeze/breeze.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
