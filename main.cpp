#include "UI/MainWindow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("Slick");

    {
        // set stylesheet
        QFile file(":/dark/stylesheet.qss");
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream stream(&file);
        app.setStyleSheet(stream.readAll());
    }

    Slick::MainWindow window;
    window.show();

    return app.exec();
}
