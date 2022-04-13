#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

/*
#include <QMainWindow>
#include <QChartView>
#include <QWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLineSeries>
#include <QBarSeries>
#include <QLayout>
#include <QGroupBox>
#include <QGraphicsEffect>
#include <QSpinBox>

#include "timerangedialog.hh"
#include "valuetabledialog.hh"
*/

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

const QString COMPARE = "COMPARE";

class Controller;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setController(Controller* controller);
    void createGasGroupBox(QString database, std::vector<std::string> gases);
    void createStationGroupBox(QString database, std::vector<std::string> stations);
    void setup();
    void updateChart(QChart *chart);

    void showStatfi();
    void showSmear();
    void showCompare();

private slots:
    void on_startButton_clicked();
    void on_quitButton_clicked();
    void on_compareButton_clicked();
    void on_setTimeRangeButton_clicked();
    void on_valueTableButton_clicked();
    void on_databaseComboBox_currentTextChanged();
    void on_showDataButton_clicked();
    void on_toYearSpinBox_valueChanged(int year);
    void on_fromYearSpinBox_valueChanged(int year);

    // uutta
    void stationCheckboxStateChanged(int state);
    void gasCheckboxStateChanged(int state);

private:
    void createSidebar();
    void createStatfiTimeRangeWidget();
    void createNewChartAreaWidget();

    Ui::MainWindow *ui;
    Controller* controller_;

    QPushButton *startButton_;

    QWidget* mainWidget_;
    QGridLayout *mainLayout_;

    QWidget *sidebarWidget_;
    QGridLayout *sidebarLayout_;

    QWidget *smearSidebarWidget_;
    QWidget *statfiSidebarWidget_;

    QFrame* graphic_frame_;
    //QChart* chart_;
    QChartView* chart_view_;

    QGridLayout *chartLayout_;

    QScrollArea *scrollArea_;
    QWidget *chartAreaWidget_;

    QComboBox* databaseComboBox_;

    QGroupBox *smearGasGroupBox_;
    QGroupBox *smearStationGroupBox_;

    QGroupBox *statfiGasGroupBox_;

    QGroupBox *compareGasGroupBox_;
    QGroupBox *compareStationGroupBox_;

    QGroupBox *gasGroupBox_;
    QGroupBox *stationGroupBox_;

    QPushButton *showDataButton_;

    QPushButton* valueTableButton_;
    QPushButton* compareButton_;
    QPushButton* quitButton_;
    QPushButton* setTimeRangeButton_;

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
    void addCardToCardArea(ChartCard *newCard);

    //void setController(Controller* controller);

public slots:
    //void cardCreated(ChartCard*);

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
    //QGridLayout *cardAreaLayout_ = new QGridLayout();

};
#endif // MAINWINDOW_HH
