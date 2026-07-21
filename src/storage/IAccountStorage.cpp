#ifndef IACCOUNTSTORAGE_H
#define IACCOUNTSTORAGE_H

#include <QList>
#include <memory>
#include "../models/account.h"
#include "../models/User.h"

class IAccountStorage {
public:
    virtual ~IAccountStorage() = default;

    virtual bool saveUser(const User& user) = 0;
    virtual std::shared_ptr<User> findUserByUsername(const QString& username) const = 0;
    virtual bool updateUser(const User& user) = 0;
    virtual bool deleteUser(const QString& username) = 0;
    virtual QList<std::shared_ptr<User>> getAllUsers() const = 0;
};

#endif // IACCOUNTSTORAGE_H