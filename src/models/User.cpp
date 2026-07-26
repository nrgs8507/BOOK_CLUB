#include "User.h"

User::User() : Account() {}

User::User(int userId, const QString& username, const QString& hashedPassword,
           const QString& fullName, const QString& securityQuestion,
           const QString& hashedSecurityAnswer,
           const QList<QString>& favoriteGenres)
    : Account(userId, username, hashedPassword, fullName, securityQuestion,
              hashedSecurityAnswer, Role::User, false, QDate::currentDate()),
    favoriteGenres(favoriteGenres) {}

QList<QString> User::getFavoriteGenres() const {
    return favoriteGenres;
}

void User::setFavoriteGenres(const QList<QString>& genres) {
    favoriteGenres = genres;
}

void User::addFavoriteGenre(const QString& genre) {
    if (!favoriteGenres.contains(genre)) {
        favoriteGenres.append(genre);
    }
}

void User::removeFavoriteGenre(const QString& genre) {
    favoriteGenres.removeAll(genre);
}

QString User::getRoleString() const {
    return "User";
}

QJsonObject User::toJson() const {
    QJsonObject json = Account::toJson();
    QJsonArray genresArray;
    for (const QString& genre : favoriteGenres) {
        genresArray.append(genre);
    }
    json["favoriteGenres"] = genresArray;
    return json;
}

User User::fromJson(const QJsonObject& json) {
    Account base = Account::fromJson(json);
    QList<QString> genres;
    QJsonArray genresArray = json["favoriteGenres"].toArray();
    for (const QJsonValue& val : genresArray) {
        genres.append(val.toString());
    }

    return User(base.getId(), base.getUsername(), base.getHashedPassword(),
                base.getFullName(), base.getSecurityQuestion(),
                base.getHashedSecurityAnswer(), genres);
}
