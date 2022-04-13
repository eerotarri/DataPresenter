#include "leftsidebar.hh"

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

    containerWidget_->setLayout(containerWidgetLayout_);
    scrollArea_->setWidget(containerWidget_);
    scrollArea_->setWidgetResizable(true);

    baseLayout_->addWidget(scrollArea_);
    baseLayout_->addWidget(showButton_,1,0,Qt::AlignBottom);

    smearTimeRangeWidget_->setTitle("Select time range");
    statfiTimeRangeWidget_->setTitle("Select time range");
    statfiTimeRangeWidget_->setFormat("yyyy");

    statfiTimeRangeWidget_->setMinimum("1975");
    statfiTimeRangeWidget_->setMaximum("2017");

    /*
    smearTimeRangeWidget_->setMinimum("---");
    smearTimeRangeWidget_->setMaximum("---");
    */

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
    statfiOptions->gases = statfiGasGroupBox_->getCheckedItems();
    statfiOptions->stations = {};
}

void LeftSidebar::createGroupBoxes()
{
    // Hakee tiedot
    std::vector<std::string> stations = {"Värriö","Kumpula","Hyytiälä"};
    std::vector<std::string> smearGases = {"CO2","NOx","SO2"};
    std::vector<std::string> statfiGases = {"CO2","CO3","CO4"};

    smearStationGroupBox_->setItems(stations);
    smearStationGroupBox_->setTitle("Stations from SMEAR");
    smearGasGroupBox_->setItems(smearGases);
    smearGasGroupBox_->setTitle("Gases from SMEAR");
    statfiGasGroupBox_->setItems(statfiGases);
    statfiGasGroupBox_->setTitle("Gases from STATFI");
}

bool LeftSidebar::isValidOptions()
{
    bool allIsValid = true;
    if ( smearCheckBox_->isChecked() ){
        if ( smearOptions->gases.empty() ){
            smearGasGroupBox_->setStyleSheet("color: red");
            allIsValid = false;
        }
        else {
            smearGasGroupBox_->setStyleSheet("color: black");
        }
        if ( smearOptions->stations.empty() ){
            smearStationGroupBox_->setStyleSheet("color: red");
            allIsValid = false;
        }
        else {
            smearStationGroupBox_->setStyleSheet("color: black");
        }
    }

    if ( statfiCheckBox_->isChecked() ){
        if ( statfiOptions->gases.empty() ){
            statfiGasGroupBox_->setStyleSheet("color: red");
            allIsValid = false;
        }
        else {
            statfiGasGroupBox_->setStyleSheet("color: black");
        }
    }
    if ( allIsValid ){
        return true;
    }
    return false;
}
