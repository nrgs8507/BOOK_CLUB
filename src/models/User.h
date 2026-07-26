#ifndef USER_H
#define USER_H

#include "Account.h"
#include <QList>

class User : public Account {
public:
    User();
    User(int userId, const QString& username, const QString& hashedPassword,
         const QString& fullName, const QString& securityQuestion,
         const QString& hashedSecurityAnswer,
         const QList<QString>& favoriteGenres = {});

    QList<QString> getFavoriteGenres() const;
    void setFavoriteGenres(const QList<QString>& genres);
    void addFavoriteGenre(const QString& genre);
    void removeFavoriteGenre(const QString& genre);

    QString getRoleString() const override;

    // JSON Serialization
    QJsonObject toJson() const;
    static User fromJson(const QJsonObject& json);

private:
    QList<QString> favoriteGenres;
};

#endif // USER_H