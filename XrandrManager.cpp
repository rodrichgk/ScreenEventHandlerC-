#include "XrandrManager.h"
#include <iostream>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

XrandrManager::XrandrManager()
    : display(XOpenDisplay(nullptr))
{
    if (!display) {
        std::cerr << "Error: Unable to open X display." << std::endl;
        exit(1);
    }


    if (!XRRQueryExtension(display, &eventBase, &errorBase)) {
        std::cerr << "Error: XRandR extension not available." << std::endl;
        XCloseDisplay(display);
        exit(1);
    }

    XRRSelectInput(display, DefaultRootWindow(display), RRScreenChangeNotifyMask);
    XFlush(display);

    this->display = display;
    this->eventBase = eventBase;
}


XrandrManager::~XrandrManager()
{
    XCloseDisplay(this->display);
}

QList<ScreenInfo> XrandrManager::getDisplaysInfos()
{
    QList<ScreenInfo> screenList;
    XRRScreenResources* screenResources = XRRGetScreenResources(this->display, DefaultRootWindow(this->display));

    for (int i = 0; i < screenResources->noutput; ++i)
    {
        XRROutputInfo* outputInfo = XRRGetOutputInfo(this->display, screenResources, screenResources->outputs[i]);

        ScreenInfo screen;
        screen.name = QString(outputInfo->name);
        screen.isConnected = (outputInfo->connection == RR_Connected);

        screenList.append(screen);

        XRRFreeOutputInfo(outputInfo);
    }

    XRRFreeScreenResources(screenResources);

    return screenList;
}

void XrandrManager::handleScreenChange()
{
    QMessageBox::information(nullptr, "Button Clicked", "The button was clicked!");
}

void XrandrManager::startListening() {
    std::cout << "XrandrEventListener is listening for screen change events." << std::endl;
    XEvent ev;
    while (!m_isThreadClosed)
    {
        while (XPending(this->display)) {

            XNextEvent(this->display, &ev);
            XRRUpdateConfiguration(&ev);

            switch (ev.type - this->eventBase) {
            case RRScreenChangeNotify:
                std::cout << "Screen change event detected." << std::endl;
                emit screenChanged();
                break;
            default:
                std::cout << "Received an unknown X event." << std::endl;
                break;
            }
        }
    }
}

bool XrandrManager::isThreadStopped() {
    return m_isThreadClosed;
}

void XrandrManager::setThreadState(bool state_thread)
{
    m_isThreadClosed = state_thread;
}
