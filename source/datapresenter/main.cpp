#include "mainwindow.hh"
#include "model.hh"
#include "controller.hh"
#include <QApplication>

#include "concretesmear.hh"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow* view = new MainWindow();
    Model* model = new Model(view);
    Controller* controller = new Controller(model);

    view->setController(controller);
    view->show();

    ConcreteSmear* smear = new ConcreteSmear(); // test
    smear->fetchData({"2022-03-07","2022-03-13"},"SO2",{"Hyytiala"}); // test

    return a.exec();
}
