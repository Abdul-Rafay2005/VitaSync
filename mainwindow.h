#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "chatwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openGeneralDoctorChat();
    void openPsychiatricDoctorChat();

private:
    Ui::MainWindow *ui;
    QWidget *centralWidget;
    QVBoxLayout *layout;
    QPushButton *generalDoctorBtn;
    QPushButton *psychiatricDoctorBtn;

    void setupUI();
    void applyStyle();
};

#endif // MAINWINDOW_H
