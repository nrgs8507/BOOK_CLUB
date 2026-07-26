#include "loginpage.h"
#include "ui_loginpage.h"
#include <QMessageBox>

LoginPage::LoginPage(std::shared_ptr<AuthManager> authManager, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginPage)
    , authManager(authManager)
{
    ui->setupUi(this);

    // Connect buttons to slots
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginPage::onLoginButtonClicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &LoginPage::onRegisterButtonClicked);
}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::onLoginButtonClicked()
{
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter username and password.");
        return;
    }

    auto user = authManager->login(username, password);
    if (user) {
        QMessageBox::information(this, "Success", "Welcome " + user->getFullName());
        // Here you can open the next page (e.g., MainWindow)
    } else {
        QMessageBox::warning(this, "Error", "Invalid username or password.");
    }
}

void LoginPage::onRegisterButtonClicked()
{
    // For now, we show a placeholder message
    QMessageBox::information(this, "Register", "Registration page will be added soon!");
}