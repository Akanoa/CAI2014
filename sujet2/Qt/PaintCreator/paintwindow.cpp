#include "paintwindow.h"
#include "ui_paintwindow.h"

PaintWindow::PaintWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PaintWindow)
{
    ui->setupUi(this);
}

PaintWindow::~PaintWindow()
{
    delete ui;
}
