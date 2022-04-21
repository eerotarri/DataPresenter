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

    /**
     * @brief Returns current plot option selected by user.
     * @return pointer to the selected plot option radiobutton
     */
    QRadioButton *getCurrentPlotOption();

signals:
    void quitButtonClicked();
    void preferencesButtonClicked();
    void saveButtonClicked();
    void statisticsButtonClicked();
    void plotOptionChanged();

private slots:
    void emitQuitButtonClicked();
    void emitPreferencesButtonClicked();
    void emitSaveButtonClicked();
    void emitStatisticsButtonClicked();
    void emitPlotOptionChanged(bool checked);

private:
    /**
     * @brief Sets radiobuttons for plot options in group box.
     */
    void createPlotOptionGroupBox();

    QGridLayout *baseLayout_ = new QGridLayout;

    QPushButton *preferencesButton_ = new QPushButton("Preferences");
    QPushButton *saveButton_ = new QPushButton("Save to preferences");

    QPushButton *statisticsButton_ = new QPushButton("Statistics");

    QGroupBox *plotOptionGroupBox_ = new QGroupBox("Choose plot option");
    QRadioButton *lineRadioButton_ = new QRadioButton("line graph");
    QRadioButton *barRadioButton_ = new QRadioButton("bar graph");
    QRadioButton *scatterRadioButton_ = new QRadioButton("scatter graph");

    QPushButton *quitButton_ = new QPushButton("Quit");

    QRadioButton *currentPlotOption_ = nullptr;
};

#endif // RIGHTSIDEBAR_HH
