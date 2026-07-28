#include "StatsService.h"
#include <algorithm>

StatsService::StatsService(BookManager* bookManager, TransactionManager* transactionManager)
    : bookManager(bookManager), transactionManager(transactionManager) {}

QVector<Book> StatsService::getTopSellingBooks(int publisherId, int count) {
    QVector<Book> all = bookManager->getAllBooks();
    QVector<Book> byPublisher;
    for (const Book& b : all) {
        if (b.getPublisherId() == publisherId) byPublisher.append(b);
    }

    std::sort(byPublisher.begin(), byPublisher.end(), [](const Book& a, const Book& b) {
        return a.getSalesCount() > b.getSalesCount(); // نزولی
    });

    if (byPublisher.size() > count) byPublisher.resize(count);
    return byPublisher;
}

QVector<Book> StatsService::getLowSellingBooks(int publisherId, int count) {
    QVector<Book> all = bookManager->getAllBooks();
    QVector<Book> byPublisher;
    for (const Book& b : all) {
        if (b.getPublisherId() == publisherId) byPublisher.append(b);
    }

    std::sort(byPublisher.begin(), byPublisher.end(), [](const Book& a, const Book& b) {
        return a.getSalesCount() < b.getSalesCount(); // صعودی
    });

    if (byPublisher.size() > count) byPublisher.resize(count);
    return byPublisher;
}

double StatsService::getTotalRevenue(int publisherId) {
    QVector<Book> all = bookManager->getAllBooks();
    double total = 0.0;
    for (const Book& b : all) {
        if (b.getPublisherId() == publisherId) {
            total += transactionManager->getTotalRevenueForBook(b.getId());
        }
    }
    return total;
}

int StatsService::getTotalPublishedBooks(int publisherId) {
    QVector<Book> all = bookManager->getAllBooks();
    int count = 0;
    for (const Book& b : all) {
        if (b.getPublisherId() == publisherId) count++;
    }
    return count;
}