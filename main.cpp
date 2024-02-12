#include "mainwindow.h"
#include "clockwidget.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ClockWidget clockWidget;
    clockWidget.setWindowTitle("Часы");
    clockWidget.show();

    return app.exec();
}
