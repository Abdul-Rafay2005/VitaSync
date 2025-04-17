#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include "chatwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *centralWidget;
    QVBoxLayout *layout;
    QPushButton *generalDoctorBtn;
    QPushButton *psychiatricDoctorBtn;
    QLabel *titleLabel;
    QGraphicsDropShadowEffect *shadowEffect;

    void setupUI();
    void applyStyle();
    void applyButtonStyle(QPushButton *button, const QString &color);

private slots:
    void openGeneralDoctorChat();
    void openPsychiatricDoctorChat();
};

#endif // MAINWINDOW_H
