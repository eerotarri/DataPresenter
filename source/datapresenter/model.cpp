#include "model.hh"
#include <iostream>


namespace Data
{
    static const std::vector<int> x = {1, 2, 3, 4, 5};
    static const std::vector<int> y = {1, 2, 1, 2, 1};
    static const std::vector<int> x1 = {1, 2, 3, 4, 5};
    static const std::vector<int> y1 = {2, 3, 2, 3, 2};
}

Model::Model(MainWindow *view, QObject* parent)
    : QObject{parent}
    , view_{view}
    , checkedStations_(new std::set<std::string>)
    , checkedGases_(new std::set<std::string>)
{
}

void Model::setupView()
{
    // hakee kaasut databasesta smearille
    std::vector<std::string> smearGases = {"CO2", "SO2", "NOx"};
    QString smear = "smear";
    view_->createGasGroupBox(smear, smearGases);

    // hakee kaasut databasesta statfille
    QString statfi = "statfi";
    std::vector<std::string> statfiGases = {"CO2 in tonnes", "CO2 intensity", "CO2 indexed", "CO2 indensity indexed"};
    view_->createGasGroupBox(statfi, statfiGases);

    // hakee molempien
    QString compare = "compare";
    std::vector<std::string> compareGases = {"CO2", "SO2", "NOx", "CO2 in tonnes", "CO2 intensity", "CO2 indexed", "CO2 indensity indexed"};
    view_->createGasGroupBox(compare, compareGases);

    // hakee asemat
    std::vector<std::string> stations = {"Hyytiälä", "Kumpula", "Värriö"};
    view_->createStationGroupBox(smear, stations);
    view_->createStationGroupBox(statfi, stations);
    view_->createStationGroupBox(compare, stations);

    view_->setup();
}

void Model::changeDatabase(const QString current_database)
{
    if( current_database == "SMEAR" ){
        view_->showSmear();
    }
    else if( current_database == "STATFI" ){
        view_->showStatfi();
    }
    else if( current_database == "COMPARE" ){
        view_->showCompare();
    }
}

void Model::updateCheckedStations(const std::string name, int state)
{
    if ( state == Qt::Checked ) {
        checkedStations_->insert(name);
    }
    else {
        checkedStations_->erase(name);
    }
}

void Model::updateCheckedGases(const std::string name, int state)
{
    if ( state == Qt::Checked ) {
        checkedGases_->insert(name);
    }
    else {
        checkedGases_->erase(name);
    }
}

void Model::updateChartView()
{
    // Tarkistaa vektorit ja niiden perusteella hakee dataa
    // Kuvaajia_lkm == kaasujen määrä
    //setChartSelection("", "");

    createChart("", "", "");
}

void Model::createChart(const QString gasSelection, const QString stationSelection, const QString timeSelection)
{
    QLineSeries *series = setChartSelection(gasSelection, timeSelection);

    QChart *chart = new QChart();
    chart->addSeries(series);

    view_->updateChart(chart);
}

QLineSeries* Model::setChartSelection(const QString dataSelection, const QString timeselection)
{
    // poimii datan

    QLineSeries *series = new QLineSeries;
    for (unsigned int i{0}; i < std::min(Data::x.size(), Data::y.size()); ++i) {
        series->append(Data::x[i], Data::y[i]);
    }
    return series;
    //view_->updateChart(series, "OTSIKKO tähän");
}


