#include <iostream>

#include <QtCore/QDebug>
#include <QtGui/QWindow>
#include <QtQml/QQmlApplicationEngine>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

#include <vlcpp/vlc.hpp>

#include "windowmanager.h"

int main(int argc, char *argv[])
{
    const QUrl qml_src = QUrl(QStringLiteral("qrc:/main.qml"));
    WId handle = 0;

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(qml_src);

    QObject *m_rootObject = engine.rootObjects().constFirst();
    QWindow *window = qobject_cast<QWindow*>(m_rootObject);
    window->show();

    QWidget mainWindow;
    VideoWidget videoWidget(&mainWindow);
    handle = videoWidget.winId();
    videoWidget.show();

    WindowManager wm(window, &videoWidget);


    const char *args[1];
    args[0] = "-q";
    VLC::Instance inst(1, args);
    VLC::MediaPlayer mp(inst);
    VLC::Media video(inst, "video.mp4",
                     VLC::Media::FromPath);
    mp.setMedia(video);
    mp.setMute(true);

#ifdef Q_OS_WIN
    mp.setHwnd(reinterpret_cast<HWND>(handle));
#else
    mp.setXwindow((uint32_t) handle);
#endif

    mp.play();

    return app.exec();
}
