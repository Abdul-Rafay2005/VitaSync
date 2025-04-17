#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void handleLogin();
    void onAgreementChanged(bool checked);
    void showTermsDialog(); // ✅ Add this to handle Terms & Conditions dialog

private:
    QLineEdit *userInput;
    QLineEdit *passInput;
    QCheckBox *agreeCheckBox; // ✅ Used to verify agreement before login
};

#endif // LOGINWINDOW_H
