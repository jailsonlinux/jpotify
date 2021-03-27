#include "api.h"

#include <QDebug>
Api::Api()
{
}

void Api::acessToken()
{
    qDebug() << "acessToker: true";
    emit on_acessToken(true);

}
