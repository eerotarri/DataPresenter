#ifndef MODEL_HH
#define MODEL_HH

#include <QObject>
#include "mainwindow.hh"
#include "idatafetcher.hh"
#include "concretestatfi.hh"
#include <set>

// statfi's gases
const std::string CO2_IN_TONNES = "Khk_yht";
const std::string CO2_INDEXED = "Khk_yht_index";
const std::string CO2_INTENSITY = "Khk_yht_las";
const std::string CO2_INTENSITY_INDEXED = "Khk_yht_las_index";

// smear's gases

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
    void updateChartView();

private:
    void createChart(std::vector<std::vector<double>> gasData);
    std::vector<std::vector<double>> fetchData();
    QLineSeries* setChartSelection(const std::vector<double> dataSelection, const std::vector<int> timeselection);

    MainWindow* view_;
    IDataFetcher* statfiIDataFetcher_;
    //IDataFetcher* smearIDataFetcher_;

    std::set<std::string> checkedStations_;
    int stationCount_;
    std::set<std::string> checkedGases_;
    QString currentDatabase_;

};

#endif // MODEL_HH
