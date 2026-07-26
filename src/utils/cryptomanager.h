#ifndef CRYPTOMANAGER_H
#define CRYPTOMANAGER_H

#include <QString>

class CryptoManager {
public:
    static QString hashOneWay(const QString& input);
    static QString encryptTwoWay(const QString& plainText);
    static QString decryptTwoWay(const QString& cipherText);

private:
    static QString getEncryptionKey();
};

#endif // CRYPTOMANAGER_H