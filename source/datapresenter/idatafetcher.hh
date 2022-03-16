#ifndef IDATAFETCHER_HH
#define IDATAFETCHER_HH

#include <vector>
#include <string>

class IDataFetcher
{
public:
    virtual std::vector<std::vector<double>> fetchData(std::vector<std::string> timeRange, std::vector<std::string> gas, std::vector<std::string> location = {}) = 0;
};

#endif // IDATAFETCHER_HH

