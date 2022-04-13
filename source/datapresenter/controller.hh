#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include <QObject>
#include "model.hh"

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller(Model* model, QObject* parent = nullptr);


public slots:
    /*
    void startButtonClicked();
    void compareButtonClicked();
    void dadabaseComboBoxCurrentTextChanged(const QString& current_database);
    void stationCheckBoxStateChanged(const std::string& name, int state);
    void gasCheckBoxStateChanged(const std::string& name, int state);
    void showDatabuttonClicked(int startTime, int endTime);
    */
    void closeApplication();
private:
    Model* model_;
};

#endif // CONTROLLER_HH
