#include "loginwindow.h"
#include "mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QKeyEvent>
#include <QCheckBox>
#include <QTextBrowser>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Secure Login");
    resize(800, 500);
    setStyleSheet("background-color: #eaeef1;");

    // Left panel - Welcome side
    QWidget *welcomeWidget = new QWidget();
    welcomeWidget->setStyleSheet(
        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #4e8cff, stop:1 #6cd4ff);"
        "border-top-left-radius: 20px; border-bottom-left-radius: 20px;"
        );

    QLabel *welcomeText = new QLabel("Welcome Back!");
    welcomeText->setStyleSheet("color: white; font-size: 36px; font-weight: bold; font-family: 'Segoe UI', sans-serif;");
    welcomeText->setAlignment(Qt::AlignCenter);

    QLabel *descText = new QLabel("Login to continue to your dashboard.");
    descText->setStyleSheet("color: #f0f0f0; font-size: 16px; font-style: italic;");
    descText->setAlignment(Qt::AlignCenter);
    descText->setWordWrap(true);

    QLabel *creditsLabel = new QLabel("Developed by:\nAbdul Rafay, Syed Nabeel, Sadia, Bisma");
    creditsLabel->setStyleSheet("color: #e0f7ff; font-size: 19px; font-weight: 500;");
    creditsLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *welcomeLayout = new QVBoxLayout(welcomeWidget);
    welcomeLayout->setContentsMargins(20, 20, 20, 20);
    welcomeLayout->addStretch();
    welcomeLayout->addWidget(welcomeText);
    welcomeLayout->addSpacing(10);
    welcomeLayout->addWidget(descText);
    welcomeLayout->addStretch();
    welcomeLayout->addWidget(creditsLabel);
    welcomeLayout->addSpacing(20);

    // Right panel - Form side
    QLabel *userLabel = new QLabel("Username:");
    QLabel *passLabel = new QLabel("Password:");
    userLabel->setStyleSheet("font-size: 16px; color: #333;");
    passLabel->setStyleSheet("font-size: 16px; color: #333;");

    userInput = new QLineEdit();
    userInput->setMinimumHeight(40);
    userInput->setStyleSheet("color: black; border-radius: 10px; padding: 8px; font-size: 14px; background-color: #ffffff; border: 1px solid #ccc;");
    userInput->setFocus();
    userInput->installEventFilter(this);

    QHBoxLayout *passLayout = new QHBoxLayout();
    passLayout->setSpacing(0);
    passLayout->setContentsMargins(0, 0, 0, 0);

    passInput = new QLineEdit();
    passInput->setMinimumHeight(40);
    passInput->setEchoMode(QLineEdit::Password);
    passInput->setStyleSheet("color: black; border-radius: 10px 0 0 10px; padding-left: 8px; font-size: 14px; background-color: #ffffff; border: 1px solid #ccc;");
    passInput->installEventFilter(this);

    QPushButton *toggleButton = new QPushButton("Show");
    toggleButton->setCheckable(true);
    toggleButton->setCursor(Qt::PointingHandCursor);
    toggleButton->setMinimumHeight(40);
    toggleButton->setFixedWidth(60);
    toggleButton->setStyleSheet("QPushButton { border-radius: 0 10px 10px 0; background-color: #dcdcdc; font-weight: bold; } QPushButton:checked { background-color: #c4c4c4; }");
    connect(toggleButton, &QPushButton::toggled, this, [=](bool checked) {
        passInput->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
        toggleButton->setText(checked ? "Hide" : "Show");
    });

    passLayout->addWidget(passInput);
    passLayout->addWidget(toggleButton);

    QPushButton *loginButton = new QPushButton("Login");
    loginButton->setFixedHeight(40);

    loginButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #87CEFA;"  // light navy blue
        "  color: white;"
        "  font-size: 16px;"
        "  border-radius: 10px;"
        "}"
        "QPushButton:hover { background-color: #3b4a65; }"  // slightly darker on hover
        );



    agreeCheckBox = new QCheckBox("I agree to the ");
    agreeCheckBox->setStyleSheet(
        "QCheckBox { font-size: 13px; color: black; }"
        "QCheckBox::indicator { width: 18px; height: 18px; border: 2px solid #2e3a59; border-radius: 4px; background-color: white; }"
        "QCheckBox::indicator:checked { background-color: #2e3a59; border: 2px solid #2e3a59; }"
        );

    QLabel *termsLink = new QLabel("<a href='#'>Terms & Conditions</a>");
    termsLink->setTextInteractionFlags(Qt::TextBrowserInteraction);
    termsLink->setOpenExternalLinks(false);
    termsLink->setStyleSheet("font-size: 13px; color: #2e3a59; text-decoration: underline;");
    connect(termsLink, &QLabel::linkActivated, this, &LoginWindow::showTermsDialog);

    QHBoxLayout *termsLayout = new QHBoxLayout();
    termsLayout->addWidget(agreeCheckBox);
    termsLayout->addWidget(termsLink);
    termsLayout->addStretch();

    QPushButton *quitButton = new QPushButton("Quit");
    quitButton->setFixedSize(80, 30);
    quitButton->setStyleSheet(
        "QPushButton { background-color: #ff4c4c; color: white; font-size: 14px; border-radius: 5px; }"
        "QPushButton:hover { background-color: #cc0000; }"
        );
    connect(quitButton, &QPushButton::clicked, this, &QWidget::close);

    QVBoxLayout *formLayout = new QVBoxLayout();
    formLayout->setContentsMargins(30, 30, 30, 30);
    formLayout->addWidget(userLabel);
    formLayout->addWidget(userInput);
    formLayout->addWidget(passLabel);
    formLayout->addLayout(passLayout);
    formLayout->addSpacing(10);
    formLayout->addWidget(loginButton);
    formLayout->addLayout(termsLayout);
    formLayout->addSpacing(10);
    formLayout->addWidget(quitButton, 0, Qt::AlignRight);

    QWidget *formWidget = new QWidget();
    formWidget->setLayout(formLayout);
    formWidget->setStyleSheet("background-color: #f6f7fa; border-top-right-radius: 20px; border-bottom-right-radius: 20px;");

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(welcomeWidget, 2);
    mainLayout->addWidget(formWidget, 3);

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLogin);
}

