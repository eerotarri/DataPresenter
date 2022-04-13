#include "leftsidebar.hh"

#include <QDebug>

LeftSidebar::LeftSidebar(QWidget *parent)
    : QWidget{parent}
{
    line_->setFrameShape(QFrame::HLine);
    line_->setFrameShadow(QFrame::Sunken);

    baseLayout_->addWidget(smearCheckBox_);
    baseLayout_->addWidget(smearGasGroupBox_);
    baseLayout_->addWidget(smearStationGroupBox_);
    baseLayout_->addWidget(smearTimeRangeWidget_);
    baseLayout_->addWidget(line_);
    baseLayout_->addWidget(statfiCheckBox_);
    baseLayout_->addWidget(statfiGasGroupBox_);
    baseLayout_->addWidget(statfiTimeRangeWidget_);
    baseLayout_->addWidget(showButton_,9,0,Qt::AlignBottom);

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
    connect(showButton_, SIGNAL(clicked()), this, SLOT(showButtonClicked()));
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
    if ( database == "SMEAR" ){
        return smearOptions;
    }
    return statfiOptions;
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

void LeftSidebar::showButtonClicked()
{
    updateSelectedOptions();
    if ( isValidOptions() ){
        // emit signal to view
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
