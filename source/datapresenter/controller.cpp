#include "controller.hh"

Controller::Controller(Model* model, QObject* parent)
    : QObject{parent}
    , model_{model}
{
}
