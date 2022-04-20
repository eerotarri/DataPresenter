#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include "model.hh"

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller(Model* model, QObject* parent = nullptr);

public slots:
    /**
     * @brief Calls model to show preference options.
     */
    void showPreferences();

    /**
     * @brief Call model to save current selected options to the preferences.
     */
    void saveOptionsToPreferences();

    /**
     * @brief Calls model to show valueTableDialog.
     */
    void showStatistics();

    /**
     * @brief Calls model to create new ChartCards to the CardArea.
     */
    void updateCardArea();
private:
    Model* model_;
};

#endif // CONTROLLER_HH
