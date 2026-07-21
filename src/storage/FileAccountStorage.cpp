#include "FileAccountStorage.h"
#include <QJsonArray>
#include <QCryptographicHash>

FileAccountStorage::FileAccountStorage(const QString& filePath)
    : filePath(filePath) {}

QJsonArray FileAccountStorage::loadAllFromFile() const {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QJsonArray();
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isArray()) {
        return QJsonArray();
    }

    return doc.array();
}

bool FileAccountStorage::saveAllToFile(const QJsonArray& usersArray) const {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error opening file for writing: " << filePath;
        return false;
    }

    QJsonDocument doc(usersArray);
    file.write(doc.toJson());
    file.close();
    return true;
}

QJsonObject FileAccountStorage::userToJson(const User& user) const {
    QJsonObject json;
    json["username"] = user.getUsername();
    json["hashedPassword"] = user.getHashedPassword();
    json["role"] = user.getRoleString();
    json["isBlocked"] = user.getisBlocked();
    json["registerDate"] = user.getRegisterDate().toString(Qt::ISODate);
    json["fullName"] = user.getFullName();
    json["securityQuestion"] = user.getSecurityQuestion();
    json["hashedSecurityAnswer"] = user.getHashedSecurityAnswer();
    json["favoriteGenres"] = QJsonArray::fromStringList(user.getFavoriteGenres());
    return json;
}

User FileAccountStorage::jsonToUser(const QJsonObject& json) const {
    User user(
        json["username"].toString(),
        json["hashedPassword"].toString(),
        json["fullName"].toString(),
        json["securityQuestion"].toString(),
        json["hashedSecurityAnswer"].toString()
        );

    if (json["isBlocked"].toBool()) {
        user.setBlocked(true);
    }

    if (json.contains("registerDate")) {
        QDate date = QDate::fromString(json["registerDate"].toString(), Qt::ISODate);
        // Note: registerDate is protected, we might need a setter or workaround
        // For now, we just keep the default
    }

    QStringList genres;
    QJsonArray genresArray = json["favoriteGenres"].toArray();
    for (const QJsonValue& val : genresArray) {
        genres << val.toString();
    }
    user.setFavoriteGenres(genres);

    return user;
}

bool FileAccountStorage::saveUser(const User& user) {
    QJsonArray usersArray = loadAllFromFile();

    // Check if username already exists
    for (int i = 0; i < usersArray.size(); ++i) {
        QJsonObject obj = usersArray[i].toObject();
        if (obj["username"].toString() == user.getUsername()) {
            return false; // User already exists
        }
    }

    QJsonObject newUserJson = userToJson(user);
    usersArray.append(newUserJson);
    return saveAllToFile(usersArray);
}

std::shared_ptr<User> FileAccountStorage::findUserByUsername(const QString& username) const {
    QJsonArray usersArray = loadAllFromFile();
    for (const QJsonValue& val : usersArray) {
        QJsonObject obj = val.toObject();
        if (obj["username"].toString() == username) {
            User user = jsonToUser(obj);
            return std::make_shared<User>(user);
        }
    }
    return nullptr;
}

bool FileAccountStorage::updateUser(const User& user) {
    QJsonArray usersArray = loadAllFromFile();
    bool found = false;

    for (int i = 0; i < usersArray.size(); ++i) {
        QJsonObject obj = usersArray[i].toObject();
        if (obj["username"].toString() == user.getUsername()) {
            usersArray[i] = userToJson(user);
            found = true;
            break;
        }
    }

    if (!found) return false;
    return saveAllToFile(usersArray);
}

bool FileAccountStorage::deleteUser(const QString& username) {
    QJsonArray usersArray = loadAllFromFile();
    bool found = false;
    for (int i = 0; i < usersArray.size(); ++i) {
        QJsonObject obj = usersArray[i].toObject();
        if (obj["username"].toString() == username) {
            usersArray.removeAt(i);
            found = true;
            break;
        }
    }

    if (!found) return false;
    return saveAllToFile(usersArray);
}

QList<std::shared_ptr<User>> FileAccountStorage::getAllUsers() const {
    QList<std::shared_ptr<User>> users;
    QJsonArray usersArray = loadAllFromFile();

    for (const QJsonValue& val : usersArray) {
        QJsonObject obj = val.toObject();
        User user = jsonToUser(obj);
        users.append(std::make_shared<User>(user));
    }

    return users;
}
