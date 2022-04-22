#ifndef BARCHARTCARD_HH
#define BARCHARTCARD_HH

#include "chartcard.hh"

#include <QBarSeries>
#include <QBarSet>
#include <QString>
#include <QStringList>
#include <QBarCategoryAxis>
#include <QValueAxis>

class BarChartCard : public ChartCard
{
public:
    BarChartCard();
    void createChartCard(std::vector<QDateTime> dates, std::vector<std::vector<double>> data, std::vector<std::string> stations ={""});
    void setHeader(QString header);
    void setAxesTitles(QString xTitle, QString yTitle);
    void setXAxisFormat(QString format);

private:

    /**
     * @brief Creates bar chart
     * @param dates list contains all x-axis values, data vector contains the values of the selected stations for the selected gas and stations vector tells selected stations.
     */
    void createChart(QStringList dates, std::vector<std::vector<double>> data, std::vector<QString> stations ={""});
    QChart *chart_ = new QChart();
    QBarCategoryAxis *axisX_ = new QBarCategoryAxis();
    QValueAxis *axisY_ = new QValueAxis();
    QString format_;


};

#endif // BARCHARTCARD_HH
