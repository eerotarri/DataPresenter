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


private:
    Model* model_;
};

#endif // CONTROLLER_HH
