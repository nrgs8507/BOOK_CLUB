#pragma once
#include "bookmanager.h"
#include <QDate>

class DiscountManager {
private:
    BookManager* bookManager;

public:
    explicit DiscountManager(BookManager* bookManager);

    void applyPercentDiscount(int bookId, double percent);
    void applyTimedDiscount(int bookId, double percent, const QDate& startDate, const QDate& endDate);
    void removeDiscount(int bookId);
    void refreshExpiredDiscounts();
};