#include "controller.hh"
#include <iostream>

Controller::Controller(Model* model, QObject* parent)
    : QObject{parent}
    , model_{model}
{
}

void Controller::startButtonClicked()
{
    std::cout << "controller" << std::endl;
    model_->setupView();
}

void Controller::compareButtonClicked()
{
    //model_->setChartSelection(xText, yText);
}

void Controller::dadabaseComboBoxCurrentTextChanged(const QString &current_database)
{
    model_->changeDatabase(current_database);
}

void Controller::stationCheckBoxStateChanged(const std::string &name, int state)
{
    model_->updateCheckedStations(name, state);
}

void Controller::gasCheckBoxStateChanged(const std::string &name, int state)
{
    model_->updateCheckedGases(name, state);
}

void Controller::showDatabuttonClicked(int startTime, int endTime)
{
    model_->updateStatfiTimeRange(startTime, endTime);
    model_->updateChartView();
}
