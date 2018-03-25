#include "songfiles.h"

#include <QFileInfoList>
#include <QDir>

QString SongFiles::m_songPath = "";

SongFiles::SongFiles(QObject *parent) : QObject(parent)
{
//    m_songPath.clear();
    m_songNameList.clear();
    m_songSourceList.clear();
}

SongFiles::~SongFiles()
{

}

void SongFiles::setCurrentSongPath(const QString songPath)
{
    m_songPath = songPath;
}

void SongFiles::gainSongsSource(void)
{
    QDir dir(m_songPath);
    QFileInfoList infos =
            dir.entryInfoList(QStringList() << "*.mp3" << "*.flac",
                                          QDir::Files, QDir::Name);
    foreach(const QFileInfo &info, infos)
    {
        m_songNameList.append(info.baseName());
        m_songSourceList.append(info.absoluteFilePath());
    }
}

QStringList &SongFiles::getSongNameList(void)
{
    return m_songNameList;
}

QStringList &SongFiles::getSongSourceList(void)
{
    return m_songSourceList;
}

