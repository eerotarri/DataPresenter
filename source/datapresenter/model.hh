#ifndef MODEL_HH
#define MODEL_HH

#include "mainwindow.hh"

class Model
{
public:
    Model(MainWindow* view);

private:
    MainWindow* view_;
};

#endif // MODEL_HH
