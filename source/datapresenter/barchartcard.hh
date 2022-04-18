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
    void createChartCard(std::vector<QDateTime> dates, std::vector<std::vector<double>> data, std::vector<QString> stations ={""});
    void setHeader(QString header);
    void setAxesTitles(QString xtitle, QString ytitle);
    void setXAxisFormat(QString format);

private:
    void createChart(QStringList dates, std::vector<std::vector<double>> data, std::vector<QString> stations ={""});
    QChart *chart_ = new QChart();
    QBarCategoryAxis *axisX_ = new QBarCategoryAxis();
    QValueAxis *axisY_ = new QValueAxis();
    QString format_;


};

#endif // BARCHARTCARD_HH
