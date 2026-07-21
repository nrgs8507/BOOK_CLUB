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
#include "src/models/User.h"
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    User user("saba", "hashed123", "Saba Net", "What is your favorite book?", "hashedAnswer");
    qDebug() << "Username:" << user.getUsername();
    qDebug() << "Role:" << user.getRoleString();
    qDebug() << "Register Date:" << user.getRegisterDate().toString();

    return a.exec();
}
