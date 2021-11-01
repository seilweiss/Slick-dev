#include "UI/MainWindow.h"

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

    Slick::MainWindow* window = Slick::MainWindow::instance();
    window->show();

    return app.exec();
}
