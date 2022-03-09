#include "timerangedialog.hh"
#include "ui_timerangedialog.h"
#include "QPushButton"

#include <QGridLayout>

TimeRangeDialog::TimeRangeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TimeRangeDialog)
    //, start_day_calendar_(new QCalendarWidget)
    //, end_day_calendar_(new QCalendarWidget)
{
    ui->setupUi(this);    
}

TimeRangeDialog::~TimeRangeDialog()
{
    delete ui;
}

void TimeRangeDialog::setUp()
{
    /*QGridLayout* mainLayout = new QGridLayout;

    mainLayout->addWidget(end_day_calendar_, 0, 0);
    mainLayout->addWidget(start_day_calendar_, 1, 1);
    QPushButton* button = new QPushButton;
    mainLayout->addWidget(button, 2, 2);
    this->setLayout(mainLayout);*/


}
