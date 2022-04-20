#include "concretesmear.hh"
#include "model.hh"
#include <QDebug>

ConcreteSmear::ConcreteSmear(Model* model, QObject *parent):
    QObject(parent), manager_(new QNetworkAccessManager(this)), model_(model),
    url_(baseUrl), valueName_(""), currentData_({{0,1,2,3,4},{0,1,2,3,4}}), // test
    timeVec_({}), units_(""), min_({}), max_({}), average_({})
{
}

ConcreteSmear::~ConcreteSmear()
{
    delete manager_;
}

std::vector<std::string> ConcreteSmear::getSupportedGases()
{
    return gases;
}

std::vector<std::string> ConcreteSmear::getSupportedStations()
{
    return stations;
}

std::vector<double> ConcreteSmear::getSupportedTimeFrame()
{
    return timeframe;
}

std::vector<std::vector<double>> ConcreteSmear::getCurrentData()
{
    return currentData_;
    // TO DO: model pyytää min, max, average ja tallentaa ne johonkin
}

std::vector<QDateTime> ConcreteSmear::getTimeVector()
{
    return timeVec_;
}

QString ConcreteSmear::getUnits()
{
    return units_;
}

std::vector<double> ConcreteSmear::getMin()
{
    return min_;
}

std::vector<double> ConcreteSmear::getMax()
{
    return max_;
}

std::vector<double> ConcreteSmear::getAverage()
{
    return average_;
}

void ConcreteSmear::fetchData(
        std::vector<std::string> timeRange, std::string gas,
        std::vector<std::string> location)
{
    generateUrl(timeRange[0], timeRange[1], gas, location[0]); // test

    QNetworkRequest request = QNetworkRequest(QUrl(url_));
    QNetworkReply* reply = manager_->get(request);
    qDebug() << "reply received" ;
    connect(reply, &QNetworkReply::readyRead, this, &ConcreteSmear::processReply);

}

void ConcreteSmear::generateUrl(std::string start, std::string end,
                         std::string gas, std::string station)
{
    url_ = baseUrl;
    url_.append("/search/timeseries?aggregation=MAX&interval=60&from=");
    url_.append(QString::fromStdString(start)); // YYYY-MM-DD
    url_.append("T00%3A00%3A00.000&to=");
    url_.append(QString::fromStdString(end)); // YYYY-MM-DD
    url_.append("T00%3A00%3A00.000&tablevariable=");

    if (station == stations[0])
    {
        // Värriö
        if(gas == gases[0])
        {
            // nox
            valueName_ = "VAR_META.NO_1";
            units_ = "ppb";
        }
        else if (gas == gases[1])
        {
            // so2
            valueName_ = "VAR_META.SO2_1";
            units_ = "ppb";
        }
        else if (gas == gases[1])
        {
            // co2
            valueName_ = "VAR_EDDY.av_c";
            units_ = "ppm";
        }
    }
    else if (station == stations[1])
    {
        // Hyytiälä
        if(gas == gases[0])
        {
            // nox
            valueName_ = "HYY_META.NO168";
            units_ = "ppb";
        }
        else if (gas == gases[1])
        {
            // so2
            valueName_ = "HYY_META.SO2168";
            units_ = "ppb";
        }
        else if (gas == gases[1])
        {
            // co2
            valueName_ = "HYY_META.CO2icos168";
            units_ = "ppm";
        }
    }
    else if (station == stations[2])
    {
        // Kumpula
        if(gas == gases[0])
        {
            // nox
            valueName_ = "KUM_META.NO_x";
            units_ = "ppb";
        }
        else if (gas == gases[1])
        {
            // so2
            valueName_ = "KUM_META.SO_2";
            units_ = "ppb";
        }
        else if (gas == gases[1])
        {
            // co2
            valueName_ = "KUM_EDDY.av_c_ep";
            units_ = "ppm";
        }
    }

    url_.append(valueName_);
    qDebug() << "url: " << QString(url_);
}

void ConcreteSmear::processReply()
{
    qDebug() << "Process reply: ";
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString replyText = reply->readAll();

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

    if(!jsonObject.contains("data"))
    {
        qDebug() << "does not have value" ;
        return;
    }

    qDebug() << "---*---*---" ;
    arrayToVector(jsonObject["data"].toArray());

    qDebug() << "end";

    return;
}

std::vector<double> ConcreteSmear::arrayToVector(QJsonArray jsonArray)
{
    std::vector<double> dataVec = {};
    std::vector<QDateTime> timeVec = {};
    double min = 1000;
    double max = 0;
    double average = 0;

    for (int i = 0; i < jsonArray.size(); i++)
    {
        QJsonObject dataObject = jsonArray[i].toObject();
        double data = dataObject[valueName_].toDouble();
        dataVec.push_back(data);

        if(data > max){
            max = data;
        }
        if(data < min){
            min = data;
        }
        average = average + data;

        QString timeString = dataObject["samptime"].toString();
        QString format = "yyyy-MM-ddThh:mm:ss.sss";
        QDateTime time = QDateTime::fromString(timeString, format);
        timeVec.push_back(time);
    }

    if(dataVec.size() != 0){
        average = average/dataVec.size();
        average_.push_back(average);
    }

    min_.push_back(min);
    max_.push_back(max);

    qDebug() << dataVec.size();
    qDebug() << min;
    qDebug() << max;
    qDebug() << average;
    qDebug() << units_;

    timeVec_ = timeVec;
    currentData_.push_back(dataVec);

    return dataVec;
}
