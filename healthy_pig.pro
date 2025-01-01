QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    logger.cpp \
    main.cpp \
    mainwindow.cpp \
    public_driver.cpp \
    public_driver_arrange.cpp \
    public_menu.cpp \
    public_order_arrange.cpp \
    public_order_list.cpp \
    public_role.cpp \
    public_user.cpp \
    public_vehicle.cpp

HEADERS += \
    BasePage.h \
    logger.h \
    mainwindow.h \
    public_driver.h \
    public_driver_arrange.h \
    public_menu.h \
    public_order_arrange.h \
    public_order_list.h \
    public_role.h \
    public_user.h \
    public_vehicle.h

FORMS += \
    mainwindow.ui \
    public_driver.ui \
    public_driver_arrange.ui \
    public_menu.ui \
    public_order_arrange.ui \
    public_order_list.ui \
    public_role.ui \
    public_user.ui \
    public_vehicle.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
