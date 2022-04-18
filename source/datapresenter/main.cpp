#include "mainwindow.hh"
#include "model.hh"
#include "controller.hh"

#include <QApplication>
#include <concretestatfi.hh>

#include "concretesmear.hh"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Model* model{new Model()};
    Controller* controller{new Controller(model)};
    MainWindow* view{new MainWindow(controller)};

    model->setView(view);
    model->setupView();
    view->show();

    //ConcreteSmear* smear = new ConcreteSmear(); // test
    //smear->fetchData({"2022-03-07","2022-03-13"},"SO2",{"Hyytiala"}); // test

    return a.exec();
}
