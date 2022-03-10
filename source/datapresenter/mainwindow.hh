#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QChartView>
#include <QWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLineSeries>
#include "timerangedialog.hh"
#include "valuetabledialog.hh"
#include "yearselectdialog.hh"


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

    void showStatfi();
    void showSmear();
    void showCompare();

private slots:
    void on_quitButton_clicked();
    void on_compareButton_clicked();
    void on_setTimeRangeButton_clicked();
    void on_valueTableButton_clicked();
    void on_database_combo_box_currentTextChanged();

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
    QPushButton* valueTableButton_;
    QPushButton* statisticsButton_;
    QPushButton* compareButton_;
    QPushButton* quitButton_;
    QPushButton* setTimeRangeButton_;
    TimeRangeDialog* time_range_dialog_;
    ValueTableDialog* value_table_dialog_;
    YearSelectDialog* year_select_dialog_;
    QCheckBox* in_tonnes_check_box_;
    QCheckBox* indexed_check_box_;
    QCheckBox* intensity_check_box_;
    QCheckBox* intensity_indexed_check_box_;
};
#endif // MAINWINDOW_HH
