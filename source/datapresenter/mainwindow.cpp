#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "controller.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setController(Controller *controller)
{
    controller_ = controller;
}
