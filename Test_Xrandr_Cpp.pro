QMAKE_CXXFLAGS += -Wall
# Add libraries
LIBS += -lX11 -lXrandr

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


# Include paths for X11 headers


# Libraries for X11 and Xrandr



SOURCES += \
    XrandrManager.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h \
    XrandrManager.h

FORMS += \
    MainWindow.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
