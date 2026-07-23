#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QDate>

enum class Role {
    User,
    Publisher,
    Admin
};

class Account {
public:
    Account();
    Account(const QString& username, const QString& hashedPassword,
            Role role, const QString& fullName,
            const QString& securityQuestion, const QString& hashedSecurityAnswer);

    // Getters
    QString getUsername() const;
    QString getHashedPassword() const;
    Role getRole() const;
    bool getIsBlocked() const;
    QDate getRegisterDate() const;
    QString getFullName() const;
    QString getSecurityQuestion() const;
    QString getHashedSecurityAnswer() const;

    // Setters
    void setHashedPassword(const QString& newPassword);
    void setBlocked(bool blocked);
    void setFullName(const QString& fullName);
    void setSecurityQuestion(const QString& question);
    void setHashedSecurityAnswer(const QString& answer);

    // Utility
    virtual QString getRoleString() const;

protected:
    QString username;
    QString hashedPassword;
    Role role;
    bool isBlocked;
    QDate registerDate;
    QString fullName;
    QString securityQuestion;
    QString hashedSecurityAnswer;
};

#endif // ACCOUNT_H
