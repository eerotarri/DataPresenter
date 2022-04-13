#include "linechartcard.hh"

#include <QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>

LineChartCard::LineChartCard()
{
    this->setChart(chart_);
}

void LineChartCard::createChartCard(std::vector<QDate> dates, std::vector<std::vector<double> > data, std::vector<QString> stations)
{
    QLineSeries *series;
    int s = 0;

    for ( std::vector<double> values : data ){
        series = new QLineSeries();
        series->setName(stations[s]);

        for ( int i = 0; i < values.size(); i++ ){
            QDateTime date;
            date.setDate(dates[i]);
            double value = values[i];
            series->append(date.toMSecsSinceEpoch(), value);
        }
        chart_->addSeries(series);
        s++;
    }


    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("dd MM yyyy");
    axisX->setTitleText("Date");
    chart_->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("YKSIKKÖ");
    chart_->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    if ( stations[0] == "" ){
        chart_->legend()->setVisible(false);
    }

    chart_->legend()->setAlignment(Qt::AlignBottom);
}

void LineChartCard::setHeader(QString header)
{
    chart_->setTitle(header);
}
