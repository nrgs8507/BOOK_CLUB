#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QString>
#include <memory>
#include "../storage/IAccountStorage.h"
#include "../models/User.h"

class AuthManager
{
public:
    // Constructor: receives a storage object (dependency injection)
    AuthManager(std::shared_ptr<IAccountStorage> storage);

    // ----- Core Functions -----

    // Register a new user
    bool registerUser(const QString& username, const QString& password,
                      const QString& fullName, const QString& securityQuestion,
                      const QString& securityAnswer);

    // Login user
    std::shared_ptr<User> login(const QString& username, const QString& password);

    // Forgot password: verify security answer, then reset password
    bool forgotPassword(const QString& username, const QString& securityAnswer,
                        const QString& newPassword);

    // Change password: verify old password, then set new password
    bool changePassword(const QString& username, const QString& oldPassword,
                        const QString& newPassword);

    // Check if a username already exists
    bool usernameExists(const QString& username) const;

private:
    std::shared_ptr<IAccountStorage> storage;

    // Helper: hash a string using SHA-256
    QString hashString(const QString& input) const;
};

#endif // AUTHMANAGER_H
