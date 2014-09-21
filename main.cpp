#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setOrganizationName("V_K_O_CH");
    app.setApplicationName("USB machine");
    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
