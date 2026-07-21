#include "User.h"

User::User() : Account() {
    role = Role::User;
}

User::User(const QString& username, const QString& hashedPassword,
           const QString& fullName, const QString& securityQuestion,
           const QString& hashedSecurityAnswer)
    : Account(username, hashedPassword, Role::User, fullName,
              securityQuestion, hashedSecurityAnswer) {}

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
