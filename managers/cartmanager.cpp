#include "cartmanager.h"
#include <algorithm>

CartManager::CartManager(ICartStorage* storage, BookManager* bookManager,
                         LibraryManager* libraryManager, TransactionManager* transactionManager,
                         DiscountManager* discountManager)
    : storage(storage), bookManager(bookManager), libraryManager(libraryManager),
    transactionManager(transactionManager), discountManager(discountManager) {}

int CartManager::generateNewId() const {
    QVector<Cart> all = storage->getAll();
    int maxId = 0;
    for (const Cart& c : all) {
        maxId = std::max(maxId, c.getId());
    }
    return maxId + 1;
}

Cart CartManager::getOrCreateCart(int userId) {
    Cart cart = storage->getByUserId(userId);
    if (cart.getId() == -1) {
        int newId = generateNewId();
        Cart newCart(newId, userId);
        storage->save(newCart);
        return newCart;
    }
    return cart;
}

void CartManager::addBookToCart(int userId, int bookId) {
    Cart cart = getOrCreateCart(userId);
    cart.addBook(bookId);
    storage->save(cart);
}

void CartManager::removeBookFromCart(int userId, int bookId) {
    Cart cart = getOrCreateCart(userId);
    cart.removeBook(bookId);
    storage->save(cart);
}

QVector<Book> CartManager::getCartItems(int userId) {
    Cart cart = getOrCreateCart(userId);
    QVector<Book> books;
    for (int bookId : cart.getBookIds()) {
        books.append(bookManager->getBookById(bookId));
    }
    return books;
}

double CartManager::getCartTotal(int userId) {
    double total = 0.0;
    for (const Book& book : getCartItems(userId)) {
        total += book.getFinalPrice();
    }
    return total;
}

void CartManager::clearCart(int userId) {
    Cart cart = getOrCreateCart(userId);
    cart.clear();
    storage->save(cart);
}

bool CartManager::checkout(int userId) {
    Cart cart = getOrCreateCart(userId);
    if (cart.itemCount() == 0) {
        return false;
    }

    QVector<int> bookIds = cart.getBookIds();

    for (int bookId : bookIds) {
        Book book = bookManager->getBookById(bookId);
        double finalPrice = book.getFinalPrice();

        // TODO: وقتی TransactionManager آماده شد:
        // transactionManager->recordTransaction(userId, bookId, finalPrice);

        // TODO: وقتی LibraryManager آماده شد:
        // libraryManager->addBookToLibrary(userId, bookId);

        bookManager->incrementSalesCount(bookId);
    }

    clearCart(userId);
    return true;
}