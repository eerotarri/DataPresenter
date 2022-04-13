#include "barchartcard.hh"

#include <QBarCategoryAxis>
#include <QValueAxis>

BarChartCard::BarChartCard()
{
    this->setChart(chart_);
}

void BarChartCard::createChartCard(std::vector<QDate> dates, std::vector<std::vector<double>> data, std::vector<QString> stations)
{
    QStringList dateList;

    for ( QDate date : dates ){
        QString dateStr = date.toString("dd.MM.yyyy");
        dateList.append(dateStr);
    }

    createChart(dateList, data, stations);
}

void BarChartCard::setHeader(QString header)
{
    chart_->setTitle(header);
}

void BarChartCard::createChart(QStringList dates, std::vector<std::vector<double> > data, std::vector<QString> stations)
{
    QBarSeries *series = new QBarSeries();

    for ( int i = 0; i < data.size(); i++ ){
        QBarSet *set = new QBarSet(stations[i]);
        std::vector<double> values = data[i];

        for ( double value : values ){
            set->append(value);
        }

        series->append(set);
    }

    chart_->addSeries(series);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(dates);
    axisX->setTitleText("Date");
    chart_->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("YKSIKKÖ");
    chart_->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    if ( stations[0] == "" ){
        chart_->legend()->setVisible(false);
    }

    chart_->legend()->setAlignment(Qt::AlignBottom);
}
