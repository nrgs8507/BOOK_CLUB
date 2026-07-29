#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>
#include <memory>
#include "registerpage.h"
#include "../auth/AuthManager.h"
#include "../network/networkclient.h"
#include "../ui/searchbookpage.h"
#include "../ui/searchresultspage.h"
#include <QResizeEvent>
#include <QJsonObject>

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
    void onForgotPasswordClicked();
    void onLoginResponse(const QJsonObject &response);

private:
    Ui::loginpage *ui;
    std::shared_ptr<AuthManager> authManager;
    NetworkClient *networkClient;

protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // LOGINPAGE_H