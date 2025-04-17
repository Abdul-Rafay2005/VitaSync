#include <QApplication>
#include "loginwindow.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Create LoginWindow object
    LoginWindow loginWindow;
    loginWindow.show();

    // Execute the application
    return a.exec();
}
