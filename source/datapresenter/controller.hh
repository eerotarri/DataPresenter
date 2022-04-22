#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include "model.hh"

class Controller
{
public:
    Controller(Model* model);

private:
    Model* model_;
};

#endif // CONTROLLER_HH
