#include "timerangewidget.hh"

#include <QGridLayout>

TimeRangeWidget::TimeRangeWidget(QWidget *parent)
    : QWidget{parent}
{
    QGridLayout *layout = new QGridLayout;
    QLabel *fromLabel = new QLabel("From:");
    QLabel *toLabel = new QLabel("To:");

    layout->addWidget(title_, 1, 1, 1, 2);
    layout->addWidget(fromLabel, 2, 1);
    layout->addWidget(toLabel, 3, 1);
    layout->addWidget(fromDateEdit_, 2, 2);
    layout->addWidget(toDateEdit_, 3, 2);

    this->setLayout(layout);
    this->setMaximumHeight(85);

    connect(fromDateEdit_, SIGNAL(dateChanged(QDate)), this, SLOT(resetTimeFrame(QDate)));
    connect(toDateEdit_, SIGNAL(dateChanged(QDate)), this, SLOT(resetTimeFrame(QDate)));
}

void TimeRangeWidget::setFormat(QString format)
{
    fromDateEdit_->setDisplayFormat(format);
    toDateEdit_->setDisplayFormat(format);
    format_ = format;
}

void TimeRangeWidget::setTitle(QString title)
{
    title_->setText(title);
}

std::vector<std::string> TimeRangeWidget::getTimeRange()
{
    std::vector<std::string> timeRange = {};

    std::string fromDate = fromDateEdit_->date().toString(format_).toStdString();
    std::string toDate = toDateEdit_->date().toString(format_).toStdString();

    timeRange.push_back(fromDate);
    timeRange.push_back(toDate);

    return timeRange;
}

void TimeRangeWidget::setTimeRange(std::string start, std::string end, std::string format)
{
    if (format == "smear") {

    } else if (format == "statfi") {
        fromDateEdit_->setDate(QDate(std::stoi(start), 1, 1));
        toDateEdit_->setDate(QDate(std::stoi(end), 1, 1));
    }
    qDebug() << "start " << QString::fromStdString(start);
    qDebug() << "end " << QString::fromStdString(start);

}

void TimeRangeWidget::setMinimum(QString min)
{
    QDate date = date.fromString(min,format_);

    fromDateEdit_->setMinimumDate(date);
    toDateEdit_->setMinimumDate(fromDateEdit_->date());
}

void TimeRangeWidget::setMaximum(QString max)
{
    QDate date = date.fromString(max,format_);

    fromDateEdit_->setMaximumDate(toDateEdit_->date());
    toDateEdit_->setMaximumDate(date);
}

void TimeRangeWidget::resetTimeFrame(QDate date)
{
    fromDateEdit_->setMaximumDate(toDateEdit_->date());
    toDateEdit_->setMinimumDate(fromDateEdit_->date());
}
