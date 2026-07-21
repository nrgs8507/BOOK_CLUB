#ifndef USER_H
#define USER_H

#include "account.h"
#include <QList>
#include <QString>

class User : public Account {
public:
    User();
    User(const QString& username, const QString& hashedPassword,
         const QString& fullName, const QString& securityQuestion,
         const QString& hashedSecurityAnswer);

    // Getters & Setters
    QList<QString> getFavoriteGenres() const;
    void setFavoriteGenres(const QList<QString>& genres);
    void addFavoriteGenre(const QString& genre);
    void removeFavoriteGenre(const QString& genre);

    QString getRoleString() const override;

private:
    QList<QString> favoriteGenres;
};

#endif // USER_H
