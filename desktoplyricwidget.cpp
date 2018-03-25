#include "desktoplyricwidget.h"
#include "ui_desktoplyricwidget.h"

#include <QDebug>

DesktopLyricWidget::DesktopLyricWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DesktopLyricWidget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->lw_lyricShow->item(0)->setTextAlignment(Qt::AlignLeft);
    ui->lw_lyricShow->item(1)->setTextAlignment(Qt::AlignRight);
    ui->lw_lyricShow->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->lw_lyricShow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(ui->pb_play, SIGNAL(clicked()),
            this, SIGNAL(signalControlPlay()));
    connect(ui->pb_next, SIGNAL(clicked()),
            this, SIGNAL(signalControlNext()));
    connect(ui->pb_prev, SIGNAL(clicked()),
            this, SIGNAL(signalControlPrev()));
}

DesktopLyricWidget::~DesktopLyricWidget()
{
    delete ui;
}

void DesktopLyricWidget::showCurrentLyric(int index, QString lyric)
{
    if(index%2==0)
    {
        ui->lw_lyricShow->setCurrentRow(1);
        ui->lw_lyricShow->item(0)->setText(lyric);
    }else
    {
        ui->lw_lyricShow->setCurrentRow(0);
        ui->lw_lyricShow->item(1)->setText(lyric);
    }
}

void DesktopLyricWidget::on_pb_close_clicked()
{
    this->hide();
}

void DesktopLyricWidget::on_pb_playMode_clicked()
{
    m_playMode++;
    m_playMode %= 5;
    emit signalControlPlayMode(m_playMode);
}

void DesktopLyricWidget::setWidgetPlayModeStyleSheet(QString mode)
{
    ui->pb_playMode->setStyleSheet(mode);
}

void DesktopLyricWidget::setWidgetPlayButtonStyleSheet(QString style)
{
    ui->pb_play->setStyleSheet(style);
}

void DesktopLyricWidget::setWidgetCurrentSongName(QString name)
{
    ui->lb_songName->setText(name);
}

void DesktopLyricWidget::mousePressEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton)
    {
        m_widgetMove = ev->globalPos()
                - this->frameGeometry().topLeft();
        ev->accept();
    }
}

void DesktopLyricWidget::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton)
    {
        move(ev->globalPos() - m_widgetMove);
        ev->accept();
    }
}
