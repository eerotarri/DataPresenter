#include "controller.hh"

Controller::Controller(Model* model, QObject* parent)
    : QObject{parent}
    , model_{model}
{
}

void Controller::compareButtonClicked(const QString &xText, const QString &yText)
{
    model_->setChartSelection(xText, yText);
}
