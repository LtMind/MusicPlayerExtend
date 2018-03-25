#ifndef DESKTOPLYRICWIDGET_H
#define DESKTOPLYRICWIDGET_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class DesktopLyricWidget;
}

class DesktopLyricWidget : public QWidget
{
    Q_OBJECT

signals:
    void signalControlPlayMode(int index);
    void signalControlNext(void);
    void signalControlPrev(void);
    void signalControlPlay(void);

public:
    explicit DesktopLyricWidget(QWidget *parent = 0);
    ~DesktopLyricWidget();

    void setWidgetPlayButtonStyleSheet(QString style);
    void setWidgetCurrentSongName(QString name);
    void setWidgetPlayModeStyleSheet(QString mode);

    void showCurrentLyric(int index, QString lyric);

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

private slots:
    void on_pb_close_clicked();
    void on_pb_playMode_clicked();

private:
    Ui::DesktopLyricWidget *ui;

    int m_playMode;
    QPoint m_widgetMove;
};

#endif // DESKTOPLYRICWIDGET_H
