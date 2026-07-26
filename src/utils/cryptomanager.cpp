#include "cryptomanager.h"
#include <QCryptographicHash>
#include <QByteArray>

QString CryptoManager::getEncryptionKey() {
    return "MySuperSecretKey123!";
}

QString CryptoManager::hashOneWay(const QString& input) {
    QByteArray hash = QCryptographicHash::hash(input.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}

QString CryptoManager::encryptTwoWay(const QString& plainText) {
    QByteArray key = getEncryptionKey().toUtf8();
    QByteArray data = plainText.toUtf8();
    for (int i = 0; i < data.size(); ++i) {
        data[i] = data[i] ^ key[i % key.size()];
    }
    return QString(data.toBase64());
}

QString CryptoManager::decryptTwoWay(const QString& cipherText) {
    QByteArray key = getEncryptionKey().toUtf8();
    QByteArray data = QByteArray::fromBase64(cipherText.toUtf8());
    for (int i = 0; i < data.size(); ++i) {
        data[i] = data[i] ^ key[i % key.size()];
    }
    return QString(data);
}