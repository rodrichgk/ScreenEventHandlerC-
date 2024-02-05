#ifndef XRANDRMANAGER_H
#define XRANDRMANAGER_H



#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QStringList>
#include <QtCore>
#include <QtEvents>
#include <X11/Xlib.h>
#include <QMutex>
#include <QWaitCondition>
#ifndef QT_NO_XRANDR
#  include <X11/extensions/Xrandr.h>
#endif // QT_NO_XRANDR

#undef None


struct ScreenInfo {
    QString name;       // Screen name or identifier
    bool isConnected;   // Indicates if the screen is connected
    bool isNew;         // Indicates if the screen is new
    // Add more attributes as needed
};

extern QList<ScreenInfo> screenList;


class XrandrManager:public QObject
{
    Q_OBJECT
public:
    XrandrManager();
    void connect_button();
    QList<ScreenInfo> getDisplaysInfos();
    void startListening();

    ~XrandrManager();
    bool isThreadStopped();
    void setThreadState(bool state_thread);

signals:
    void screenChanged(); // Define a custom signal for screen change.

private slots:
    void handleScreenChange();

private:
    Display* display;
    int eventBase, errorBase;
    bool m_isThreadClosed = false;
};

#endif // XRANDRMANAGER_H
