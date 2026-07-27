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
#include "src/ui/loginpage.h"
#include "src/auth/AuthManager.h"
#include "src/storage/FileAccountStorage.h"
#include <memory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 1. Create storage and auth manager
    auto storage = std::make_shared<FileAccountStorage>("data/users.json");
    auto authManager = std::make_shared<AuthManager>(storage);

    // 2. Register a test user (if not exists)
    bool registered = authManager->registerUser(
        "saba",
        "1234",
        "Saba Net",
        "What is your favorite book?",
        "C++"
        );

    if (registered) {
        qDebug() << "Test user 'saba' registered successfully!";
    } else {
        qDebug() << "User 'saba' already exists.";
    }

    // 3. Show login page
    loginpage w(authManager);
    w.show();

    return a.exec();
}