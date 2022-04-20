#include "leftsidebar.hh"
#include "model.hh"

#include <QDebug>

LeftSidebar::LeftSidebar(QWidget *parent)
    : QWidget{parent}
{
    this->setMinimumWidth(170);

    line_->setFrameShape(QFrame::HLine);
    line_->setFrameShadow(QFrame::Sunken);

    containerWidgetLayout_->addWidget(smearCheckBox_);
    containerWidgetLayout_->addWidget(smearGasGroupBox_);
    containerWidgetLayout_->addWidget(smearStationGroupBox_);
    containerWidgetLayout_->addWidget(smearTimeRangeWidget_);
    containerWidgetLayout_->addWidget(line_);
    containerWidgetLayout_->addWidget(statfiCheckBox_);
    containerWidgetLayout_->addWidget(statfiGasGroupBox_);
    containerWidgetLayout_->addWidget(statfiTimeRangeWidget_);
    containerWidgetLayout_->addWidget(new QWidget, 0, Qt::AlignBottom);

    containerWidget_->setLayout(containerWidgetLayout_);
    scrollArea_->setWidget(containerWidget_);
    scrollArea_->setWidgetResizable(true);
    //scrollArea_->setFixedWidth(200);
    scrollArea_->setMinimumWidth(240);

    baseLayout_->addWidget(scrollArea_);
    baseLayout_->addWidget(showButton_,1,0,Qt::AlignBottom);

    smearTimeRangeWidget_->setTitle("Select time range");
    smearTimeRangeWidget_->setFormat("yyyy-MM-dd");
    /*
    smearTimeRangeWidget_->setMinimum("---");
    smearTimeRangeWidget_->setMaximum("---");
    */
    smearTimeRangeWidget_->setMaxTimeRangeLenght(14);

    statfiTimeRangeWidget_->setTitle("Select time range");
    statfiTimeRangeWidget_->setFormat("yyyy");
    statfiTimeRangeWidget_->setMaximum("2017");
    statfiTimeRangeWidget_->setMinimum("1975");

    this->setLayout(baseLayout_);

    createGroupBoxes();

    smearGasGroupBox_->setVisible(false);
    smearStationGroupBox_->setVisible(false);
    smearTimeRangeWidget_->setVisible(false);

    statfiGasGroupBox_->setVisible(false);
    statfiTimeRangeWidget_->setVisible(false);

    connect(smearCheckBox_,SIGNAL(stateChanged(int)), this, SLOT(smearCheckBoxStateChanged(int)));
    connect(statfiCheckBox_,SIGNAL(stateChanged(int)), this, SLOT(statfiCheckBoxStateChanged(int)));
    connect(showButton_, SIGNAL(clicked()), this, SLOT(emitShowButtonClicked()));
}

void LeftSidebar::setSupportedOptions(supportedOptions *options)
{
    smearStationGroupBox_->setItems(options->smearStations);
    smearGasGroupBox_->setItems(options->smearGases);
    statfiGasGroupBox_->setItems(options->statfiGases);
}

std::vector<std::string> LeftSidebar::getSelectedDatabase()
{
    if ( smearCheckBox_->isChecked() && statfiCheckBox_->isChecked() ){
        return {"smear", "statfi"};
    }
    else if ( smearCheckBox_->isChecked() ){
        return {"smear"};
    }
    else if ( statfiCheckBox_->isChecked() ){
        return {"statfi"};
    }
    return {};
}

selectedOptions *LeftSidebar::getSelectedOptions(std::string database)
{
    if ( database == "smear" ){
        return smearOptions;
    }
    else if ( database == "statfi" ){
        return statfiOptions;
    }
    return nullptr;
}

