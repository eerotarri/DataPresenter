#ifndef LEFTSIDEBAR_HH
#define LEFTSIDEBAR_HH

#include "checkboxgroup.hh"
#include "timerangewidget.hh"

#include <QWidget>
#include <QCheckBox>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>
#include <QScrollArea>

struct selectedOptions {
    std::vector<std::string> gases = {};
    std::vector<std::string> stations = {};
    std::vector<std::string> timeRange = {};
};

struct supportedOptions;

class LeftSidebar : public QWidget
{
    Q_OBJECT
public:
    explicit LeftSidebar(QWidget *parent = nullptr);
    void setSupportedOptions(supportedOptions *options);
    std::vector<std::string> getSelectedDatabase();
    selectedOptions *getSelectedOptions(std::string database);

signals:
    void showButtonClicked();

private slots:
    void smearCheckBoxStateChanged(int state);
    void statfiCheckBoxStateChanged(int state);
    void emitShowButtonClicked();

private:
    void updateSelectedOptions();
    void createGroupBoxes();
    bool isValidOptions();

    selectedOptions *smearOptions = new selectedOptions;
    selectedOptions *statfiOptions = new selectedOptions;

    QGridLayout *baseLayout_ = new QGridLayout;
    QFrame *line_ = new QFrame;

    QWidget *containerWidget_ = new QWidget;
    QVBoxLayout *containerWidgetLayout_ = new QVBoxLayout;

    QScrollArea *scrollArea_ = new QScrollArea;

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
