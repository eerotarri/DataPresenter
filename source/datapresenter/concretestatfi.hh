#ifndef CONCRETESTATFI_HH
#define CONCRETESTATFI_HH

#include "idatafetcher.hh"

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

class ConcreteStatfi : public QObject, public IDataFetcher
{
    Q_OBJECT
public:
    explicit ConcreteStatfi(QObject *parent = nullptr);

    virtual std::vector<std::vector<double>> fetchData(std::vector<std::string> timeRange, std::vector<std::string> gas, std::vector<std::string> location = {});

private slots:
    void post(QByteArray data);
    void readyRead();

private:
    const QUrl url_ = QUrl("https://pxnet2.stat.fi/PXWeb/api/v1/en/ymp/taulukot/Kokodata.px");
    const std::pair<int, int> supportedTimeFrame = {1975, 2017};

    QNetworkAccessManager* manager_;
    std::vector<double> values_;


    /*!
     * \fn QByteArray ConcreteStatfi::generateQuery(std::string data, std::vector<int> years)
     * \brief Generates QByteArray formatted query for posting
    */
    QByteArray generateQuery(std::vector<std::string> data, std::vector<std::string> years);
    std::vector<double> arrayToVector(QJsonArray array);
};

#endif // CONCRETESTATFI_HH
