#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

signals:
    void signalShowDesktopLyricWidget(void);
    void signalShowSettingWigdet(void);
    void signalControlPlayMode(int index);
    void signalControlNext(void);
    void signalControlPrev(void);
    void signalControlPlay(void);
    void signalControlPosition(int position);
    void signalControlVolume(int volume);
    void signalControlSongChange(int index);

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    void setWidgetPlayModeStyleSheet(QString mode);
    void setWidgetPlayButtonStyleSheet(QString style);
    void setWidgetPlaylistSongs(QStringList list);
    void clearWidgetPlaylistSongs();

    void setWidgetCurrentSongName(int index, QString name);
    void setWidgetCurrentSongPlayPositionTextShow(QString &time);
    void setWidgetCurrentSongPlayPosition(quint64 time);
    void setWidgetCurrentSongTotalTime(quint64 time);
    void setWidgetCurrentSongLyricShow(QStringList list);
    void setWidgetCurrentSongPlayRailTimeLyric(quint64 index);

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

private slots:
    void on_pb_min_clicked();
    void on_pb_max_clicked();
    void on_pb_close_clicked();

    void on_hs_position_sliderMoved(int position);
    void on_hs_volume_sliderMoved(int position);

    void on_lw_songNameList_clicked(const QModelIndex &index);
    void on_pb_prev_clicked();
    void on_pb_next_clicked();
    void on_pb_playMode_clicked();
    void on_pb_setting_clicked();

private:
    Ui::MainWidget *ui;

    ///初始化界面部件
    int m_playMode;
    QPoint m_widgetMove;
    void initWidgetUnits(void);
};

#endif // MAINWIDGET_H
