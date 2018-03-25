#include "lyricfiles.h"

#include <QFile>
#include <QDebug>
#include <QtMath>

QString LyricFiles::m_lyricPath = "";

LyricFiles::LyricFiles(QObject *parent) : QObject(parent)
{

}

void LyricFiles::gainCurrentLyric(QString songName)
{
    QString fileName = m_lyricPath + "/" + songName + ".lrc";
    QFile lyricFile(fileName);
    if(!lyricFile.open(QIODevice::ReadOnly)){
        qDebug() << "Error: File Opened";
    }else{
        quint64 index = 0;
        QString line, lyric, pos;
        QStringList posAndLyric;
        QTextStream in(&lyricFile);
        m_lyricList.clear();
        m_mapLyricIndex.clear(); //歌词跟踪
        while(!in.atEnd()){
            line = in.readLine();
            posAndLyric = line.split("]");
            lyric = posAndLyric.at(1);
            if(!lyric.isEmpty())
            {
                pos = posAndLyric.at(0).mid(0,6);
                QStringList time = pos.remove("[").split(":");
                quint64 t = time[0].toInt()*60 + time[1].toInt();
                m_mapLyricIndex.insert(t, index++); //歌词跟踪逻辑数据记录
                m_lyricList.append(lyric);
            }
            posAndLyric.clear();
        }
        lyricFile.close();
    }
}

QStringList &LyricFiles::getLyricList(void)
{
    return m_lyricList;
}

QMap<quint64, quint64> LyricFiles::getMapLyricIndex(void)
{
    return m_mapLyricIndex;
}

void LyricFiles::setLyricPath(QString lyricPath)
{
    m_lyricPath = lyricPath;
}

