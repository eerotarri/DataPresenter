#ifndef CONCRETESTATFI_HH
#define CONCRETESTATFI_HH

#include "idatafetcher.hh"

#include "model.hh"

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

    virtual void fetchData(std::vector<std::string> timeRange, std::string gas, std::vector<std::string> location = {});
    std::vector<std::vector<double>> getCurrentData();
    virtual std::vector<double> getSupportedTimeFrame();
    virtual std::vector<std::string> getSupportedStations();
    virtual std::vector<std::string> getSupportedGases();

private slots:
    void post(QByteArray data);
    void readyRead();

private:
    const QUrl url_ = QUrl("https://pxnet2.stat.fi/PXWeb/api/v1/en/ymp/taulukot/Kokodata.px");
    const std::vector<double> supportedTimeFrame_ = {1975, 2017};
    const std::vector<std::string> supportedGases_ = {"Khk_yht","Khk_yht_index","Khk_yht_las","Khk_yht_las_index"};

    QNetworkAccessManager* manager_;
    Model* model_;
    std::vector<std::vector<double> > currentData_ = {};


    /*!
     * \fn QByteArray ConcreteStatfi::generateQuery(std::string data, std::vector<int> years)
     * \brief Generates QByteArray formatted query for posting
    */
    QByteArray generateQuery(std::string data, std::vector<std::string> years);
    std::vector<double> arrayToVector(QJsonArray array);
};

#endif // CONCRETESTATFI_HH
