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
    view_->showPreferences(preferences_->smearPreferences, preferences_->statfiPreferences);
}

void Model::saveToPreferences()
{
    auto db = view_->getSelectedDatabases();
    if (std::find(db.begin(), db.end(), "smear") != db.end()) {
        preferences_->smearPreferences = view_->getSelectedOptions("smear");
    } else {
        preferences_->smearPreferences = nullptr;
    }
    if (std::find(db.begin(), db.end(), "statfi") != db.end()) {
        preferences_->statfiPreferences = view_->getSelectedOptions("statfi");
    } else {
        preferences_->statfiPreferences = nullptr;
    }
}

void Model::showStatistics()
{
    valueTable_->show();
}

void Model::updateCardArea()
{
    valueTable_->resetValues();

    std::vector<std::string> databases = view_->getSelectedDatabases();
    updateSelectedOptions();
    view_->clearCardArea();

    for ( std::string &base : databases ){
        if ( base == "smear" ){
            for ( std::string &gas : smearSelectedOptions_->gases ){
                smear_->fetchData(smearSelectedOptions_->timeRange, gas, smearSelectedOptions_->stations);
            }
        }
        if ( base == "statfi" ){
            for ( std::string &gas : statfiSelectedOptions_->gases ){
                statfi_->fetchData(statfiSelectedOptions_->timeRange, gas, statfiSelectedOptions_->stations);
            }
        }
    }
    std::vector<ChartCard*> cards = view_->getCards();
}

void Model::updateSelectedOptions()
{
    std::vector<std::string> databases = view_->getSelectedDatabases();

    for( std::string &database : databases ){
        selectedOptions *selected = view_->getSelectedOptions(database);

        if ( database == "smear" ){
            smearSelectedOptions_ = selected;
        }
        if ( database == "statfi" ){
            statfiSelectedOptions_ = selected;
        }
    }
}

void Model::createCard(IDataFetcher* fetcher, QString format, QString unit, QString title)
{
    auto data = fetcher->getCurrentData();
    auto timeVec = fetcher->getTimeVector();

    auto plotOption = view_->getCurrentPlotOption();

    ChartCard *card;

    if ( plotOption->text() == "line graph" ){
        card = new LineChartCard();
    }
    else if ( plotOption->text() == "bar graph" ){
        card = new BarChartCard();
    }
    else if ( plotOption->text() == "scatter graph" ){
        card = new ScatterChartCard();
    }
    else {
        card = nullptr;
        return;
    }

    QString date1 = "2000";
    QDateTime Date1 = QDateTime::fromString(date1,"yyyy");
    QString date2 = "2001";
    QDateTime Date2 = QDateTime::fromString(date2,"yyyy");
    std::vector<QDateTime> DATES ={Date1, Date2};

    card->setXAxisFormat(format);

    if(fetcher->getDatabaseName() == "STATFI")
    {
        card->createChartCard(timeVec,data,statfiSelectedOptions_->stations);
    }
    else if(fetcher->getDatabaseName() == "SMEAR")
    {
        card->createChartCard(timeVec,data,smearSelectedOptions_->stations);
    }

    card->setAxesTitles("Time", unit);
    card->setHeader(title); // TO DO
    view_->addCardToCardArea(card);

}

void Model::getSupportedOptions()
{
    supportedOptions *options = new supportedOptions;

    options->smearGases = smear_->getSupportedGases();
    options->statfiGases = statfi_->getSupportedGases();
    options->smearStations = smear_->getSupportedStations();

    options->smearTimeRange = smear_->getSupportedTimeFrame();
    options->statfiTimeRange = statfi_->getSupportedTimeFrame();

    supportedOptions_ = options;
}

void Model::getStatistics(QString gas)
{
    ConcreteSmear *smear = dynamic_cast<ConcreteSmear*>(smear_);
    std::vector<double> min = smear->getMin();
    std::vector<double> max = smear->getMax();
    std::vector<double> average = smear->getAverage();

    std::vector<std::vector<double>> valueVec;
    valueVec.push_back(min);
    valueVec.push_back(max);
    valueVec.push_back(average);

    valueTable_->setValues(gas, valueVec);
}
