#include "Account.h"
#include <QCryptographicHash>

Account::Account()
    : role(Role::User), isBlocked(false), registerDate(QDate::currentDate()) {}

Account::Account(const QString& username, const QString& hashedPassword,
                 Role role, const QString& fullName,
                 const QString& securityQuestion, const QString& hashedSecurityAnswer)
    : username(username), hashedPassword(hashedPassword), role(role),
    isBlocked(false), registerDate(QDate::currentDate()),
    fullName(fullName), securityQuestion(securityQuestion),
    hashedSecurityAnswer(hashedSecurityAnswer) {}

// Getters
QString Account::getUsername() const { return username; }
QString Account::getHashedPassword() const { return hashedPassword; }
Role Account::getRole() const { return role; }
bool Account::getisBlocked() const { return isBlocked; }
QDate Account::getRegisterDate() const { return registerDate; }
QString Account::getFullName() const { return fullName; }
QString Account::getSecurityQuestion() const { return securityQuestion; }
QString Account::getHashedSecurityAnswer() const { return hashedSecurityAnswer; }

// Setters
void Account::setHashedPassword(const QString& newPassword) {
    hashedPassword = newPassword;
}

void Account::setBlocked(bool blocked) {
    isBlocked = blocked;
}

void Account::setFullName(const QString& fullName) {
    this->fullName = fullName;
}

void Account::setSecurityQuestion(const QString& question) {
    securityQuestion = question;
}

void Account::setHashedSecurityAnswer(const QString& answer) {
    hashedSecurityAnswer = answer;
}

QString Account::getRoleString() const {
    switch(role) {
    case Role::User: return "User";
    case Role::Publisher: return "Publisher";
    case Role::Admin: return "Admin";
    default: return "Unknown";
    }
}
