#include "mainwindow.hh"
#include "model.hh"
#include "controller.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow* view{new MainWindow()};
    Model* model{new Model(view)};
    Controller* controller{new Controller(model)};

    view->setController(controller);
    view->show();

    return a.exec();
}