void LeftSidebar::setValues(selectedOptions *smear, selectedOptions *statfi)
{
    if (smear == nullptr) {
        smearCheckBox_->setChecked(false);
        smearCheckBoxStateChanged(Qt::Unchecked);
    } else {
        statfiTimeRangeWidget_->setTimeRange(smear->timeRange[0], smear->timeRange[0], "smear");
        smearCheckBox_->setChecked(true);
        smearCheckBoxStateChanged(Qt::Checked);
        // aseta kaikki smear valinnat.
        for (QObject *const child : smearGasGroupBox_->children()) {
            if (child->isWidgetType()) {
                auto obj = qobject_cast<QCheckBox*>(child);
                if (std::find(smear->gases.begin(), smear->gases.end(), obj->text().toStdString()) != smear->gases.end()) {
                    obj->setChecked(true);
                } else {
                    obj->setChecked(false);
                }
            }
        }
        for (QObject *const child : smearStationGroupBox_->children()) {
            if (child->isWidgetType()) {
                auto obj = qobject_cast<QCheckBox*>(child);
                if (std::find(smear->gases.begin(), smear->gases.end(), obj->text().toStdString()) != smear->gases.end()) {
                    obj->setChecked(true);
                } else {
                    obj->setChecked(false);
                }
            }
        }
    }

    if (statfi == nullptr) {
        statfiCheckBox_->setChecked(false);
        statfiCheckBoxStateChanged(Qt::Unchecked);
    } else {
        statfiTimeRangeWidget_->setTimeRange(statfi->timeRange[0], statfi->timeRange[0], "statfi");
        statfiCheckBox_->setChecked(true);
        statfiCheckBoxStateChanged(Qt::Checked);
        // aseta kaikki statfi valinnat.


        for (QObject *const child : statfiGasGroupBox_->children()) {
            if (child->isWidgetType()) {
                auto obj = qobject_cast<QCheckBox*>(child);
                if (std::find(statfi->gases.begin(), statfi->gases.end(), obj->text().toStdString()) != statfi->gases.end()) {
                    obj->setChecked(true);
                } else {
                    obj->setChecked(false);
                }
            }
        }
    }
}

void LeftSidebar::smearCheckBoxStateChanged(int state)
{
    if ( state == Qt::Checked ){
        smearGasGroupBox_->setVisible(true);
        smearStationGroupBox_->setVisible(true);
        smearTimeRangeWidget_->setVisible(true);
    }
    else {
        smearGasGroupBox_->setVisible(false);
        smearStationGroupBox_->setVisible(false);
        smearTimeRangeWidget_->setVisible(false);
    }
}

void LeftSidebar::statfiCheckBoxStateChanged(int state)
{
    if ( state == Qt::Checked ){
        statfiGasGroupBox_->setVisible(true);
        statfiTimeRangeWidget_->setVisible(true);
    }
    else {
        statfiGasGroupBox_->setVisible(false);
        statfiTimeRangeWidget_->setVisible(false);
    }
}

void LeftSidebar::emitShowButtonClicked()
{
    updateSelectedOptions();
    if ( isValidOptions() ){
        emit showButtonClicked();
    }
}

void LeftSidebar::updateSelectedOptions()
{
    smearOptions->gases = smearGasGroupBox_->getCheckedItems();
    smearOptions->stations = smearStationGroupBox_->getCheckedItems();
    smearOptions->timeRange = smearTimeRangeWidget_->getTimeRange();

    statfiOptions->gases = statfiGasGroupBox_->getCheckedItems();
    statfiOptions->stations = {};
    statfiOptions->timeRange = statfiTimeRangeWidget_->getTimeRange();
}

void LeftSidebar::createGroupBoxes()
{
    //smearStationGroupBox_->setItems(stations);
    smearStationGroupBox_->setTitle("Stations from SMEAR");
    //smearGasGroupBox_->setItems(smearGases);
    smearGasGroupBox_->setTitle("Gases from SMEAR");
    //statfiGasGroupBox_->setItems(statfiGases);
    statfiGasGroupBox_->setTitle("Gases from STATFI");
}

bool LeftSidebar::isValidOptions()
{
    bool allIsValid = true;
    if ( smearCheckBox_->isChecked() ){
        if ( smearOptions->gases.empty() ){
            smearGasGroupBox_->setStyleSheet("color: deeppink");
            allIsValid = false;
        }
        else {
            smearGasGroupBox_->setStyleSheet("color: #2F285A");
        }
        if ( smearOptions->stations.empty() ){
            smearStationGroupBox_->setStyleSheet("color: deeppink");
            allIsValid = false;
        }
        else {
            smearStationGroupBox_->setStyleSheet("color: #2F285A");
        }
    }

    if ( statfiCheckBox_->isChecked() ){
        if ( statfiOptions->gases.empty() ){
            statfiGasGroupBox_->setStyleSheet("color: deeppink");
            allIsValid = false;
        }
        else {
            statfiGasGroupBox_->setStyleSheet("color: #2F285A");
        }
    }
    if ( allIsValid ){
        return true;
    }
    return false;
}
