#ifndef RIGHTSIDEBAR_HH
#define RIGHTSIDEBAR_HH

#include <QWidget>
#include <QGridLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QGroupBox>

class RightSidebar : public QWidget
{
    Q_OBJECT
public:
    explicit RightSidebar(QWidget *parent = nullptr);

    // getSelectedPlotOption();

signals:
    void quitButtonClicked();
    void historyButtonClicked();
    void saveButtonClicked();
    void statisticsButtonClicked();

private slots:
    void emitQuitButtonClicked();
    void emitHistoryButtonClicked();
    void emitSaveButtonClicked();
    void emitStatisticsButtonClicked();

private:
    void createPlotOptionGroupBox();
    void setStatisticsButtonVisible(bool state = true);

    QGridLayout *baseLayout_ = new QGridLayout;

    QPushButton *historyButton_ = new QPushButton("History");
    QPushButton *saveButton_ = new QPushButton("Save");

    QPushButton *statisticsButton_ = new QPushButton("Statistics");

    QGroupBox *plotOptionGroupBox_ = new QGroupBox("Choose plot option");
    QRadioButton *lineRadioButton_ = new QRadioButton("line graph");
    QRadioButton *barRadioButton_ = new QRadioButton("bar graph");
    QRadioButton *scatterRadioButton_ = new QRadioButton("scatter graph");

    QPushButton *quitButton_ = new QPushButton("Quit");
};

#endif // RIGHTSIDEBAR_HH
