#include "settingwidget.h"
#include "ui_settingwidget.h"

#include <QDebug>
#include <QSettings>
#include <QFileDialog>

#include "songfiles.h"
#include "lyricfiles.h"

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);

    m_settingFileName = "./../MusicPlayerExtend/user.ini";


    QString songsPath;
    QString lyricsPath;
    readInit("Path", "Songs", songsPath);
    readInit("Path", "Lyrics", lyricsPath);

    ui->le_songsPath->setText(songsPath);
    ui->le_lyricsPath->setText(lyricsPath);

    SongFiles::setCurrentSongPath(songsPath);
    LyricFiles::setLyricPath(lyricsPath);
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

bool SettingWidget::writeInit(QString group, QString key, QString value)
{
    if(group.isEmpty() || key.isEmpty())
    {
        return false;
    }
    else
    {
        //创建配置文件操作对象
        QSettings config(m_settingFileName, QSettings::IniFormat);

        //将信息写入配置文件
        config.beginGroup(group);
        config.setValue(key, value);
        config.endGroup();

        return true;
    }
}

bool SettingWidget::readInit(QString group, QString key, QString &value)
{
    value.clear();
    if(m_settingFileName.isEmpty() || key.isEmpty())
    {
        return false;
    }
    else
    {
        //创建配置文件操作对象
        QSettings config(m_settingFileName, QSettings::IniFormat);

        //读取用户配置信息
        value = config.value(group + "/" + key).toString();

        return true;
    }
}

void SettingWidget::on_pb_save_clicked()
{
    writeInit("Path", "Songs", ui->le_songsPath->text());
    writeInit("Path", "Lyrics", ui->le_lyricsPath->text());

    emit signalChangeSongPathAndLyricPath(ui->le_songsPath->text(),
                                          ui->le_lyricsPath->text());
}

void SettingWidget::on_pb_songsPath_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select the song path"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    ui->le_songsPath->setText(dir);
}

void SettingWidget::on_pb_lyricsPath_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select the lyric path"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    ui->le_lyricsPath->setText(dir);
}
