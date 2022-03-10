#include "controller.hh"

Controller::Controller(Model* model, QObject* parent)
    : QObject{parent}
    , model_{model}
{
}

void Controller::compareButtonClicked()
{
    //model_->setChartSelection(xText, yText);
}

void Controller::dadabaseComboBoxCurrentTextChanged(const QString &current_database)
{
    model_->changeDatabase(current_database);
}
