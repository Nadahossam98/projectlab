cmake_minimum_required(VERSION 3.16)

project(Hospital_Patient_Management_system VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES Hospital_Patient_Management_system_en_GB.ts
  Hospital_Patient_Management_system_en_GB.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Hospital_Patient_Management_system
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        login.h login.cpp login.ui
        adminpage.h adminpage.cpp adminpage.ui
        dashboard.h dashboard.cpp dashboard.ui
        patientrecords.h patientrecords.cpp patientrecords.ui

        adminpage.cpp adminpage.h adminpage.ui AppointmentForm.cpp AppointmentForm.h AppointmentForm.ui    billingpage.cpp billingpage.h billingpage.ui build.ninja cmake_install.cmake CMakeCache.txt CMakeCache.txt.prev CMakeLists.txt CMakeLists.txt.user dashboard.cpp dashboard.h dashboard.ui databasemanager.cpp databasemanager.h   Hospital_Patient_Management_system.exe login.cpp login.h login.ui main.cpp mainwindow.cpp mainwindow.h mainwindow.ui patientrecords.cpp patientrecords.h patientrecords.ui qtcsettings.cmake
        reportspage.h reportspage.cpp reportspage.ui

   
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Hospital_Patient_Management_system APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(Hospital_Patient_Management_system SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Hospital_Patient_Management_system
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(Hospital_Patient_Management_system PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Hospital_Patient_Management_system)
endif()
set_target_properties(Hospital_Patient_Management_system PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Hospital_Patient_Management_system
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Hospital_Patient_Management_system)
endif()
