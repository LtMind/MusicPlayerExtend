#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QWidget
{
    Q_OBJECT

signals:
    void signalChangeSongPathAndLyricPath(
            QString songPath, QString lyricPath);

public:
    explicit SettingWidget(QWidget *parent = 0);
    ~SettingWidget();

    bool writeInit(QString group, QString key, QString value);
    bool readInit(QString group, QString key, QString &value);

private slots:
    void on_pb_save_clicked();
    void on_pb_songsPath_clicked();
    void on_pb_lyricsPath_clicked();

private:
    Ui::SettingWidget *ui;

    QString m_settingFileName;
};

#endif // SETTINGWIDGET_H
