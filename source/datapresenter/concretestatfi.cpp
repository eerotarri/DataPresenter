#include "concretestatfi.hh"

#include <QDebug>

ConcreteStatfi::ConcreteStatfi(QObject *parent) : QObject(parent)
{
}

void ConcreteStatfi::post(QString location, QByteArray data)
{
    QNetworkRequest request = QNetworkRequest(QUrl(location));
    request.setHeader(QNetworkRequest::ContentTypeHeader, 0);
    QNetworkReply* reply = manager_.post(request, data);
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
    std::vector<double> values = arrayToVector(jsonArray);

    return;
}

QByteArray ConcreteStatfi::generateQuery(std::string data, std::vector<int> years)
{
    QByteArray query("{\n"
    "    \"query\": [\n"
    "        {\n"
    "            \"code\": \"Tiedot\",\n"
    "            \"selection\": {\n"
    "                \"filter\": \"item\",\n"
    "                \"values\": [\n"
    "                    \"");
    query.append(data);
    query.append("\"\n"
    "                ]\n"
    "            }\n"
    "        },\n"
    "        {\n"
    "            \"code\": \"Vuosi\",\n"
    "            \"selection\": {\n"
    "                \"filter\": \"item\",\n"
    "                \"values\": [\n");

    for (int year : years) {
        std::string y = std::to_string(year);
        query.append("                    \"" + y + "\",\n");
    }
    query.append("                ]\n"
    "            }\n"
    "        }\n"
    "    ]\n"
    "}\n");


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
