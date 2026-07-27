#include "User.h"
#include "utils/cryptomanager.h"

User::User() : Account() {}

User::User(int userId, const QString& username, const QString& hashedPassword,
           const QString& fullName, const QString& securityQuestion,
           const QString& hashedSecurityAnswer,
           const QList<QString>& favoriteGenres,
           bool isBlocked,
           const QDate& registerDate)
    : Account(userId, username, hashedPassword, fullName,
              securityQuestion, hashedSecurityAnswer, Role::User,
              isBlocked, registerDate),
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
    int userId = json["userId"].toInt();
    QString username = CryptoManager::decryptTwoWay(json["encryptedUsername"].toString());
    QString hashedPassword = json["hashedPassword"].toString();
    QString fullName = CryptoManager::decryptTwoWay(json["encryptedFullName"].toString());
    QString securityQuestion = CryptoManager::decryptTwoWay(json["encryptedSecurityQuestion"].toString());
    QString hashedSecurityAnswer = json["hashedSecurityAnswer"].toString();
    bool isBlocked = json["isBlocked"].toBool(false);
    QDate registerDate = QDate::fromString(json["registerDate"].toString(), Qt::ISODate);

    QList<QString> favoriteGenres;
    QJsonArray genresArray = json["favoriteGenres"].toArray();
    for (const QJsonValue& val : genresArray) {
        favoriteGenres.append(val.toString());
    }

    return User(userId, username, hashedPassword, fullName,
                securityQuestion, hashedSecurityAnswer,
                favoriteGenres, isBlocked, registerDate);
}
