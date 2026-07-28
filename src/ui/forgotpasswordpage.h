#ifndef FORGOTPASSWORDPAGE_H
#define FORGOTPASSWORDPAGE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QJsonObject>
#include <QVBoxLayout>
#include <memory>
#include "../auth/AuthManager.h"
#include "../network/networkclient.h"

class ForgotPasswordPage : public QWidget
{
    Q_OBJECT

public:
    explicit ForgotPasswordPage(std::shared_ptr<AuthManager> authManager, QWidget *parent = nullptr);

private slots:
    void onResetClicked();
    void onNetworkResponse(const QJsonObject &response);

private:
    std::shared_ptr<AuthManager> authManager;

    QLabel *titleLabel;
    QLabel *usernameLabel;
    QLineEdit *usernameEdit;
    QLabel *securityQuestionLabel;
    QLabel *securityQuestionDisplay;
    QLineEdit *securityAnswerEdit;
    QLabel *newPasswordLabel;
    QLineEdit *newPasswordEdit;
    QPushButton *resetButton;
    QPushButton *backToLoginButton;
    QLabel *errorLabel;
    NetworkClient *networkClient;
};

#endif
