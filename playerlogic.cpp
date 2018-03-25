#include "playerlogic.h"

#include <QDir>
#include <QFileInfoList>

#include <QTime>

PlayerLogic::PlayerLogic(QObject *parent) : QObject(parent)
{
    initMainWidget();
    initSettingWidget();
    initDesktopLyricWidget();

    m_player = new QMediaPlayer;
    m_playlist = new QMediaPlaylist;
    m_lyricFiles = new LyricFiles;
    m_songFiles = new SongFiles;
    m_songFiles->gainSongsSource();

    initPlayList();
    initPlayer();
}

PlayerLogic::~PlayerLogic()
{

}

void PlayerLogic::slotChangeSongPathAndLyricPath(
        QString songPath, QString lyricPath)
{
    //清除原有的资源内容及显示
    m_playlist->clear();
    m_mainWidget->clearWidgetPlaylistSongs();
    m_songFiles->getSongNameList().clear();
    m_songFiles->getSongSourceList().clear();

    //填充新的资源内容
    m_lyricFiles->setLyricPath(lyricPath);
    m_songFiles->setCurrentSongPath(songPath);
    m_songFiles->gainSongsSource();

    initPlayList();
    initPlayer();
}

void PlayerLogic::initPlayList(void)
{
    foreach(QString songSource, m_songFiles->getSongSourceList())
    {
        m_playlist->addMedia(QUrl(songSource));
    }

    m_playMode = 3;
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);

    m_mainWidget->setWidgetPlaylistSongs(m_songFiles->getSongNameList());

    connect(m_playlist, SIGNAL(currentIndexChanged(int)),
            this, SLOT(slotCurrentIndexChanged(int)));
}

void PlayerLogic::slotCurrentIndexChanged(int position)
{
    m_songName = m_songFiles->getSongNameList().at(position);
    m_mainWidget->setWidgetCurrentSongName(position, m_songName);
    m_desktopLyricWidget->setWidgetCurrentSongName(m_songName);

    gainCurrentSongLyrics();

    if(m_lyricFiles->getLyricList().length() > 2)
    {
        m_desktopLyricWidget->showCurrentLyric(0, m_lyricFiles->getLyricList().at(0));
        m_desktopLyricWidget->showCurrentLyric(1, m_lyricFiles->getLyricList().at(1));

    }
}

void PlayerLogic::gainCurrentSongLyrics(void)
{
    m_lyricFiles->gainCurrentLyric(m_songName);
    m_mainWidget->setWidgetCurrentSongLyricShow(m_lyricFiles->getLyricList());
}

void PlayerLogic::initPlayer(void)
{
    m_player->setPlaylist(m_playlist);
    m_player->setVolume(50);

    m_playIndex = 0;
    m_playlist->setCurrentIndex(m_playIndex);

    connect(m_player, SIGNAL(durationChanged(qint64)),
            this, SLOT(slotDurationChanged(qint64)));
    connect(m_player, SIGNAL(positionChanged(qint64)),
            this, SLOT(slotPositionChanged(qint64)));
}

void PlayerLogic::slotDurationChanged(qint64 duration)
{
    m_currentPlayerTime = 0;
    m_totalPlayerTime = duration / 1000;

    QTime currentTime((m_currentPlayerTime/3600)%60, (m_currentPlayerTime/60)%60,
                      m_currentPlayerTime%60, (m_currentPlayerTime*1000)%1000);
    QTime totalTime((m_totalPlayerTime/3600)%60, (m_totalPlayerTime/60)%60,
                    m_totalPlayerTime%60, (m_totalPlayerTime*1000)%1000);

    m_playPosition = currentTime.toString("mm:ss")
                                + "/" + totalTime.toString("mm:ss");

    m_mainWidget->setWidgetCurrentSongPlayPositionTextShow(m_playPosition);
    m_mainWidget->setWidgetCurrentSongTotalTime(m_totalPlayerTime);
}

