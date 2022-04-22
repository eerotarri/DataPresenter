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

    chart_->addAxis(axisX_, Qt::AlignBottom);

    axisY_->setLabelFormat("%.2f");
    chart_->addAxis(axisY_, Qt::AlignLeft);

    double max = data[0][0];
    double min = data[0][0];

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

            qDebug() << date.date();

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

    setAxisRange(dates.front(), dates.back(), min, max);

    setTickCount(dates);

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

    if ( dates.size() == 1 ) {
        axisY_->setTickCount(3);
        axisX_->setTickCount(3);
    }
    else if ( dates.size() < 15 ) {
        axisY_->setTickCount(dates.size());
        axisX_->setTickCount(dates.size());
    }
    else {
        axisY_->setTickCount(7);
        axisX_->setTickCount(7);
    }
}

void LineChartCard::setAxisRange(QDateTime firstDate, QDateTime lastDate, double minValue, double maxValue)
{
    QDateTime firstTickX = firstDate;
    QDateTime lastTickX = lastDate;

    double firstTickY = minValue;
    double lastTickY = maxValue;

    if ( minValue == maxValue ) {
        firstTickY -= 1;
        lastTickY += 1;

        if ( format_ == "yyyy" ) {
            firstTickX = firstTickX.addYears(-1);
            lastTickX = lastTickX.addYears(1);
        }
        else if ( format_ == "yyyy-MM-dd" ){
            firstTickX = firstTickX.addDays(-1);
            lastTickX = lastTickX.addDays(1);
        }
        else {
            firstTickX = firstTickX.addSecs(-180);
            lastTickX = lastTickX.addDays(180);
        }
    }

    axisY_->setRange(firstTickY, lastTickY);
    axisX_->setRange(firstTickX, lastTickX);
}
