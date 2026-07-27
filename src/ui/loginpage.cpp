#include "loginpage.h"
#include "ui_loginpage.h"
#include "registerpage.h"
#include "forgotpasswordpage.h"
#include <QMessageBox>
#include <QDebug>
#include <QStyle>
#include <QScreen>
#include <QGuiApplication>

/*loginpage::loginpage(std::shared_ptr<AuthManager> authManager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::loginpage)
    , authManager(authManager)
{
    ui->setupUi(this);

    // دکمه‌ی فراموشی رمز
    QPushButton *forgotButton = new QPushButton("Forgot Password?", this);
    forgotButton->setObjectName("forgotButton");
    forgotButton->setStyleSheet("background: none; color: #6C63FF; text-decoration: underline;");
    ui->loginpage->addWidget(forgotButton);
    connect(forgotButton, &QPushButton::clicked, this, &loginpage::onForgotPasswordClicked);


    connect(ui->loginButton, &QPushButton::clicked, this, &loginpage::onLoginButtonClicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &loginpage::onRegisterButtonClicked);
}*/
loginpage::loginpage(std::shared_ptr<AuthManager> authManager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::loginpage)
    , authManager(authManager)
{
    ui->setupUi(this);

    // اتصال دکمه‌های موجود در ui
    connect(ui->loginButton, &QPushButton::clicked, this, &loginpage::onLoginButtonClicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &loginpage::onRegisterButtonClicked);

    // ========== دکمه‌ی فراموشی رمز (ساخت دستی با ظاهر لینک) ==========
    QPushButton *forgotButton = new QPushButton("Forgot Password?", this);
    forgotButton->setObjectName("forgotButton");
    forgotButton->setStyleSheet(
        "QPushButton#forgotButton {"
        "    background: none;"
        "    color: #6C63FF;"
        "    text-decoration: underline;"
        "    border: none;"
        "    font-size: 13px;"
        "}"
        "QPushButton#forgotButton:hover {"
        "    color: #7C73FF;"
        "}"
        );

    // پیدا کردن layout اصلی که دکمه‌های Login و Register داخل آن هستند
    QLayout *mainLayout = this->layout();
    if (mainLayout) {
        mainLayout->addWidget(forgotButton);
    } else {
        // اگر به هر دلیلی layout وجود نداشت، یک layout جدید بساز
        QVBoxLayout *newLayout = new QVBoxLayout(this);
        newLayout->addWidget(forgotButton);
    }

    connect(forgotButton, &QPushButton::clicked, this, &loginpage::onForgotPasswordClicked);
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

void loginpage::onForgotPasswordClicked()
{
    ForgotPasswordPage *forgotPage = new ForgotPasswordPage(authManager, this);

    // ========== وسط‌چین کردن ==========
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - forgotPage->width()) / 2;
    int y = (screenGeometry.height() - forgotPage->height()) / 2;
    forgotPage->move(x, y);

    forgotPage->setWindowTitle("Reset Password");
    forgotPage->resize(400, 500);
    forgotPage->show();
}
