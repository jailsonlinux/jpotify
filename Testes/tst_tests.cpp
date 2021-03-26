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

#include "../src/Dao/musica.h"
#include "../src/Dao/musicalist.h"
#include "../src/Dao/musicasdao.h"

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
    Musica * initMusica(const QString &key, const int idplaylist, const QString &descricao);

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
    void testUserList();
    void testPlaylist();
    void testPlaylists();
    void testMusica();
    void testMusicaList();


    //Dao
    void testUsersDao();
    void testPlayListsDao();
    void testMusicasDao();

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

Musica *Tests::initMusica(const QString &key, const int idplaylist, const QString &nome)
{

    Musica *musica = new Musica;
    musica->setKey(key);
    musica->setNome(nome);
    musica->setOrdem(1);
    musica->setTrack(QStringLiteral("iddotrack"));
    musica->setImagem(QStringLiteral("https://urlsdaimagem"));
    musica->setDuracao(3600);
    musica->setPlaylistid(idplaylist);
    musica->setPreviewUrl(QStringLiteral("https://urlsdeprevisaodosample"));
    return musica;
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

void Tests::testUserList()
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

void Tests::testMusica()
{
    Musica *musica = initMusica(QStringLiteral("chaveunicadamusicapelaapi"),
                                1, QStringLiteral("nomedamusica"));

    QCOMPARE(musica->key(), QStringLiteral("chaveunicadamusicapelaapi"));
    QCOMPARE(musica->nome(), QStringLiteral("nomedamusica"));
    QCOMPARE(musica->ordem(), 1);
    QCOMPARE(musica->track(), QStringLiteral("iddotrack"));
    QCOMPARE(musica->imagem(), QStringLiteral("https://urlsdaimagem"));
    QCOMPARE(musica->duracao(), 3600);
    QCOMPARE(musica->playlistid(), 1);
    QCOMPARE(musica->previewUrl(), QStringLiteral("https://urlsdeprevisaodosample"));

    delete musica;

}

void Tests::testMusicaList()
{

    Musica *musica = initMusica(QStringLiteral("chaveunicadamusicapelaapi"),
                                1, QStringLiteral("nomedamusica"));

    Musica *musica2 = initMusica(QStringLiteral("chaveunicadamusicapelaapi2"),
                                1, QStringLiteral("nomedamusica2"));

    Musica *musica3 = initMusica(QStringLiteral("chaveunicadamusicapelaapi3"),
                                1, QStringLiteral("nomedamusica3"));

    Musica *musica4 = initMusica(QStringLiteral("chaveunicadamusicapelaapi4"),
                                1, QStringLiteral("nomedamusica4"));

    MusicaList *musicas = new MusicaList;
    MusicaList *musicas2 = new MusicaList;

    QCOMPARE(musicas->size(), 0);

    musicas->addMusica(musica);
    QCOMPARE(musicas->size(), 1);
    musicas->addMusica(musica2);
    QCOMPARE(musicas->size(), 2);

    musicas2->addMusica(musica3);
    musicas2->addMusica(musica4);

    musicas->addMusicas(musicas2);
    QCOMPARE(musicas->size(), 4);

    Musica *musicaOk = musicas->getMusicaByKey(QStringLiteral("chaveunicadamusicapelaapi3"));
    QCOMPARE(musicaOk->key(), QStringLiteral("chaveunicadamusicapelaapi3"));
    QCOMPARE(musicaOk->nome(), QStringLiteral("nomedamusica3"));
    QCOMPARE(musicaOk->ordem(), 1);

    musicas->removeMusica(musicaOk);
    QCOMPARE(musicas->size(), 3);

    musicaOk = musicas->getMusicaByName(QStringLiteral("nomedamusica2"));
    QCOMPARE(musicaOk->key(), QStringLiteral("chaveunicadamusicapelaapi2"));
    QCOMPARE(musicaOk->nome(), QStringLiteral("nomedamusica2"));
    QCOMPARE(musicaOk->ordem(), 1);
    musicas->removeMusica(musicaOk);
    QCOMPARE(musicas->size(), 2);

    delete musicaOk;
    delete musica;
//    delete musica2;
//    delete musica3;
//    delete musica4;

    musicas->clear();
    delete musicas;
    musicas2->clear();
    delete musicas2;

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

    Musica *musica = initMusica(QStringLiteral("chaveunicadamusicapelaapi"),
                                1, QStringLiteral("nomedamusica"));
    MusicaList *musicas = new MusicaList;
    musicas->addMusica(musica);
    playlist2->setMusicas(musicas);
    QCOMPARE(playlist2->getMusicas()->size(), 1);

    musicas->clear();
    delete musica;
    delete musicas;
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

void Tests::testMusicasDao()
{
    initUser();
    PlayList *playlist =  createPlayList(1,
                                         QStringLiteral("Rock"),
                                         QStringLiteral("Bandas de Rock 80"),
                                         QStringLiteral("asdfasdfasdf"),
                                         user.get()->id()
                                         );

    PlaylistDao playlistDao = PlaylistDao(user.get()->id());


    Musica *musica3 = initMusica(QStringLiteral("chaveunicadamusicapelaapi3"),
                                1, QStringLiteral("nomedamusica3"));

    Musica *musica4 = initMusica(QStringLiteral("chaveunicadamusicapelaapi4"),
                                1, QStringLiteral("nomedamusica4"));

    MusicaList *musicas = new MusicaList;
    musicas->addMusica(musica3);
    musicas->addMusica(musica4);

    playlistDao.add(playlist);

    MusicasDao musicaDao = MusicasDao(playlist->getId());
    musicaDao.removeAll();

    musicaDao.add(musica3);

    MusicaList *musicas2 = new MusicaList;
    musicaDao.loadAll(musicas2);
    QCOMPARE(musicas2->size(), 1);

    musicas2->clear();
    musicaDao.loadFromKey(musicas2, QStringLiteral("chaveunicadamusicapelaapi3"));
    QCOMPARE(musicas2->size(), 1);

    musicaDao.remove(musica3);

    musicaDao.loadAll(musicas2);
    QCOMPARE(musicas2->size(), 0);

    delete playlist;
    musicas->clear();
    delete musicas;
    musicas2->clear();
    delete musicas2;

    delete musica3;
    delete musica4;

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
