#include "AuthManager.h"
#include "utils/cryptomanager.h"
#include <QCryptographicHash>

AuthManager::AuthManager(std::shared_ptr<FileRepository<User>> userRepository)
    : userRepository(userRepository) {}

QString AuthManager::hashString(const QString& input) const {
    QByteArray hash = QCryptographicHash::hash(input.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}

bool AuthManager::registerUser(const QString& username, const QString& password,
                               const QString& fullName, const QString& securityQuestion,
                               const QString& securityAnswer) {
    if (usernameExists(username)) {
        return false;
    }

    QString hashedPassword = hashString(password);
    QString hashedSecurityAnswer = CryptoManager::encryptTwoWay(securityAnswer);

    static int nextUserId = 1;
    int userId = nextUserId++;

    User newUser(userId, username, hashedPassword, fullName,
                 securityQuestion, hashedSecurityAnswer, {});
    userRepository->save(newUser);
    return true;
}

std::shared_ptr<User> AuthManager::login(const QString& username, const QString& password) {
    QVector<User> allUsers = userRepository->getAll();
    for (const User& user : allUsers) {
        if (user.getUsername() == username) {
            if (user.getIsBlocked()) {
                return nullptr;
            }
            QString hashedInput = hashString(password);
            if (user.getHashedPassword() == hashedInput) {
                return std::make_shared<User>(user);
            }
            return nullptr;
        }
    }
    return nullptr;
}

bool AuthManager::forgotPassword(const QString& username, const QString& securityAnswer,
                                 const QString& newPassword) {
    QVector<User> allUsers = userRepository->getAll();
    for (int i = 0; i < allUsers.size(); ++i) {
        if (allUsers[i].getUsername() == username) {
            QString hashedInput = CryptoManager::encryptTwoWay(securityAnswer);
            if (allUsers[i].getHashedSecurityAnswer() != hashedInput) {
                return false;
            }
            QString newHashedPassword = hashString(newPassword);
            allUsers[i].setHashedPassword(newHashedPassword);
            userRepository->save(allUsers[i]);
            return true;
        }
    }
    return false;
}

bool AuthManager::changePassword(const QString& username, const QString& oldPassword,
                                 const QString& newPassword) {
    QVector<User> allUsers = userRepository->getAll();
    for (int i = 0; i < allUsers.size(); ++i) {
        if (allUsers[i].getUsername() == username) {
            QString hashedOld = hashString(oldPassword);
            if (allUsers[i].getHashedPassword() != hashedOld) {
                return false;
            }
            QString newHashedPassword = hashString(newPassword);
            allUsers[i].setHashedPassword(newHashedPassword);
            userRepository->save(allUsers[i]);
            return true;
        }
    }
    return false;
}

bool AuthManager::usernameExists(const QString& username) const {
    QVector<User> allUsers = userRepository->getAll();
    for (const User& user : allUsers) {
        if (user.getUsername() == username) {
            return true;
        }
    }
    return false;
}

std::shared_ptr<User> AuthManager::findUser(const QString& username) const
{
    QVector<User> allUsers = userRepository->getAll();
    for (const User& user : allUsers) {
        if (user.getUsername() == username) {
            return std::make_shared<User>(user);
        }
    }
    return nullptr;
}
