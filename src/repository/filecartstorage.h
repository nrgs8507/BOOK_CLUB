#pragma once
#include "filerepository.h"
#include "icartstorage.h"
#include "../models/cart.h"

class FileCartStorage : public FileRepository<Cart>, public ICartStorage {
public:
    explicit FileCartStorage(const QString& path);

    Cart getByUserId(int userId) override;
};