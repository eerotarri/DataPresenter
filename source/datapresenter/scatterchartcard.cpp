#include "scatterchartcard.hh"

#include <QScatterSeries>


#include <iostream>

ScatterChartCard::ScatterChartCard()
{
    this->setChart(chart_);
    this->setMinimumHeight(500);
}

void ScatterChartCard::createChartCard(std::vector<QDateTime> dates, std::vector<std::vector<double> > data, std::vector<QString> stations)
{
    QScatterSeries *series;
    int s = 0;

    axisX_->setTickCount(dates.size());
    chart_->addAxis(axisX_, Qt::AlignBottom);

    axisY_->setLabelFormat("%i");
    chart_->addAxis(axisY_, Qt::AlignLeft);

    // NÄIN SAA MUOKATTUA Y-AKSELIA SOPIVAKSI
    // katsotaan yksikön mukaan? -> oma funktio
    axisY_->setRange(0,10);
    axisY_->setTickCount(10);

    for ( std::vector<double> values : data ){
        series = new QScatterSeries();
        series->setName(stations[s]);

        for ( int i = 0; i < values.size(); i++ ){
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

    chart_->legend()->setAlignment(Qt::AlignBottom);
}

void ScatterChartCard::setHeader(QString header)
{
    chart_->setTitle(header);
}

void ScatterChartCard::setAxesTitles(QString xtitle, QString ytitle)
{
    axisX_->setTitleText(xtitle);
    axisY_->setTitleText(ytitle);
}

void ScatterChartCard::setXAxisFormat(QString format)
{
    axisX_->setFormat(format);
}
