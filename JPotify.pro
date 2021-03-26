TEMPLATE = subdirs

api.subdir                      = src/Api
testes.subdir                   = Testes
db.subdir                       = src/Db
dao.subdir                      = src/Dao
app.subdir                      = src/App

#dependencias
dao.depends                     = db
#app.depends                 = api db dao
testes.depends                  = api db dao

SUBDIRS += \
    app \
    api \
    db \
    dao \
    testes