void PlayerLogic::slotPositionChanged(qint64 position)
{
    m_currentPlayerTime = position / 1000;

    QTime currentTime((m_currentPlayerTime/3600)%60, (m_currentPlayerTime/60)%60,
                      m_currentPlayerTime%60, (m_currentPlayerTime*1000)%1000);
    QTime totalTime((m_totalPlayerTime/3600)%60, (m_totalPlayerTime/60)%60,
                    m_totalPlayerTime%60, (m_totalPlayerTime*1000)%1000);

    m_playPosition = currentTime.toString("mm:ss")
                                + "/" + totalTime.toString("mm:ss");
    m_mainWidget->setWidgetCurrentSongPlayPositionTextShow(m_playPosition);

    if(m_lyricFiles->getMapLyricIndex().contains(m_currentPlayerTime))
    {
        int currentLyricIndex = m_lyricFiles->getMapLyricIndex().value(m_currentPlayerTime);
        m_mainWidget->setWidgetCurrentSongPlayRailTimeLyric(currentLyricIndex);

        m_desktopLyricWidget->showCurrentLyric(currentLyricIndex+1,
                                               m_lyricFiles->getLyricList().at(currentLyricIndex+1));
    }

    m_mainWidget->setWidgetCurrentSongPlayPosition(m_currentPlayerTime);
}

void PlayerLogic::initSettingWidget(void)
{
    m_settingWidget = new SettingWidget;
    connect(m_mainWidget, SIGNAL(signalShowSettingWigdet()),
            this, SLOT(slotShowSettingWigdet()));
    connect(m_settingWidget, SIGNAL(signalChangeSongPathAndLyricPath(QString,QString)),
            this, SLOT(slotChangeSongPathAndLyricPath(QString,QString)));
}

void PlayerLogic::initDesktopLyricWidget(void)
{
    m_desktopLyricWidget = new DesktopLyricWidget;
    connect(m_mainWidget, SIGNAL(signalShowDesktopLyricWidget()),
            this, SLOT(slotShowDesktopLyricWidget()));
    connect(m_desktopLyricWidget, SIGNAL(signalControlPlayMode(int)),
            this, SLOT(slotControlPlayMode(int)));
    connect(m_desktopLyricWidget, SIGNAL(signalControlNext()),
            this, SLOT(slotControlNext()));
    connect(m_desktopLyricWidget, SIGNAL(signalControlPrev()),
            this, SLOT(slotControlPrev()));
    connect(m_desktopLyricWidget, SIGNAL(signalControlPlay()),
            this, SLOT(slotControlPlay()));
}

void PlayerLogic::slotShowDesktopLyricWidget(void)
{
    m_desktopLyricWidget->show();
}

void PlayerLogic::slotShowSettingWigdet(void)
{
    m_settingWidget->show();
}


void PlayerLogic::initMainWidget(void)
{
    m_mainWidget = new MainWidget;

    connect(m_mainWidget, SIGNAL(signalControlPlayMode(int)),
            this, SLOT(slotControlPlayMode(int)));
    connect(m_mainWidget, SIGNAL(signalControlNext()),
            this, SLOT(slotControlNext()));
    connect(m_mainWidget, SIGNAL(signalControlPrev()),
            this, SLOT(slotControlPrev()));
    connect(m_mainWidget, SIGNAL(signalControlPlay()),
            this, SLOT(slotControlPlay()));
    connect(m_mainWidget, SIGNAL(signalControlPosition(int)),
            this, SLOT(slotControlPosition(int)));
    connect(m_mainWidget, SIGNAL(signalControlSongChange(int)),
            this, SLOT(slotControlSongChange(int)));
    connect(m_mainWidget, SIGNAL(signalControlVolume(int)),
            this, SLOT(slotControlVolume(int)));
}

void PlayerLogic::showMainWidget(void)
{
    m_mainWidget->show();
}

