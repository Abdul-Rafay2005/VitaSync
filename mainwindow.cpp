#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("VitaSync");

    // Use Maximized instead of FullScreen so title bar + buttons appear
    this->setWindowState(Qt::WindowMaximized);

    setupUI();
    applyStyle();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupUI() {
    centralWidget = new QWidget(this);
    layout = new QVBoxLayout(centralWidget);

    generalDoctorBtn = new QPushButton("🩺 General Doctor", this);
    psychiatricDoctorBtn = new QPushButton("🧠 Psychiatric Doctor", this);

    layout->addStretch();
    layout->addWidget(generalDoctorBtn);
    layout->addSpacing(20);
    layout->addWidget(psychiatricDoctorBtn);
    layout->addStretch();

    layout->setAlignment(Qt::AlignCenter);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(generalDoctorBtn, &QPushButton::clicked, this, &MainWindow::openGeneralDoctorChat);
    connect(psychiatricDoctorBtn, &QPushButton::clicked, this, &MainWindow::openPsychiatricDoctorChat);
}

void MainWindow::applyStyle() {
    QFont font("Segoe UI", 20, QFont::Bold);
    generalDoctorBtn->setFont(font);
    psychiatricDoctorBtn->setFont(font);

    QString buttonStyle = R"(
        QPushButton {
            background-color: #4CAF50;
            color: white;
            border-radius: 15px;
            padding: 15px 30px;
        }
        QPushButton:hover {
            background-color: #45a049;
        }
    )";

    generalDoctorBtn->setStyleSheet(buttonStyle);
    psychiatricDoctorBtn->setStyleSheet(buttonStyle);

    centralWidget->setStyleSheet("background-color: #f0f4f8;");
}

void MainWindow::openGeneralDoctorChat() {
    ChatWindow *chat = new ChatWindow("General Doctor");
    chat->show();
}

void MainWindow::openPsychiatricDoctorChat() {
    ChatWindow *chat = new ChatWindow("Psychiatric Doctor");
    chat->show();
}
