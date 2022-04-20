#include "linechartcard.hh"

#include <QLineSeries>

LineChartCard::LineChartCard()
{
    this->setChart(chart_);
    this->setMinimumHeight(500);
}

void LineChartCard::createChartCard(std::vector<QDateTime> dates, std::vector<std::vector<double> > data, std::vector<QString> stations)
{
    setTickCount(dates);

    QLineSeries *series;
    int s = 0;

    //axisX_->setTickCount(10);
    axisX_->setFormat("dd MM yyyy");
    chart_->addAxis(axisX_, Qt::AlignBottom);

    axisY_->setLabelFormat("%i");
    chart_->addAxis(axisY_, Qt::AlignLeft);

    // NÄIN SAA MUOKATTUA Y-AKSELIA SOPIVAKSI
    // katsotaan yksikön mukaan? -> oma funktio
    //axisY_->setRange(0,10);
    //axisY_->setTickCount(10);

    double max;
    double min;

    for ( std::vector<double> values : data ){
        series = new QLineSeries();
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

        for ( int i = 0; i < values.size(); i++ ){
            QDateTime date = dates[i];
            double value = values[i];
            series->append(date.toMSecsSinceEpoch(), value);
        }
        chart_->addSeries(series);
        series->attachAxis(axisX_);
        series->attachAxis(axisY_);
        s++;
    }

    if ( stations[0] == "" ){
        chart_->legend()->setVisible(false);
    }

    // vasemman ja oikeel tilaa STATFI
    QDateTime start = dates.front().addYears(-1);
    QDateTime end = dates.back().addYears(1);

    axisX_->setRange(start, end);
    axisY_->setRange(floor(min), ceil(max));

    chart_->legend()->setAlignment(Qt::AlignBottom);
}

void LineChartCard::setHeader(QString header)
{
    chart_->setTitle(header);
}

void LineChartCard::setAxesTitles(QString xTitle, QString yTitle)
{
    axisX_->setTitleText(xTitle);
    axisY_->setTitleText(yTitle);
}

void LineChartCard::setXAxisFormat(QString format)
{
    format_ = format;
    axisX_->setFormat(format_);
}

void LineChartCard::setTickCount(std::vector<QDateTime> dates)
{
    axisY_->setTickCount(dates.size()+2);
    axisX_->setTickCount(dates.size()+2);
}

void LineChartCard::setAxisXRange()
{
    if ( format_ == "yyyy" ) {

    }
    else if ( format_ == "yyyy-MM-dd" ){

    }
    else {

    }
}
