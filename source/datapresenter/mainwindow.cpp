#include "mainwindow.hh"
#include "ui_mainwindow.h"

/*
#include "controller.hh"
#include "timerangedialog.hh"

#include <iostream>

#include <QLineSeries>
#include <QGridLayout>
#include <QLabel>
#include <QScrollBar>
*/

#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    using QLineSeries = QtCharts::QLineSeries;
#endif

// TESTI
#include <QDate>
QString date1 = "20/12/2015";
QDate Date1 = QDate::fromString(date1,"dd/MM/yyyy");
QString date2 = "24/12/2015";
QDate Date2 = QDate::fromString(date2,"dd/MM/yyyy");
std::vector<std::vector<double>> DATA = {{2,4},{5,2}};
std::vector<QString> STATIONS = {"S1", "S2"};
std::vector<QDate> DATES ={Date1, Date2};

MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller_{controller}
{
    ui->setupUi(this);

    setup();

    connect(rightSidebarWidget_, SIGNAL(quitButtonClicked()), this, SLOT(closeApplication()));
    connect(rightSidebarWidget_, SIGNAL(preferencesButtonClicked()), controller_, SLOT(showPreferences()));
    connect(rightSidebarWidget_, SIGNAL(saveButtonClicked()), controller_, SLOT(saveOptionsToPreferences()));
    connect(rightSidebarWidget_, SIGNAL(statisticsButtonClicked()), controller_, SLOT(showStatistics()));
    connect(leftSidebarWidget_, SIGNAL(showButtonClicked()), controller_, SLOT(updateCardArea()));

/*
    ui->setupUi(this);

    connect(startButton_, SIGNAL(clicked()), this, SLOT(on_startButton_clicked()));
    connect(quitButton_, SIGNAL(clicked()), this, SLOT(on_quitButton_clicked()));
    connect(compareButton_, SIGNAL(clicked()), this, SLOT(on_compareButton_clicked()));
    connect(setTimeRangeButton_, SIGNAL(clicked()), this, SLOT(on_setTimeRangeButton_clicked()));
    connect(valueTableButton_, SIGNAL(clicked()), this, SLOT(on_valueTableButton_clicked()));
    connect(databaseComboBox_, SIGNAL(currentTextChanged(QString)), this, SLOT(on_databaseComboBox_currentTextChanged()));
    connect(showDataButton_, SIGNAL(clicked()), this, SLOT(on_showDataButton_clicked()));
    connect(toYearSpinBox_, SIGNAL(valueChanged(int)), this, SLOT(on_toYearSpinBox_valueChanged(int)));
    connect(fromYearSpinBox_, SIGNAL(valueChanged(int)), this, SLOT(on_fromYearSpinBox_valueChanged(int)));

    QWidget *startWidget = new QWidget;
    QHBoxLayout *startLayout = new QHBoxLayout;

    this->setWindowTitle("Sovelluksen NIMI tähän");

    //chart_view_->setChart(chart_);
    /*chart_view_->setRenderHint(QPainter::Antialiasing);
    chart_view_->setParent(graphic_frame_);  // add chart view to UI
    chart_view_->resize(graphic_frame_->size());
    chart_->setGraphicsEffect(blurEffect_);*/
    /*

    startWidget->setLayout(startLayout);
    startLayout->addWidget(startButton_);
    startButton_->setMaximumWidth(150);
    startButton_->setMaximumHeight(50);

    setCentralWidget(startWidget);
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addCardToCardArea(ChartCard *newCard)
{
    cardArea_->addCard(newCard);
}

void MainWindow::closeApplication()
{
    close();
}

void MainWindow::setup()
{
    setCentralWidget(mainWidget_);
    mainWidget_->setLayout(mainLayout_);

    mainLayout_->addWidget(leftSidebarWidget_, 1, 1);
    mainLayout_->addWidget(scrollArea_, 1, 2);
    mainLayout_->addWidget(rightSidebarWidget_, 1, 3);

    mainLayout_->setColumnMinimumWidth(2, 500);
    mainLayout_->setColumnMinimumWidth(1, 150);

    scrollArea_->setWidget(cardArea_);
    scrollArea_->setWidgetResizable(true);
}
/*
void MainWindow::setController(Controller *controller)
{
    controller_ = controller;

}

void MainWindow::createGasGroupBox(QString database, std::vector<std::string> gases)
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

        connect(gasCheckBox, SIGNAL(stateChanged(int)), this, SLOT(gasCheckboxStateChanged(int)));

        groupBoxLayout->addWidget(gasCheckBox);
    }
}

void MainWindow::createStationGroupBox(QString database, std::vector<std::string> stations)
{
    QGroupBox *stationGroupBox;

    if ( database == SMEAR )
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

    //chart_->removeAllSeries();
}

void MainWindow::showStatfi()
{
    compareGasGroupBox_->setVisible(false);
    compareStationGroupBox_->setVisible(false);

    smearGasGroupBox_->setVisible(false);
    smearStationGroupBox_->setVisible(false);

    statfiGasGroupBox_->setVisible(true);
    statfiTimeRangeWidget_->setVisible(true);

    compareButton_->setVisible(false);
    setTimeRangeButton_->setVisible(false);
    valueTableButton_->setVisible(false);
}

void MainWindow::showSmear()
{
    compareGasGroupBox_->setVisible(false);
    compareStationGroupBox_->setVisible(false);

    statfiGasGroupBox_->setVisible(false);
    statfiTimeRangeWidget_->setVisible(false);

    smearGasGroupBox_->setVisible(true);
    smearStationGroupBox_->setVisible(true);

    compareButton_->setVisible(true);
    setTimeRangeButton_->setVisible(true);
    valueTableButton_->setVisible(true);
}

void MainWindow::showCompare()
{
    statfiGasGroupBox_->setVisible(false);
    statfiTimeRangeWidget_->setVisible(false);

    smearGasGroupBox_->setVisible(false);
    smearStationGroupBox_->setVisible(false);

    compareGasGroupBox_->setVisible(true);
    compareStationGroupBox_->setVisible(true);

    compareButton_->setVisible(false);
    setTimeRangeButton_->setVisible(true);
    valueTableButton_->setVisible(false);
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
    //mitä tänne?
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

    delete chartLayout_;
    delete chartAreaWidget_;
    createNewChartAreaWidget();

    // MITES smearin kohdalla kun asetetaan päivinä?
    controller_->showDatabuttonClicked(fromYearSpinBox_->value(), toYearSpinBox_->value());
}

void MainWindow::on_toYearSpinBox_valueChanged(int year)
{
    fromYearSpinBox_->setMaximum(year);
}

void MainWindow::on_fromYearSpinBox_valueChanged(int year)
{
    toYearSpinBox_->setMinimum(year);
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
    createStatfiTimeRangeWidget();

    sidebarWidget_->setLayout(sidebarLayout_);
    sidebarWidget_->setMaximumWidth(300);

    databaseComboBox_->addItem("SMEAR");
    databaseComboBox_->addItem("STATFI");
    databaseComboBox_->addItem("COMPARE");

    sidebarLayout_->addWidget(databaseComboBox_, 1, 1);

    sidebarLayout_->addWidget(smearGasGroupBox_, 2, 1);
    sidebarLayout_->addWidget(smearStationGroupBox_, 3, 1);

    sidebarLayout_->addWidget(statfiGasGroupBox_, 2, 1);
    sidebarLayout_->addWidget(statfiTimeRangeWidget_, 3, 1);

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

void MainWindow::createStatfiTimeRangeWidget()
{
    QLabel *toLabel = new QLabel("To:");
    QLabel *fromLabel = new QLabel("From:");
    QLabel *infoLabel = new QLabel("Select time range");

    QGridLayout *timeRangeLayout = new QGridLayout;
    timeRangeLayout->addWidget(infoLabel, 1, 1, 1, 2);
    timeRangeLayout->addWidget(fromLabel, 2, 1);
    timeRangeLayout->addWidget(toLabel, 3, 1);
    timeRangeLayout->addWidget(fromYearSpinBox_, 2, 2);
    timeRangeLayout->addWidget(toYearSpinBox_, 3, 2);

    // Statfin aikajana
    toYearSpinBox_->setMinimum(1975);
    toYearSpinBox_->setMaximum(2017);
    fromYearSpinBox_->setMinimum(1975);
    fromYearSpinBox_->setMaximum(2017);

    statfiTimeRangeWidget_->setMaximumHeight(100);

    statfiTimeRangeWidget_->setLayout(timeRangeLayout);
}

void MainWindow::createNewChartAreaWidget()
{
    QWidget *newChartAreaWidget = new QWidget;
    QGridLayout *newChartLayout = new QGridLayout;

    newChartAreaWidget->setLayout(newChartLayout);
    scrollArea_->setWidget(newChartAreaWidget);

    chartAreaWidget_ = newChartAreaWidget;
    chartLayout_ = newChartLayout;
}
*/
