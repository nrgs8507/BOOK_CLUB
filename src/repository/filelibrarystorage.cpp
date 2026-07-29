#include "filelibrarystorage.h"

FileLibraryStorage::FileLibraryStorage(const QString& path)
    : FileRepository<Library>(path) {}

Library FileLibraryStorage::getByUserId(int userId) {
    for (const Library& lib : getAll()) {
        if (lib.getUserId() == userId) {
            return lib;
        }
    }
    return Library(-1, userId);
}