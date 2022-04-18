#ifndef LINECHARTCARD_HH
#define LINECHARTCARD_HH

#include "chartcard.hh"

#include <QDateTimeAxis>
#include <QValueAxis>

class LineChartCard : public ChartCard
{
public:
    LineChartCard();
    void createChartCard(std::vector<QDateTime> dates, std::vector<std::vector<double>> data, std::vector<QString> stations ={""});
    void setHeader(QString header);
    void setAxesTitles(QString xtitle, QString ytitle);
    void setXAxisFormat(QString format);

private:
    QChart *chart_ = new QChart();
    QDateTimeAxis *axisX_ = new QDateTimeAxis;
    QValueAxis *axisY_ = new QValueAxis;
};

#endif // LINECHARTCARD_HH
