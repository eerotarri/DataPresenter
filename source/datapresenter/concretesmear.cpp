#include "concretesmear.hh"
#include "model.hh"
#include <QDebug>

ConcreteSmear::ConcreteSmear(Model* model, QObject *parent):
    QObject(parent), manager_(new QNetworkAccessManager(this)), model_(model),
    url_(baseUrl), co2ValueName_({}), noxValueName_({}), so2ValueName_({}),
    co2Data_({}), noxData_({}), so2Data_({}),
    timeVec_({}), currentGas_(""), units_(""), ready_(false),
    co2Min_({}), co2Max_({}), co2Average_({}),
    noxMin_({}), noxMax_({}), noxAverage_({}),
    so2Min_({}), so2Max_({}), so2Average_({})
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

std::vector<QString> ConcreteSmear::getSupportedTimeFrame()
{
    return timeframe;
}

std::vector<std::vector<double>> ConcreteSmear::getCurrentData()
{
    model_->getStatistics(currentGas_);
    std::vector<std::vector<double>> emptyVec = {};
    std::vector<std::vector<double>> &currentData = emptyVec;
    if(currentGas_ == QString::fromStdString(gases[0]))
    {
        currentData = noxData_;
    }
    else if(currentGas_ == QString::fromStdString(gases[1]))
    {
        currentData = so2Data_;
    }
    else if(currentGas_ == QString::fromStdString(gases[2]))
    {
        currentData = co2Data_;
    }
    return currentData;
}

std::vector<QDateTime> ConcreteSmear::getTimeVector()
{
    return timeVec_;
}

std::vector<double> ConcreteSmear::getMin()
{
    std::vector<double> emptyVec = {};
    std::vector<double> &currentMin = emptyVec;
    if(currentGas_ == QString::fromStdString(gases[0]))
    {
        currentMin = noxMin_;
    }
    else if(currentGas_ == QString::fromStdString(gases[1]))
    {
        currentMin = so2Min_;
    }
    else if(currentGas_ == QString::fromStdString(gases[2]))
    {
        currentMin = co2Min_;
    }
    return currentMin;
}

std::vector<double> ConcreteSmear::getMax()
{
    std::vector<double> emptyVec = {};
    std::vector<double> &currentMax = emptyVec;
    if(currentGas_ == QString::fromStdString(gases[0]))
    {
        currentMax = noxMax_;
    }
    else if(currentGas_ == QString::fromStdString(gases[1]))
    {
        currentMax = so2Max_;
    }
    else if(currentGas_ == QString::fromStdString(gases[2]))
    {
        currentMax = co2Max_;
    }
    return currentMax;
}

std::vector<double> ConcreteSmear::getAverage()
{
    std::vector<double> emptyVec = {};
    std::vector<double> &currentAverage = emptyVec;
    if(currentGas_ == QString::fromStdString(gases[0]))
    {
        currentAverage = noxAverage_;
    }
    else if(currentGas_ == QString::fromStdString(gases[1]))
    {
        currentAverage = so2Average_;
    }
    else if(currentGas_ == QString::fromStdString(gases[2]))
    {
        currentAverage = co2Average_;
    }
    return currentAverage;
}

QString ConcreteSmear::getDatabaseName()
{
    return "SMEAR";
}

void ConcreteSmear::fetchData(
        std::vector<std::string> timeRange, std::string gas,
        std::vector<std::string> location)
{
    currentGas_ = QString::fromStdString(gas);
    if(gas == gases[0])
    {
        noxValueName_.clear();
        noxData_.clear();
        for(unsigned int i = 0 ; i < location.size() ; i++)
        {
            noxData_.push_back({});
        }
        noxMin_ = {};
        noxMax_= {};
        noxAverage_ = {};
    }
    else if(gas == gases[1])
    {
        so2ValueName_.clear();
        so2Data_.clear();
        for(unsigned int i = 0 ; i < location.size() ; i++)
        {
            so2Data_.push_back({});
        }
        so2Min_ = {};
        so2Max_= {};
        so2Average_ = {};
    }
    else if(gas == gases[2])
    {
        co2ValueName_.clear();
        co2Data_.clear();
        for(unsigned int i = 0 ; i < location.size() ; i++)
        {
            co2Data_.push_back({});
        }
        co2Min_ = {};
        co2Max_= {};
        co2Average_ = {};
    }
    else
    {
        return;
    }

    for(const std::string &station : location)
    {
        generateUrl(timeRange[0], timeRange[1], gas, station);
        QNetworkRequest request = QNetworkRequest(QUrl(url_));
        QNetworkReply* reply = manager_->get(request);
        connect(reply, &QNetworkReply::readyRead, this, &ConcreteSmear::processReply);
    }
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

    QString valueName = "";

    if (station == stations[0]) // Värriö
    {
        if(gas == gases[0]) // nox
        {
            valueName = "VAR_META.NO_1";
            noxValueName_.push_back(valueName);
        }
        else if (gas == gases[1]) // so2
        {
            valueName = "VAR_META.SO2_1";
            so2ValueName_.push_back(valueName);
        }
        else if (gas == gases[2]) // co2
        {
            valueName = "VAR_EDDY.av_c";
            co2ValueName_.push_back(valueName);
        }
    }
    else if (station == stations[1]) // Hyytiälä
    {
        if(gas == gases[0]) // nox
        {
            valueName = "HYY_META.NO168";
            noxValueName_.push_back(valueName);
        }
        else if (gas == gases[1]) // so2
        {
            valueName = "HYY_META.SO2168";
            so2ValueName_.push_back(valueName);
        }
        else if (gas == gases[2]) // co2
        {
            valueName = "HYY_META.CO2icos168";
            co2ValueName_.push_back(valueName);
        }
    }
    else if (station == stations[2]) // Kumpula
    {
        if(gas == gases[0]) // nox
        {
            valueName = "KUM_META.NO_x";
            noxValueName_.push_back(valueName);
        }
        else if (gas == gases[1]) // so2
        {
            valueName = "KUM_META.SO_2";
            so2ValueName_.push_back(valueName);
        }
        else if (gas == gases[2]) // co2
        {
            valueName = "KUM_EDDY.av_c_ep";
            co2ValueName_.push_back(valueName);
        }
    }
    url_.append(valueName);
}

