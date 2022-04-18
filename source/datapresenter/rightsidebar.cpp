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

    //Värit
    /*
    preferencesButton_->setStyleSheet("background-color: #4C0390");
    saveButton_->setStyleSheet("background-color: #4C0390");
    statisticsButton_->setStyleSheet("background-color: #4C0390");
    quitButton_->setStyleSheet("background-color: #4C0390");
    plotOptionGroupBox_->setStyleSheet("background-color: #b0c4de");
*/

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
            qDebug() << "Plot line.";
        }
        else if ( qobject_cast<QRadioButton*>(sender()) == barRadioButton_ ){
            currentPlotOption_ = barRadioButton_;
            qDebug() << "Plot bar.";
        }
        else if ( qobject_cast<QRadioButton*>(sender()) == scatterRadioButton_ ){
            currentPlotOption_ = scatterRadioButton_;
            qDebug() << "Plot scatter.";
        }
        else {
            currentPlotOption_ = nullptr;
            qDebug() << "None plot option.";
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

void RightSidebar::setStatisticsButtonVisible(bool state)
{
    statisticsButton_->setVisible(state);
}
