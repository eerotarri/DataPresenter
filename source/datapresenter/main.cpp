#include <concretestatfi.hh>

#include "mainwindow.hh"
#include "model.hh"
#include "controller.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow* view = new MainWindow();
    Model* model = new Model(view);
    Controller* controller = new Controller(model);

    view->setController(controller);
    view->show();

    // STATFI test lines
    std::vector<std::string> timeRange = {"2010", "2011"};
    std::vector<std::string> gas = {"Khk_yht_index", "Khk_yht_las_index"};

    ConcreteStatfi* statfi = new ConcreteStatfi();

    statfi->fetchData(timeRange, gas);

    return a.exec();
}
