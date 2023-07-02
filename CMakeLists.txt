cmake_minimum_required(VERSION 3.16)

project(SeeMoneySpending VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(app_icon_resource_windows "ressources/images.rc")

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED Widgets Charts)

set(CMAKE_AUTORCC ON)

qt_add_executable(appSeeMoneySpending
    main.cpp
    ${app_icon_resource_windows}
    images.qrc
    datamanager.h datamanager.cpp GraphDesignHelper.h
)

qt_add_qml_module(appSeeMoneySpending
    URI SeeMoneySpending
    VERSION 1.0
    QML_FILES main.qml SpendMoney.qml MoneyHistoryDisplay.qml MoneyListModel.qml SpendingGraph.qml
)

set_target_properties(appSeeMoneySpending PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSeeMoneySpending
    PRIVATE Qt6::Quick Qt6::Widgets Qt6::Charts)

install(TARGETS appSeeMoneySpending
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})


