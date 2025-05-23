cmake_minimum_required(VERSION 3.16)

project(Expense_manager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        addexpensedialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Expense_manager
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        addexpensedialog.h addexpensedialog.cpp addexpensedialog.ui



        simplelogger.h simplelogger.cpp
        summarydialog.h summarydialog.cpp summarydialog.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Expense_manager APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Expense_manager SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Expense_manager
          main.cpp
          mainwindow.cpp
          Business_logic/expense.cpp
          Business_logic/simplelogger.cpp
        )

        target_link_libraries(Expense_manager
          PRIVATE Qt6::Widgets
        )
    endif()
endif()

target_link_libraries(Expense_manager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Expense_manager PRIVATE Business_logic Qt6::Widgets)
target_include_directories(Expense_manager PRIVATE ${CMAKE_SOURCE_DIR}/Business_logic)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Expense_manager)
endif()
set_target_properties(Expense_manager PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Expense_manager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Expense_manager)
endif()
add_subdirectory(Business_logic)

