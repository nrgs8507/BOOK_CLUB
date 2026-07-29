#include "filecartstorage.h"

FileCartStorage::FileCartStorage(const QString& path)
    : FileRepository<Cart>(path) {}

Cart FileCartStorage::getByUserId(int userId) {
    for (const Cart& c : getAll()) {
        if (c.getUserId() == userId) {
            return c;
        }
    }
    return Cart(-1, userId); }