#ifndef SCATTERCHARTCARD_HH
#define SCATTERCHARTCARD_HH

#include "chartcard.hh"
#include <QDateTimeAxis>
#include <QValueAxis>

class ScatterChartCard : public ChartCard
{
public:
    ScatterChartCard();
    void createChartCard(std::vector<QDate> dates, std::vector<std::vector<double>> data, std::vector<QString> stations ={""});
    void setHeader(QString header);
    void setAxesTitles(QString xtitle, QString ytitle);
    void setXAxisFormat(QString format);

private:
    QChart *chart_ = new QChart();
    QDateTimeAxis *axisX_ = new QDateTimeAxis;
    QValueAxis *axisY_ = new QValueAxis;
};

#endif // SCATTERCHARTCARD_HH
