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

    /**
     * @brief Sets asked options to the leftSidebarWidget
     * @param options pointer to struct which contains all supported gases, stations and time frames by databases.
     */
    void setSupportedOptions(supportedOptions *options);

    /**
     * @brief Calls cardArea to clear all ChartCard items.
     */
    void clearCardArea();

    /**
     * @brief Calls leftSidebarWidget to set preference values to the view.
     * @param smear pointer to struct which contains gases, stations and time range from Smear selected by user
     * @param statfi pointer to struct which contains gases, stations and time range from Statfi selected by user
     */
    void showPreferences(selectedOptions* smear, selectedOptions* statfi);

    /**
     * @brief Calls cardArea to add new card to the area
     * @param newCard pointer to created ChartCard object
     */
    void addCardToCardArea(ChartCard *newCard);

    /**
     * @brief Asks options selected by user from leftSidebarWidget and returns them.
     * @param database string which one databases options is asked
     * @return ponter to the struct of asked database's selected options
     */
    selectedOptions *getSelectedOptions(std::string database);

    /**
     * @brief Calls leftSidebarWidget to get selected databases.
     * @return vector of databases selected by user
     */
    std::vector<std::string> getSelectedDatabases();

    /**
     * @brief Calls rightSidebarWidget to get plot option selected by user
     * @return pointer to the selected radiobutton of plot option
     */
    QRadioButton *getCurrentPlotOption();

    /**
     * @brief Calls cardArea to get cards in view.
     * @return vector of shown cards in view
     */
    std::vector<ChartCard*> getCards();

private slots:
    /**
     * @brief Closes the application.
     */
    void closeApplication();

private:
    /**
     * @brief Sets layouts and widgets to the view.
     */
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
