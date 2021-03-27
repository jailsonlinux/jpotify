include($$PWD/../globals.pri)
QT += testlib sql
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app
TARGET = Testes

HEADERS += $$PWD/../src/Db/abstractdao.h \
           $$PWD/../src/Db/dbconn.h \
           $$PWD/../src/Dao/user.h \
           $$PWD/../src/Dao/userlist.h \
           $$PWD/../src/Dao/usersdao.h \
           $$PWD/../src/Dao/playlist.h \
           $$PWD/../src/Dao/playlists.h \
           $$PWD/../src/Dao/playlistdao.h \
           $$PWD/../src/Dao/musica.h \
           $$PWD/../src/Dao/musicalist.h \
           $$PWD/../src/Dao/musicasdao.h


SOURCES +=  $$PWD/../src/Db/abstractdao.cpp \
            $$PWD/../src/Db/dbconn.cpp \
            $$PWD/../src/Dao/user.cpp \
            $$PWD/../src/Dao/userlist.cpp \
            $$PWD/../src/Dao/usersdao.cpp \
            $$PWD/../src/Dao/playlist.cpp \
            $$PWD/../src/Dao/playlists.cpp \
            $$PWD/../src/Dao/playlistdao.cpp \
            $$PWD/../src/Dao/musica.cpp \
            $$PWD/../src/Dao/musicalist.cpp \
            $$PWD/../src/Dao/musicasdao.cpp \
            tst_tests.cpp

INCLUDEPATH += $$DIR_INCLUDE
#DESTDIR      = $${DIR_BUILD}/lib
