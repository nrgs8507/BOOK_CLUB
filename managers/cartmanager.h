#pragma once
#include "../repositories/icartstorage.h"
#include "bookmanager.h"
#include "discountmanager.h"
#include "../models/cart.h"
#include <QVector>

class LibraryManager;
class TransactionManager;

class CartManager {
private:
    ICartStorage* storage;
    BookManager* bookManager;
    LibraryManager* libraryManager;
    TransactionManager* transactionManager;
    DiscountManager* discountManager;

    int generateNewId() const;
    Cart getOrCreateCart(int userId);

public:
    CartManager(ICartStorage* storage, BookManager* bookManager,
                LibraryManager* libraryManager, TransactionManager* transactionManager,
                DiscountManager* discountManager);

    void addBookToCart(int userId, int bookId);
    void removeBookFromCart(int userId, int bookId);
    QVector<Book> getCartItems(int userId);
    double getCartTotal(int userId);
    void clearCart(int userId);

    bool checkout(int userId);
};