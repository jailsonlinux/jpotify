#include <QtTest>
#include <QFile>
#include <QDir>
#include <memory.h>

#include "../src/Db/abstractdao.h"

#include "../src/Dao/user.h"
#include "../src/Dao/userlist.h"
#include "../src/Dao/usersdao.h"

#include "../src/Dao/playlist.h"
#include "../src/Dao/playlists.h"
#include "../src/Dao/playlistdao.h"

#include "../src/Db/dbconn.h"
#include "../src/Db/abstractdao.h"



class Tests : public QObject
{
    Q_OBJECT

public:
    Tests();
    ~Tests();

private:
    void initUser();

    PlayList *createPlayList(
            const int id,
            const QString &nome,
            const QString &descricao,
            const QString &apiId,
            const int &userId);

    Playlists initPlayLists();

    std::unique_ptr<User> user;
    std::unique_ptr<UserList> users;

    const QString connId{QStringLiteral("connTest")};

private slots:
    //    void initTestCase();
    //    void cleanupTestCase();

    //Dto
    void testUser();
    void testUsers();

    void testPlaylist();
    void testPlaylists();

    //Dao
    void testUsersDao();
    void testPlayListsDao();

    //Db
    void testDbConn();

    //Api

    //Controllers
};

Tests::Tests():
    user(std::make_unique<User>()),
    users(std::make_unique<UserList>())
{

}

Tests::~Tests()
{

}

void Tests::initUser()
{
    user->setId(1);
    user->setNome(QStringLiteral("Jailson"));
    user->setClientid(QStringLiteral("qwertqwertqwert"));
    user->setSecret(QStringLiteral("qwertqwertqwert"));
    user->setAccess_token(QStringLiteral("asasasasasasas"));
    user->setAutologin(true);
}

Playlists Tests::initPlayLists()
{
    initUser();
    Playlists playlists = Playlists();
    playlists.addPlaylist(createPlayList(1,
                                         QStringLiteral("Rock"),
                                         QStringLiteral("Bandas de Rock 80"),
                                         QStringLiteral("asdfasdfasdf"),
                                         user.get()->id()
                                         ));
    playlists.addPlaylist(createPlayList(2,
                                         QStringLiteral("Balada"),
                                         QStringLiteral("Bandas de Balada 80"),
                                         QStringLiteral("bbbbbbbbbbbbb"),
                                         user.get()->id()
                                         ));

    return playlists;
}

PlayList *Tests::createPlayList(const int id, const QString &nome, const QString &descricao, const QString &apiId, const int &userId)
{
    PlayList *playLst = new PlayList();
    playLst->setId(id);
    playLst->setNome(nome);
    playLst->setDescricao(descricao);
    playLst->setApiid(apiId);
    playLst->setUserid(userId);

    return playLst;
}


void Tests::testUser()
{
    initUser();
    QCOMPARE(user.get()->id(), 1);
    QCOMPARE(user.get()->nome(), QStringLiteral("Jailson"));
    QCOMPARE(user.get()->clientid(), QStringLiteral("qwertqwertqwert"));
    QCOMPARE(user.get()->secret(), QStringLiteral("qwertqwertqwert"));
    QCOMPARE(user.get()->access_token(), QStringLiteral("asasasasasasas"));
    QCOMPARE(user.get()->autologin(), true);
}

void Tests::testUsers()
{
    users.get()->clear();
    QCOMPARE(users.get()->size(), 0);

    initUser();
    users.get()->addUser(user.get());
    QCOMPARE(users.get()->size(), 1);

    users.get()->removeUser(user.get());
    QCOMPARE(users.get()->size(), 0);

    initUser();
    users.get()->addUser(user.get());

    User *_user;
    _user = users.get()->getUserById(1);
    QCOMPARE(_user->id(), 1);

    _user = users.get()->getUserByName(QStringLiteral("Jailson"));
    QCOMPARE(_user->nome(), QStringLiteral("Jailson"));

    _user = users.get()->getUserByClientId(QStringLiteral("qwertqwertqwert"));
    QCOMPARE(_user->clientid(), QStringLiteral("qwertqwertqwert"));

    users.get()->clear();
    QCOMPARE(users.get()->size(), 0);
}

