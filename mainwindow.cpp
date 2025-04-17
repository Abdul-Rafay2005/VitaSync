#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QTimerEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    this->setWindowTitle("VitaSync");
    this->setWindowState(Qt::WindowMaximized);

    setupUI();
    applyStyle();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    centralWidget = new QWidget(this);
    layout = new QVBoxLayout(centralWidget);

    titleLabel = new QLabel("✨ Welcome to VitaSync ✨", this);
    QFont titleFont("Segoe UI", 40, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: white;");

    generalDoctorBtn = new QPushButton("🩺 Dr. Driva", this);
    psychiatricDoctorBtn = new QPushButton("🧠 Mood Mentor", this);

    layout->addStretch();
    layout->addWidget(titleLabel);
    layout->addSpacing(50);
    layout->addWidget(generalDoctorBtn);
    layout->addSpacing(30);
    layout->addWidget(psychiatricDoctorBtn);
    layout->addStretch();

    layout->setAlignment(Qt::AlignCenter);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(generalDoctorBtn, &QPushButton::clicked, this, &MainWindow::openGeneralDoctorChat);
    connect(psychiatricDoctorBtn, &QPushButton::clicked, this, &MainWindow::openPsychiatricDoctorChat);
}

void MainWindow::applyStyle() {
    QFont buttonFont("Segoe UI", 24, QFont::Bold);
    generalDoctorBtn->setFont(buttonFont);
    psychiatricDoctorBtn->setFont(buttonFont);

    // Neon-style button hover effect and 3D pop-out
    QString buttonStyle = R"(
        QPushButton {
            background-color: #1E1E1E;
            color: white;
            border: 2px solid #3F3F3F;
            border-radius: 25px;
            padding: 20px 40px;
            font-weight: bold;
            letter-spacing: 1px;
            font-size: 18px;
            transition: all 0.3s ease;
        }
        QPushButton:hover {
            background-color: #3F3F3F;
            color: #00FF00;
            border: 2px solid #00FF00;
            box-shadow: 0 0 20px 5px rgba(0, 255, 0, 0.7);
            transform: scale(1.1) translateY(-5px);
        }
    )";

    generalDoctorBtn->setStyleSheet(buttonStyle);
    psychiatricDoctorBtn->setStyleSheet(buttonStyle);

    // Drop shadow effect for buttons
    QGraphicsDropShadowEffect *shadow1 = new QGraphicsDropShadowEffect(this);
    shadow1->setBlurRadius(20);
    shadow1->setOffset(0, 5);
    shadow1->setColor(QColor(0, 0, 0, 120));
    generalDoctorBtn->setGraphicsEffect(shadow1);

    QGraphicsDropShadowEffect *shadow2 = new QGraphicsDropShadowEffect(this);
    shadow2->setBlurRadius(20);
    shadow2->setOffset(0, 5);
    shadow2->setColor(QColor(0, 0, 0, 120));
    psychiatricDoctorBtn->setGraphicsEffect(shadow2);

    // Dynamic gradient moving background effect (still needs QTimerEvent for animation)
    centralWidget->setStyleSheet(R"(
        QWidget {
            background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1,
                stop:0 #1e1e1e, stop:1 #34495e);
            border-radius: 25px;
        }
    )");

    // Title fade-in effect with color change
    QGraphicsOpacityEffect *fadeEffect = new QGraphicsOpacityEffect(titleLabel);
    titleLabel->setGraphicsEffect(fadeEffect);
    QPropertyAnimation *animation = new QPropertyAnimation(fadeEffect, "opacity");
    animation->setDuration(1500);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start();

    // Title glowing effect
    QPropertyAnimation *glowEffect = new QPropertyAnimation(titleLabel, "color");
    glowEffect->setDuration(3000);
    glowEffect->setStartValue(QColor(255, 255, 255));
    glowEffect->setEndValue(QColor(255, 0, 255));
    glowEffect->start();
}

void MainWindow::openGeneralDoctorChat() {
    ChatWindow *chat = new ChatWindow("General Doctor");
    chat->show();
}

void MainWindow::openPsychiatricDoctorChat() {
    ChatWindow *chat = new ChatWindow("Psychiatric Doctor");
    chat->show();
}
