#ifndef MODEL_HH
#define MODEL_HH

#include <QObject>
#include "mainwindow.hh"

class Model : public QObject
{
    Q_OBJECT

public:
    Model(MainWindow* view, QObject* parent = nullptr);

private:
    MainWindow* view_;
};

#endif // MODEL_HH
