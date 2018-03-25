#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QDebug>
#include <QMouseEvent>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    initWidgetUnits();

    connect(ui->pb_player, SIGNAL(clicked()),
            this, SIGNAL(signalControlPlay()));
    connect(ui->pb_desktopLyric, SIGNAL(clicked()),
            this, SIGNAL(signalShowDesktopLyricWidget()));
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::initWidgetUnits(void)
{
    this->setWindowFlags(Qt::FramelessWindowHint);

    //隐藏水平方向和垂直方向的滚动条
    ui->lw_songNameList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->lw_songNameList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->lw_lyricShow->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->lw_lyricShow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWidget::setWidgetPlayModeStyleSheet(QString mode)
{
    ui->pb_playMode->setStyleSheet(mode);
}

void MainWidget::setWidgetPlaylistSongs(QStringList list)
{
    ui->lw_songNameList->addItems(list);
    qDebug() << "MainWidget::setWidgetPlaylistSongs";
}

void MainWidget::clearWidgetPlaylistSongs()
{
    ui->lw_songNameList->clear();
    qDebug() << "MainWidget::clearWidgetPlaylistSongs";
}

void MainWidget::setWidgetCurrentSongPlayRailTimeLyric(quint64 index)
{
    ui->lw_lyricShow->setCurrentRow(index);
}

void MainWidget::setWidgetCurrentSongLyricShow(QStringList list)
{
    ui->lw_lyricShow->clear();
    ui->lw_lyricShow->addItems(list);
    for(int i = 0; i < list.length(); i++)
    {
        ui->lw_lyricShow->item(i)->setTextAlignment(Qt::AlignCenter);
    }

}

void MainWidget::setWidgetCurrentSongName(int index, QString name)
{
    ui->lw_songNameList->setCurrentRow(index);
    ui->lb_songName->setText(name);
}

void MainWidget::setWidgetCurrentSongPlayPositionTextShow(QString &time)
{
    ui->lb_position->setText(time);
}

void MainWidget::setWidgetCurrentSongTotalTime(quint64 time)
{
    ui->hs_position->setMaximum(time);
}

void MainWidget::setWidgetCurrentSongPlayPosition(quint64 time)
{
    if(!ui->hs_position->isSliderDown()) //当slider不被按下时
    {
        ui->hs_position->setValue(time);
    }
}

void MainWidget::setWidgetPlayButtonStyleSheet(QString style)
{
    ui->pb_player->setStyleSheet(style);
}

//void MainWidget::on_pb_player_clicked()
//{
//    emit signalControlPlay();
//}

void MainWidget::on_hs_position_sliderMoved(int position)
{
    emit signalControlPosition(position);
}

void MainWidget::on_hs_volume_sliderMoved(int position)
{
    emit signalControlVolume(position);
}

void MainWidget::on_lw_songNameList_clicked(const QModelIndex &index)
{
    emit signalControlSongChange(index.row());
    ui->pb_player->setStyleSheet("border-image: "
                 "url(:/images/skins/images/pausePressed.png);");
}

void MainWidget::on_pb_prev_clicked()
{
    emit signalControlPrev();
}

void MainWidget::on_pb_next_clicked()
{
    emit signalControlNext();
}

void MainWidget::on_pb_playMode_clicked()
{
    m_playMode++;
    m_playMode %= 5;
    emit signalControlPlayMode(m_playMode);
}

void MainWidget::on_pb_min_clicked()
{
    this->showMinimized();
}

void MainWidget::on_pb_max_clicked()
{
    if(this->isMaximized())
    {
        this->showNormal();
    }else{
        this->showMaximized();
    }
}

void MainWidget::on_pb_close_clicked()
{
    this->close();
}

void MainWidget::mousePressEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton)
    {
        m_widgetMove = ev->globalPos() - this->frameGeometry().topLeft();
        ev->accept();
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton)
    {
        move(ev->globalPos() - m_widgetMove);
        ev->accept();
    }
}

void MainWidget::on_pb_setting_clicked()
{
    emit signalShowSettingWigdet();
}
