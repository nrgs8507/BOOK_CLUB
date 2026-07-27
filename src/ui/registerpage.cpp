#include "registerpage.h"
#include <QMessageBox>

RegisterPage::RegisterPage(std::shared_ptr<AuthManager> authManager, QWidget *parent)
    : QWidget(parent)
    , authManager(authManager)
{
    // ========== Create UI ==========
    titleLabel = new QLabel("📚 Create Account", this);
    titleLabel->setAlignment(Qt::AlignCenter);

    usernameLabel = new QLabel("Username:", this);
    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("Choose a username");

    passwordLabel = new QLabel("Password:", this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Enter password");
    passwordEdit->setEchoMode(QLineEdit::Password);

    confirmPasswordLabel = new QLabel("Confirm Password:", this);
    confirmPasswordEdit = new QLineEdit(this);
    confirmPasswordEdit->setPlaceholderText("Re-enter password");
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);

    fullNameLabel = new QLabel("Full Name:", this);
    fullNameEdit = new QLineEdit(this);
    fullNameEdit->setPlaceholderText("Your full name");

    securityQuestionLabel = new QLabel("Security Question:", this);
    securityQuestionEdit = new QLineEdit(this);
    securityQuestionEdit->setPlaceholderText("e.g. What is your favorite book?");

    securityAnswerLabel = new QLabel("Security Answer:", this);
    securityAnswerEdit = new QLineEdit(this);
    securityAnswerEdit->setPlaceholderText("Your answer");

    registerButton = new QPushButton("Register", this);
    backToLoginButton = new QPushButton("Back to Login", this);

    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color: red;");
    errorLabel->setVisible(false);

    // ========== Layout ==========
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(usernameLabel);
    layout->addWidget(usernameEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordEdit);
    layout->addWidget(confirmPasswordLabel);
    layout->addWidget(confirmPasswordEdit);
    layout->addWidget(fullNameLabel);
    layout->addWidget(fullNameEdit);
    layout->addWidget(securityQuestionLabel);
    layout->addWidget(securityQuestionEdit);
    layout->addWidget(securityAnswerLabel);
    layout->addWidget(securityAnswerEdit);
    layout->addWidget(registerButton);
    layout->addWidget(backToLoginButton);
    layout->addWidget(errorLabel);

    // ========== Apply Stylesheet ==========
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

    // ========== Connections ==========
    connect(registerButton, &QPushButton::clicked, this, &RegisterPage::onRegisterClicked);
    connect(backToLoginButton, &QPushButton::clicked, this, &RegisterPage::close);
}
void RegisterPage::onRegisterClicked()
{
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text();
    QString confirm = confirmPasswordEdit->text();
    QString fullName = fullNameEdit->text().trimmed();
    QString securityQuestion = securityQuestionEdit->text().trimmed();
    QString securityAnswer = securityAnswerEdit->text().trimmed();

    // ========== Validation ==========
    if (username.isEmpty() || password.isEmpty() || confirm.isEmpty() ||
        fullName.isEmpty() || securityQuestion.isEmpty() || securityAnswer.isEmpty()) {
        errorLabel->setText("All fields are required.");
        errorLabel->setVisible(true);
        return;
    }

    if (password != confirm) {
        errorLabel->setText("Passwords do not match.");
        errorLabel->setVisible(true);
        return;
    }

    if (password.length() < 4) {
        errorLabel->setText("Password must be at least 4 characters.");
        errorLabel->setVisible(true);
        return;
    }

    // ========== Register ==========
    bool success = authManager->registerUser(username, password, fullName,
                                             securityQuestion, securityAnswer);

    if (success) {
        QMessageBox::information(this, "Success", "Account created! Please login.");
        close(); // Go back to login page
    } else {
        errorLabel->setText("Username already exists or registration failed.");
        errorLabel->setVisible(true);
    }
}
