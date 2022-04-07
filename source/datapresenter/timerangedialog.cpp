#include "timerangedialog.hh"
#include "ui_timerangedialog.h"
#include "QPushButton"

#include <QGridLayout>

TimeRangeDialog::TimeRangeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TimeRangeDialog)
{
    ui->setupUi(this);
    setUp();
}

TimeRangeDialog::~TimeRangeDialog()
{
    delete ui;
}

void TimeRangeDialog::setUp()
{
    this->setWindowTitle("Give a time range");

}
