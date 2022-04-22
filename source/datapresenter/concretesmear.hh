#ifndef CONCRETESMEAR_HH
#define CONCRETESMEAR_HH

#include "idatafetcher.hh"
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QByteArray>
#include <vector>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QDateTime>
#include <QEventLoop>

const std::vector<std::string> gases = {"NOx", "SO2", "CO2"};
const std::vector<std::string> stations = {"Varrio", "Hyytiala", "Kumpula"};
const std::vector<double> timeframe = {0, 0};
const QString baseUrl = "https://smear-backend.rahtiapp.fi";

class Model;
class ConcreteSmear: public IDataFetcher, public QObject
{
public:
    explicit ConcreteSmear(Model* model, QObject *parent = nullptr);
    ~ConcreteSmear();

    virtual std::vector<std::string> getSupportedGases() override;
    virtual std::vector<std::string> getSupportedStations() override;
    virtual std::vector<double> getSupportedTimeFrame() override;

    virtual void fetchData(
            std::vector<std::string> timeRange, std::string gas,
            std::vector<std::string> location = {}) override;

    virtual std::vector<std::vector<double>> getCurrentData() override;
    virtual std::vector<QDateTime> getTimeVector() override;
    virtual QString getDatabaseName() override;

    /**
     * @brief Get minimum values from stations and gases given when fetched data
     * @return vector of minimum values for one gas and one or more stations
     */
    std::vector<double> getMin();

    /**
     * @brief Get maximum values from stations and gases given when fetched data
     * @return vector of maximum values for one gas and one or more stations
     */
    std::vector<double> getMax();

    /**
     * @brief Get average values from stations and gases given when fetched data
     * @return vector of average values for one gas and one or more stations
     */
    std::vector<double> getAverage();

private slots:
    void processReply();

private:
    void generateUrl(std::string start, std::string end,
                             std::string gas, std::string station);

    std::string arrayToVector(QJsonArray jsonArray);

    QNetworkAccessManager *manager_;
    Model* model_;
    QString url_;
    std::vector<QString> co2ValueName_;
    std::vector<QString> noxValueName_;
    std::vector<QString> so2ValueName_;
    std::vector<std::vector<double>> co2Data_;
    std::vector<std::vector<double>> noxData_;
    std::vector<std::vector<double>> so2Data_;
    std::vector<QDateTime> timeVec_;
    QString currentGas_;
    QString units_;
    bool ready_;
    std::vector<double> co2Min_;
    std::vector<double> co2Max_;
    std::vector<double> co2Average_;
    std::vector<double> noxMin_;
    std::vector<double> noxMax_;
    std::vector<double> noxAverage_;
    std::vector<double> so2Min_;
    std::vector<double> so2Max_;
    std::vector<double> so2Average_;


};

#endif // CONCRETESMEAR_HH
