#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QChartView>
#include <QWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QCalendar>
#include <QLineSeries>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// For Qt 5, which used QtCharts namespace for the classes in the charts module
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    using QChart = QtCharts::QChart;
    using QChartView = QtCharts::QChartView;
#endif

class Controller;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setController(Controller* controller);

    void updateChart(QLineSeries* series, const QString& title);

private slots:
    void on_quitButton_clicked();
    void on_compareButton_clicked();

private:
    void setup();
    void addConnects();

    Ui::MainWindow *ui;
    Controller* controller_;
    QWidget* containerWidget_;
    QWidget* mainWidget_;
    QFrame* graphic_frame_;
    QChart* chart_;
    QChartView* chart_view_;
    QComboBox* gas_combo_box_;
    QComboBox* database_combo_box_;
    QCheckBox* hyytiala_check_box_;
    QCheckBox* kumpula_check_box_;
    QCheckBox* varrio_check_box_;
    QCalendar* start_day_calendar_;
    QCalendar* end_day_calendar_;
    QPushButton* averageButton_;
    QPushButton* statisticsButton_;
    QPushButton* compareButton_;
    QPushButton* quitButton_;
};
#endif // MAINWINDOW_HH
