#ifndef IDATAFETCHER_HH
#define IDATAFETCHER_HH

#include <vector>
#include <string>
#include <QDateTime>

// Copy the method below to your code and change classname if necessary.

//void Model::getData(IDataFetcher *sender)
//{
//    auto data = sender->getCurrentData();
//    // Nyt datan voi tallentaa tai suoraan esittää graafisesti
//}

class IDataFetcher
{
public:

    /**
     * @brief Sets the asked values in object and notifies model when data is ready to be collected.
     * @param timeRange vector of begin and end values for data
     * @param gas vector of 1 or more gases for data
     * @param location vector of stations where data is required from
     *
     * fetchData combined with getCurrentData (see next public method) allows client to access data from
     * networks asynchronously. fetchData alone is responsible for taking client parameters and executing
     * the process of getting the correct data from network to local.
     */
    virtual void fetchData(std::vector<std::string> timeRange, std::string gas, std::vector<std::string> location = {}) = 0;

    /**
     * @brief Get function for the data previously fetched from network
     * @return data in the form of std::vector<std::vector<double>>
     *
     * getCurrentData is necessary to actually get access to data fetched in datafetcher.
     * getCurrentData should always be called from clients method named "getData()" because
     * fetchData will emit function call to said mehtod in client after getting the data is finished.
     */
    virtual std::vector<std::vector<double>> getCurrentData() = 0;

    /**
     * @brief Get function for the range of time that is possible for certain website queries
     * @return range in the form of std::vector<double>
     */
    virtual std::vector<double> getSupportedTimeFrame() = 0;

    /**
     * @brief Get function for the stations that are possible for certain website queries
     * @return stations in the form of std::vector<std::string>
     *
     * This method will return an empty vector if location is not a parameter at all in given website
     */
    virtual std::vector<std::string> getSupportedStations() = 0;

    /**
     * @brief Get function for the gases that are possible for certain website queries
     * @return possible gases in the form of std::vector<std::string>
     */
    virtual std::vector<std::string> getSupportedGases() = 0;

    virtual std::vector<QDateTime> getTimeVector() = 0;

    virtual QString getDatabaseName() = 0;
};

#endif // IDATAFETCHER_HH

