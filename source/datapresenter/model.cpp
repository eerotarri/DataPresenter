#include "model.hh"

Model::Model(QObject *parent)
    : QObject{parent}
    , view_{nullptr}
{
}

void Model::setView(MainWindow *view)
{
    view_ = view;
}

void Model::updateChartView(IDataFetcher *base)
{

}
/*
#include <iostream>
#include <QBarSet>

#include <QDebug>


namespace Data
{
    static const std::vector<int> x = {1, 2, 3, 4, 5};
    static const std::vector<int> y = {1, 2, 1, 2, 1};
}

Model::Model(MainWindow *view, QObject* parent)
    : QObject{parent}
    , view_{view}
    , statfiIDataFetcher_(new ConcreteStatfi(this))
    , checkedStations_
    , checkedGases_
{
}

void Model::setupView()
{
    // hakee kaasut databasesta smearille
    std::vector<std::string> smearGases = {"CO2", "SO2", "NOx"};
    //QString smear = "smear";
    view_->createGasGroupBox(SMEAR, smearGases);

    // hakee kaasut databasesta statfille
    //QString statfi = "statfi";
    //std::vector<std::string> statfiGases = {"CO2 in tonnes", "CO2 intensity", "CO2 indexed", "CO2 indensity indexed"};
    std::vector<std::string> statfiGases = {"Khk_yht", "Khk_yht_index", "Khk_yht_las", "Khk_yht_las_index"};
    view_->createGasGroupBox(STATFI, statfiGases);

    // hakee molempien
    //QString compare = "compare";
    std::vector<std::string> compareGases = {"CO2", "SO2", "NOx", "CO2 in tonnes", "CO2 intensity", "CO2 indexed", "CO2 indensity indexed"};
    view_->createGasGroupBox(COMPARE, compareGases);

    // hakee asemat
    std::vector<std::string> stations = {"Hyytiälä", "Kumpula", "Värriö"};
    view_->createStationGroupBox(SMEAR, stations);
    view_->createStationGroupBox(STATFI, stations);
    view_->createStationGroupBox(COMPARE, stations);

    view_->setup();
}

void Model::changeDatabase(const QString current_database)
{
    currentDatabase_ = current_database;
    //checkedGases_.clear();
    checkedStations_.clear();

    if( current_database == SMEAR ){
        view_->showSmear();
    }
    else if( current_database == STATFI ){
        view_->showStatfi();
    }
    else if( current_database == COMPARE ){
        view_->showCompare();
    }
}

void Model::updateCheckedStations(const std::string name, int state)
{
    if ( state == Qt::Checked ) {
        checkedStations_.insert(name);
    }
    else {
        checkedStations_.erase(name);
    }
}

void Model::updateCheckedGases(const std::string name, int state)
{
    if ( state == Qt::Checked ) {
        checkedGases_.insert(name);
    }
    else {
        checkedGases_.erase(name);
    }
}

void Model::updateChartView(IDataFetcher* base)
{
    auto data = base->getCurrentData();
    // yhdestä kaasusta tehdään yksi kuva

    if ( currentDatabase_ == SMEAR ){
        // miten erotellaan vektorista eri kaasut asemien kanssa
        std::vector<std::vector<double>> testiData = {{3,4,5,4,3},{6,5,6,5,6}};
        createLineChart(testiData);
    }
    else if ( currentDatabase_ == STATFI ){
        int gas = 0;
        if (data.size() == checkedGases_.size()) {
            for ( std::vector<double> gasData : data ){
                createBarChart(gasData);
                ++gas;
            }
        }

    } else if ( currentDatabase_ == COMPARE ){

    }

}

void Model::updateStatfiTimeRange(int startYear, int endYear)
{
    statfiStartYear_ = startYear;
    statfiEndYear_ = endYear;
}

void Model::createChart(std::vector<std::vector<double>> gasData)
{
    // TÄÄÄ TULEE POISTAA

    // testi dataa
    // statfi stringinä
    std::vector<QString> timeSelection = {"2010", "2011", "2012", "2013", "2014"};
    // smear stringinä vai inttinä??
    //std::vector<int> timeSelection1 = {2010, 2011, 2012, 2013, 2014};

    // käytetään?
    //int timeRangeLength = 2011 - 2010 + 1;
    //std::vector<int> timernange(timeRangeLength);
    //std::iota(timeSelection.begin(), timeSelection.end(), 2010);

    // asemat samaan kuvaan

    for ( std::vector<double> stationData : gasData ){
        QBarSeries *series = createBarSeries(stationData, timeSelection);

        QChart *chart = new QChart();

        // samaan chartiin lisätään samat kaasut eri asemilta
        chart->addSeries(series);
        chart->setTitle("OTSIKKO");
        chart->createDefaultAxes();

        view_->updateChart(chart);
    }

}
*/

