#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>
#include <memory>
#include "registerpage.h"
#include "../auth/AuthManager.h"
#include <QResizeEvent>

namespace Ui {
class loginpage;
}

class loginpage : public QMainWindow
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

protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // LOGINPAGE_H