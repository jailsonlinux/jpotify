include($$PWD/../../globals.pri)

QT -= gui

TEMPLATE = lib
TARGET = Api
DEFINES += API_LIBRARY

DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    api.cpp

HEADERS += \
    api.h

# Default rules for deployment.
#unix {
#    target.path = $$DIR_INSTALL
#}
#!isEmpty(target.path): INSTALLS += target
#DESTDIR      = $${DIR_BUILD}/lib
