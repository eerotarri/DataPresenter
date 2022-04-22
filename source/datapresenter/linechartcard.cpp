#include "linechartcard.hh"

#include <QLineSeries>

LineChartCard::LineChartCard()
{
    this->setChart(chart_);
    this->setMinimumHeight(500);
}

void LineChartCard::createChartCard(std::vector<QDateTime> dates, std::vector<std::vector<double> > data, std::vector<std::string> stations)
{
    if(stations.empty())
    {
        stations.push_back("");
    }
    qDebug() << "Create chart card 1";
    setTickCount(dates);

    QLineSeries *series;
    int s = 0;

    qDebug() << "Create chart card 2";
    chart_->addAxis(axisX_, Qt::AlignBottom);
    qDebug() << "Create chart card 3";

    axisY_->setLabelFormat("%.2f");
    qDebug() << "Create chart card 4";
    chart_->addAxis(axisY_, Qt::AlignLeft);
    qDebug() << "Create chart card 5";

    double max = data[0][0];
    double min = data[0][0];

    qDebug() << "Create chart card 6";

    for ( std::vector<double> values : data ){
        qDebug() << "Create chart card for loop 1";
        series = new QLineSeries();
        qDebug() << "Create chart card for loop 2";
        qDebug() << "s: " << s;
        qDebug() << "stations s: " << QString::fromStdString(stations[s]);
        series->setName(QString::fromStdString(stations[s]));
        qDebug() << "Create chart card for loop 3";
        qDebug() << "Create chart card for loop 4";
        double vectors_min = *min_element(values.begin(), values.end());
        double vectors_max = *max_element(values.begin(), values.end());

        qDebug() << "Create chart card for loop 5";
        if ( vectors_max > max ) {
            max = vectors_max;
        }
        qDebug() << "Create chart card for loop 6";
        if ( vectors_min < min ) {
            min = vectors_min;
        }
        qDebug() << "Create chart card for loop 7";
        for (unsigned int i = 0; i < values.size(); i++ ){
            qDebug() << "Create chart card for loop 8";
            QDateTime date = dates[i];

            qDebug() << "Create chart card for loop 9";
            qDebug() << date.date();

            double value = values[i];
            qDebug() << "Create chart card for loop 10";
            series->append(date.toMSecsSinceEpoch(), value);
            qDebug() << "Create chart card for loop 11";
        }
        qDebug() << "Create chart card for loop 12";
        chart_->addSeries(series);
        qDebug() << "Create chart card for loop 13";
        series->attachAxis(axisX_);
        qDebug() << "Create chart card for loop 14";
        series->attachAxis(axisY_);
        qDebug() << "Create chart card for loop 15";
        s++;
    }
    qDebug() << "Create chart card 7";
    if ( stations[0] == "" ){
        qDebug() << "Create chart card if no stations";
        chart_->legend()->setVisible(false);
    }
    qDebug() << "Create chart card 8";
    setAxisRange(dates.front(), dates.back(), min, max);
    qDebug() << "Create chart card 9";
    setTickCount(dates);
    qDebug() << "Create chart card 10";
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
