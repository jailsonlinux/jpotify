#include "uiplaylist.h"
#include "ui_uiplaylist.h"

UiPlaylist::UiPlaylist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiPlaylist),
    m_qtdMusicas{0}
{
    ui->setupUi(this);

}

UiPlaylist::~UiPlaylist()
{
    delete ui;
}

void UiPlaylist::on_btnCancelar_clicked()
{
    emit on_cancelarPlaylist();
}

QString UiPlaylist::getDuracao() const
{
    return QStringLiteral("%1min %2s").arg(m_duracao.toString("mm")).arg(m_duracao.toString("ss"));
}

void UiPlaylist::setDuracao(const QTime &duracao)
{
    m_duracao = duracao;
}


int UiPlaylist::getQtdMusicas() const
{
    return m_qtdMusicas;
}

void UiPlaylist::setQtdMusicas(int qtdMusicas)
{
    m_qtdMusicas = qtdMusicas;
}

PlayList *UiPlaylist::getPlaylist() const
{
    return m_playlist;
}

void UiPlaylist::setPlaylist(PlayList *value)
{
    m_playlist = value;
    //Edicao/Adicao de Playlist
    m_duracao = *new QTime;
    if(m_playlist == nullptr || m_playlist->nome().isEmpty() || m_playlist->userid() <= 0){

        ui->stackedWidget->setCurrentIndex(1);
    }//Visualizacao
    else
    {
        std::for_each(std::begin(m_playlist->getMusicas()->getMusicas()), std::end(m_playlist->getMusicas()->getMusicas()), [&](Musica *musica){
           m_duracao = m_duracao.addSecs(musica->duracao());
        });
        ui->stackedWidget->setCurrentIndex(0);
        ui->lblPlaylistNome->setText(m_playlist->nome());
        const QString detalhes = QStringLiteral("<b>%1 <b> - %2 músicas, %3")
                .arg(m_usuario->nome())
                .arg(m_qtdMusicas)
                .arg(getDuracao());

        ui->lblInfo->setText(detalhes);
    }
}



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

void UiPlaylist::setUsuario(Usuario *usuario)
{
    m_usuario = usuario;
}

void UiPlaylist::on_btnExcluir_clicked()
{
    emit on_excluirPlayList(m_playlist);
}

void UiPlaylist::on_btnEditar_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->edtNome->setText(m_playlist->nome());
    ui->edtDescricao->setText(m_playlist->descricao());
}
