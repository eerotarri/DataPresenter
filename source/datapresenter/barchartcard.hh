#ifndef BARCHARTCARD_HH
#define BARCHARTCARD_HH

#include "chartcard.hh"

#include <QBarSeries>
#include <QBarSet>
#include <QString>
#include <QStringList>

class BarChartCard : public ChartCard
{
public:
    BarChartCard();
    void createChartCard(std::vector<QDate> dates, std::vector<std::vector<double>> data, std::vector<QString> stations ={""});
    void setHeader(QString header);

private:
    void createChart(QStringList dates, std::vector<std::vector<double>> data, std::vector<QString> stations ={""});
    QChart *chart_ = new QChart();

};

#endif // BARCHARTCARD_HH
