#ifndef SCATTERCHARTCARD_HH
#define SCATTERCHARTCARD_HH

#include "chartcard.hh"
#include <QDateTimeAxis>
#include <QValueAxis>

class ScatterChartCard : public ChartCard
{
public:
    ScatterChartCard();
    void createChartCard(std::vector<QDateTime> dates, std::vector<std::vector<double>> data, std::vector<QString> stations ={""});
    void setHeader(QString header);
    void setAxesTitles(QString xTitle, QString yTitle);
    void setXAxisFormat(QString format);

private:
    void setTickCount(std::vector<QDateTime> dates);
    void setAxisXRange();
    QChart *chart_ = new QChart();
    QDateTimeAxis *axisX_ = new QDateTimeAxis;
    QValueAxis *axisY_ = new QValueAxis;
    QString format_;
};

#endif // SCATTERCHARTCARD_HH
