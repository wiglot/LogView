
TARGET = logview
QT += core \
    gui
HEADERS += logger.h \
    logview.h
SOURCES += logger.cpp \
    logview.cpp
FORMS += logview.ui

INCLUDEPATH += .

CONFIG(TEST){
    TEMPLATE = app
    QT+=testlib
    SOURCES += tests/testlogger.cpp
}else{
    TEMPLATE = lib
}

