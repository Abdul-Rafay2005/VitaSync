#include "chatwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTime>
#include <QScrollBar>
#include <QLabel>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QNetworkReply>

ChatWindow::ChatWindow(const QString &doctorType, QWidget *parent)
    : QWidget(parent), doctorType(doctorType)
{
    setWindowTitle("VitaSync Chat - " + doctorType);
    setMinimumSize(600, 700);
    setStyleSheet("background-color: #f5f7fa;");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(15);

    QLabel *header = new QLabel("Chat with " + doctorType);
    header->setStyleSheet("font-size: 18px;font-weight: bold;color: #2c3e50;padding: 10px;background-color: #ffffff;border-radius: 8px;");
    mainLayout->addWidget(header);

    chatBox = new QTextEdit();
    chatBox->setReadOnly(true);
    chatBox->setStyleSheet(R"(
        QTextEdit {
            font-size: 14px;
            background-color: white;
            color: #34495e;
            border: 1px solid #dfe6e9;
            border-radius: 8px;
            padding: 15px;
        }
        QScrollBar:vertical {
            width: 10px;
            background: #f1f5f9;
        }
        QScrollBar::handle:vertical {
            background: #bdc3c7;
            border-radius: 4px;
        }
    )");
    mainLayout->addWidget(chatBox, 1);

    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->setSpacing(10);

    inputField = new QLineEdit();
    inputField->setPlaceholderText("Type your message...");
    inputField->setStyleSheet(R"(
        QLineEdit {
            font-size: 14px;
            padding: 12px 15px;
            border: 2px solid #dfe6e9;
            border-radius: 20px;
            background-color: white;
        }
        QLineEdit:focus {
            border: 2px solid #3498db;
        }
    )");

    sendButton = new QPushButton("Send");
    sendButton->setStyleSheet(R"(
        QPushButton {
            font-size: 14px;
            font-weight: bold;
            color: white;
            background-color: #3498db;
            border: none;
            border-radius: 20px;
            padding: 12px 20px;
        }
        QPushButton:hover {
            background-color: #2980b9;
        }
        QPushButton:pressed {
            background-color: #2471a3;
        }
    )");

    inputLayout->addWidget(inputField, 1);
    inputLayout->addWidget(sendButton);
    mainLayout->addLayout(inputLayout);

    networkManager = new QNetworkAccessManager(this);

    connect(sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);
    connect(inputField, &QLineEdit::returnPressed, this, &ChatWindow::sendMessage);

    chatBox->append("<div style='color:#7f8c8d;font-style:italic;'>"
                    "VitaSync: Hello! How can I help you today?"
                    "</div>");
}

void ChatWindow::sendMessage()
{
    QString message = inputField->text().trimmed();
    if (message.isEmpty()) return;

    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
    chatBox->append("<div style='margin:10px 0;text-align:right;'>"
                    "<span style='background:#3498db;color:white;border-radius:15px;padding:8px 12px;display:inline-block;'>"
                    "<b>You [" + time + "]:</b> " + message +
                    "</span></div>");
    inputField->clear();

    // Gemini API request format
    QJsonObject textPart;
    textPart["text"] = message;

    QJsonObject content;
    content["parts"] = QJsonArray{ textPart };

    QJsonObject requestBody;
    requestBody["contents"] = QJsonArray{ content };

    QNetworkRequest request(QUrl("https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key=our API KEY HERE "));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->post(request, QJsonDocument(requestBody).toJson());

    connect(reply, &QNetworkReply::finished, this, [=]() {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);

        if (reply->error() == QNetworkReply::NoError) {
            if (jsonDoc.isObject()) {
                QJsonObject obj = jsonDoc.object();
                if (obj.contains("candidates")) {
                    QJsonArray candidates = obj["candidates"].toArray();
                    if (!candidates.isEmpty()) {
                        QString responseText = candidates[0].toObject()["content"]
                                                   .toObject()["parts"]
                                                   .toArray()[0].toObject()["text"].toString();

                        QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
                        chatBox->append("<div style='margin:10px 0;'>"
                                        "<span style='background:#ecf0f1;color:#2c3e50;border-radius:15px;padding:8px 12px;display:inline-block;'>"
                                        "<b>VitaSync [" + time + "]:</b> " + responseText +
                                        "</span></div>");
                    } else {
                        chatBox->append("<div style='color:#e67e22;'><b>Warning:</b> No response received.</div>");
                    }
                } else {
                    chatBox->append("<div style='color:#e74c3c;'><b>Error:</b> No 'candidates' in response.</div>");
                }
            } else {
                chatBox->append("<div style='color:#e74c3c;'><b>Error:</b> Invalid JSON received.</div>");
            }
        } else {
            chatBox->append("<div style='color:#e74c3c;'><b>Error:</b> " + reply->errorString() + "</div>");
        }

        reply->deleteLater();

        QScrollBar *scrollBar = chatBox->verticalScrollBar();
        scrollBar->setValue(scrollBar->maximum());
    });
}