bool LoginWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            if (obj == userInput) {
                passInput->setFocus();
                return true;
            } else if (obj == passInput) {
                handleLogin();
                return true;
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}

void LoginWindow::handleLogin() {
    if (!agreeCheckBox->isChecked()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Terms Required");
        msgBox.setText("<font color='white'>You must agree to the Terms and Conditions to login.</font>");
        msgBox.setStyleSheet("QLabel{color: white; font-size: 14px;} QPushButton{min-width: 80px;} QMessageBox{background-color: #2e3a59;}");
        msgBox.exec();
        return;
    }

    QString username = userInput->text();
    QString password = passInput->text();

    if (username == "admin" && password == "1234") {
        MainWindow *mainWin = new MainWindow();
        mainWin->show();
        this->close();
    } else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("<font color='white'>Invalid username or password!</font>");
        msgBox.setStyleSheet("QLabel{color: white; font-size: 14px;} QPushButton{min-width: 80px;} QMessageBox{background-color: #2e3a59;}");
        msgBox.exec();
        userInput->clear();
        passInput->clear();
        userInput->setFocus();
    }
}

void LoginWindow::onAgreementChanged(bool checked) {
    agreeCheckBox->setStyleSheet(
        QString("font-size: 13px; color: %1; padding-left: 5px;")
            .arg(checked ? "#2e3a59" : "#555")
        );
}

void LoginWindow::showTermsDialog() {
    QDialog *termsDialog = new QDialog(this);
    termsDialog->setWindowTitle("Terms & Conditions");
    termsDialog->resize(400, 300);

    QTextBrowser *textBrowser = new QTextBrowser();
    textBrowser->setText(
        "• Your activities may be monitored.\n"
        "• Unauthorized access is strictly prohibited.\n"
        "• Keep your credentials confidential.\n"
        "• Admin may revoke access at any time.\n"
        "• Respect the privacy and rights of others."
        );
    textBrowser->setStyleSheet("QTextBrowser { color: black; }");

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(buttonBox, &QDialogButtonBox::rejected, termsDialog, &QDialog::reject);

    QVBoxLayout *layout = new QVBoxLayout(termsDialog);
    layout->addWidget(textBrowser);
    layout->addWidget(buttonBox);

    termsDialog->exec();
}
