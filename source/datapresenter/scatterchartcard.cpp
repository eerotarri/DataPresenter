#include "scatterchartcard.hh"

#include <QScatterSeries>

ScatterChartCard::ScatterChartCard()
{
    this->setChart(chart_);
    this->setMinimumHeight(500);
}

void ScatterChartCard::createChartCard(std::vector<QDateTime> dates, std::vector<std::vector<double> > data, std::vector<QString> stations)
{
    setTickCount(dates);

    QScatterSeries *series;
    int s = 0;

    //axisX_->setFormat("yyyy");
    chart_->addAxis(axisX_, Qt::AlignBottom);

    //axisY_->setLabelFormat("%d");
    chart_->addAxis(axisY_, Qt::AlignLeft);

    double max;
    double min;

    for ( std::vector<double> values : data ){
        series = new QScatterSeries();
        series->setName(stations[s]);

        max = values[0];
        min = values[0];

        double vectors_min = *min_element(values.begin(), values.end());
        double vectors_max = *max_element(values.begin(), values.end());

        if ( vectors_max > max ) {
            max = vectors_max;
        }
        if ( vectors_min < min ) {
            min = vectors_min;
        }

        for ( unsigned i = 0; i < values.size(); i++ ){
            QDateTime date = dates[i];
            double value = values[i];
            series->append(date.toMSecsSinceEpoch(), value);
        }

        chart_->addSeries(series);
        series->attachAxis(axisY_);
        series->attachAxis(axisX_);
        s++;
    }

    if ( stations[0] == "" ){
        chart_->legend()->setVisible(false);
    }

    // vasemman ja oikeel tilaa STATFI
    QDateTime start = dates.front().addYears(-1);
    QDateTime end = dates.back().addYears(1);

    // mikkä tähä
    min = min - 0.1;
    max = max + 0.1;

    axisX_->setRange(start, end);
    axisY_->setRange(min, max);

    chart_->legend()->setAlignment(Qt::AlignBottom);
}

void ScatterChartCard::setHeader(QString header)
{
    chart_->setTitle(header);
}

void ScatterChartCard::setAxesTitles(QString xTitle, QString yTitle)
{
    axisX_->setTitleText(xTitle);
    axisY_->setTitleText(yTitle);
}

void ScatterChartCard::setXAxisFormat(QString format)
{
    format_ = format;
    axisX_->setFormat(format_);
}

void ScatterChartCard::setTickCount(std::vector<QDateTime> dates)
{
    axisY_->setTickCount(dates.size()+2);
    axisX_->setTickCount(dates.size()+2);
}

void ScatterChartCard::setAxisXRange()
{
    if ( format_ == "yyyy" ) {

    }
    else if ( format_ == "yyyy-MM-dd" ){

    }
    else {

    }
}
