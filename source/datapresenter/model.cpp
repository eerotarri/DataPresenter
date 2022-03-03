#include "model.hh"

namespace Data
{
    static const std::vector<int> x = {1, 2, 3, 4, 5};
    static const std::vector<int> y = {1, 2, 1, 2, 1};
}

Model::Model(MainWindow *view, QObject* parent)
    : QObject{parent}
    , view_{view}
{
}

void Model::setChartSelection(const QString &dataSelection, const QString &timeselection)
{
    // poimii datan

    QLineSeries* series = new QLineSeries();
    for (unsigned int i{0}; i < std::min(Data::x.size(), Data::y.size()); ++i) {
        series->append(Data::x[i], Data::y[i]);
    }
    view_->updateChart(series, "OTSIKKO tähän");
}
