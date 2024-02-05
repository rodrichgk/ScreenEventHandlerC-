#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "XrandrManager.h"
#include "SignalManager.h"
#include <QStandardItemModel>
#include <QGuiApplication>
#include <QEvent>
#include <QtConcurrent/QtConcurrent>
#define GRID_COLS 3
#define GRID_ROWS 3


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stopThread = false;
    gridLayout = new QGridLayout(ui->centralwidget);
    gridLayout->setSpacing(10); // Adjust spacing between screens if needed

    for (int row = 0; row < GRID_ROWS; ++row) {
        for (int col = 0; col < GRID_COLS; ++col) {
            screens[row][col] = new QLabel();
            screens[row][col]->setStyleSheet("background-color: black; color: white; border-radius: 10px;"); // Set style with rounded corners
            screens[row][col]->setAlignment(Qt::AlignCenter);

            screens[row][col]->setFixedSize(200, 200);

            gridLayout->addWidget(screens[row][col], row, col);
        }
    }

    ui->centralwidget->setLayout(gridLayout);

    updateConnectedDisplaysInfo();
    QObject::connect(&xrandrManager, &XrandrManager::screenChanged, this, &MainWindow::updateConnectedDisplaysInfo);
    connect(qApp, &QCoreApplication::aboutToQuit, this, &MainWindow::AppIsStopping);


    QFuture<void> future = QtConcurrent::run([=]() {

        xrandrManager.startListening();

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateConnectedDisplaysInfo()
{
    QLayoutItem* item;
    int row = 0;
    int col = 0;

    QList<ScreenInfo> screensInfos = xrandrManager.getDisplaysInfos();

    while ((item = gridLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    for(const ScreenInfo& screen : screensInfos)
    {
        if (screen.isConnected)
        {
            screens[row][col] = new QLabel(screen.name);
            screens[row][col]->setStyleSheet("background-color: black; color: white; border-radius: 10px;");
            screens[row][col]->setAlignment(Qt::AlignCenter);
            screens[row][col]->setFixedSize(200, 200);
            gridLayout->addWidget(screens[row][col], row, col);

            col++;
            if (col >= GRID_COLS) {
                col = 0;
                row++;
            }
            if (row >= GRID_ROWS) {
                // You may handle the case where more than 9 screens are connected here.
                break;
            }
        }
    }
}

void MainWindow::AppIsStopping()
{
    stopThread = true;
    xrandrManager.setThreadState(true);
}



