#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>  // <-- QWidget رو به QMainWindow تغییر بده
#include <memory>
#include "../auth/AuthManager.h"

namespace Ui {
class loginpage;
}

class loginpage : public QMainWindow  // <-- QWidget رو به QMainWindow تغییر بده
{
    Q_OBJECT

public:
    explicit loginpage(std::shared_ptr<AuthManager> authManager, QWidget *parent = nullptr);
    ~loginpage();

private slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();

private:
    Ui::loginpage *ui;
    std::shared_ptr<AuthManager> authManager;
};

#endif // LOGINPAGE_H