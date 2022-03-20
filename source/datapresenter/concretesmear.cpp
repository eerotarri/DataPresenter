#include "concretesmear.hh"
#include <QDebug>

ConcreteSmear::ConcreteSmear(QObject *parent):
    QObject(parent), manager_(new QNetworkAccessManager(this)),
    url_(baseUrl)
{
}

ConcreteSmear::~ConcreteSmear()
{
    delete manager_;
}

std::vector<std::string> ConcreteSmear::returnGases()
{
    return gases;
}

std::vector<std::string> ConcreteSmear::returnStations()
{
    return stations;
}

std::vector<std::vector<double>> ConcreteSmear::fetchData(
        std::vector<std::string> timeRange, std::string gas,
        std::vector<std::string> location)
{
    generateUrl(timeRange[0], timeRange[1], gas, location[0]); // test

    QNetworkRequest request = QNetworkRequest(QUrl(url_));
    QNetworkReply* reply = manager_->get(request);
    qDebug() << "reply received" ;
    connect(reply, &QNetworkReply::readyRead, this, &ConcreteSmear::processReply);
    return {};
}

void ConcreteSmear::generateUrl(std::string start, std::string end,
                         std::string gas, std::string station)
{
    url_ = baseUrl;
    url_.append("/search/timeseries/chart?aggregation=NONE&from=");
    url_.append(QString::fromStdString(start)); // YYYY-MM-DD
    url_.append("T00%3A00%3A00.000&interval=60&quality=ANY&tablevariable=");

    if (station == stations[0])
    {
        // Värriö
        url_.append("VAR_META.");
        if(gas == gases[0])
        {
            // nox
        }
        else if (gas == gases[1])
        {
            // so2
        }
        else if (gas == gases[1])
        {
            // co2
        }
    }
    else if (station == stations[1])
    {
        // Hyytiälä
        url_.append("HYY_META.");
        if(gas == gases[0])
        {
            // nox
            url_.append("NOx168");
        }
        else if (gas == gases[1])
        {
            // so2
            url_.append("SO2168");
        }
        else if (gas == gases[1])
        {
            // co2
            url_.append("CO2icos168");
        }
    }
    else if (station == stations[2])
    {
        // Kumpula
        url_.append("KUM_META.");
        if(gas == gases[0])
        {
            // nox
            url_.append("NO_x");
        }
        else if (gas == gases[1])
        {
            // so2
            url_.append("SO_2");
        }
        else if (gas == gases[1])
        {
            // co2
        }
    }

    url_.append("&to=");
    url_.append(QString::fromStdString(end)); // YYYY-MM-DD
    url_.append("T00%3A00%3A00.000");
    qDebug() << "url: " << QString(url_);
}

void ConcreteSmear::processReply()
{
    // TO DO
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString replyText = reply->readAll();
    qDebug() << replyText;

    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "didn't get value" ;
        return;
    }

    QJsonDocument jsonResponse(QJsonDocument::fromJson(replyText.toUtf8()));

    if(jsonResponse.isNull() || !jsonResponse.isObject())
    {
        qDebug() << "does not have content or content is shit" ;
        return;
    }

    QJsonObject jsonObject = jsonResponse.object();

    if(!jsonObject.contains("value"))
    {
        qDebug() << "does not have value" ;
        return;
    }

    QJsonArray jsonArray = jsonObject["values"].toArray();
    qDebug() << "end";

    return;
}

// Station:
// Värriö: 1: 15m
// NOx: 540, NOX_0
// SO2: 554, SO2_0
// CO2: 636, CO206

// Hyytiälä: 2: 16,8m
// NOx: 155, NOx168
// SO2: 163, SO2168
// CO2: 114, CO2icos168

// Kumpula: 3: 4m
// NOx: 43, NO_x
// SO2: 46, SO_2
// CO2:
