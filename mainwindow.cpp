#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"

#include "QDebug"
#include "QScreen"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timerManager = new TimerManager(ui->minutesLabel,ui->secondsLabel);
    float scaleFactor = QGuiApplication::primaryScreen()->logicalDotsPerInch() / 96.0;

    this->resize(constants::WINDOWS_WIDTH * scaleFactor,
                 constants::WINDOWS_HEIGHT * scaleFactor);

}

void MainWindow::wheelEvent(QWheelEvent* e)
{
    bool IsUp = e->angleDelta().y() > 0;
    auto cursorPos = e->pos();
    if(IsCursorOnLabel(cursorPos,ui->minutesLabel))
        timerManager->ChangeMinutes(IsUp);
    else if(IsCursorOnLabel(cursorPos,ui->secondsLabel))
        timerManager->ChangeSeconds(IsUp);
}

MainWindow::~MainWindow()
{
    delete timerManager;
    delete ui;
}

bool MainWindow::IsCursorOnLabel(QPoint p, QLabel *lb)
{
    auto label_x = lb->pos().x();
    auto label_y = lb->pos().y();
    auto cursor_x = p.x();
    auto cursor_y = p.y();
    return cursor_x > label_x &&
            cursor_x < label_x + lb->size().width() &&
            cursor_y > label_y &&
            cursor_y < label_y + lb->size().height();
}
