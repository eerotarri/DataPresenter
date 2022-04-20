#include "model.hh"
#include "mainwindow.hh"
#include "linechartcard.hh"
#include "barchartcard.hh"
#include "scatterchartcard.hh"

#include <QDebug>
#include <iostream>

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

    view_->showPreferences(preferences_->smearPreferences, preferences_->statfiPreferences);
}

void Model::saveToPreferences()
{
    qDebug() << "Model: Save to preferences.";
    auto db = view_->getSelectedDatabases();
    if (std::find(db.begin(), db.end(), "smear") != db.end()) {
        preferences_->smearPreferences = view_->getSelectedOptions("smear");
    } else {
        preferences_->smearPreferences = nullptr;
    }
    if (std::find(db.begin(), db.end(), "statfi") != db.end()) {
        preferences_->statfiPreferences = view_->getSelectedOptions("statfi");
        qDebug() << view_->getSelectedOptions("statfi")->gases.empty();
    } else {
        preferences_->statfiPreferences = nullptr;
    }
}

void Model::showStatistics()
{
    qDebug() << "Model: Show statistics.";
    valueTable_->show();
}

void Model::updateCardArea()
{
    // Tää funktio kutsuis fetchDataa ja Concretet kutsuu createCardia kun haku on valmis.
    // fetchData(parametrit, mitä, onkaan);
    std::vector<std::string> databases = view_->getSelectedDatabases();
    updateSelectedOptions();
    view_->clearCardArea();

    for ( std::string base : databases ){
        if ( base == "smear" ){
            for ( std::string gas : smearSelectedOptions_->gases ){
                qDebug() << "SMEAR";
                smear_->fetchData(smearSelectedOptions_->timeRange, gas, smearSelectedOptions_->stations);
            }
        }
        if ( base == "statfi" ){
            for ( std::string gas : statfiSelectedOptions_->gases ){
                qDebug() << "STATFI";
                statfi_->fetchData(statfiSelectedOptions_->timeRange, gas, statfiSelectedOptions_->stations);
            }
        }
    }
    qDebug() << "Model: Update cardArea.";
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


void Model::createCard(IDataFetcher* fetcher, QString format, QString unit)
{
    auto data = fetcher->getCurrentData();
    auto timeVec = fetcher->getTimeVector();

    auto plotOption = view_->getCurrentPlotOption();

    ChartCard *card;

    if ( plotOption->text() == "line graph" ){
        card = new LineChartCard();
        qDebug() << "Model: Line graph.";
    }
    else if ( plotOption->text() == "bar graph" ){
        card = new BarChartCard();
        qDebug() << "Model: Bar graph.";
    }
    else if ( plotOption->text() == "scatter graph" ){
        card = new ScatterChartCard();
        qDebug() << "Model: Scatter graph.";
    }
    else {
        card = nullptr;
        qDebug() << "Model: None graph.";
    }

    qDebug() << "Data: " << data;
    qDebug() << "Time vector size: " << timeVec.size();

    // TESTI
    QString date1 = "2000";
    QDateTime Date1 = QDateTime::fromString(date1,"yyyy");
    QString date2 = "2001";
    QDateTime Date2 = QDateTime::fromString(date2,"yyyy");
    std::vector<QDateTime> DATES ={Date1, Date2};

    card->createChartCard(timeVec,data,{""});
    qDebug() << unit;
    card->setAxesTitles("Time", unit);

    card->setXAxisFormat(format);
    card->setHeader("KAASU");
    view_->addCardToCardArea(card);
    // TESTI
}

void Model::getSupportedOptions()
{
    supportedOptions *options = new supportedOptions;

    options->smearGases = {"CO2", "SO2", "NOx"}; //smear_->getSupportedGases();
    options->statfiGases = {"CO2 in tonnes", "CO2 intensity", "CO2 indexed", "CO2 indensity indexed"}; //statfi_->getSupportedGases();
    options->smearStations = smear_->getSupportedStations();

    // Missä muodossa aika?
    //options->smearTimeRange = smear_->getSupportedTimeFrame();
    //options->statfiTimeRange = statfi_->getSupportedTimeFrame();

    supportedOptions_ = options;
}

void Model::getStatistics()
{
    ConcreteSmear *smear = dynamic_cast<ConcreteSmear*>(smear_);
    std::vector<double> min = smear->getMin();
    std::vector<double> max = smear->getMax();
    std::vector<double> average = smear->getAverage();
    // TO DO
}
