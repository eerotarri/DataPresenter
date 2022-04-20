#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "rightsidebar.hh"
#include "leftsidebar.hh"
#include "controller.hh"
#include "cardarea.hh"

#include <QMainWindow>
#include <QWidget>
#include <QLayout>
#include <QScrollArea>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// For Qt 5, which used QtCharts namespace for the classes in the charts module
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    using QChart = QtCharts::QChart;
    using QChartView = QtCharts::QChartView;
#endif

/*
// databases
const QString SMEAR = "SMEAR";
const QString STATFI = "STATFI";

private:
    QWidget *statfiTimeRangeWidget_;
    QSpinBox *toYearSpinBox_;
    QSpinBox *fromYearSpinBox_;

    TimeRangeDialog* time_range_dialog_;
    ValueTableDialog* value_table_dialog_;

    QGraphicsBlurEffect *blurEffect_;

};
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Controller *controller, QWidget *parent = nullptr);
    ~MainWindow();
    void setSupportedOptions(supportedOptions *options);
    void clearCardArea();
    void showPreferences(selectedOptions* smear, selectedOptions* statfi);
    void addCardToCardArea(ChartCard *newCard);
    selectedOptions *getSelectedOptions(std::string database);
    std::vector<std::string> getSelectedDatabases();
    QRadioButton *getCurrentPlotOption();
    std::vector<ChartCard*> getCards();

private slots:
    void closeApplication();

private:
    void setup();

    Ui::MainWindow *ui;
    Controller *controller_;

    QWidget *mainWidget_ = new QWidget();
    QGridLayout *mainLayout_ = new QGridLayout();

    RightSidebar *rightSidebarWidget_ = new RightSidebar;
    LeftSidebar *leftSidebarWidget_ = new LeftSidebar;

    QScrollArea *scrollArea_ = new QScrollArea;
    CardArea *cardArea_ = new CardArea;

};
#endif // MAINWINDOW_HH
