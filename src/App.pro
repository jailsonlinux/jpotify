include($$PWD/../globals.pri)

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    searchresult.cpp \
    usuarios.cpp

HEADERS += \
    MouseButtomSignaler.h \
    login.h \
    mainwindow.h \
    searchresult.h \
    usuarios.h


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
            $$PWD/../src/Dao/musicasdao.cpp


INCLUDEPATH += $$DIR_INCLUDE

FORMS += \
    login.ui \
    mainwindow.ui \
    searchresult.ui \
    usuarios.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc



