#include "pesquisacontroller.h"

/**
 * @brief PesquisaController::PesquisaController
 * @param api
 * recebe instancia da api logada e com ela gerencia lista de musicas da pesquisa recente.
 */
PesquisaController::PesquisaController(Api *api):
    m_api(api)
  ,m_musicaList(new MusicaList)
{

}

/**
 * @brief PesquisaController::pesquisarMusicas
 * @param termo
 * executa a busca pela API a determinado termo...no momento apenas tracks.
 */
void PesquisaController::pesquisarMusicas(const QString &termo)
{
    m_musicaList->clear();

    if(!m_api->precisaAutenticar()){

        QJsonObject resultJson =  m_api->pesquisaMusicas(termo);
        //Extrair do json todos os itens de tracks encontrados...
        const auto &tracks = resultJson.value(QStringLiteral("tracks")).toObject().toVariantMap()[QStringLiteral("items")].toList();

        //adicionar os encontrados a lista de musicas..
        for (const auto &track: tracks) {
            const auto &map = track.toMap();
            // nao interessa os que nao tem amostras
            if (map[QStringLiteral("preview_url")].toString().isEmpty())
                continue;

            Musica *musica = new Musica();
            musica->setNome(map[QStringLiteral("name")].toString());
            musica->setPreviewUrl(map[QStringLiteral("preview_url")].toString());
            musica->setArtista(map[QStringLiteral("artists")].toList().at(0).toMap()[QStringLiteral("name")].toString());
            musica->setImagem(map[QStringLiteral("album")].toMap()[QStringLiteral("images")].toList().last().toMap()[QStringLiteral("url")].toString());
            musica->setAlbum(map[QStringLiteral("album")].toMap()[QStringLiteral("name")].toString());
            musica->setDuracao(map[QStringLiteral("duration_ms")].toInt());
            musica->setKey(map[QStringLiteral("id")].toString());

            m_musicaList->addMusica(musica);
        }
    }

    emit on_pesquisaConcluida();
}

/**
 * @brief PesquisaController::musicaList
 * @return lista de musicas da ultima busca.
 */
MusicaList *PesquisaController::musicaList() const
{
    return m_musicaList;
}

