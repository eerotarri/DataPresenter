#include "model.hh"

Model::Model(MainWindow *view, QObject* parent)
    : QObject{parent}
    , view_{view}
{
}
