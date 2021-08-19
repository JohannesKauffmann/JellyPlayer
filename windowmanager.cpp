#include "windowmanager.h"

#include <QtCore/QDebug>
#include <QtGui/QWindow>
#include <QtWidgets/QWidget>

WindowManager::WindowManager(QWindow *qmlWindow, QWidget *videoWidget, QObject *parent)
    : QObject(parent)
    , m_qmlWindow(qmlWindow)
    , m_videoWidget(videoWidget)
{
    // m_videoWidget should have the same inital size and position as m_qmlWindow.
    m_videoWidget->resize(m_qmlWindow->width(), m_qmlWindow->height());
    m_videoWidget->move(m_qmlWindow->x(), m_qmlWindow->y());

    // Focus m_qmlWindow.
    m_qmlWindow->raise();

    connect(m_qmlWindow, &QWindow::xChanged,
            this,        &WindowManager::onXChanged);
    connect(m_qmlWindow, &QWindow::yChanged,
            this,        &WindowManager::onYChanged);
    connect(m_qmlWindow, &QWindow::widthChanged,
            this,        &WindowManager::onWidthChanged);
    connect(m_qmlWindow, &QWindow::heightChanged,
            this,        &WindowManager::onHeightChanged);

    connect(m_qmlWindow, &QWindow::windowStateChanged,
            this,        &WindowManager::onWindowStateChanged);

}

void WindowManager::onXChanged(int x)
{
    m_videoWidget->move(x, m_videoWidget->y());
}

void WindowManager::onYChanged(int y)
{
    m_videoWidget->move(m_videoWidget->x(), y);
}

void WindowManager::onWidthChanged(int width)
{
    m_videoWidget->setFixedSize(width, m_videoWidget->height());
}

void WindowManager::onHeightChanged(int height)
{
    m_videoWidget->setFixedSize(m_videoWidget->width(), height);
}

void WindowManager::onWindowStateChanged(Qt::WindowState windowState)
{
    switch (windowState)
    {
    default:
        break;
    }

    qDebug() << "INFO: QML new state:" << windowState;
    qDebug() << "INFO: Widget current state:" << m_videoWidget->windowState();
}
