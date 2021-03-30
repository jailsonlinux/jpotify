#include "uiplaylist.h"
#include "ui_uiplaylist.h"

/**
 * @brief UiPlaylist::UiPlaylist
 * @param parent
 * tela de cadastro de playlists
 */
UiPlaylist::UiPlaylist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiPlaylist),
    m_playlist(new PlayList),
    m_qtdMusicas{0},
    m_usuario(new Usuario)
{
    ui->setupUi(this);
}

/**
 * @brief UiPlaylist::~UiPlaylist
 */
UiPlaylist::~UiPlaylist()
{
    delete ui;
}

/**
 * @brief UiPlaylist::on_btnCancelar_clicked
 */
void UiPlaylist::on_btnCancelar_clicked()
{
    emit on_cancelarPlaylist();
}

/**
 * @brief UiPlaylist::getDuracao
 * @return
 */
QString UiPlaylist::getDuracao() const
{
    const QString duracao = QString("%1min %2s")
            .arg(QString::number(m_duracao.minute()).rightJustified(2, '0'))
            .arg(QString::number(m_duracao.second()).rightJustified(2, '0'));
    return  duracao;
}

/**
 * @brief UiPlaylist::setDuracao
 * @param duracao
 */
void UiPlaylist::setDuracao(const QTime &duracao)
{
    m_duracao = duracao;
}

/**
 * @brief UiPlaylist::getQtdMusicas
 * @return
 */
int UiPlaylist::getQtdMusicas() const
{
    return m_qtdMusicas;
}

/**
 * @brief UiPlaylist::setQtdMusicas
 * @param qtdMusicas
 */
void UiPlaylist::setQtdMusicas(int qtdMusicas)
{
    m_qtdMusicas = qtdMusicas;
}

/**
 * @brief UiPlaylist::getPlaylist
 * @return
 */
PlayList *UiPlaylist::getPlaylist() const
{
    return m_playlist;
}

/**
 * @brief UiPlaylist::setPlaylist
 * @param value
 */
void UiPlaylist::setPlaylist(PlayList *value)
{
    m_playlist = value;
    m_duracao = m_playlist->getDuracaoTotal();
    //Edicao/Adicao de Playlist

    if(m_playlist == nullptr || m_playlist->nome().isEmpty() || m_playlist->userid() <= 0){
        ui->stackedWidget->setCurrentIndex(1);
    }//Visualizacao
    else
    {
        ui->stackedWidget->setCurrentIndex(0);
        ui->lblPlaylistNome->setText(m_playlist->nome());
        ui->lblPlaylistDescricao->setText(m_playlist->descricao());

        const QString detalhes = QStringLiteral("<b>%1 <b> - %2 músicas, %3")
                .arg(m_usuario->nome())
                .arg(m_playlist->getMusicas()->size())
                .arg(getDuracao());

        ui->lblInfo->setText(detalhes);
    }
}

/**
 * @brief UiPlaylist::on_btnSalvar_clicked
 */
void UiPlaylist::on_btnSalvar_clicked()
{
    if(m_playlist == nullptr)
        m_playlist= new PlayList();

    m_playlist->setUsuarioid(m_usuario->id());
    m_playlist->setNome(ui->edtNome->text().trimmed());
    m_playlist->setDescricao(ui->edtDescricao->text().trimmed());
    m_playlist->setUsuarioid(m_usuario->id());

    emit on_salvarPlayList(m_playlist);
}

/**
 * @brief UiPlaylist::setUsuario
 * @param usuario
 */
void UiPlaylist::setUsuario(Usuario *usuario)
{
    m_usuario = usuario;
}

/**
 * @brief UiPlaylist::on_btnExcluir_clicked
 */
void UiPlaylist::on_btnExcluir_clicked()
{
    emit on_excluirPlayList(m_playlist);
}

/**
 * @brief UiPlaylist::on_btnEditar_clicked
 */
void UiPlaylist::on_btnEditar_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->edtNome->setText(m_playlist->nome());
    ui->edtDescricao->setText(m_playlist->descricao());
}
