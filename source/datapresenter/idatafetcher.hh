#ifndef IDATAFETCHER_HH
#define IDATAFETCHER_HH

#include <vector>
#include <string>

class IDataFetcher
{
public:
    IDataFetcher();

    std::vector<std::vector<double>> fetchData(std::vector<std::string> timeRange, std::string gas, std::vector<std::string> location = {});
};

#endif // IDATAFETCHER_HH
