#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "XrandrManager.h"
#include <QScreen>
#include <QVBoxLayout>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void requestThreadExit();

private slots:
    void updateConnectedDisplaysInfo();
    void AppIsStopping();
    // Slot to handle the button click.


private:
    bool stopThread;
    Ui::MainWindow *ui;
    XrandrManager xrandrManager;
    QThread xrandrThread;
    QLabel* screens[3][3];
    QGridLayout* gridLayout;

};
#endif // MAINWINDOW_H
