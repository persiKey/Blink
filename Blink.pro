QT       += core gui
QT       += winextras
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    scipy/cephes/const.c \
    scipy/cephes/ellie.c \
    scipy/cephes/ellik.c \
    scipy/cephes/ellpe.c \
    scipy/cephes/ellpk.c \
    scipy/cephes/gamma.c \
    scipy/cephes/unity.c \
    scipy/cephes/zeta.c \
    timermanager.cpp

HEADERS += \
    animwindow.h \
    constants.h \
    mainwindow.h \
    scipy/cephes/cephes.h \
    scipy/cephes/cephes_names.h \
    scipy/cephes/mconf.h \
    scipy/cephes/polevl.h \
    timermanager.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
