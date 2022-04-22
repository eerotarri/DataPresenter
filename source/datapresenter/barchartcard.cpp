#include "barchartcard.hh"

BarChartCard::BarChartCard()
{
    this->setChart(chart_);
    this->setMinimumHeight(500);
}

void BarChartCard::createChartCard(std::vector<QDateTime> dates, std::vector<std::vector<double>> data, std::vector<std::string> stations)
{
    if(stations.empty())
    {
        stations.push_back("");
    }

    QStringList dateList;

    for ( QDateTime &date : dates ){
        QString dateStr = date.toString(format_);
        dateList.append(dateStr);
    }
    std::vector<QString> qStations = {};
    for(auto &station : stations)
    {
        qStations.push_back(QString::fromStdString(station));
    }
    createChart(dateList, data, qStations);
}

void BarChartCard::setHeader(QString header)
{
    chart_->setTitle(header);
}

void BarChartCard::setAxesTitles(QString xTitle, QString yTitle)
{
    axisX_->setTitleText(xTitle);
    axisY_->setTitleText(yTitle);
}

void BarChartCard::setXAxisFormat(QString format)
{
    format_ = format;
}

void BarChartCard::createChart(QStringList dates, std::vector<std::vector<double> > data, std::vector<QString> stations)
{
    QBarSeries *series = new QBarSeries();

    for (unsigned int i = 0; i < data.size(); i++ ){
        QBarSet *set = new QBarSet(stations[i]);
        std::vector<double> values = data[i];

        for ( double value : values ){
            set->append(value);
        }

        series->append(set);
    }

    chart_->addSeries(series);

    axisX_->append(dates);
    chart_->addAxis(axisX_, Qt::AlignBottom);
    series->attachAxis(axisX_);

    chart_->addAxis(axisY_, Qt::AlignLeft);
    series->attachAxis(axisY_);

    if ( stations[0] == "" ){
        chart_->legend()->setVisible(false);
    }

    chart_->legend()->setAlignment(Qt::AlignBottom);
}
