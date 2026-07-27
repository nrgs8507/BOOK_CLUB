#pragma once
#include <QVector>

template <typename T>
class IRepository {
public:
    virtual ~IRepository() = default;

    virtual T getById(int id) = 0;
    virtual QVector<T> getAll() = 0;
    virtual void save(const T& item) = 0;
    virtual void remove(int id) = 0;
};