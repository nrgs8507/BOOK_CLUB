#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QJsonObject>
#include <memory>
#include "../auth/AuthManager.h"
#include "../network/networkclient.h"

class RegisterPage : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterPage(std::shared_ptr<AuthManager> authManager, QWidget *parent = nullptr);

private slots:
    void onRegisterClicked();
    void onRegisterResponse(const QJsonObject &response);

private:
    std::shared_ptr<AuthManager> authManager;

    QLabel *titleLabel;
    QLabel *usernameLabel;
    QLineEdit *usernameEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordEdit;
    QLabel *confirmPasswordLabel;
    QLineEdit *confirmPasswordEdit;
    QLabel *fullNameLabel;
    QLineEdit *fullNameEdit;
    QLabel *securityQuestionLabel;
    QLineEdit *securityQuestionEdit;
    QLabel *securityAnswerLabel;
    QLineEdit *securityAnswerEdit;
    QPushButton *registerButton;
    QPushButton *backToLoginButton;
    QLabel *errorLabel;
    NetworkClient *networkClient;
};

#endif // REGISTERPAGE_H
