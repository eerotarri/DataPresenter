#include "rightsidebar.hh"
#include <QDebug>

RightSidebar::RightSidebar(QWidget *parent)
    : QWidget{parent}
{
    createPlotOptionGroupBox();

    baseLayout_->addWidget(preferencesButton_);
    baseLayout_->addWidget(saveButton_);
    baseLayout_->addWidget(statisticsButton_);
    baseLayout_->addWidget(plotOptionGroupBox_);
    baseLayout_->addWidget(quitButton_,5,0,Qt::AlignBottom);

    this->setLayout(baseLayout_);

    lineRadioButton_->setChecked(true);
    currentPlotOption_ = lineRadioButton_;

    connect(preferencesButton_, SIGNAL(clicked()), this, SLOT(emitPreferencesButtonClicked()));
    connect(saveButton_, SIGNAL(clicked()), this, SLOT(emitSaveButtonClicked()));
    connect(statisticsButton_, SIGNAL(clicked()), this, SLOT(emitStatisticsButtonClicked()));
    connect(quitButton_, SIGNAL(clicked()), this, SLOT(emitQuitButtonClicked()));
    connect(lineRadioButton_, SIGNAL(toggled(bool)), this, SLOT(emitPlotOptionChanged(bool)));
    connect(barRadioButton_, SIGNAL(toggled(bool)), this, SLOT(emitPlotOptionChanged(bool)));
    connect(scatterRadioButton_, SIGNAL(toggled(bool)), this, SLOT(emitPlotOptionChanged(bool)));


}

QRadioButton *RightSidebar::getCurrentPlotOption()
{
    return currentPlotOption_;
}

void RightSidebar::emitQuitButtonClicked()
{
    emit quitButtonClicked();
}

void RightSidebar::emitPreferencesButtonClicked()
{
    emit preferencesButtonClicked();
}

void RightSidebar::emitSaveButtonClicked()
{
    emit saveButtonClicked();
}

void RightSidebar::emitStatisticsButtonClicked()
{
    emit statisticsButtonClicked();
}

void RightSidebar::emitPlotOptionChanged(bool checked)
{
    if ( checked ){
        if ( qobject_cast<QRadioButton*>(sender()) == lineRadioButton_ ){
            currentPlotOption_ = lineRadioButton_;
        }
        else if ( qobject_cast<QRadioButton*>(sender()) == barRadioButton_ ){
            currentPlotOption_ = barRadioButton_;
        }
        else if ( qobject_cast<QRadioButton*>(sender()) == scatterRadioButton_ ){
            currentPlotOption_ = scatterRadioButton_;
        }
        else {
            currentPlotOption_ = nullptr;
        }

        emit plotOptionChanged();
    }
}

void RightSidebar::createPlotOptionGroupBox()
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addStretch(1);

    layout->addWidget(lineRadioButton_);
    layout->addWidget(barRadioButton_);
    layout->addWidget(scatterRadioButton_);

    plotOptionGroupBox_->setMaximumHeight(100);
    plotOptionGroupBox_->setLayout(layout);
}

