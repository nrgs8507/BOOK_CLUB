/*#include "loginpage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginpage w;
    w.show();
    return QApplication::exec();
}*/
#include <QApplication>
#include <QDebug>
#include "src/ui/loginpage.h"
#include "src/ui/registerpage.h"
#include "src/auth/AuthManager.h"
#include "src/repository/filerepository.h"
#include "src/models/User.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto userRepo = std::make_shared<FileRepository<User>>("data/users.json");
    auto authManager = std::make_shared<AuthManager>(userRepo);

    // Register test user (if not exists)
    if (!authManager->usernameExists("saba")) {
        bool registered = authManager->registerUser(
            "saba", "1234", "Saba Net",
            "What is your favorite book?", "C++"
            );
        qDebug() << (registered ? "User registered!" : "Registration failed!");
    }

    // Show login page
    loginpage w(authManager);
    w.show();

    return a.exec();
}