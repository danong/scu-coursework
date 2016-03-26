#-------------------------------------------------
#
# Project created by QtCreator 2015-02-18T14:40:16
#
#-------------------------------------------------

QT       -= core gui

TARGET = ongAlgData
TEMPLATE = lib
CONFIG += staticlib

SOURCES += ongalgdata.cpp \
    linkedlist.cpp \
    vector.cpp

HEADERS += ongalgdata.h \
    stack.h \
    queue.h \
    linkedlist.h \
    vector.h \
    node.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

QMAKE_CXXFLAGS += -std=c++0x
