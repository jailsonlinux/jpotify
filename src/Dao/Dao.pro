include($$PWD/../../globals.pri)
QT -= gui

TEMPLATE = lib
TARGET = Dao
DEFINES += DAO_LIBRARY

DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    musica.cpp \
    musicalist.cpp \
    musicasdao.cpp \
    playlistdao.cpp \
    playlists.cpp \
    playlist.cpp \
    user.cpp \
    userlist.cpp \
    usersdao.cpp

HEADERS += \
    musica.h \
    musicalist.h \
    musicasdao.h \
    playlist.h \
    playlistdao.h \
    playlists.h \
    user.h \
    userlist.h \
    usersdao.h

# Default rules for deployment.

#LIBS        += -lDb
#DESTDIR      = $${DIR_BUILD}/lib
