/*#include "loginpage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginpage w;
    w.show();
    return QApplication::exec();
}*/
#include <QCoreApplication>
#include <QDebug>
#include "src/auth/AuthManager.h"
#include "src/storage/FileAccountStorage.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto storage = std::make_shared<FileAccountStorage>("data/users.json");

    AuthManager auth(storage);

    bool registered = auth.registerUser("saba", "1234", "Saba Net", "What is your favorite book?", "C++");
    qDebug() << "Registration:" << (registered ? "Success ✅" : "Failed ❌");

    auto user = auth.login("saba", "1234");
    if (user) {
        qDebug() << "Login successful! Welcome" << user->getFullName() << "🎉";
    } else {
        qDebug() << "Login failed! ❌";
    }

    bool duplicate = auth.registerUser("saba", "5678", "Duplicate", "Question", "Answer");
    qDebug() << "Duplicate registration:" << (duplicate ? "Success ❌" : "Failed ✅ (correct behavior)");

    return a.exec();
}