void PlayerLogic::slotControlPlayMode(int mode)
{
    m_playMode = mode;
    switch (m_playMode) {
    case QMediaPlaylist::CurrentItemOnce:
        m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        m_mainWidget->setWidgetPlayModeStyleSheet("border-image: "
                                            "url(:/images/skins/images/currentItemOncePressed.png)");
        m_desktopLyricWidget->setWidgetPlayModeStyleSheet("border-image: "
                                            "url(:/images/skins/images/currentItemOncePressed.png)");
        break;
    case QMediaPlaylist::CurrentItemInLoop:
        m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        m_mainWidget->setWidgetPlayModeStyleSheet("border-image: "
                                            "url(:/images/skins/images/currentItemInLoopPressed.png)");
        m_desktopLyricWidget->setWidgetPlayModeStyleSheet("border-image: "
                                            "url(:/images/skins/images/currentItemInLoopPressed.png)");
        break;
    case QMediaPlaylist::Sequential:
        m_playlist->setPlaybackMode(QMediaPlaylist::Sequential);
        m_mainWidget->setWidgetPlayModeStyleSheet("border-image: "
                                            "url(:/images/skins/images/sequentialPressed.png)");
        m_desktopLyricWidget->setWidgetPlayModeStyleSheet("border-image: "
                                            "url(:/images/skins/images/sequentialPressed.png)");
        break;
    case QMediaPlaylist::Loop:
        m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
        m_mainWidget->setWidgetPlayModeStyleSheet("border-image: "
                                            "url(:/images/skins/images/loopPressed.png)");
        m_desktopLyricWidget->setWidgetPlayModeStyleSheet("border-image: "
                                            "url(:/images/skins/images/loopPressed.png)");
        break;
    case QMediaPlaylist::Random:
        m_playlist->setPlaybackMode(QMediaPlaylist::Random);
        m_mainWidget->setWidgetPlayModeStyleSheet("border-image: "
                                            "url(:/images/skins/images/randomPressed.png)");
        m_desktopLyricWidget->setWidgetPlayModeStyleSheet("border-image: "
                                            "url(:/images/skins/images/randomPressed.png)");
        break;
    default: break;
    }
}

void PlayerLogic::slotControlNext(void)
{
    m_playIndex = m_playlist->nextIndex();

    if(m_playIndex == -1)
    {
        m_player->stop();
        m_mainWidget->setWidgetPlayButtonStyleSheet("border-image: "
                                              "url(:/images/skins/images/playStartPressed.png)");
        m_desktopLyricWidget->setWidgetPlayButtonStyleSheet("border-image: "
                                              "url(:/images/skins/images/playStartPressed.png)");
    }else{
        m_playlist->setCurrentIndex(m_playIndex);
    }
}

void PlayerLogic::slotControlPrev(void)
{
    m_playIndex = m_playlist->previousIndex();
    if(m_playIndex == -1)
    {
        m_player->stop();
        m_mainWidget->setWidgetPlayButtonStyleSheet("border-image: "
                                              "url(:/images/skins/images/playStartPressed.png)");
        m_desktopLyricWidget->setWidgetPlayButtonStyleSheet("border-image: "
                                                            "url(:/images/skins/images/playStartPressed.png)");
    }else{
        m_playlist->setCurrentIndex(m_playIndex);
    }
}

void PlayerLogic::slotControlPlay(void)
{
    if(m_player->state() == QMediaPlayer::PlayingState)
    {
        m_player->pause();
        m_mainWidget->setWidgetPlayButtonStyleSheet("border-image: "
                                             "url(:/images/skins/images/playStartNormal.png);");
        m_desktopLyricWidget->setWidgetPlayButtonStyleSheet("border-image: "
                                                            "url(:/images/skins/images/playStartNormal.png);");
    }else
    {
        m_player->play();
        m_mainWidget->setWidgetPlayButtonStyleSheet("border-image: "
                                              "url(:/images/skins/images/pausePressed.png);");
        m_desktopLyricWidget->setWidgetPlayButtonStyleSheet("border-image: "
                                                                        "url(:/images/skins/images/pausePressed.png);");
    }
}

void PlayerLogic::slotControlPosition(int position)
{
    m_player->setPosition(position * 1000);
}

void PlayerLogic::slotControlVolume(int volume)
{
    m_player->setVolume(volume);
}

void PlayerLogic::slotControlSongChange(int index)
{
    m_playlist->setCurrentIndex(index);
    m_player->play();
}
