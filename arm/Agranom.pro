QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basa.cpp \
    grafik.cpp \
    main.cpp \
    mainwindow.cpp \
    srav.cpp \
    zametki.cpp

HEADERS += \
    basa.h \
    grafik.h \
    mainwindow.h \
    srav.h \
    zametki.h

FORMS += \
    basa.ui \
    grafik.ui \
    mainwindow.ui \
    srav.ui \
    zametki.ui
win32:RC_FILE = fil.rc
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
