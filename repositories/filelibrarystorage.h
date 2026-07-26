#pragma once
#include "filerepository.h"
#include "ilibrarystorage.h"
#include "../models/library.h"

class FileLibraryStorage : public FileRepository<Library>, public ILibraryStorage {
public:
    explicit FileLibraryStorage(const QString& path);

    Library getByUserId(int userId) override;
};