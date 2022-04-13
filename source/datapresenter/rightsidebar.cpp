#include "rightsidebar.hh"

RightSidebar::RightSidebar(QWidget *parent)
    : QWidget{parent}
{
    createPlotOptionGroupBox();

    baseLayout_->addWidget(historyButton_);
    baseLayout_->addWidget(saveButton_);
    baseLayout_->addWidget(statisticsButton_);
    baseLayout_->addWidget(plotOptionGroupBox_);
    baseLayout_->addWidget(quitButton_,5,0,Qt::AlignBottom);

    this->setLayout(baseLayout_);

    connect(quitButton_, SIGNAL(clicked()), this, SLOT(emitQuitButtonClicked()));
}

void RightSidebar::emitQuitButtonClicked()
{
    emit quitButtonClicked();
}

void RightSidebar::emitHistoryButtonClicked()
{
    emit historyButtonClicked();
}

void RightSidebar::emitSaveButtonClicked()
{
    emit saveButtonClicked();
}

void RightSidebar::emitStatisticsButtonClicked()
{
    emit statisticsButtonClicked();
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

void RightSidebar::setStatisticsButtonVisible(bool state)
{
    statisticsButton_->setVisible(state);
}
