#include "concretestatfi.hh"
#include "model.hh"

#include <QDebug>

ConcreteStatfi::ConcreteStatfi(Model* model, QObject *parent) : QObject(parent)
  , model_(model)
{
    manager_ = new QNetworkAccessManager();
}

void ConcreteStatfi::fetchData(std::vector<std::string> timeRange, std::string gas, std::vector<std::string> location)
{
    if ( timeRange.size() > 1) {
        Q_UNUSED(location);

        //    std::vector<double> range{};
        //    for (size_t i = 0; i < timeRange.size(); i++) {
        //        range.push_back(std::stod(timeRange[i]));
        //    }
        //    currentData_.push_back(range);

        QByteArray query = generateQuery(gas, timeRange);
        post(query);
    }
}

std::vector<std::vector<double>> ConcreteStatfi::getCurrentData()
{
    return currentData_;
}

std::vector<double> ConcreteStatfi::getSupportedTimeFrame()
{
    return supportedTimeFrame_;
}

std::vector<std::string> ConcreteStatfi::getSupportedStations()
{
    return {};
}

std::vector<std::string> ConcreteStatfi::getSupportedGases()
{
    return supportedGases_;
}

QString ConcreteStatfi::getUnits()
{
    // TO DO
    return "";
}

std::vector<QDateTime> ConcreteStatfi::getTimeVector()
{
    // TO DO
    return {};
}

void ConcreteStatfi::post(QByteArray data)
{
    QNetworkRequest request = QNetworkRequest(QUrl(url_));
    request.setHeader(QNetworkRequest::ContentTypeHeader, 0);
    QNetworkReply* reply = manager_->post(request, data);
    connect(reply, &QNetworkReply::readyRead, this, &ConcreteStatfi::readyRead);

}

void ConcreteStatfi::readyRead()
{

    // Haetaan raaka vastaus
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "STATFI: There was an error fetching the data from website.";
        return;
    }

    QJsonDocument jsonResponse(QJsonDocument::fromJson(reply->readAll()));



    if (jsonResponse.isNull() || !jsonResponse.isObject()) {
        qDebug() << "STATFI: Fetched data did not exist or it was not convertible to object.";
        return;
    }

    QJsonObject jsonObject = jsonResponse.object();

    if (!jsonObject.contains("value")) {
        qDebug() << "STATFI: Fetched data does not contain asked values.";
        return;
    }

    auto values = arrayToVector(jsonObject["value"].toArray());

    currentData_.clear();
    currentData_.push_back(values);

    qDebug() << values;

    model_->createCard(this);

    return;
}

QByteArray ConcreteStatfi::generateQuery(std::string data, std::vector<std::string> years)
{
        QByteArray query("{\"query\": [{\"code\": \"Tiedot\",\"selection\": {\"filter\": \"item\",\"values\": [");

        // Dynamically adds datasets to query
        query.append("\"" + toEncodedQuery(data) + "\",");


        query.append("]}},{\"code\": \"Vuosi\",\"selection\": {\"filter\": \"item\",\"values\": [");

        // Dynamically adds timerange to query
        for (int i = 0; i <= stoi(years.at(1)) - stoi(years.at(0)); ++i) {

            query.append("\"" + std::to_string(stoi(years.at(0)) + i) + "\",");
        }

        query.append("]}}]}");
        return query;
}

std::vector<double> ConcreteStatfi::arrayToVector(QJsonArray array)
{
    std::vector<double> dataVector = {};

    for (int i = 0; i < array.size(); i++) {
        dataVector.push_back(array[i].toDouble());
    }

    return dataVector;
}

std::string ConcreteStatfi::toEncodedQuery(std::string gas)
{
    if (gas == "CO2 in tonnes") {
        currentUnit_ = "1000 t";
        return "Khk_yht";
    }
    if (gas == "CO2 intensity") {
        currentUnit_ = "intensity";
        return "Khk_yht_las";
    }
    if (gas == "CO2 indexed") {
        currentUnit_ = "indexed, 1990 = 100";
        return "Khk_yht_index";
    }
    if (gas == "CO2 indensity indexed") {
        currentUnit_ = "indexed, 1990 = 100";
        return "Khk_yht_las_index";
    }
    return "ERROR";
}
