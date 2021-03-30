#include "tocaplaylist.h"
#include "ui_tocaplaylist.h"
#include "widgetutil.h"

/**
 * @brief TocaPlaylist::TocaPlaylist
 * @param parent
 */
TocaPlaylist::TocaPlaylist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TocaPlaylist),
    m_musica(nullptr),
    m_musicaList(new MusicaList),
    m_playlist(new PlayList),
    m_usuario(new Usuario)
{
    ui->setupUi(this);
}

/**
 * @brief TocaPlaylist::~TocaPlaylist
 */
TocaPlaylist::~TocaPlaylist()
{
    delete ui;
}


/**
 * @brief TocaPlaylist::setPlaylists
 * @param playlists
 */
void TocaPlaylist::setPlaylist(PlayList *playlist)
{
    m_playlist = playlist;
    m_musicaList = m_playlist->getMusicas();

    m_duracao = m_playlist->getDuracaoTotal();
    //Edicao/Adicao de Playlist

    if(m_playlist != nullptr || !m_playlist->nome().isEmpty()){

        ui->lblPlaylistNome->setText(m_playlist->nome());
        ui->lblPlaylistDescricao->setText(m_playlist->descricao());

        const QString detalhes = QStringLiteral("<b>%1 <b> - %2 músicas, duração %3")
                .arg(m_usuario->nome())
                .arg(m_playlist->getMusicas()->size())
                .arg(m_playlist->getDuracaoToString());

        ui->lblInfo->setText(detalhes);
        preencheGrid();
    }

}

/**
 * @brief TocaPlaylist::resizeEvent
 * @param event
 */
void TocaPlaylist::resizeEvent(QResizeEvent *event)
{
    //Devido a semelhança da pesquisa com a playlist do usuario, foi centralizado numa util..
    WidgetUtil::resizeGrid(this->width(), ui->tabelaResultados);

    QWidget::resizeEvent(event);
}

/**
 * @brief TocaPlaylist::preencheGrid
 */
void TocaPlaylist::preencheGrid()
{
    WidgetUtil::preencheGrid(ui->tabelaResultados, m_musicaList);
}

void TocaPlaylist::setUsuario(Usuario *usuario)
{
    m_usuario = usuario;
}

void TocaPlaylist::on_tabelaResultados_doubleClicked(const QModelIndex &index)
{
    QTableWidgetItem *item =  ui->tabelaResultados->item(ui->tabelaResultados->currentRow(), ColunasTabela::Key);
    const QString keyMusica = item->text();
    Musica *musica = m_musicaList->getMusicaByKey(keyMusica);
    const int playlistId = m_playlist->getId();

    if(musica != nullptr && !musica->key().isEmpty() && playlistId > -1){
        musica->setPlaylistid(m_playlist->getId());
        const int rowIdx = index.row();
        emit on_playCurrentMusica(playlistId, musica, rowIdx);
    }
}
