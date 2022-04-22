#ifndef CONCRETESTATFI_HH
#define CONCRETESTATFI_HH

#include "idatafetcher.hh"

//#include "model.hh"

#include <vector>
#include <string>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class Model;
class ConcreteStatfi : public QObject, public IDataFetcher
{
    Q_OBJECT
public:
    explicit ConcreteStatfi(Model* model, QObject *parent = nullptr);

    // Virtual functions explained in IDataFetcher.hh
    virtual void fetchData(std::vector<std::string> timeRange, std::string gas, std::vector<std::string> location = {});
    virtual std::vector<std::vector<double>> getCurrentData();
    virtual std::vector<QString> getSupportedTimeFrame();
    virtual std::vector<std::string> getSupportedStations();
    virtual std::vector<std::string> getSupportedGases();
    virtual std::vector<QDateTime> getTimeVector();
    virtual QString getDatabaseName();

private slots:
    void post(QByteArray data);
    void readyRead();

private:
    const QUrl url_ = QUrl("https://pxnet2.stat.fi/PXWeb/api/v1/en/ymp/taulukot/Kokodata.px");
    const std::vector<QString> supportedTimeFrame_ = {"1975", "2017"};
    const std::vector<std::string> supportedGases_ = {"CO2 in tonnes", "CO2 intensity", "CO2 indexed", "CO2 indensity indexed"};

    QNetworkAccessManager* manager_;
    Model* model_;

    std::vector<std::vector<double> > currentData_ = {};
    std::vector<QDateTime> currentTimeRange_ = {};
    QString currentUnit_ = "";


    /*!
     * \fn QByteArray ConcreteStatfi::generateQuery(std::string data, std::vector<int> years)
     * \brief Generates QByteArray formatted query for posting
    */
    QByteArray generateQuery(std::string data, std::vector<std::string> years);
    /*!
     * \fn std::vector<double> ConcreteStatfi::arrayToVector(QJsonArray array)
     * \brief Changes JsonArray to vector of doubles
    */
    std::vector<double> arrayToVector(QJsonArray array);
    /*!
     * \fn std::string ConcreteStatfi::toEncodedQuery(std::string gas)
     * \brief Takes website given code for a gas and returns corresponding gas name
    */
    std::string toEncodedQuery(std::string gas);
};

#endif // CONCRETESTATFI_HH
