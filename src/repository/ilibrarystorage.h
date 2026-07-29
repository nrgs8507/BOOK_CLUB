#pragma once
#include "irepository.h"
#include "../models/library.h"

class ILibraryStorage : public virtual IRepository<Library> {
public:
    virtual ~ILibraryStorage() = default;

    virtual Library getByUserId(int userId) = 0;
};