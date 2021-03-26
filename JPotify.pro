TEMPLATE = subdirs

api.subdir                      = src/Api
testes.subdir                   = Testes
#widgets.subdir                  = src/Widgets
db.subdir                       = src/Db
dao.subdir                      = src/Dao
app.subdir                      = src/App
#resources.subdir                = src/Widgets/resources

#dependencias
dao.depends                     = db
#widgets.depends                 = api db dao
testes.depends                  = api db dao
#app.depends

SUBDIRS += \
    app \
    api \
    db \
    dao \
#    widgets \
    testes
