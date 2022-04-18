#include "mainwindow.hh"
#include "ui_mainwindow.h"

// violetti: #4C0390
// sininen: #88CCFF
// lila: #E2E5F5
// pinkki: #EB94CF
// tumma: #2F285A

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
    /*
    this->setStyleSheet("background-color: #FFFFFF");
    this->setStyleSheet("background-color: #4C0390");
    */
    this->setWindowTitle("Datapresenter");


    setup();

    connect(rightSidebarWidget_, SIGNAL(quitButtonClicked()), this, SLOT(closeApplication()));
    connect(rightSidebarWidget_, SIGNAL(preferencesButtonClicked()), controller_, SLOT(showPreferences()));
    connect(rightSidebarWidget_, SIGNAL(saveButtonClicked()), controller_, SLOT(saveOptionsToPreferences()));
    connect(rightSidebarWidget_, SIGNAL(statisticsButtonClicked()), controller_, SLOT(showStatistics()));
    connect(leftSidebarWidget_, SIGNAL(showButtonClicked()), controller_, SLOT(updateCardArea()));
    connect(rightSidebarWidget_, SIGNAL(plotOptionChanged()), controller_, SLOT(updateCardArea()));
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

QRadioButton *MainWindow::getCurrentPlotOption()
{
    return rightSidebarWidget_->getCurrentPlotOption();
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
    mainLayout_->setColumnMinimumWidth(0, 250);
    mainLayout_->setColumnMinimumWidth(2, 150);

    scrollArea_->setWidget(cardArea_);
    scrollArea_->setWidgetResizable(true);
}
