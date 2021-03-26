#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebEngineView>

class LoginWeb : public QWebEngineView
{
    Q_OBJECT

public:
     LoginWeb(QWidget *parent = nullptr);
      ~LoginWeb() = default;

private:
};

#endif
