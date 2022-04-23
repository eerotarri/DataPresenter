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

    /**
     * @brief Set items to the option checkboxes.
     * @param options pointer to the options supported by databases.
     */
    void setSupportedOptions(supportedOptions *options);

    /**
     * @brief Sends databases selected by user.
     * @return vector of selected databases
     */
    std::vector<std::string> getSelectedDatabase();

    /**
     * @brief Sends options selected by user from asked database.
     * @param database which selected options are asked
     * @return pointer to the options selected by user
     */
    selectedOptions *getSelectedOptions(std::string database);

    /**
     * @brief Sets given options in the view.
     * @param smear pointer to the options from smear
     * @param statfi pointer to the options from statfi
     */
    void setValues(selectedOptions* smear, selectedOptions* statfi);

signals:
    void showButtonClicked();

private slots:
    /**
     * @brief Set smear options visible or invisible.
     * @param state of checkbox
     */
    void smearCheckBoxStateChanged(int state);

    /**
     * @brief Set statfi options visible or invisible.
     * @param state of checkbox
     */
    void statfiCheckBoxStateChanged(int state);
    void emitShowButtonClicked();

private:
    /**
     * @brief Set options selected by user to private variables.
     */
    void updateSelectedOptions();

    /**
     * @brief Sets titles for all option groupboxes.
     */
    void createGroupBoxes();

    /**
     * @brief Checks if user has given all needed options.
     * @return true if all options is given, else false
     */
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