//void Model::createLineChart(std::vector<std::vector<double> > gasData /* std::vector<double> timeSelection */)
//{
    /*
    //int timeRangeLength = statfiEndYear_ - statfiStartYear_ + 1;
    //std::vector<int> timeRange(timeRangeLength);
    //std::iota(timeRange.begin(), timeRange.end(), statfiStartYear_);

    //QStringList timeSelection;
    //QString yearString;
    std::vector<double> timeSelection = {1,2,3,4,5}; // paremetrina

    QChart *chart = new QChart();
    chart->setTitle("OTSIKKO");

    for ( std::vector data : gasData ) {
        QLineSeries *series = createLineSeries(data, timeSelection);
        chart->addSeries(series);
    }

    //QBarCategoryAxis *axisX = new QBarCategoryAxis;
    //axisX->append(timeSelection);

    chart->createDefaultAxes();
    //chart->setAxisX(axisX, series);
    // laittaa serieksen nimen piiloon
    chart->legend()->setVisible(false);

    view_->updateChart(chart);
}

void Model::createBarChart(std::vector<double> gasData)
{
    qDebug() << "käy";
    int timeRangeLength = statfiEndYear_ - statfiStartYear_ + 1;
    std::vector<int> timeRange(timeRangeLength);
    std::iota(timeRange.begin(), timeRange.end(), statfiStartYear_);

    QStringList timeSelection;
    QString yearString;
    for ( int year : timeRange ) {
        yearString = QString::number(year);
        timeSelection.append(yearString);
    }

    QChart *chart = new QChart();
    chart->setTitle("OTSIKKO");

    QBarSeries *series = createBarSeries(gasData);
    chart->addSeries(series);

    QBarCategoryAxis *axisX = new QBarCategoryAxis;
    axisX->append(timeSelection);

    chart->createDefaultAxes();
    chart->setAxisX(axisX, series);
    // laittaa serieksen nimen piiloon
    chart->legend()->setVisible(false);

    view_->updateChart(chart);
}

void Model::fetchData()
{
    std::vector<std::string> time = {std::to_string(statfiStartYear_), std::to_string(statfiEndYear_)};
    std::vector<std::string> gases(checkedGases_.begin(), checkedGases_.end());
    // EI toimi jos set on tyhjä
    //std::vector<std::string> stations(checkedStations_.begin(), checkedGases_.end());

    // näitä käytetään niin saadaan valitut kaasut ja asemat
    //std::vector<std::string> gases(checkedGases_.begin(), checkedGases_.end());
    //std::vector<std::string> stations(checkedStations_.begin(), checkedStations_.end());
    //stationCount_ = gases.size();

    // kummasta databasesta haetaan?
    for (std::string gas : checkedGases_) {
        statfiIDataFetcher_->fetchData(time, gas);
    }

}

QBarSeries *Model::createBarSeries(const std::vector<double> dataSelection)
{
    QBarSeries *series = new QBarSeries;
    QBarSet *set = new QBarSet("???");

    for ( double value : dataSelection ) {
        set->append(value);
    }
    series->append(set);

    return series;
}

QLineSeries *Model::createLineSeries(const std::vector<double> dataSelection, const std::vector<double> timeselection)
{
    QLineSeries *series = new QLineSeries;
    for (unsigned int i{0}; i < std::min(timeselection.size(), dataSelection.size()); ++i) {
        series->append(timeselection[i],dataSelection[i]);
    }
    return series;
}
*/

