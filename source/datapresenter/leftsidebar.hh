#ifndef LEFTSIDEBAR_HH
#define LEFTSIDEBAR_HH

#include "checkboxgroup.hh"
#include "timerangewidget.hh"

#include <QWidget>
#include <QCheckBox>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>

struct selectedOptions {
    std::vector<std::string> gases;
    std::vector<std::string> stations;
    std::vector<std::string> timeRange;
};

class LeftSidebar : public QWidget
{
    Q_OBJECT
public:
    explicit LeftSidebar(QWidget *parent = nullptr);
    std::vector<std::string> getSelectedDatabase();
    selectedOptions *getSelectedOptions(std::string database);

signals:

private slots:
    void smearCheckBoxStateChanged(int state);
    void statfiCheckBoxStateChanged(int state);
    void showButtonClicked();

private:
    void updateSelectedOptions();
    void createGroupBoxes();
    bool isValidOptions();

    selectedOptions *smearOptions = new selectedOptions;
    selectedOptions *statfiOptions = new selectedOptions;

    QGridLayout *baseLayout_ = new QGridLayout;
    QFrame *line_ = new QFrame;

    QCheckBox *smearCheckBox_ = new QCheckBox("SMEAR");
    QCheckBox *statfiCheckBox_ = new QCheckBox("STATFI");

    CheckBoxGroup *smearGasGroupBox_ = new CheckBoxGroup;
    CheckBoxGroup *statfiGasGroupBox_ = new CheckBoxGroup;

    CheckBoxGroup *smearStationGroupBox_ = new CheckBoxGroup;

    TimeRangeWidget *smearTimeRangeWidget_ = new TimeRangeWidget;
    TimeRangeWidget *statfiTimeRangeWidget_ = new TimeRangeWidget;

    QPushButton *showButton_ = new QPushButton("Show");

};

#endif // LEFTSIDEBAR_HH
