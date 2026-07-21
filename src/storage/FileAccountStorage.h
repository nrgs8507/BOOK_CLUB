#ifndef FILEACCOUNTSTORAGE_H
#define FILEACCOUNTSTORAGE_H

#include "IAccountStorage.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

class FileAccountStorage : public IAccountStorage {
public:
    FileAccountStorage(const QString& filePath = "data/users.json");

    bool saveUser(const User& user) override;
    std::shared_ptr<User> findUserByUsername(const QString& username) const override;
    bool updateUser(const User& user) override;
    bool deleteUser(const QString& username) override;
    QList<std::shared_ptr<User>> getAllUsers() const override;

private:
    QString filePath;

    QJsonArray loadAllFromFile() const;
    bool saveAllToFile(const QJsonArray& usersArray) const;
    QJsonObject userToJson(const User& user) const;
    User jsonToUser(const QJsonObject& json) const;
};

#endif // FILEACCOUNTSTORAGE_H