void Tests::testPlaylist()
{
    initUser();

    PlayList *playlist =  createPlayList(1,
                                        QStringLiteral("Rock"),
                                        QStringLiteral("Bandas de Rock 80"),
                                        QStringLiteral("asdfasdfasdf"),
                                        user.get()->id()
                                        );

    PlayList *playlist2 =  createPlayList(2,
                                         QStringLiteral("Balada"),
                                         QStringLiteral("Bandas de Balada 80"),
                                         QStringLiteral("bbbbbbbbbbbbb"),
                                         user.get()->id()
                                         );
    QCOMPARE(playlist->getId(), 1);
    QCOMPARE(playlist->nome(), QStringLiteral("Rock"));
    QCOMPARE(playlist->descricao(), QStringLiteral("Bandas de Rock 80"));
    QCOMPARE(playlist->apiId(), QStringLiteral("asdfasdfasdf"));
    QCOMPARE(playlist->userid(), user.get()->id());
    //
    QCOMPARE(playlist2->getId(), 2);
    QCOMPARE(playlist2->nome(), QStringLiteral("Balada"));
    QCOMPARE(playlist2->descricao(), QStringLiteral("Bandas de Balada 80"));
    QCOMPARE(playlist2->apiId(), QStringLiteral("bbbbbbbbbbbbb"));
    QCOMPARE(playlist2->userid(), user.get()->id());

    delete playlist;
    delete playlist2;

}

void Tests::testPlaylists()
{
    Playlists playlists;

    playlists = initPlayLists();
    QCOMPARE(playlists.getSize(), 2);
    playlists.clear();
    QCOMPARE(playlists.getSize(), 0);

    playlists = initPlayLists();
    QCOMPARE(playlists.getSize(), 2);
    playlists.removePlaylistById(1);
    QCOMPARE(playlists.getSize(), 1);

    playlists.removePlaylistById(2);
    QCOMPARE(playlists.getSize(), 0);

    playlists = initPlayLists();

    PlayList * _playlist(nullptr);
    _playlist = playlists.getPlaylistById(1);
    QCOMPARE(_playlist->getId(), 1);
    QCOMPARE(_playlist->nome(), QStringLiteral("Rock"));

    PlayList * _playlist2 = playlists.getPlaylistByName(QStringLiteral("Balada")); //id = 2
    QCOMPARE(_playlist2->getId(), 2);
    QCOMPARE(_playlist2->nome(), QStringLiteral("Balada"));
}

void Tests::testUsersDao()
{
    UsersDao usersDao = UsersDao();

    // inicia limpando caso exista o user inicial
    initUser();
    usersDao.remove(user.get());
    users.get()->clear();

    usersDao.loadAll(users.get());
    QCOMPARE(users.get()->size(), 0);

    usersDao.add(user.get());
    usersDao.loadAll(users.get());
    QCOMPARE(users.get()->size(), 1);

    users.get()->clear();
    usersDao.loadFromId(users.get(), user.get()->id());
    QCOMPARE(users.get()->size(), 1);

    usersDao.remove(user.get());
    initUser();
    usersDao.loadAll(users.get());
    QCOMPARE(users.get()->size(), 0);

}

void Tests::testPlayListsDao()
{
    initUser();
    PlayList *playlist =  createPlayList(1,
                                        QStringLiteral("Rock"),
                                        QStringLiteral("Bandas de Rock 80"),
                                        QStringLiteral("asdfasdfasdf"),
                                        user.get()->id()
                                        );

    Playlists playlists = Playlists();

    PlaylistDao playlistDao = PlaylistDao(user.get()->id());

    // inicia limpando todas playlistsdo user inicial
    playlistDao.removeAll();

    playlistDao.loadAll(&playlists);
    QCOMPARE(playlists.getSize(), 0);

    playlistDao.add(playlist);
    playlistDao.loadAll(&playlists);
    QCOMPARE(playlists.getSize(), 1);

    playlists.clear();
    playlistDao.loadFromId(&playlists, 1);
    QCOMPARE(playlists.getSize(), 1);

    playlistDao.remove(playlist);

    playlistDao.loadAll(&playlists);
    QCOMPARE(users.get()->size(), 0);
}

void Tests::testDbConn()
{
    DbConn conn = DbConn();
    conn.create(connId);
    QCOMPARE(conn.connect(connId), true);
    QCOMPARE(conn.connected(connId), true);

    conn.disconect(connId);

    const QString dbPath(QStringLiteral("%1/database").arg(ROOT_PATH));
    QDir dir;
    QCOMPARE(dir.exists(dbPath), true);

    const QString databaseName(QStringLiteral("%1/jspot.db").arg(dbPath));
    QFile file(databaseName);
    QCOMPARE(file.exists(databaseName), true);

    conn.destroy(connId);
    QCOMPARE(conn.connected(connId), false);

}

QTEST_APPLESS_MAIN(Tests)

#include "tst_tests.moc"
