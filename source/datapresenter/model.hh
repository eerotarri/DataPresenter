#ifndef MODEL_HH
#define MODEL_HH

#include <QObject>
#include "mainwindow.hh"
#include "idatafetcher.hh"
#include "concretestatfi.hh"
#include <set>

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
    void createChart(const QString gasSelection, const QString stationSelection, const QString timeSelection);


private:
    QLineSeries* setChartSelection(const QString dataSelection, const QString timeselection);

    MainWindow* view_;
    IDataFetcher* statfiIDataFetcher_;
    //IDataFetcher* smearIDataFetcher_;

    std::set<std::string> checkedStations_;
    std::set<std::string> checkedGases_;

};

#endif // MODEL_HH
