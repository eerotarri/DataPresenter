#include "model.hh"
#include "mainwindow.hh"

#include <QDebug>
#include <iostream>

#include "linechartcard.hh"

Model::Model(QObject *parent)
    : QObject{parent}
    , view_{nullptr}
{
}

void Model::setView(MainWindow *view)
{
    view_ = view;
}

void Model::setupView()
{
    getSupportedOptions();
    view_->setSupportedOptions(supportedOptions_);
}

void Model::showPreferences()
{
    qDebug() << "Model: Show preferences.";

}

void Model::saveToPreferences()
{
    qDebug() << "Model: Save to preferences.";
    auto db = view_->getSelectedDatabases();
    if (std::find(db.begin(), db.end(), "smear") != db.end()) {
        preferences_->smearPreferences = view_->getSelectedOptions("smear");
    }
    if (std::find(db.begin(), db.end(), "statfi") != db.end()) {
        preferences_->statfiPreferences = view_->getSelectedOptions("statfi");
    }
}

void Model::showStatistics()
{
    qDebug() << "Model: Show statistics.";
}

void Model::updateCardArea()
{
    // Tää funktio kutsuis fetchDataa ja Concretet kutsuu createCardia kun haku on valmis.
    // fetchData(parametrit, mitä, onkaan);
    std::vector<std::string> databases = view_->getSelectedDatabases();
    updateSelectedOptions();

    for ( std::string base : databases ){
        if ( base == "smear" ){
            for ( std::string gas : smearSelectedOptions_->gases ){
                qDebug() << "SMEAR";
                //smear_->fetchData(smearSelectedOptions_->timeRange, gas, smearSelectedOptions_->stations);
            }
        }
        if ( base == "statfi" ){
            for ( std::string gas : statfiSelectedOptions_->gases ){
                qDebug() << "STATFI";
                //statfi_->fetchData({"2000", "2006"}, gas, statfiSelectedOptions_->stations);
            }
        }
    }

    qDebug() << "Model: Update cardArea.";


//    createCard(nullptr);
}

void Model::updateSelectedOptions()
{
    std::vector<std::string> databases = view_->getSelectedDatabases();

    for( std::string database : databases ){
        selectedOptions *selected = view_->getSelectedOptions(database);

        if ( database == "smear" ){
            qDebug() << "Model: Update selected options from Smear.";
            smearSelectedOptions_ = selected;
        }
        if ( database == "statfi" ){
            qDebug() << "Model: Update selected options from Statfi.";
            statfiSelectedOptions_ = selected;
        }
    }
    qDebug() << "Model: Selected options updated.";
}


void Model::createCard(IDataFetcher* fetcher)
{
    auto data = fetcher->getCurrentData();

    // TESTI
    QString date1 = "20/12/2015";
    QDate Date1 = QDate::fromString(date1,"dd/MM/yyyy");
    QString date2 = "24/12/2015";
    QDate Date2 = QDate::fromString(date2,"dd/MM/yyyy");
    std::vector<std::vector<double>> DATA = {{2,4},{5,2}};
    std::vector<QString> STATIONS = {"S1", "S2"};
    std::vector<QDate> DATES ={Date1, Date2};

    ChartCard *card = new LineChartCard();
    card->setHeader("KAASU");
    card->createChartCard(DATES,DATA,STATIONS);

    view_->addCardToCardArea(card);
    // TESTI
}

void Model::getSupportedOptions()
{
    supportedOptions *options = new supportedOptions;

    options->smearGases = {"CO2", "SO2", "NOx"}; //smear_->getSupportedGases();
    options->statfiGases = {"CO2 in tonnes", "CO2 intensity", "CO2 indexed", "CO2 indensity indexed"}; //statfi_->getSupportedGases();
    options->smearStations = {"Hyytiälä", "Kumpula", "Värriö"}; //smear_->getSupportedStations();

    // Missä muodossa aika?
    //options->smearTimeRange = smear_->getSupportedTimeFrame();
    //options->statfiTimeRange = statfi_->getSupportedTimeFrame();

    supportedOptions_ = options;
}
/*
Model::Model(MainWindow *view, QObject* parent)
    : QObject{parent}
    , view_{view}
    , statfiIDataFetcher_(new ConcreteStatfi(this))
    , checkedStations_
    , checkedGases_
{
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
*/
