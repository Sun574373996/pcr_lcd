#-------------------------------------------------
#
# Project created by QtCreator 2019-08-20T17:55:36
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pcr
TEMPLATE = app


SOURCES += main.cpp \
    button.cpp \
    common.cpp \
    widget.cpp \
    topview.cpp \
    topsense.cpp \
    popups.cpp \
    page2.cpp \
    page1.cpp \
    label.cpp \
    key.cpp \
    pnumkb.cpp \
    pqwertkb.cpp \
    communicate.cpp \
    dev_file.cpp \
    beep.cpp \
    page3.cpp \
    stage.cpp \
    run_monitor.cpp \
    arrow.cpp \
    page4.cpp \
    page5.cpp \
    page6.cpp \
    page7.cpp \
    psetdir.cpp \
    psetname.cpp

HEADERS  += \
    button.h \
    common.h \
    widget.h \
    topview.h \
    topsense.h \
    popups.h \
    page2.h \
    page1.h \
    label.h \
    key.h \
    pnumkb.h \
    pqwertkb.h \
    communicate.h \
    dev_file.h \
    beep.h \
    page3.h \
    stage.h \
    run_monitor.h \
    arrow.h \
    page4.h \
    page5.h \
    page6.h \
    page7.h \
    psetdir.h \
    psetname.h

DISTFILES += \
    readme

RESOURCES += \
    picture.qrc

target.path=/home
INSTALLS += target
