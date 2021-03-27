#pragma once

#include <QObject>

class Api : public QObject
{
    Q_OBJECT

public:
    Api();
    void acessToken();

signals:
    void on_acessToken(bool value);

};
