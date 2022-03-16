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

const std::vector<std::string> gases = {"NOx", "SO2", "CO2"};
const std::vector<std::string> stations = {"Varrio", "Hyytiala", "Kumpula"};
const QString baseUrl = "https://smear-backend.rahtiapp.fi";

class ConcreteSmear: public IDataFetcher, public QObject
{
public:
    explicit ConcreteSmear(QObject *parent = nullptr);
    ~ConcreteSmear();

    std::vector<std::string> returnGases();

    std::vector<std::string> returnStations();

    virtual std::vector<std::vector<double>> fetchData(
            std::vector<std::string> timeRange, std::string gas,
            std::vector<std::string> location = {}) override;

private:
    void generateUrl(std::string start, std::string end,
                             std::string gas, std::string station);

    void processReply();

    QNetworkAccessManager *manager_;
    QString url_;


};

#endif // CONCRETESMEAR_HH
