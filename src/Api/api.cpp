#include "api.h"

#include <QDebug>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCoreApplication>
//#include <QtGui/QDesktopServices>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QEventLoop>
#include <QProcess>
#include <QTimer>

Api::Api(QObject *parent):
    QObject(parent)
  //   m_NetManager(std::make_unique<QNetworkAccessManager>())
  ,m_servidor(std::make_unique<QTcpServer>(nullptr))
  ,m_usuario(std::make_unique<Usuario>())
  ,m_jaAutenticado(false)
{

}

Api::~Api()
{
    finalizaServico();
    //    m_NetManager->disconnect();
}

void Api::acessToken()
{
    qDebug() << "acessToken: true";
    emit on_acessToken(true);
}

bool Api::precisaAutenticar()
{
    m_jaAutenticado = (QDateTime::currentDateTime() < m_dtExpiraToken) &&
            (m_usuario != nullptr && !m_usuario.get()->access_token().isEmpty());

    if (m_jaAutenticado)
        emit on_JaAutenticado();

    return !m_jaAutenticado;
}

/**
 * @brief Api::parseHttpResponse
 * parseia a resposta do servidor local para retirar o acesstoken do usuario.
 */
void Api::parseHttpResponse()
{
    emit newConnection();

    auto *socket = m_servidor->nextPendingConnection();

    if (socket == nullptr) {
        emit on_Erro(QStringLiteral("Erro: Invalido em parseHttpResponse: nextPendingConnection"));
        return;
    }

    socket->waitForReadyRead();

    const auto response = QString(socket->readAll());

    if (!response.contains(m_paramCode) || response.contains(QStringLiteral("favicon.ico"))) {
        socket->write(QStringLiteral("HTTP/1.1 400 Bad Request\r\n\r\nBad Request").toUtf8());
        socket->waitForBytesWritten();

        m_jaAutenticado = false;

        emit on_Erro(QStringLiteral("Erro: Resposta não contém paramCode"));

        socket->flush();
        socket->close();

        return;
    }

    // Fecha o socket
    socket->write(QStringLiteral("HTTP/1.1 200 OK\r\n\r\nOk\nSucesso\nParabens\nWowww..rsrsrs").toUtf8());
    socket->flush();
    socket->waitForBytesWritten();
    socket->close();

    emit responseParseado();

    //ToDo: Fechar aba do browser de autenticao aqui??How??
    constexpr auto posRight = 6;
    auto strLeft = response.left(response.indexOf(m_headerHttp)).trimmed();
    QString acesstoken = strLeft.right(strLeft.length() - strLeft.indexOf(m_paramCode) - posRight).trimmed();
    m_usuario.get()->setAccess_token(acesstoken);

    emit on_acessToken(m_usuario.get()->access_token().trimmed().length() > 0);
}

/**
 * @brief Api::abrirLogin
 * Escuta localmente pela resposta do spotify,
 * abre uma janela do browser para autenticacao na api,
 * entao parseia em parseHttpResponse, capturando o acesstoken do user logado.
 */
void Api::abrirLogin()
{
    m_servidor = std::make_unique<QTcpServer>();

    connect(m_servidor.get(), &QTcpServer::newConnection, this, &Api::parseHttpResponse);

    if (!m_servidor->listen(QHostAddress::Any, m_tcpServerPort)) {
        qCritical() << QStringLiteral("Erro ao iniciar o servidor") << m_servidor->errorString();
        return;
    }

    //ToDo:: Gambiarra com process, pq o QDesktopServices nao ta compilandoooo!!!!
    //ARRRGGGGG!!!!
    const auto url = getUrlDeAutenticacao();
    QString program = QStringLiteral("google-chrome");
    QStringList arguments;
    arguments << "--chrome-frame " << "--kiosk " << QUrl(url).toString();

    QProcess *chromeProcess = new QProcess(this);

    chromeProcess->start(program, arguments);
    chromeProcess->waitForStarted(15000);

    //    chromeProcess->close();
    //    chromeProcess->kill();

}

void Api::finalizaServico()
{
    if(m_servidor != nullptr)
        m_servidor->close();

    m_servidor.reset(nullptr);
}

