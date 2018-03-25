#ifndef LYRICFILES_H
#define LYRICFILES_H

#include <QObject>
#include <QStringList>
#include <QMap>

class LyricFiles : public QObject
{
    Q_OBJECT
public:
    explicit LyricFiles(QObject *parent = 0);

    void gainCurrentLyric(QString songName);
    QStringList &getLyricList(void);
    QMap<quint64, quint64> getMapLyricIndex(void);
    static void setLyricPath(QString lyricPath);

private:
    static QString m_lyricPath;
    QStringList m_lyricList;
    QMap<quint64, quint64> m_mapLyricIndex; //time, index

};

#endif // LYRICFILES_H
