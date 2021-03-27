!win32-msvc {
    CONFIG += c++17
    QMAKE_CXXFLAGS += -std=c++17

    QMAKE_CXXFLAGS_RELEASE -= -O1
    QMAKE_CXXFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE *= -O3
}

CONFIG(debug, debug|release) {
    unix:!macx {
        DIR_INSTALL=$$OUT_PWD/JPotify
    }
} else {
    unix:!macx {
        DIR_INSTALL=$$OUT_PWD/JPotify
    }
}

DEFINES += ROOT_PATH=\\\"$$DIR_INSTALL\\\"

#DIR_LIB=$$DIR_INSTALL

DIR_INCLUDE += $$PWD/src \
              $$PWD/src/Api \
              $$PWD/src/Dao \
              $$PWD/src/Db \
              $$PWD/src/Controller \
              $$PWD/Testes

#CONFIG(debug, debug|release) {
#    DEFINES += APPMODE=\\\"debug\\\"
#} else {
#    DEFINES += APPMODE=\\\"release\\\"
#}


DIR_BUILD = $$OUT_PWD/JPotify
target.path = $$DIR_BUILD
DEFINES += APP_DIR=\\\"$${target.path}\\\"


#LIBS            += -L$${DIR_BUILD}
#INCLUDEPATH += $$DIR_INCLUDE
DESTDIR      = $${DIR_BUILD}

#!isEmpty(target.path): INSTALLS += target
