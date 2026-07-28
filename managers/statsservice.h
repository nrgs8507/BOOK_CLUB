#pragma once
#include "BookManager.h"
#include "TransactionManager.h"
#include <QVector>

struct BookSalesInfo {
    int bookId;
    QString title;
    int salesCount;
    double revenue;
};

class StatsService {
private:
    BookManager* bookManager;
    TransactionManager* transactionManager;

public:
    StatsService(BookManager* bookManager, TransactionManager* transactionManager);

    // بخش 3-3 داک: داشبورد آمار ناشر
    QVector<Book> getTopSellingBooks(int publisherId, int count = 5);
    QVector<Book> getLowSellingBooks(int publisherId, int count = 5);
    double getTotalRevenue(int publisherId);
    int getTotalPublishedBooks(int publisherId);
};
