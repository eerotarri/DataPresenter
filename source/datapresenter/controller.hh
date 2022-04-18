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
    void showPreferences();
    void saveOptionsToPreferences();
    void showStatistics();
    void updateCardArea();
private:
    Model* model_;
};

#endif // CONTROLLER_HH
