#include "loginpage.h"
#include "ui_loginpage.h"
#include <QMessageBox>

loginpage::loginpage(std::shared_ptr<AuthManager> authManager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::loginpage)
    , authManager(authManager)
{
    ui->setupUi(this);

    connect(ui->loginButton, &QPushButton::clicked, this, &loginpage::onLoginButtonClicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &loginpage::onRegisterButtonClicked);
}

loginpage::~loginpage()
{
    delete ui;
}

void loginpage::onLoginButtonClicked()
{
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        ui->errorLabel->setText("Please enter username and password.");
        ui->errorLabel->setVisible(true);
        return;
    }

    auto user = authManager->login(username, password);
    if (user) {
        QMessageBox::information(this, "Success", "Welcome " + user->getFullName());
    } else {
        ui->errorLabel->setText("Invalid username or password.");
        ui->errorLabel->setVisible(true);
    }
}

void loginpage::onRegisterButtonClicked()
{
    QMessageBox::information(this, "Register", "Registration page will be added soon!");
}
