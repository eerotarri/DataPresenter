#include "concretesmear.hh"
#include "model.hh"
#include <QDebug>

ConcreteSmear::ConcreteSmear(Model* model, QObject *parent):
    QObject(parent), manager_(new QNetworkAccessManager(this)), model_(model),
    url_(baseUrl), valueName_({}), currentData_({}),
    timeVec_({}), units_(""), min_({}), max_({}), average_({}), ready_(false)
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
    model_->getStatistics(currentGas_);
    return currentData_;
}

std::vector<QDateTime> ConcreteSmear::getTimeVector()
{
    return timeVec_;
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

QString ConcreteSmear::getDatabaseName()
{
    return "SMEAR";
}

void ConcreteSmear::fetchData(
        std::vector<std::string> timeRange, std::string gas,
        std::vector<std::string> location)
{
    qDebug() << "---*---*---" ;
    qDebug() << "FETCH DATA: " << QString::fromStdString(gas);
    currentGas_ = QString::fromStdString(gas);
    currentData_.clear();
    valueName_.clear();
    qDebug() << "locations: " << location.size() << " kpl" ;
    for(unsigned int i = 0 ; i < location.size() ; i++)
    {
        currentData_.push_back({});
    }
    qDebug() << "current data size: " << currentData_.size() << "   " << currentData_ ;
    min_ = {};
    max_= {};
    average_ = {};

    for(const std::string &station : location)
    {
        qDebug() << QString::fromStdString(station);
        qDebug() << "url funktioon fetch datasta->";
        generateUrl(timeRange[0], timeRange[1], gas, station);
        qDebug() << "->takaisin fetch dataan";
        QNetworkRequest request = QNetworkRequest(QUrl(url_));
        QNetworkReply* reply = manager_->get(request);
        qDebug() << "reply received";
        qDebug() << "before connect";
        connect(reply, &QNetworkReply::readyRead, this, &ConcreteSmear::processReply);
        qDebug() << "after connect";
    }
    qDebug() << "---*---*---" ;
    return;
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

    qDebug() << "-*-*-*-*-*-" ;
    qDebug() << "URL:";
    qDebug() << QString::fromStdString(station);
    qDebug() << QString::fromStdString(gas);

    if (station == stations[0])
    {
        // Värriö
        if(gas == gases[0])
        {
            // nox
            valueName_.push_back("VAR_META.NO_1");
            units_ = "ppb";
        }
        else if (gas == gases[1])
        {
            // so2
            valueName_.push_back("VAR_META.SO2_1");
            units_ = "ppb";
        }
        else if (gas == gases[2])
        {
            // co2
            valueName_.push_back("VAR_EDDY.av_c");
            units_ = "ppm";
        }
    }
    else if (station == stations[1])
    {
        // Hyytiälä
        if(gas == gases[0])
        {
            // nox
            valueName_.push_back("HYY_META.NO168");
            units_ = "ppb";
        }
        else if (gas == gases[1])
        {
            // so2
            valueName_.push_back("HYY_META.SO2168");
            units_ = "ppb";
        }
        else if (gas == gases[2])
        {
            // co2
            valueName_.push_back("HYY_META.CO2icos168");
            units_ = "ppm";
        }
    }
    else if (station == stations[2])
    {
        // Kumpula
        if(gas == gases[0])
        {
            // nox
            valueName_.push_back("KUM_META.NO_x");
            units_ = "ppb";
        }
        else if (gas == gases[1])
        {
            // so2
            valueName_.push_back("KUM_META.SO_2");
            units_ = "ppb";
        }
        else if (gas == gases[2])
        {
            // co2
            valueName_.push_back("KUM_EDDY.av_c_ep");
            units_ = "ppm";
        }
    }

    url_.append(valueName_.at(valueName_.size() - 1));
    qDebug() << "-*-*-*-*-*-" ;
}

void ConcreteSmear::processReply()
{
    qDebug() << "-----------" ;
    qDebug() << "PROCESS REPLY:" << valueName_;
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

    arrayToVector(jsonObject["data"].toArray());

    qDebug() << "end of value processed";

    ready_ = true;
    for(auto& vec : currentData_)
    {
        if(vec.empty())
        {
            ready_ = false;
        }
    }

    qDebug() << "is ready: " << ready_ ;

    if(ready_)
    {
        model_->createCard(this, "MM-dd-hh:mm", units_); // kesken
    }

    qDebug() << "-----------" ;
    return;
}

std::vector<double> ConcreteSmear::arrayToVector(QJsonArray jsonArray)
{
    qDebug() << "***********" ;
    qDebug() << "ARRAY TO VECTOR:" << valueName_;
    int valueIndex = 0;
    std::vector<double> dataVec = {};
    std::vector<QDateTime> timeVec = {};
    double min = 1000;
    double max = 0;
    double average = 0;

    for (int i = 0; i < jsonArray.size(); i++)
    {
        QJsonObject dataObject = jsonArray[i].toObject();
        qDebug() << "data object: " << dataObject;
        for(unsigned int i = 0 ; i < valueName_.size() ; i++)
        {
            if(dataObject.contains(valueName_[i]))
            {
                valueIndex = i;
            }
        }
        double data = dataObject[valueName_[valueIndex]].toDouble();
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

    qDebug() << dataVec;
    qDebug() << ", the size of the vector is: " << dataVec.size();
    qDebug() << ", the min value of it is: " << min;
    qDebug() << ", the max value of it is: " << max;
    qDebug() << ", the average value of it is: " << average;
    qDebug() << ", the units of it is: " << units_;

    timeVec_ = timeVec;
    currentData_.at(valueIndex) = dataVec;

    qDebug() << currentData_;

    qDebug() << "***********" ;

    return dataVec;
}
