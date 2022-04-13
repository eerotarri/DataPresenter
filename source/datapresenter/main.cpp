#include "mainwindow.hh"
#include "model.hh"
#include "controller.hh"

#include <QApplication>
#include <concretestatfi.hh>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Model* model{new Model()};
    Controller* controller{new Controller(model)};
    MainWindow* view{new MainWindow(controller)};

    model->setView(view);
    view->show();

    return a.exec();
}
