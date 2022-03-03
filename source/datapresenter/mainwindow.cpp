#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "controller.hh"

#include <QLineSeries>
#include <QGridLayout>


#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    using QLineSeries = QtCharts::QLineSeries;
#endif


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller_{nullptr}
    , containerWidget_(new QWidget(this))
    , mainWidget_(new QWidget)
    , graphic_frame_(new QFrame)
    , chart_(new QChart)
    , chart_view_(new QChartView)
    , gas_combo_box_(new QComboBox)
    , database_combo_box_(new QComboBox)
    , hyytiala_check_box_(new QCheckBox)
    , kumpula_check_box_(new QCheckBox)
    , varrio_check_box_(new QCheckBox)
    , start_day_calendar_(new QCalendar)
    , end_day_calendar_(new QCalendar)
    , averageButton_(new QPushButton("average"))
    , statisticsButton_(new QPushButton("statistics"))
    , compareButton_(new QPushButton("compare"))
    , quitButton_(new QPushButton("quit"))
{
    ui->setupUi(this);

    chart_view_->setChart(chart_);
    chart_view_->setRenderHint(QPainter::Antialiasing);
    chart_view_->setParent(graphic_frame_);  // add chart view to UI
    chart_view_->resize(graphic_frame_->size());

    setup();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setController(Controller *controller)
{
    controller_ = controller;

}

void MainWindow::on_quitButton_clicked()
{
    close();
}

void MainWindow::setup()
{
    this->setWindowTitle("Sovelluksen NIMI tähän");
    QGridLayout* mainLayout = new QGridLayout;

    mainWidget_->setLayout(mainLayout);
    setCentralWidget(mainWidget_);

    mainLayout->addWidget(graphic_frame_,1,2,2,2);

    mainLayout->addWidget(quitButton_, 1, 1, 2, 5);
    mainLayout->addWidget(compareButton_, 2, 2);
    mainLayout->addWidget(statisticsButton_, 3, 3);
    mainLayout->addWidget(averageButton_, 4, 4);
}

