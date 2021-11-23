#include "UI/MainWindow.h"

#include "rws_core.h"
#include "rws_world.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("Slick Editor");

    {
        // set stylesheet
        QFile file(":/dark/stylesheet.qss");
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream stream(&file);
        app.setStyleSheet(stream.readAll());
    }

    Rws::Core::Register();
    Rws::WorldPlugin::Register();

    Slick::MainWindow* window = Slick::MainWindow::instance();
    window->show();

    return app.exec();
}
