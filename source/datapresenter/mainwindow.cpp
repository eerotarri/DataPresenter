#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "controller.hh"
#include "timerangedialog.hh"

#include <QLineSeries>
#include <QGridLayout>
#include <QLabel>


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
    , valueTableButton_(new QPushButton("average"))
    , statisticsButton_(new QPushButton("statistics"))
    , compareButton_(new QPushButton("compare"))
    , quitButton_(new QPushButton("quit"))
    , setTimeRangeButton_(new QPushButton("set time range"))
    , time_range_dialog_(new TimeRangeDialog(this))
    , value_table_dialog_(new ValueTableDialog(this))
{
    ui->setupUi(this);

    chart_view_->setChart(chart_);
    chart_view_->setRenderHint(QPainter::Antialiasing);
    chart_view_->setParent(graphic_frame_);  // add chart view to UI
    chart_view_->resize(graphic_frame_->size());

    setup();
    addConnects();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setController(Controller *controller)
{
    controller_ = controller;

}

void MainWindow::updateChart(QLineSeries *series, const QString &title)
{
    chart_->removeAllSeries();
    chart_->addSeries(series);
    chart_->setTitle(title);
    chart_->createDefaultAxes();
    chart_->legend()->setVisible(false);
}

void MainWindow::on_quitButton_clicked()
{
    close();
}

void MainWindow::on_compareButton_clicked()
{
    // Täl hetkel ku painaa compare napist saa dataa näkyviin
    controller_->compareButtonClicked("x", "y");
}

void MainWindow::on_setTimeRangeButton_clicked()
{
    time_range_dialog_->show();
}

void MainWindow::on_valueTableButton_clicked()
{
    value_table_dialog_->show();
}

void MainWindow::setup()
{
    this->setWindowTitle("Sovelluksen NIMI tähän");
    QGridLayout* mainLayout = new QGridLayout;

    mainWidget_->setLayout(mainLayout);
    setCentralWidget(mainWidget_);

    mainLayout->addWidget(chart_view_, 4, 1, 10, 20);

    mainLayout->addWidget(quitButton_, 30, 18, 1, 2);
    mainLayout->addWidget(compareButton_, 30, 2, 1, 2);
    mainLayout->addWidget(statisticsButton_, 30, 5, 1, 2);
    mainLayout->addWidget(valueTableButton_, 30, 8, 1, 2);

    gas_combo_box_->addItem("CO2");
    gas_combo_box_->addItem("SO2");
    gas_combo_box_->addItem("NOx");
    mainLayout->addWidget(gas_combo_box_, 3, 2, 1, 5);
    database_combo_box_->addItem("SMEAR");
    database_combo_box_->addItem("COMPARE");
    database_combo_box_->addItem("STATFI");
    mainLayout->addWidget(database_combo_box_, 3, 15, 1, 5);

    QLabel* hyytiala_label = new QLabel("Hyytiälä");
    QLabel* kumpula_label = new QLabel("Kumpula");
    QLabel* varrio_label = new QLabel("Värriö");

    mainLayout->addWidget(hyytiala_check_box_, 24, 2, 1, 1);
    mainLayout->addWidget(kumpula_check_box_, 24, 5, 1, 1);
    mainLayout->addWidget(varrio_check_box_, 24, 8, 1, 1);
    mainLayout->addWidget(hyytiala_label, 24, 3, 1, 1);
    mainLayout->addWidget(kumpula_label, 24, 6, 1, 1);
    mainLayout->addWidget(varrio_label, 24, 9, 1, 1);

    mainLayout->addWidget(setTimeRangeButton_, 24, 15, 5, 5);

}

void MainWindow::addConnects()
{
    QObject::connect(quitButton_, SIGNAL(clicked()), this, SLOT(on_quitButton_clicked()));
    QObject::connect(compareButton_, SIGNAL(clicked()), this, SLOT(on_compareButton_clicked()));
    QObject::connect(setTimeRangeButton_, SIGNAL(clicked()), this, SLOT(on_setTimeRangeButton_clicked()));
    QObject::connect(valueTableButton_, SIGNAL(clicked()), this, SLOT(on_valueTableButton_clicked()));
}

