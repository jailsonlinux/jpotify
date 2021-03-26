#include "loginweb.h"
#include <QWebEngineSettings>
#include <QWebEngineProfile>

LoginWeb::LoginWeb(QWidget *parent) :
    QWebEngineView(parent)
{
    QWebEngineProfile *profile = page()->profile();
    QWebEngineSettings * settings = page()->settings();

    settings->defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    #if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
        settings->defaultSettings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
        profile->defaultProfile()->setUseForGlobalCertificateVerification();
        profile->defaultProfile()->setPersistentCookiesPolicy(QWebEngineProfile::PersistentCookiesPolicy::AllowPersistentCookies);
    #endif

    setUrl(QUrl(QStringLiteral("https://accounts.spotify.com/authorize-client_id=db40e232cbe848108107a35b2f157026&response_type=code&redirect_uri=localhost:8888&scope=streaming")));
    resize(500, 640);
    show();
}
