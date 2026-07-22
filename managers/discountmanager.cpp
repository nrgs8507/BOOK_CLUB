#include "discountmanager.h"
#include "../models/percentdiscount.h"
#include "../models/timeddiscount.h"

DiscountManager::DiscountManager(BookManager* bookManager) : bookManager(bookManager) {}

void DiscountManager::applyPercentDiscount(int bookId, double percent) {
    Book book = bookManager->getBookById(bookId);
    book.setDiscount(std::make_shared<PercentDiscount>(percent));
    bookManager->updateBook(book);
}

void DiscountManager::applyTimedDiscount(int bookId, double percent, const QDate& startDate, const QDate& endDate) {
    Book book = bookManager->getBookById(bookId);
    book.setDiscount(std::make_shared<TimedDiscount>(percent, startDate, endDate));
    bookManager->updateBook(book);
}

void DiscountManager::removeDiscount(int bookId) {
    Book book = bookManager->getBookById(bookId);
    book.setDiscount(nullptr);
    bookManager->updateBook(book);
}

void DiscountManager::refreshExpiredDiscounts() {
    QVector<Book> allBooks = bookManager->getAllBooks();
    for (Book& book : allBooks) {
        auto discount = book.getDiscount();
        if (discount && !discount->isActive()) {
            book.setDiscount(nullptr);
            bookManager->updateBook(book);
        }
    }
}