#include "controller.hh"
#include <QDebug>

Controller::Controller(Model *model, QObject *parent)
    : QObject{parent}
    , model_{model}
{
}

void Controller::showPreferences()
{
    model_->showPreferences();
}

void Controller::saveOptionsToPreferences()
{
    model_->saveToPreferences();
}

void Controller::showStatistics()
{
    model_->showStatistics();
}

void Controller::updateCardArea()
{
    model_->updateCardArea();
}
