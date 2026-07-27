#include "loginpage.h"
#include "ui_loginpage.h"
#include "registerpage.h"
#include <QMessageBox>
#include <QDebug>
#include <QStyle>
#include <QScreen>
#include <QGuiApplication>

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
    qDebug() << "Register button clicked!";

    RegisterPage *registerPage = new RegisterPage(authManager, this);
    if (registerPage) {
        // تنظیم اندازه و موقعیت
        registerPage->setWindowTitle("Register");
        registerPage->resize(450, 700);
        registerPage->setWindowModality(Qt::ApplicationModal);

        registerPage->setGeometry(
            QStyle::alignedRect(
                Qt::LeftToRight,
                Qt::AlignCenter,
                registerPage->size(),
                qApp->primaryScreen()->availableGeometry()
                )
            );

        registerPage->show();
    } else {
        qDebug() << "Failed to create RegisterPage!";
    }
}

void loginpage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (ui->frame) {
        int x = (this->width() - ui->frame->width()) / 2;
        int y = (this->height() - ui->frame->height()) / 2;
        ui->frame->move(x, y);
    }
}

