#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QString>
#include <memory>
#include "../repository/filerepository.h"
#include "../models/User.h"

class AuthManager {
public:
    AuthManager(std::shared_ptr<FileRepository<User>> userRepository);

    bool registerUser(const QString& username, const QString& password,
                      const QString& fullName, const QString& securityQuestion,
                      const QString& securityAnswer);

    std::shared_ptr<User> login(const QString& username, const QString& password);

    bool forgotPassword(const QString& username, const QString& securityAnswer,
                        const QString& newPassword);

    bool changePassword(const QString& username, const QString& oldPassword,
                        const QString& newPassword);

    bool usernameExists(const QString& username) const;

private:
    std::shared_ptr<FileRepository<User>> userRepository;
    QString hashString(const QString& input) const;
};

#endif // AUTHMANAGER_H
