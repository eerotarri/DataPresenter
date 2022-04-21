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
    std::vector<double> getMin();
    std::vector<double> getMax();
    std::vector<double> getAverage();

private:
    void generateUrl(std::string start, std::string end,
                             std::string gas, std::string station);

    void processReply();

    std::vector<double> arrayToVector(QJsonArray jsonArray);

    QNetworkAccessManager *manager_;
    Model* model_;
    QString url_;
    QString valueName_;
    std::vector<std::vector<double>> currentData_;
    std::vector<QDateTime> timeVec_;
    QString units_;
    std::vector<double> min_;
    std::vector<double> max_;
    std::vector<double> average_;

    QString currentGas_;


};

#endif // CONCRETESMEAR_HH
