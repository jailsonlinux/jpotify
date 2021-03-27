include($$PWD/../globals.pri)
QT += testlib sql
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app
TARGET = Testes

HEADERS += $$PWD/../src/Db/abstractdao.h \
           $$PWD/../src/Db/dbconn.h \
           $$PWD/../src/Dao/usuario.h \
           $$PWD/../src/Dao/usuariolist.h \
           $$PWD/../src/Dao/usuariosdao.h \
           $$PWD/../src/Dao/playlist.h \
           $$PWD/../src/Dao/playlists.h \
           $$PWD/../src/Dao/playlistdao.h \
           $$PWD/../src/Dao/musica.h \
           $$PWD/../src/Dao/musicalist.h \
           $$PWD/../src/Dao/musicasdao.h \
           $$PWD/../src/Api/api.h \
           $$PWD/../src/Controllers/usuarioscontroller.h



SOURCES +=  $$PWD/../src/Db/abstractdao.cpp \
            $$PWD/../src/Db/dbconn.cpp \
            $$PWD/../src/Dao/usuario.cpp \
            $$PWD/../src/Dao/usuariolist.cpp \
            $$PWD/../src/Dao/usuariosdao.cpp \
            $$PWD/../src/Dao/playlist.cpp \
            $$PWD/../src/Dao/playlists.cpp \
            $$PWD/../src/Dao/playlistdao.cpp \
            $$PWD/../src/Dao/musica.cpp \
            $$PWD/../src/Dao/musicalist.cpp \
            $$PWD/../src/Dao/musicasdao.cpp \
            $$PWD/../src/Api/api.cpp \
            $$PWD/../src/Controllers/usuarioscontroller.cpp \
            tst_tests.cpp

INCLUDEPATH += $$DIR_INCLUDE
#DESTDIR      = $${DIR_BUILD}/lib
