#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QtCore/QObject>
#include <QtWidgets/QWidget>

class QWindow;


class VideoWidget : public QWidget
{
public:
    VideoWidget(QWidget *parent)
        : QWidget(parent, Qt::Tool | Qt::FramelessWindowHint)
    {

    }

};


class WindowManager : public QObject
{
    Q_OBJECT

public:
    WindowManager(QWindow *qmlWindow, QWidget *videoWidget, QObject *parent = nullptr);

private slots:
    void onXChanged(int x);
    void onYChanged(int y);
    void onWidthChanged(int width);
    void onHeightChanged(int height);
    void onWindowStateChanged(Qt::WindowState windowState);

private:
    QWindow *m_qmlWindow;
    QWidget *m_videoWidget;
};

#endif // WINDOWMANAGER_H
