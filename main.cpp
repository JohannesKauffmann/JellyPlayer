#include <vlcpp/vlc.hpp>

#include <QtCore/QDebug>
#include <QtGui/QGuiApplication>
#include <QtGui/QWindow>
#include <QtQml/QQmlApplicationEngine>

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    WId handle = 0;
    QObject *m_rootObject = engine.rootObjects().constFirst();
    if(m_rootObject)
    {
        QWindow *window = qobject_cast<QWindow *>(m_rootObject);
        if(window)
        {
            handle = window->winId();
        }
    }

    VLC::Instance inst(0, NULL);
    VLC::MediaPlayer mp(inst);
    VLC::Media video(inst, "http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/BigBuckBunny.mp4",
                     VLC::Media::FromLocation);
    mp.setMedia(video);

#ifdef Q_OS_WIN
    mp.setHwnd(reinterpret_cast<HWND>(handle));
#else
    mp.setXwindow((uint32_t) handle);
#endif

    mp.play();

    return app.exec();
}