void ConcreteSmear::processReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString replyText = reply->readAll();

    if(reply->error() != QNetworkReply::NoError)
    {
        return;
    }

    QJsonDocument jsonResponse(QJsonDocument::fromJson(replyText.toUtf8()));

    if(jsonResponse.isNull() || !jsonResponse.isObject())
    {
        return;
    }

    QJsonObject jsonObject = jsonResponse.object();

    if(!jsonObject.contains("data"))
    {
        return;
    }

    std::string gas = arrayToVector(jsonObject["data"].toArray());

    QString title = "";
    bool ready = true;
    if(gas == gases[0]) // nox
    {
        title = "NoX";
        units_ = "ppb";
        for(auto& vec : noxData_)
        {
            if(vec.empty())
            {
                ready = false;
            }
        }

    }
    else if(gas == gases[1]) // so2
    {
        title = "SO2";
        units_ = "ppb";
        for(auto& vec : so2Data_)
        {
            if(vec.empty())
            {
                ready = false;
            }
        }
    }
    else if(gas == gases[2]) // co2
    {
        title = "CO2";
        units_ = "ppm";
        for(auto& vec : co2Data_)
        {
            if(vec.empty())
            {
                ready = false;
            }
        }
    }
    else
    {
        return;
    }

    if(ready)
    {
        currentGas_ = QString::fromStdString(gas);
        model_->createCard(this, "MM-dd-hh:mm", units_, title); // kesken
    }

    return;
}

std::string ConcreteSmear::arrayToVector(QJsonArray jsonArray)
{
    std::string gas = "";
    int valueIndex = 0;
    std::vector<double> dataVec = {};
    std::vector<QDateTime> timeVec = {};
    double min = 1000;
    double max = 0;
    double average = 0;
    std::vector<std::vector<double>> *dataPointer = nullptr;
    std::vector<double> *minPointer = nullptr;
    std::vector<double> *maxPointer = nullptr;
    std::vector<double> *averagePointer = nullptr;
    std::vector<QString> *namePointer = nullptr;

    if(jsonArray.empty())
    {
        return {};
    }

    QJsonObject dataObject = jsonArray[0].toObject();
    for(unsigned int i = 0 ; i < co2ValueName_.size() ; i++)
    {
        if(dataObject.contains(co2ValueName_[i]))
        {
            valueIndex = i;
            dataPointer = &co2Data_;
            minPointer = &co2Min_;
            maxPointer = &co2Max_;
            averagePointer = &co2Average_;
            namePointer = &co2ValueName_;
            gas = gases[2];
        }
    }
    for(unsigned int i = 0 ; i < noxValueName_.size() ; i++)
    {
        if(dataObject.contains(noxValueName_[i]))
        {
            valueIndex = i;
            dataPointer = &noxData_;
            minPointer = &noxMin_;
            maxPointer = &noxMax_;
            averagePointer = &noxAverage_;
            namePointer = &noxValueName_;
            gas = gases[0];
        }
    }
    for(unsigned int i = 0 ; i < so2ValueName_.size() ; i++)
    {
        if(dataObject.contains(so2ValueName_[i]))
        {
            valueIndex = i;
            dataPointer = &so2Data_;
            minPointer = &so2Min_;
            maxPointer = &so2Max_;
            averagePointer = &so2Average_;
            namePointer = &so2ValueName_;
            gas = gases[1];
        }
    }

    if(dataPointer == nullptr)
    {
        return "";
    }

    for (int j = 0; j < jsonArray.size(); j++)
    {
        dataObject = jsonArray[j].toObject();

        double data = dataObject[namePointer->at(valueIndex)].toDouble();
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
        averagePointer->push_back(average);
    }

    minPointer->push_back(min);
    maxPointer->push_back(max);

    timeVec_ = timeVec;
    dataPointer->at(valueIndex) = dataVec;

    return gas;
}
