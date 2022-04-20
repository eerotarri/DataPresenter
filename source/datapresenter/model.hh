#ifndef MODEL_HH
#define MODEL_HH

#include "idatafetcher.hh"
#include "concretestatfi.hh"
#include "concretesmear.hh"
#include "valuetabledialog.hh"

#include <QObject>

class MainWindow;
struct selectedOptions;

struct supportedOptions {
    std::vector<std::string> smearGases;
    std::vector<std::string> statfiGases;
    std::vector<std::string> smearStations;
    std::vector<std::string> smearTimeRange;
    std::vector<std::string> statfiTimeRange;
};

struct Preferences{
    selectedOptions *statfiPreferences = nullptr;
    selectedOptions *smearPreferences = nullptr;
};

class Model : public QObject
{
    Q_OBJECT
public:
    Model(QObject *parent = nullptr);
    void setView(MainWindow *view);
    void setupView();
    void showPreferences();
    void saveToPreferences();
    void showStatistics();
    void updateCardArea();
    void createCard(IDataFetcher* fetcher);

private:
    void getSupportedOptions();
    void updateSelectedOptions();

    MainWindow *view_;
    selectedOptions *smearSelectedOptions_ = nullptr;
    selectedOptions *statfiSelectedOptions_ = nullptr;
    supportedOptions *supportedOptions_ = nullptr;
    Preferences *preferences_ = new Preferences;
    IDataFetcher *statfi_ = new ConcreteStatfi(this);
    IDataFetcher *smear_ = nullptr; //new ConcreteSmear(this);
    ValueTableDialog *valueTable_ = new ValueTableDialog;
};

#endif // MODEL_HH
