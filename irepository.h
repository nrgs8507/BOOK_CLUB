#pragma once
#include <QVector>

// این یک Interface عمومی است. هر نوع T (مثل Account، Book، Cart) می‌تواند
// از این استفاده کند، به شرطی که سه متد getId/toJson/fromJson را داشته باشد.
template <typename T>
class IRepository {
public:
    virtual ~IRepository() = default;

    virtual T getById(int id) = 0;
    virtual QVector<T> getAll() = 0;
    virtual void save(const T& item) = 0;
    virtual void remove(int id) = 0;
};
