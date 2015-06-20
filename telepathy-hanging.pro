QT -= gui
QT += dbus network
TEMPLATE = app
TARGET = telepathy-hanging
CONFIG   += console
CONFIG   -= app_bundle
INCLUDEPATH += ../libhangish $$OUT_PWD/../libhangish/


LIBS += ../libhangish/libhangish.so
CONFIG += link_pkgconfig
PKGCONFIG += TelepathyQt5 TelepathyQt5Service protobuf

PRE_TARGETDEPS += ../libhangish/libhangish.so

SOURCES += hangingtextchannel.cpp connection.cpp main.cpp  protocol.cpp
HEADERS += hangingtextchannel.h connection.h protocol.h
 
astyle.params += --style=linux
astyle.params += -z2
astyle.params += -c
astyle.params += --add-brackets
astyle.params += -H
astyle.commands = cd $$PWD; astyle $$astyle.params $$HEADERS $$SOURCES

QMAKE_EXTRA_TARGETS += astyle
