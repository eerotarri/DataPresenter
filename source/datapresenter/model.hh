#ifndef MODEL_HH
#define MODEL_HH

#include "idatafetcher.hh"
#include "concretestatfi.hh"

#include <QObject>

struct supportedOptions {
    std::vector<std::string> smearGases;
    std::vector<std::string> statfiGases;
    std::vector<std::string> smearStations;
    std::vector<std::string> smearTimeRange;
    std::vector<std::string> statfiTimeRange;
};

class MainWindow;
struct selectedOptions;

/*
// stations
class Model : public QObject
{
    Q_OBJECT

public:
    Model(MainWindow* view, QObject* parent = nullptr);
    void setupView();

    void changeDatabase(const QString current_database);
    void updateCheckedStations(const std::string name, int state);
    void updateCheckedGases(const std::string name, int state);
    void fetchData();
    void updateChartView(IDataFetcher* base);
    void updateStatfiTimeRange(int startYear, int endYear);

private:
    void createChart(std::vector<std::vector<double>> gasData);
    void createLineChart(std::vector<std::vector<double>> gasData);
    void createBarChart(std::vector<double> gasData);

    QBarSeries* createBarSeries(const std::vector<double> dataSelection);
    QLineSeries* createLineSeries(const std::vector<double> dataSelection, const std::vector<double> timeselection);

    MainWindow* view_;
    IDataFetcher* statfiIDataFetcher_;
    //IDataFetcher* smearIDataFetcher_;

    std::set<std::string> checkedStations_;
    int stationCount_;
    std::set<std::string> checkedGases_;
    QString currentDatabase_;
    int statfiStartYear_;
    int statfiEndYear_;

};
*/
struct Preferences{
    selectedOptions *statfiPreferences;
    selectedOptions *smearPreferences;
};

class Model : public QObject
{
    Q_OBJECT
public:
    Model(QObject *parent = nullptr);
    void setView(MainWindow *view);
    void setupView();
    void updateChartView(IDataFetcher* base);
    void showPreferences();
    void saveToPreferences();
    void showStatistics();
    void updateCardArea();
    void createCard(selectedOptions *selectedOptions, IDataFetcher* fetcher);

private:
    void getSupportedOptions();
    void updateSelectedOptions();
    MainWindow *view_;
    selectedOptions *smearSelectedOptions_ = nullptr;
    selectedOptions *statfiSelectedOptions_ = nullptr;
    supportedOptions *supportedOptions_ = nullptr;
    Preferences *preferences_ = nullptr;
    IDataFetcher *statfi_ = new ConcreteStatfi(this);
    IDataFetcher *smear_ = nullptr; // new ConcreteSmear(this);
};

#endif // MODEL_HH
