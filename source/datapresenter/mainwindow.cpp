#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "controller.hh"
#include "timerangedialog.hh"

#include <iostream>

#include <QLineSeries>
#include <QGridLayout>
#include <QLabel>
#include <QScrollBar>


#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    using QLineSeries = QtCharts::QLineSeries;
#endif


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller_{nullptr}

    , startButton_(new QPushButton("Start"))

    , mainWidget_(new QWidget)
    , mainLayout_(new QGridLayout)

    , sidebarWidget_(new QWidget)
    , sidebarLayout_(new QGridLayout)

    , graphic_frame_(new QFrame)
    //, chart_(new QChart)
    , chart_view_(new QChartView)

    , chartLayout_(new QGridLayout)

    , scrollArea_(new QScrollArea)
    , chartAreaWidget_(new QWidget)

    , databaseComboBox_(new QComboBox)

    , smearGasGroupBox_(new QGroupBox)
    , smearStationGroupBox_(new QGroupBox)

    , statfiGasGroupBox_(new QGroupBox)
    , statfiStationGroupBox_(new QGroupBox)

    , compareGasGroupBox_(new QGroupBox)
    , compareStationGroupBox_(new QGroupBox)

    , gasGroupBox_()
    , stationGroupBox_()

    , showDataButton_(new QPushButton("Show data"))
    , valueTableButton_(new QPushButton("average"))
    , compareButton_(new QPushButton("compare"))
    , quitButton_(new QPushButton("quit"))
    , setTimeRangeButton_(new QPushButton("set time range"))
    , time_range_dialog_(new TimeRangeDialog(this))
    , value_table_dialog_(new ValueTableDialog(this))
    , year_select_dialog_(new YearSelectDialog(this))

    , blurEffect_(new QGraphicsBlurEffect)

