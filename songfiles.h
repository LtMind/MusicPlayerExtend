#ifndef SONGFILES_H
#define SONGFILES_H

#include <QObject>
#include <QStringList>

class SongFiles : public QObject
{
    Q_OBJECT
public:
    explicit SongFiles(QObject *parent = 0);
    ~SongFiles();

    static void setCurrentSongPath(const QString songPath);

    void gainSongsSource(void);
    QStringList &getSongNameList(void);
    QStringList &getSongSourceList(void);

private:
    static QString m_songPath;
    QStringList m_songNameList;
    QStringList m_songSourceList;
};

#endif // SONGFILES_H
