include($$PWD/../../globals.pri)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT       += core gui svg sql

DEFINES += QT_DEPRECATED_WARNINGS
TARGET = jpotify
SOURCES += \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    playlist.cpp \
    searchresult.cpp \
    usuarios.cpp

HEADERS += \
    login.h \
    mainwindow.h \
    playlist.h \
    searchresult.h \
    usuarios.h


FORMS += \
    mainwindow.ui \
    ui/login.ui \
    ui/playlist.ui \
    ui/searchresult.ui \
    ui/usuarios.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc


INCLUDEPATH += $$DIR_INCLUDE

#DESTDIR += $$DIR_BUILD
#unix:!macx: LIBS += -L$$OUT_PWD/../Api/ -lApi
#unix:!macx: LIBS += -L$$OUT_PWD/../Db/ -lDb
#unix:!macx: LIBS += -L$$OUT_PWD/../Dao/ -lDao

#INCLUDEPATH += $$PWD/../Api
#DEPENDPATH += $$PWD/../Api
#INCLUDEPATH += $$PWD/../Db
#DEPENDPATH += $$PWD/../Db
#INCLUDEPATH += $$PWD/../Dao
#DEPENDPATH += $$PWD/../Dao




