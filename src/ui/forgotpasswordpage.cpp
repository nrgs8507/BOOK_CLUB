#include "forgotpasswordpage.h"
#include <QMessageBox>
#include "../network/networkclient.h"
#include <QJsonObject>

ForgotPasswordPage::ForgotPasswordPage(std::shared_ptr<AuthManager> authManager, QWidget *parent)
    : QWidget(parent)
    , authManager(authManager)
{
    // عنوان
    titleLabel = new QLabel("🔐 Forgot Password", this);
    titleLabel->setAlignment(Qt::AlignCenter);

    // فیلد نام کاربری
    usernameLabel = new QLabel("Enter your username:", this);
    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("Your username");

    // نمایش سوال امنیتی
    securityQuestionLabel = new QLabel("Security Question:", this);
    securityQuestionDisplay = new QLabel(this);
    securityQuestionDisplay->setStyleSheet("color: #6C63FF; font-weight: bold;");
    securityQuestionDisplay->setText("(Enter your username first)");

    // پاسخ سوال امنیتی
    securityAnswerEdit = new QLineEdit(this);
    securityAnswerEdit->setPlaceholderText("Your answer");

    // رمز جدید
    newPasswordLabel = new QLabel("New Password:", this);
    newPasswordEdit = new QLineEdit(this);
    newPasswordEdit->setPlaceholderText("Enter new password");
    newPasswordEdit->setEchoMode(QLineEdit::Password);

    // دکمه‌ها
    resetButton = new QPushButton("Reset Password", this);
    backToLoginButton = new QPushButton("Back to Login", this);

    // خطا
    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color: red;");
    errorLabel->setVisible(false);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(usernameLabel);
    layout->addWidget(usernameEdit);
    layout->addWidget(securityQuestionLabel);
    layout->addWidget(securityQuestionDisplay);
    layout->addWidget(securityAnswerEdit);
    layout->addWidget(newPasswordLabel);
    layout->addWidget(newPasswordEdit);
    layout->addWidget(resetButton);
    layout->addWidget(backToLoginButton);
    layout->addWidget(errorLabel);

    // استایل
    setStyleSheet(R"(
        QWidget {
            background-color: #1E1E2F;
            font-family: Segoe UI;
        }
        QLabel {
            color: #CDCDCD;
            font-size: 13px;
        }
        QLineEdit {
            background-color: #3A3A4E;
            border: 1px solid #5A5A7A;
            border-radius: 10px;
            padding: 10px;
            color: #FFFFFF;
            font-size: 14px;
        }
        QLineEdit:focus {
            border: 2px solid #6C63FF;
        }
        QPushButton {
            background-color: #6C63FF;
            color: white;
            border: none;
            border-radius: 12px;
            padding: 12px;
            font-weight: bold;
            font-size: 15px;
        }
        QPushButton:hover {
            background-color: #7C73FF;
        }
        QPushButton#backToLoginButton {
            background-color: transparent;
            color: #6C63FF;
            border: 2px solid #6C63FF;
        }
        QPushButton#backToLoginButton:hover {
            background-color: #6C63FF;
            color: white;
        }
        QLabel#errorLabel {
            color: #FF6B6B;
            font-size: 12px;
        }
    )");

    // ========== اتصالات (Connections) ==========
    connect(resetButton, &QPushButton::clicked, this, &ForgotPasswordPage::onResetClicked);
    connect(backToLoginButton, &QPushButton::clicked, this, &ForgotPasswordPage::close);

    // وقتی کاربر نام کاربری رو تایپ می‌کنه، سوال امنیتی رو نمایش بده
    connect(usernameEdit, &QLineEdit::textChanged, [this]() {
        QString username = usernameEdit->text().trimmed();
        if (!username.isEmpty()) {
            QJsonObject request;
            request["action"] = "getSecurityQuestion";
            request["username"] = username;
            networkClient->sendRequest(request);
        } else {
            securityQuestionDisplay->setText("(Enter your username first)");
            securityQuestionDisplay->setStyleSheet("color: #6C63FF;");
        }
    });
    networkClient = new NetworkClient(this);
    networkClient->connectToServer("127.0.0.1", 5050);
    connect(networkClient, &NetworkClient::responseReceived, this, &ForgotPasswordPage::onNetworkResponse);
}

void ForgotPasswordPage::onResetClicked()
{
    QString username = usernameEdit->text().trimmed();
    QString securityAnswer = securityAnswerEdit->text().trimmed();
    QString newPassword = newPasswordEdit->text();

    if (username.isEmpty() || securityAnswer.isEmpty() || newPassword.isEmpty()) {
        errorLabel->setText("All fields are required.");
        errorLabel->setVisible(true);
        return;
    }

    if (newPassword.length() < 4) {
        errorLabel->setText("Password must be at least 4 characters.");
        errorLabel->setVisible(true);
        return;
    }

    QJsonObject request;
    request["action"] = "forgotPassword";
    request["username"] = username;
    request["securityAnswer"] = securityAnswer;
    request["newPassword"] = newPassword;
    networkClient->sendRequest(request);
}

void ForgotPasswordPage::onNetworkResponse(const QJsonObject &response)
{
    QString action = response.value("action").toString();

    if (action == "getSecurityQuestion") {
        if (response.value("status").toString() == "ok") {
            securityQuestionDisplay->setText(response.value("securityQuestion").toString());
            securityQuestionDisplay->setStyleSheet("color: #6C63FF;");
        } else {
            securityQuestionDisplay->setText("Username not found");
            securityQuestionDisplay->setStyleSheet("color: red;");
        }
    }
    else if (action == "forgotPassword") {
        if (response.value("status").toString() == "ok") {
            QMessageBox::information(this, "Success", "Password reset successfully! Please login.");
            close();
        } else {
            errorLabel->setText(response.value("message").toString());
            errorLabel->setVisible(true);
        }
    }
}
