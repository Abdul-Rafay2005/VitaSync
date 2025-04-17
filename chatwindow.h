#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QNetworkAccessManager>

class ChatWindow : public QWidget {
    Q_OBJECT

public:
    ChatWindow(const QString &doctorType, QWidget *parent = nullptr);

private slots:
    void sendMessage();

private:
    QString doctorType;
    QTextEdit *chatBox;
    QLineEdit *inputField;
    QPushButton *sendButton;
    QNetworkAccessManager *networkManager;
};

#endif // CHATWINDOW_H
