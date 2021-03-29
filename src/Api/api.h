#pragma once

#include <QObject>
#include <QString>
//#include <QNetworkAccessManager>
#include <QtNetwork/QTcpServer>
#include <QDateTime>
#include <memory>
#include <QNetworkRequest>

#include "../Dao/usuario.h"


class Api : public QObject
{
    Q_OBJECT

public:
    Api(QObject *parent = 0);
    ~Api();

    void acessToken();

    std::unique_ptr<Usuario> getUsuario() const;
    bool precisaAutenticar();
    void abrirLogin();
    void finalizaServico();
    void getApiToken();

    QNetworkRequest montaRequisicao(const QString &uri);
    QJsonObject pesquisaMusicas(const QString &termo);

    QString getClientId() const;
    void setClientId(const QString &clientId);

    QString getClientSecret() const;
    void setClientSecret(const QString &clientSecret);

    QString getAuthorizationCode() const;
    void setAuthorizationCode(const QString &authorizationCode);

    QString getAcessTokenn() const;
    void setAcessTokenn(const QString &acessToken);

    QDateTime getTokenExpires() const;
    void setTokenExpires(const QDateTime &tokenExpires);

    void setUsuario(Usuario *usuario);

    QString getApiacess_token() const;
    void setApiacess_token(const QString &apiacess_token);

signals:
    void on_JaAutenticado();
    void authenticationFailed();
    void newConnection();
    void responseParseado();

    void clientIdChanged();
    void clientSecretChanged();
    void authorizationCodeChanged();
    void AcessTokennChanged();
    void tokenExpiresChanged();
    void on_Conectado();
    void on_Erro(const QString &mensagem);
    void on_acessToken(bool value);

private slots:
    void parseHttpResponse();
    QString getUrlDeAutenticacao();

private:
//    std::unique_ptr<QNetworkAccessManager>m_NetManager;
    std::unique_ptr<QTcpServer>m_servidor;
    std::unique_ptr<Usuario>m_usuario;
    QDateTime m_dtExpiraToken;
    bool m_jaAutenticado;
    QString m_apiacess_token;

    QString getToken();

    const int m_tcpServerPort = 8888;
    const QString m_redirectUrl{QStringLiteral("http://localhost:%1").arg(m_tcpServerPort)};
    const QString m_paramCode{QStringLiteral("?code=")};
    const QString m_headerHttp{QStringLiteral("HTTP")};

};





