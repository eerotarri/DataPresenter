#include "model.hh"
#include <iostream>


namespace Data
{
    static const std::vector<int> x = {1, 2, 3, 4, 5};
    static const std::vector<int> y = {1, 2, 1, 2, 1};
}

Model::Model(MainWindow *view, QObject* parent)
    : QObject{parent}
    , view_{view}
    , statfiIDataFetcher_(new ConcreteStatfi)
    /*, checkedStations_
    , checkedGases_*/
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
    currentDatabase_ = current_database;

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

void Model::updateChartView()
{
    std::vector<std::vector<double>> data = fetchData();
    // yhdestä kaasusta tehdään yksi kuva

    if ( currentDatabase_ == STATFI ){
        // miten erotellaan vektorista eri kaasut asemien kanssa
    }
    else if ( currentDatabase_ == SMEAR ){
        for ( std::vector<double> gasData : data ){
            createChart({gasData});
        }
    }

}

void Model::createChart(std::vector<std::vector<double>> gasData)
{
    // testi dataa
    std::vector<int> timeSelection = {"2010", "2011"};

    // käytetään?
    //int timeRangeLength = 2011 - 2010 + 1;
    //std::vector<int> timernange(timeRangeLength);
    //std::iota(timeSelection.begin(), timeSelection.end(), 2010);

    // asemat samaan kuvaan
    for ( std::vector<double> stationData : gasData ){
        QLineSeries *series = setChartSelection(stationData, timeSelection);

        QChart *chart = new QChart();

        // samaan chartiin lisätään samat kaasut eri asemilta
        chart->addSeries(series);
        chart->setTitle("OTSIKKO");

        view_->updateChart(chart);
    }
}

std::vector<std::vector<double> > Model::fetchData()
{
    std::vector<std::string> time = {"2010", "2011"};
    std::vector<int> years = {2010, 2017};
    std::vector<std::string> gas = {CO2_IN_TONNES};
    std::vector<std::string> location = {};

    // näitä käytetään niin saadaan valitut kaasut ja asemat
    //std::vector<std::string> gases(checkedGases_.begin(), checkedGases_.end());
    //std::vector<std::string> stations(checkedStations_.begin(), checkedStations_.end());
    //stationCount_ = gases.size();

    // kummasta databasesta haetaan?
    std::vector<std::vector<double>> data = statfiIDataFetcher_->fetchData(time, gas, location);

    return data;
}

QLineSeries* Model::setChartSelection(std::vector<double> dataSelection, std::vector<int> timeselection)
{
    // asema kerrallaan


    /*
    for ( std::vector<double> gasData : data ){
        QLineSeries *series = new QLineSeries;

    }
    QLineSeries *series = new QLineSeries;
    for (unsigned int i{0}; i < std::min(Data::x.size(), Data::y.size()); ++i) {
        series->append(Data::x[i], Data::y[i]);
    }



    */
    //std::cout << data[0][0] << std::endl;
        QLineSeries *series = new QLineSeries;
    for (unsigned int i{0}; i < std::min(timeselection.size(), dataSelection.size()); ++i) {
        //std::cout << data[0][i] << std::endl;
        series->append(timeselection[i],dataSelection[i]);
        //series->append()
    }
    return series;
    //view_->updateChart(series, "OTSIKKO tähän");
}


