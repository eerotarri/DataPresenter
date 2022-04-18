#include "mainwindow.hh"
#include "ui_mainwindow.h"

/* TESTI DATAA
#include "barchartcard.hh"
#include "linechartcard.hh"
#include "scatterchartcard.hh"
#include <QDate>
QString date1 = "20/12/2015";
QDate Date1 = QDate::fromString(date1, "dd/MM/yyyy");
QString date2 = "21/12/2015";
QDate Date2 = QDate::fromString(date2, "dd/MM/yyyy");
QString date3 = "22/12/2015";
QDate Date3 = QDate::fromString(date3, "dd/MM/yyyy");
QString date4 = "23/12/2015";
QDate Date4 = QDate::fromString(date4, "dd/MM/yyyy");
QString date5 = "24/12/2015";
QDate Date5 = QDate::fromString(date5, "dd/MM/yyyy");
std::vector<std::vector<double>> DATA = {{2,4,5,2,5},{5,2,8,3,1}};
std::vector<QString> STATIONS = {"S1", "S2"};
std::vector<QDate> DATES = {Date1, Date2, Date3, Date4, Date5};
*/
/*
#include "controller.hh"
#include "timerangedialog.hh"
*/


#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    using QLineSeries = QtCharts::QLineSeries;
#endif

MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller_{controller}
{
    ui->setupUi(this);

    // taustaväri
    this->setStyleSheet("background-color: #8a2be2");
    this->setWindowTitle("Sovelluksen NIMI tähän");

    setup();

    connect(rightSidebarWidget_, SIGNAL(quitButtonClicked()), this, SLOT(closeApplication()));
    connect(rightSidebarWidget_, SIGNAL(preferencesButtonClicked()), controller_, SLOT(showPreferences()));
    connect(rightSidebarWidget_, SIGNAL(saveButtonClicked()), controller_, SLOT(saveOptionsToPreferences()));
    connect(rightSidebarWidget_, SIGNAL(statisticsButtonClicked()), controller_, SLOT(showStatistics()));
    connect(leftSidebarWidget_, SIGNAL(showButtonClicked()), controller_, SLOT(updateCardArea()));

/*


    //chart_view_->setChart(chart_);
    /*chart_view_->setRenderHint(QPainter::Antialiasing);
    chart_view_->setParent(graphic_frame_);  // add chart view to UI
    chart_view_->resize(graphic_frame_->size());
    chart_->setGraphicsEffect(blurEffect_);
*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSupportedOptions(supportedOptions *options)
{
    leftSidebarWidget_->setSupportedOptions(options);
}

void MainWindow::clearCardArea()
{
    cardArea_->clearArea();
}

void MainWindow::addCardToCardArea(ChartCard *newCard)
{
    cardArea_->addCard(newCard);
}

selectedOptions *MainWindow::getSelectedOptions(std::string database)
{
    selectedOptions *selected = leftSidebarWidget_->getSelectedOptions(database);
    return selected;
}

std::vector<std::string> MainWindow::getSelectedDatabases()
{
    std::vector<std::string> databases = leftSidebarWidget_->getSelectedDatabase();
    return databases;
}

void MainWindow::closeApplication()
{
    close();
}

void MainWindow::setup()
{
    setCentralWidget(mainWidget_);
    mainWidget_->setLayout(mainLayout_);

    mainLayout_->addWidget(leftSidebarWidget_, 0, 0,Qt::AlignLeft);
    mainLayout_->addWidget(scrollArea_, 0, 1);
    mainLayout_->addWidget(rightSidebarWidget_, 0, 2);

    mainLayout_->setColumnMinimumWidth(1, 500);
    mainLayout_->setColumnMinimumWidth(0, 220);
    // ei toimi, miksi??
    //mainLayout_->setColumnStretch(0,0);

    scrollArea_->setWidget(cardArea_);
    scrollArea_->setWidgetResizable(true);

}
/*

void MainWindow::updateChart(QChart *chart)
{
    scrollArea_->setWidget(chartAreaWidget_);
    scrollArea_->setWidgetResizable(true);

    //chart_->removeAllSeries();
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
