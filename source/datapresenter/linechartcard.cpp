#include "linechartcard.hh"

#include <QLineSeries>

LineChartCard::LineChartCard()
{
    this->setChart(chart_);
}

void LineChartCard::createChartCard(std::vector<QDateTime> dates, std::vector<std::vector<double> > data, std::vector<QString> stations)
{
    QLineSeries *series;
    int s = 0;

    axisX_->setTickCount(10);
    axisX_->setFormat("dd MM yyyy");
    chart_->addAxis(axisX_, Qt::AlignBottom);

    axisY_->setLabelFormat("%i");
    chart_->addAxis(axisY_, Qt::AlignLeft);

    // NÄIN SAA MUOKATTUA Y-AKSELIA SOPIVAKSI
    // katsotaan yksikön mukaan? -> oma funktio
    axisY_->setRange(0,10);
    axisY_->setTickCount(10);

    for ( std::vector<double> values : data ){
        series = new QLineSeries();
        series->setName(stations[s]);

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

    chart_->legend()->setAlignment(Qt::AlignBottom);
}

void LineChartCard::setHeader(QString header)
{
    chart_->setTitle(header);
}

void LineChartCard::setAxesTitles(QString xtitle, QString ytitle)
{
    axisX_->setTitleText(xtitle);
    axisY_->setTitleText(ytitle);
}

void LineChartCard::setXAxisFormat(QString format)
{
    axisX_->setFormat(format);
}
