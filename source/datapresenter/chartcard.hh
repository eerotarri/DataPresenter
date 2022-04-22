#ifndef CHARTCARD_HH
#define CHARTCARD_HH

#include <QString>
#include <QDate>
#include <QChartView>

class ChartCard : public QChartView
{
public:

    /**
     * @brief Adds values of one gas to the same chart, so it creates chart
     * @param dates contains all y-axis values
     * @param data vector contains the values of the selected stations for the selected gas
     * @param stations vector tells selected stations
     */

    virtual void createChartCard(std::vector<QDateTime> dates, std::vector<std::vector<double>> data, std::vector<std::string> stations ={""}) = 0;
    /**
     * @brief Sets the header for the chart
     * @param header
     */

    virtual void setHeader(QString header) = 0;

    /**
     * @brief Sets axes' titles
     * @param xTitle
     * @param yTitle
     */
    virtual void setAxesTitles(QString xTitle, QString yTitle) = 0;

    /**
     * @brief Sets x-axis format
     * @param format
     */
    virtual void setXAxisFormat(QString format) = 0;
};

#endif // CHARTCARD_HH
