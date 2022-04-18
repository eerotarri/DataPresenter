#ifndef CHARTCARD_HH
#define CHARTCARD_HH

#include <QString>
#include <QDate>
#include <QChartView>

class ChartCard : public QChartView
{
public:
    virtual void createChartCard(std::vector<QDateTime> dates, std::vector<std::vector<double>> data, std::vector<QString> stations ={""}) = 0;
    virtual void setHeader(QString header) = 0;
    virtual void setAxesTitles(QString xTitle, QString yTitle) = 0;
    virtual void setXAxisFormat(QString format) = 0;
};

#endif // CHARTCARD_HH
