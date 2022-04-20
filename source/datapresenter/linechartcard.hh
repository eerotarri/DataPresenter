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
    void setAxesTitles(QString xTitle, QString yTitle);
    void setXAxisFormat(QString format);

private:

    /**
     * @brief Sets tick count to x- and y-axis
     * @param Gets dates, because whit it add extra ticks
     */
    void setTickCount(std::vector<QDateTime> dates);

    /**
     * @brief Sets x-axis range using the format. Format tells, how much we wnat extra space to the right and left.
     */
    void setAxisXRange();
    QChart *chart_ = new QChart();
    QDateTimeAxis *axisX_ = new QDateTimeAxis;
    QValueAxis *axisY_ = new QValueAxis;
    QString format_;
};

#endif // LINECHARTCARD_HH
