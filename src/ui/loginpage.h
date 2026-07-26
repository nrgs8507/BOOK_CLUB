#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include <memory>
#include "../auth/AuthManager.h"

namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(std::shared_ptr<AuthManager> authManager, QWidget *parent = nullptr);
    ~LoginPage();

private slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();

private:
    Ui::LoginPage *ui;
    std::shared_ptr<AuthManager> authManager;
};

#endif // LOGINPAGE_H