{
    ui->setupUi(this);

    connect(startButton_, SIGNAL(clicked()), this, SLOT(on_startButton_clicked()));
    connect(quitButton_, SIGNAL(clicked()), this, SLOT(on_quitButton_clicked()));
    connect(compareButton_, SIGNAL(clicked()), this, SLOT(on_compareButton_clicked()));
    connect(setTimeRangeButton_, SIGNAL(clicked()), this, SLOT(on_setTimeRangeButton_clicked()));
    connect(valueTableButton_, SIGNAL(clicked()), this, SLOT(on_valueTableButton_clicked()));
    connect(databaseComboBox_, SIGNAL(currentTextChanged(QString)), this, SLOT(on_databaseComboBox_currentTextChanged()));
    connect(showDataButton_, SIGNAL(clicked()), this, SLOT(on_showDataButton_clicked()));

    QWidget *startWidget = new QWidget;
    QHBoxLayout *startLayout = new QHBoxLayout;

    this->setWindowTitle("Sovelluksen NIMI tähän");

    //chart_view_->setChart(chart_);
    /*chart_view_->setRenderHint(QPainter::Antialiasing);
    chart_view_->setParent(graphic_frame_);  // add chart view to UI
    chart_view_->resize(graphic_frame_->size());
    chart_->setGraphicsEffect(blurEffect_);*/

    startWidget->setLayout(startLayout);
    startLayout->addWidget(startButton_);
    startButton_->setMaximumWidth(150);
    startButton_->setMaximumHeight(50);

    setCentralWidget(startWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setController(Controller *controller)
{
    controller_ = controller;

}

void MainWindow::createGasGroupBox(QString &database, std::vector<std::string> &gases)
{
    QGroupBox *gasGroupBox;

    if( database == STATFI )
    {
        gasGroupBox = statfiGasGroupBox_;
    }
    else if ( database == SMEAR )
    {
        gasGroupBox = smearGasGroupBox_;
    }
    else
    {
        gasGroupBox = compareGasGroupBox_;
    }

    QVBoxLayout *groupBoxLayout = new QVBoxLayout;
    gasGroupBox->setLayout(groupBoxLayout);
    gasGroupBox->setTitle("Gases");

    for( std::string gas : gases )
    {
        QString gasName = QString::fromUtf8(gas.c_str());

        QCheckBox *gasCheckBox = new QCheckBox;
        gasCheckBox->setText(gasName);

        connect(gasCheckBox, SIGNAL(stateChanged(int)), this, SLOT(gasCheckBoxStateChanged(gasName)));

        groupBoxLayout->addWidget(gasCheckBox);
    }
}

void MainWindow::createStationGroupBox(QString &database, std::vector<std::string> &stations)
{
    QGroupBox *stationGroupBox;

    if( database == STATFI )
    {
        stationGroupBox = statfiStationGroupBox_;
    }
    else if ( database == SMEAR )
    {
        stationGroupBox = smearStationGroupBox_;
    }
    else
    {
        stationGroupBox = compareStationGroupBox_;
    }

    QVBoxLayout *groupBoxLayout = new QVBoxLayout;
    stationGroupBox->setLayout(groupBoxLayout);
    stationGroupBox->setTitle("Stations");

    for( std::string station : stations )
    {
        QString gasName = QString::fromUtf8(station.c_str());

        QCheckBox *stationCheckBox = new QCheckBox;
        stationCheckBox->setText(gasName);

        connect(stationCheckBox, SIGNAL(stateChanged(int)), this, SLOT(stationCheckboxStateChanged(int)));

        groupBoxLayout->addWidget(stationCheckBox);
    }
}

void MainWindow::setup()
{
    QGridLayout* rightLayout = new QGridLayout;
    QWidget* rightWidget = new QWidget;
    rightWidget->setLayout(rightLayout);

    setCentralWidget(mainWidget_);
    mainWidget_->setLayout(mainLayout_);

    createSidebar();

    mainLayout_->addWidget(sidebarWidget_, 1, 1);
    mainLayout_->addWidget(scrollArea_, 1, 2);
    mainLayout_->addWidget(rightWidget, 1, 3);

    rightLayout->addWidget(valueTableButton_, 1, 1);
    rightLayout->addWidget(quitButton_, 2, 1);

    mainLayout_->setColumnMinimumWidth(2, 500);

    chartAreaWidget_->setLayout(chartLayout_);

    //chartLayout_->setRowMinimumHeight(1, 1000);
}

void MainWindow::updateChart(QChart *chart)
{
    QChartView *chart_view = new QChartView;

    chartLayout_->addWidget(chart_view);

    chart_view->setChart(chart);

    // Kuvan minimikorkeus
    chart_view->setMinimumHeight(500);

    scrollArea_->setWidget(chartAreaWidget_);
    scrollArea_->setWidgetResizable(true);

    //chart_view_->setChart(chart);
    /*chart_->removeAllSeries();
    chart_->addSeries(series);
    chart_->setTitle(title);*/
    chart->createDefaultAxes();
    chart->legend()->setVisible(false);
}

void MainWindow::showStatfi()
{
    compareGasGroupBox_->setVisible(false);
    compareStationGroupBox_->setVisible(false);

    smearGasGroupBox_->setVisible(false);
    smearStationGroupBox_->setVisible(false);

    statfiGasGroupBox_->setVisible(true);
    statfiStationGroupBox_->setVisible(true);
}

void MainWindow::showSmear()
{
    compareGasGroupBox_->setVisible(false);
    compareStationGroupBox_->setVisible(false);

    statfiGasGroupBox_->setVisible(false);
    statfiStationGroupBox_->setVisible(false);

    smearGasGroupBox_->setVisible(true);
    smearStationGroupBox_->setVisible(true);
}

void MainWindow::showCompare()
{
    statfiGasGroupBox_->setVisible(false);
    statfiStationGroupBox_->setVisible(false);

    smearGasGroupBox_->setVisible(false);
    smearStationGroupBox_->setVisible(false);

    compareGasGroupBox_->setVisible(true);
    compareStationGroupBox_->setVisible(true);
}

void MainWindow::on_startButton_clicked()
{
    controller_->startButtonClicked();
}

void MainWindow::on_quitButton_clicked()
{
    close();
}

void MainWindow::on_compareButton_clicked()
{
    // Täl hetkel ku painaa compare napist saa yearselect ikkuna näkyviin
    year_select_dialog_->show();
}

void MainWindow::on_setTimeRangeButton_clicked()
{
    time_range_dialog_->show();
}

void MainWindow::on_valueTableButton_clicked()
{
    value_table_dialog_->show();
}

void MainWindow::on_databaseComboBox_currentTextChanged()
{
    blurEffect_->setBlurRadius(3);
    controller_->dadabaseComboBoxCurrentTextChanged(databaseComboBox_->currentText());
}

void MainWindow::on_showDataButton_clicked()
{
    blurEffect_->setBlurRadius(0);
    controller_->showDatabuttonClicked();
}

void MainWindow::stationCheckboxStateChanged(int state)
{
    QCheckBox *checkbox = qobject_cast<QCheckBox*>(sender());
    controller_->stationCheckBoxStateChanged(checkbox->text().toStdString(), state);
}

void MainWindow::gasCheckboxStateChanged(int state)
{
    QCheckBox *checkbox = qobject_cast<QCheckBox*>(sender());
    controller_->gasCheckBoxStateChanged(checkbox->text().toStdString(), state);
}

void MainWindow::createSidebar()
{
    sidebarWidget_->setLayout(sidebarLayout_);
    sidebarWidget_->setMaximumWidth(300);

    databaseComboBox_->addItem("SMEAR");
    databaseComboBox_->addItem("STATFI");
    databaseComboBox_->addItem("COMPARE");

    sidebarLayout_->addWidget(databaseComboBox_, 1, 1);

    sidebarLayout_->addWidget(smearGasGroupBox_, 2, 1);
    sidebarLayout_->addWidget(smearStationGroupBox_, 3, 1);

    sidebarLayout_->addWidget(statfiGasGroupBox_, 2, 1);
    sidebarLayout_->addWidget(statfiStationGroupBox_, 3, 1);

    sidebarLayout_->addWidget(compareGasGroupBox_, 2, 1);
    sidebarLayout_->addWidget(compareStationGroupBox_, 3, 1);

    // compareButton pitäisi olla yearselectbutton
    // yearselect pitäisi näkyä vain statfissa
    // timerange pitäisi näkyä vain smearissa
    // comparedialogia ei ole toteutettu
    sidebarLayout_->addWidget(compareButton_, 5, 1);
    sidebarLayout_->addWidget(setTimeRangeButton_, 4, 1);

    sidebarLayout_->addWidget(showDataButton_, 6, 1);
}
