#include "Account.h"
#include "utils/cryptomanager.h"
#include <QCryptographicHash>


static int nextUserId = 1;

Account::Account()
    : userId(0), role(Role::User), isBlocked(false), registerDate(QDate::currentDate()) {}

Account::Account(int userId, const QString& username, const QString& hashedPassword,
                 const QString& fullName, const QString& securityQuestion,
                 const QString& hashedSecurityAnswer, Role role,
                 bool isBlocked, const QDate& registerDate)
    : userId(userId),
    username(username),
    hashedPassword(hashedPassword),
    encryptedFullName(CryptoManager::encryptTwoWay(fullName)),
    encryptedSecurityQuestion(CryptoManager::encryptTwoWay(securityQuestion)),
    hashedSecurityAnswer(hashedSecurityAnswer),
    role(role),
    isBlocked(isBlocked),
    registerDate(registerDate) {}

int Account::getId() const {
    return userId;
}

QString Account::getUsername() const { return username; }
QString Account::getHashedPassword() const { return hashedPassword; }
QString Account::getFullName() const {
    return CryptoManager::decryptTwoWay(encryptedFullName);
}
QString Account::getSecurityQuestion() const {
    return CryptoManager::decryptTwoWay(encryptedSecurityQuestion);
}
QString Account::getHashedSecurityAnswer() const { return hashedSecurityAnswer; }
Role Account::getRole() const { return role; }
bool Account::getIsBlocked() const { return isBlocked; }
QDate Account::getRegisterDate() const { return registerDate; }

void Account::setHashedPassword(const QString& newPassword) {
    hashedPassword = newPassword;
}
void Account::setFullName(const QString& fullName) {
    encryptedFullName = CryptoManager::encryptTwoWay(fullName);
}
void Account::setSecurityQuestion(const QString& question) {
    encryptedSecurityQuestion = CryptoManager::encryptTwoWay(question);
}
void Account::setHashedSecurityAnswer(const QString& answer) {
    hashedSecurityAnswer = answer;
}
void Account::setBlocked(bool blocked) {
    isBlocked = blocked;
}

QString Account::getRoleString() const {
    switch(role) {
    case Role::User: return "User";
    case Role::Publisher: return "Publisher";
    case Role::Admin: return "Admin";
    default: return "Unknown";
    }
}

// ---------- JSON Serialization ----------
QJsonObject Account::toJson() const {
    QJsonObject json;
    json["userId"] = userId;
    json["username"] = username;
    json["hashedPassword"] = hashedPassword;
    json["encryptedFullName"] = encryptedFullName;
    json["encryptedSecurityQuestion"] = encryptedSecurityQuestion;
    json["hashedSecurityAnswer"] = hashedSecurityAnswer;
    json["role"] = getRoleString();
    json["isBlocked"] = isBlocked;
    json["registerDate"] = registerDate.toString(Qt::ISODate);
    return json;
}

Account Account::fromJson(const QJsonObject& json) {
    int userId = json["userId"].toInt();
    QString username = json["username"].toString();
    QString hashedPassword = json["hashedPassword"].toString();
    QString encryptedFullName = json["encryptedFullName"].toString();
    QString encryptedSecurityQuestion = json["encryptedSecurityQuestion"].toString();
    QString hashedSecurityAnswer = json["hashedSecurityAnswer"].toString();
    QString roleStr = json["role"].toString("User");
    bool isBlocked = json["isBlocked"].toBool(false);
    QDate registerDate = QDate::fromString(json["registerDate"].toString(), Qt::ISODate);

    Role role;
    if (roleStr == "Publisher") role = Role::Publisher;
    else if (roleStr == "Admin") role = Role::Admin;
    else role = Role::User;

    // Create a temporary Account with all fields
    Account acc;
    acc.userId = userId;
    acc.username = username;
    acc.hashedPassword = hashedPassword;
    acc.encryptedFullName = encryptedFullName;
    acc.encryptedSecurityQuestion = encryptedSecurityQuestion;
    acc.hashedSecurityAnswer = hashedSecurityAnswer;
    acc.role = role;
    acc.isBlocked = isBlocked;
    acc.registerDate = registerDate;

    return acc;
}
