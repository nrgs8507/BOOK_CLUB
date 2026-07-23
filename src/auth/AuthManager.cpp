#include "AuthManager.h"
#include <QCryptographicHash>

// Constructor
AuthManager::AuthManager(std::shared_ptr<IAccountStorage> storage)
    : storage(storage) {}

// ----- Helper: Hash Function -----
QString AuthManager::hashString(const QString& input) const
{
    QByteArray hash = QCryptographicHash::hash(input.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}

// ----- Register -----
bool AuthManager::registerUser(const QString& username, const QString& password,
                               const QString& fullName, const QString& securityQuestion,
                               const QString& securityAnswer)
{
    // 1. Check if username already exists
    if (storage->findUserByUsername(username) != nullptr) {
        return false; // Username taken
    }

    // 2. Hash password and security answer
    QString hashedPassword = hashString(password);
    QString hashedSecurityAnswer = hashString(securityAnswer);

    // 3. Create new User object
    User newUser(username, hashedPassword, fullName, securityQuestion, hashedSecurityAnswer);

    // 4. Save to storage
    return storage->saveUser(newUser);
}

// ----- Login -----
std::shared_ptr<User> AuthManager::login(const QString& username, const QString& password)
{
    // 1. Find user
    auto user = storage->findUserByUsername(username);
    if (!user) {
        return nullptr; // User not found
    }

    // 2. Check if user is blocked
    if (user->getIsBlocked()) {
        return nullptr; // User is blocked
    }

    // 3. Verify password
    QString hashedInput = hashString(password);
    if (user->getHashedPassword() != hashedInput) {
        return nullptr; // Wrong password
    }

    // 4. Login successful
    return user;
}

// ----- Forgot Password (Reset via Security Question) -----
bool AuthManager::forgotPassword(const QString& username, const QString& securityAnswer,
                                 const QString& newPassword)
{
    // 1. Find user
    auto user = storage->findUserByUsername(username);
    if (!user) {
        return false; // User not found
    }

    // 2. Verify security answer
    QString hashedInput = hashString(securityAnswer);
    if (user->getHashedSecurityAnswer() != hashedInput) {
        return false; // Wrong security answer
    }

    // 3. Update password
    QString newHashedPassword = hashString(newPassword);
    user->setHashedPassword(newHashedPassword);

    // 4. Save changes
    return storage->updateUser(*user);
}

// ----- Change Password (with old password verification) -----
bool AuthManager::changePassword(const QString& username, const QString& oldPassword,
                                 const QString& newPassword)
{
    // 1. Find user
    auto user = storage->findUserByUsername(username);
    if (!user) {
        return false; // User not found
    }

    // 2. Verify old password
    QString hashedOld = hashString(oldPassword);
    if (user->getHashedPassword() != hashedOld) {
        return false; // Wrong old password
    }

    // 3. Update to new password
    QString newHashedPassword = hashString(newPassword);
    user->setHashedPassword(newHashedPassword);

    // 4. Save changes
    return storage->updateUser(*user);
}

// ----- Check if username exists -----
bool AuthManager::usernameExists(const QString& username) const
{
    return storage->findUserByUsername(username) != nullptr;
}
