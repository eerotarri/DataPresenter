#ifndef SCATTERCHARTCARD_HH
#define SCATTERCHARTCARD_HH

#include "chartcard.hh"
#include <QDateTimeAxis>
#include <QValueAxis>

class ScatterChartCard : public ChartCard
{
public:
    ScatterChartCard();
    void createChartCard(std::vector<QDateTime> dates, std::vector<std::vector<double>> data, std::vector<std::string> stations ={""});
    void setHeader(QString header);
    void setAxesTitles(QString xTitle, QString yTitle);
    void setXAxisFormat(QString format);

private:

    /**
     * @brief Sets tick count to x- and y-axis
     * @param Gets dates, because it demands number of ticks
     */
    void setTickCount(std::vector<QDateTime> dates);

    /**
     * @brief Sets x- and y-axis range. If there is only one plot, makes free spaces around
     * @param firstDate
     * @param lastDate
     * @param minValue
     * @param maxValue
     */
    void setAxisRange(QDateTime firstDate, QDateTime lastDate, double minValue, double maxValue);

    QChart *chart_ = new QChart();
    QDateTimeAxis *axisX_ = new QDateTimeAxis;
    QValueAxis *axisY_ = new QValueAxis;
    QString format_;
};

#endif // SCATTERCHARTCARD_HH
