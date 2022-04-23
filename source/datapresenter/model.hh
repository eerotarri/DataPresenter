#ifndef MODEL_HH
#define MODEL_HH

#include "idatafetcher.hh"
#include "concretestatfi.hh"
#include "concretesmear.hh"
#include "concretesmear.hh"
#include "valuetabledialog.hh"

#include <QObject>

class MainWindow;
struct selectedOptions;

struct supportedOptions {
    std::vector<std::string> smearGases;
    std::vector<std::string> statfiGases;
    std::vector<std::string> smearStations;
    std::vector<QString> smearTimeRange;
    std::vector<QString> statfiTimeRange;
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

    /**
     * @brief Sets used MainWindow object to private variable
     * @param view pointer to used MainWindow object
     */
    void setView(MainWindow *view);

    /**
     * @brief Sends supported options to the view.
     */
    void setupView();

    /**
     * @brief Calls view to show preference options to the user.
     */
    void showPreferences();

    /**
     * @brief Saves current selected options to the preferenses.
     */
    void saveToPreferences();

    /**
     * @brief Opens valueTableDialog.
     */
    void showStatistics();

    /**
     * @brief Calls DataFetcher with options selected by user.
     */
    void updateCardArea();

    /**
     * @brief Get data from fetcher and creates new ChartCard based on plot option selected by user.
     * @param fetcher pointer to the used concrete fetcher
     * @param format for time unit
     * @param unit for gas
     */
    void createCard(IDataFetcher* fetcher, QString format, QString unit, QString title);

    /**
     * @brief Gets min, max and average values for valueTableDialog from Smear.
     */
    void getStatistics(QString gas);

private:
    /**
     * @brief Gets supported gases, stations and time frames from databases.
     */
    void getSupportedOptions();

    /**
     * @brief Updates selectedOptions variable based on user's selections.
     */
    void updateSelectedOptions();

    MainWindow *view_;
    selectedOptions *smearSelectedOptions_ = nullptr;
    selectedOptions *statfiSelectedOptions_ = nullptr;
    supportedOptions *supportedOptions_ = nullptr;
    Preferences *preferences_ = new Preferences;
    IDataFetcher *statfi_ = new ConcreteStatfi(this);
    IDataFetcher *smear_ = new ConcreteSmear(this);
    ValueTableDialog *valueTable_ = new ValueTableDialog;
    std::string gasInGraph_ = "";
};

#endif // MODEL_HH
