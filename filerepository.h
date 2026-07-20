#pragma once
#include "irepository.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <stdexcept>

// پیاده‌سازی عمومی IRepository<T> با استفاده از یک فایل JSON.
// نیازمندی‌های T: getId() const, toJson() const, static T fromJson(QJsonObject)
template <typename T>
class FileRepository : public IRepository<T> {
protected:
    QString filePath;

public:
    explicit FileRepository(const QString& path) : filePath(path) {}

    QVector<T> getAll() override {
        QVector<T> result;
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {
            return result; // فایل هنوز وجود ندارد -> لیست خالی
        }
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonArray array = doc.array();
        for (const QJsonValue& val : array) {
            result.append(T::fromJson(val.toObject()));
        }
        return result;
    }

    T getById(int id) override {
        QVector<T> all = getAll();
        for (const T& item : all) {
            if (item.getId() == id) return item;
        }
        throw std::runtime_error("Item not found");
    }

    void save(const T& item) override {
        QVector<T> all = getAll();
        bool found = false;
        for (int i = 0; i < all.size(); i++) {
            if (all[i].getId() == item.getId()) {
                all[i] = item;
                found = true;
                break;
            }
        }
        if (!found) all.append(item);
        writeAll(all);
    }

    void remove(int id) override {
        QVector<T> all = getAll();
        for (int i = 0; i < all.size(); i++) {
            if (all[i].getId() == id) {
                all.removeAt(i);
                break;
            }
        }
        writeAll(all);
    }

private:
    void writeAll(const QVector<T>& items) {
        QJsonArray array;
        for (const T& item : items) {
            array.append(item.toJson());
        }
        QJsonDocument doc(array);
        QFile file(filePath);
        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        file.write(doc.toJson());
        file.close();
    }
};
