#-------------------------------------------------
#
# Project created by QtCreator 2018-06-12T11:27:45
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DTCS_Slave
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    DB_ACCESS.cpp \
    MASTER.cpp \
    SLAVE.cpp \
    Public_Define.cpp \
    Report.cpp \
    room.cpp \
    slavecharge.cpp \
    thread_one.cpp \
    login2.cpp \
    thread_two.cpp

HEADERS += \
    DB_ACCESS.h \
    MASTER.h \
    SLAVE.h \
    Public_Define.h \
    Struct_Define.h \
    Report.h \
    room.h \
    slavecharge.h \
    thread_one.h \
    login2.h \
    thread_two.h \
    stylesheet.h

FORMS += \
    room.ui \
    slavecharge.ui \
    login2.ui

RESOURCES += \
    imgs.qrc
