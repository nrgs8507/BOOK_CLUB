cmake_minimum_required(VERSION 3.19)
project(BOOK_CLUB LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)

include_directories(${CMAKE_SOURCE_DIR}/src)
qt_standard_project_setup()

qt_add_executable(BOOK_CLUB
    WIN32 MACOSX_BUNDLE
    main.cpp
    src/ui/loginpage.h
    src/ui/loginpage.cpp
    src/ui/loginpage.ui
    src/models/Account.h src/models/Account.cpp
    src/models/User.h src/models/User.cpp
    src/auth/AuthManager.h src/auth/AuthManager.cpp
    src/utils/cryptomanager.h src/utils/cryptomanager.cpp
    src/utils/cryptomanager.h src/utils/cryptomanager.cpp
    src/ui/loginpage.h src/ui/loginpage.cpp src/ui/loginpage.ui
    src/repository/irepository.h
    src/repository/filerepository.h
    src/ui/registerpage.h src/ui/registerpage.cpp
    src/ui/forgotpasswordpage.h src/ui/forgotpasswordpage.cpp
    src/ui/bookcardwidget.h src/ui/bookcardwidget.cpp
    src/ui/searchresultspage.h src/ui/searchresultspage.cpp
    src/ui/searchbookpage.h src/ui/searchbookpage.cpp src/ui/searchbookpage.ui
    src/network/networkclient.h src/network/networkclient.cpp

)

target_link_libraries(BOOK_CLUB
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
)

qt_add_executable(BOOK_CLUB_SERVER
    server_main.cpp
    src/models/Account.h src/models/Account.cpp
    src/models/User.h src/models/User.cpp
    src/models/book.h src/models/book.cpp
    src/models/discount.h
    src/models/percentdiscount.h src/models/percentdiscount.cpp
    src/models/timeddiscount.h src/models/timeddiscount.cpp
    src/managers/bookmanager.h src/managers/bookmanager.cpp
    src/auth/AuthManager.h src/auth/AuthManager.cpp
    src/utils/cryptomanager.h src/utils/cryptomanager.cpp
    src/repository/irepository.h
    src/repository/filerepository.h
    src/repository/ibookstorage.h
    src/repository/filebookstorage.h src/repository/filebookstorage.cpp
    src/network/clienthandler.h src/network/clienthandler.cpp
    src/network/tcpserver.h src/network/tcpserver.cpp
    src/models/cart.h src/models/cart.cpp
    src/models/library.h src/models/library.cpp
    src/models/shelf.h src/models/shelf.cpp
    src/models/transaction.h src/models/transaction.cpp
    src/managers/cartmanager.h src/managers/cartmanager.cpp
    src/managers/librarymanager.h src/managers/librarymanager.cpp
    src/managers/discountmanager.h src/managers/discountmanager.cpp
    src/managers/transactionmanager.h src/managers/transactionmanager.cpp
    src/repository/icartstorage.h src/repository/filecartstorage.h src/repository/filecartstorage.cpp
    src/repository/ilibrarystorage.h src/repository/filelibrarystorage.h src/repository/filelibrarystorage.cpp
    src/repository/itransactionstorage.h src/repository/filetransactionstorage.h src/repository/filetransactionstorage.cpp
)

target_link_libraries(BOOK_CLUB_SERVER
    PRIVATE
        Qt::Core
        Qt::Network
)

install(TARGETS BOOK_CLUB
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET BOOK_CLUB
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
