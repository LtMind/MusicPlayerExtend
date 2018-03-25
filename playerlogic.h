#ifndef PLAYERLOGIC_H
#define PLAYERLOGIC_H

#include <QObject>

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "mainwidget.h"
#include "settingwidget.h"
#include "songfiles.h"
#include "lyricfiles.h"
#include "desktoplyricwidget.h"

class PlayerLogic : public QObject
{
    Q_OBJECT

public slots:
    void slotShowDesktopLyricWidget(void);
    void slotChangeSongPathAndLyricPath(
            QString songPath, QString lyricPath);
    void slotShowSettingWigdet(void);
    void slotControlPlayMode(int mode);
    void slotControlNext(void);
    void slotControlPrev(void);
    void slotControlPlay(void);
    void slotControlPosition(int position);
    void slotControlVolume(int volume);
    void slotControlSongChange(int index);

public:
    explicit PlayerLogic(QObject *parent = 0);
    ~PlayerLogic();

    void showMainWidget(void);

private slots:
    ///歌曲切换槽
    void slotCurrentIndexChanged(int position);
    ///歌曲播放进度自定义槽
    void slotPositionChanged(qint64 position);
    ///当前歌曲总时长自定义槽
    void slotDurationChanged(qint64 duration);

private:
    ///获取歌词
    LyricFiles *m_lyricFiles;
    void gainCurrentSongLyrics(void);

    ///初始化播放列表
    int m_playMode;
    int m_playIndex; //当前播放索引
    QMediaPlaylist *m_playlist;
    SongFiles *m_songFiles;
    void initPlayList(void);

    ///初始化播放器
    QString m_songName;
    qint64 m_totalPlayerTime;
    qint64 m_currentPlayerTime;
    QString m_playPosition;
    QMediaPlayer *m_player;
    void initPlayer(void);

    ///初始化用户界面
    MainWidget *m_mainWidget;
    void initMainWidget(void);

    SettingWidget *m_settingWidget;
    void initSettingWidget(void);

    DesktopLyricWidget *m_desktopLyricWidget;
    void initDesktopLyricWidget(void);
};

#endif // PLAYERLOGIC_H