void Api::getApiToken(){

    if (m_usuario.get()->access_token().isEmpty()) {
        qCritical() << "Erro: Authorization Code vazio";
        return;
    }

    //Pedir um novo token para o usuario logado.
    QNetworkRequest request(QStringLiteral("https://accounts.spotify.com/api/token"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    request.setRawHeader("Authorization", "Basic " + QStringLiteral("%1:%2").arg(m_usuario.get()->clientid(),
                                                                                 m_usuario.get()->secret()).toUtf8().toBase64());

    const QString postData(QStringLiteral("grant_type=authorization_code&code=%1&redirect_uri=%2")
                           .arg(m_usuario.get()->access_token(), m_redirectUrl));

    // Aguardar resposta do POST...
    QNetworkAccessManager networkManager;
    auto *reply = networkManager.post(request, postData.toUtf8());
    while (!reply->isFinished())
        QCoreApplication::processEvents();

    if (reply->error() != QNetworkReply::NoError)
        qCritical() << "Erro no request" << reply->error() << reply->errorString();

    //Pegar o resultado em json.
    QJsonParseError parseError{};
    const auto data = reply->readAll();
    reply->deleteLater();

    try {
        auto json = QJsonDocument::fromJson(data, &parseError);

        if (parseError.error != QJsonParseError::NoError)
            qCritical() << "Error tentado parsear o JSON" << parseError.errorString() << data;

        const auto &obj = json.object();
        const auto field_accesstoken(QStringLiteral("access_token"));
        const auto field_expiresin(QStringLiteral("expires_in"));

        if (obj.contains(field_accesstoken) && obj.contains(field_expiresin)) {
            setAcessTokenn(obj.value(field_accesstoken).toString());;
            setTokenExpires(QDateTime::currentDateTime().addSecs(obj.value(field_expiresin).toInt()));

            m_jaAutenticado = true;
            emit on_Conectado();
            return;
        }
    }  catch (...) {
        qCritical() << QStringLiteral("Error ao ler mensagem");
    }

    emit on_Erro(QStringLiteral("Error ao ler mensagem"));
}

QNetworkRequest Api::montaRequisicao(const QString &uri)
{
    QUrl url("https://api.spotify.com/v1/" + uri);
    QNetworkRequest request(url);
    if(getAcessTokenn().isEmpty()){
        qWarning() << QStringLiteral("AcessToken vazio! url: ") << url;
    }
    request.setRawHeader("Authorization", QStringLiteral("Bearer %1").arg(getAcessTokenn()).toUtf8());

    return request;
}


QJsonObject Api::pesquisaMusicas(const QString &termo)
{
    const QString resource = QStringLiteral("search?q=%1&type=track").arg(termo);
    QNetworkAccessManager networkManager;
    auto *reply = networkManager.get(montaRequisicao(resource));

    while(!reply->isFinished())
        QCoreApplication::processEvents();

    QJsonParseError parseError{};
    auto json = QJsonDocument::fromJson(reply->readAll(), &parseError);

    if (parseError.error != QJsonParseError::NoError)
        qCritical() << "Error ao parsear JSON" << parseError.errorString();
    reply->deleteLater();

    return json.object();
}

QString Api::getClientId() const
{
    return m_usuario.get()->clientid();
}

void Api::setClientId(const QString &clientId)
{
    m_usuario.get()->setClientid(clientId);
}

QString Api::getClientSecret() const
{
    return m_usuario.get()->secret();
}

void Api::setClientSecret(const QString &clientSecret)
{
    m_usuario.get()->setSecret(clientSecret);
}

QString Api::getAuthorizationCode() const
{
    return m_usuario.get()->access_token();
}

void Api::setAuthorizationCode(const QString &authorizationCode)
{
    m_usuario.get()->setAccess_token(authorizationCode);
}

/**
 * @brief Api::getAcessTokenn
 * @return
 */
QString Api::getAcessTokenn() const
{
    return m_apiacess_token;
}

/**
 * @brief Api::setAcessTokenn
 * @param acessToken
 */
void Api::setAcessTokenn(const QString &acessToken)
{
    m_apiacess_token = acessToken;
    m_usuario->setApi_token(m_apiacess_token);
}

QDateTime Api::getTokenExpires() const
{
    return m_dtExpiraToken;
}

void Api::setTokenExpires(const QDateTime &tokenExpires)
{
    if (m_dtExpiraToken == tokenExpires)
        return;

    m_dtExpiraToken = tokenExpires;
    emit tokenExpiresChanged();
}



/**
 * @brief Api::getUrlDeAutenticacao
 * @return url formatada para autrizacao da api.
 * https://developer.spotify.com/documentation/general/guides/authorization-guide/
 */
QString Api::getUrlDeAutenticacao()
{
    const QStringList scopes {
        "playlist-read-collaborative",
        "playlist-read-private",
        "playlist-modify-private",
        "playlist-modify-public",
        "user-library-modify",
        "user-library-read",
        "user-modify-playback-state",
        "user-read-currently-playing",
        "user-read-playback-state",
        "user-read-private",
        "streaming",
    };

    return QStringLiteral("https://accounts.spotify.com/authorize?client_id=%1&response_type=code&redirect_uri=%2&scope=%3")
            .arg(m_usuario.get()->clientid(), m_redirectUrl, scopes.join(QStringLiteral("%20")));
}

QString Api::getApiacess_token() const
{
    return m_apiacess_token;
}

void Api::setApiacess_token(const QString &apiacess_token)
{
    m_apiacess_token = apiacess_token;
}

void Api::setUsuario( Usuario *usuario)
{
    m_usuario.reset(usuario);
}


QString Api::getToken()
{
    return m_usuario->access_token();
}
