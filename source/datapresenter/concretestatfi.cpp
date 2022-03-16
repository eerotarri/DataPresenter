#include "concretestatfi.hh"

#include <QDebug>

ConcreteStatfi::ConcreteStatfi(QObject *parent) : QObject(parent)
{
    manager_ = new QNetworkAccessManager();
}

std::vector<std::vector<double> > ConcreteStatfi::fetchData(std::vector<std::string> timeRange, std::vector<std::string> gas, std::vector<std::string> location)
{
    Q_UNUSED(location);

    QByteArray query = generateQuery(gas, timeRange);
    post(query);
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

    QJsonArray jsonArray = jsonObject["values"].toArray();
    values_ = arrayToVector(jsonArray);

    return;
}

QByteArray ConcreteStatfi::generateQuery(std::vector<std::string> data, std::vector<std::string> years)
{
    QByteArray query("{\"query\": [{\"code\": \"Tiedot\",\"selection\": {\"filter\": \"item\",\"values\": [");

    // Dynamically adds datasets to query
    for (size_t i = 0; i < data.size(); ++i) {
        query.append("\"" + data.at(i) + "\",");
    }

    query.append("]}},{\"code\": \"Vuosi\",\"selection\": {\"filter\": \"item\",\"values\": [");

    // Dynamically adds timerange to query
    for (size_t i = 0; i < data.size(); ++i) {
        query.append("\"" + years.at(i) + "\",");
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


