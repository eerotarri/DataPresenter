#ifndef LINECHARTCARD_HH
#define LINECHARTCARD_HH

#include "chartcard.hh"

class LineChartCard : public ChartCard
{
public:
    LineChartCard();
    void createChartCard(std::vector<QDate> dates, std::vector<std::vector<double>> data, std::vector<QString> stations ={""});
    void setHeader(QString header);

private:
    QChart *chart_ = new QChart();
};

#endif // LINECHARTCARD_HH
