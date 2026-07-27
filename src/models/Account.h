#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QDate>
#include <QJsonObject>
#include <QJsonArray>

enum class Role {
    User,
    Publisher,
    Admin
};

class Account {
public:
    Account();
    Account(int userId, const QString& username, const QString& hashedPassword,
            const QString& fullName, const QString& securityQuestion,
            const QString& hashedSecurityAnswer, Role role = Role::User,
            bool isBlocked = false, const QDate& registerDate = QDate::currentDate());

    // Getters
    int getId() const;
    QString getUsername() const;
    QString getHashedPassword() const;
    QString getFullName() const;
    QString getSecurityQuestion() const;
    QString getHashedSecurityAnswer() const;
    Role getRole() const;
    bool getIsBlocked() const;
    QDate getRegisterDate() const;

    // Setters
    void setHashedPassword(const QString& newPassword);
    void setFullName(const QString& fullName);
    void setSecurityQuestion(const QString& question);
    void setHashedSecurityAnswer(const QString& answer);
    void setBlocked(bool blocked);
    void setRegisterDate(const QDate& date);

    virtual QString getRoleString() const;

    // JSON
    QJsonObject toJson() const;
    static Account fromJson(const QJsonObject& json);

protected:
    int userId;
    QString encryptedUsername;
    QString hashedPassword;
    QString encryptedFullName;
    QString encryptedSecurityQuestion;
    QString hashedSecurityAnswer;
    Role role;
    bool isBlocked;
    QDate registerDate;
};

#endif // ACCOUNT_H
