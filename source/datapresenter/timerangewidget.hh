#ifndef TIMERANGEWIDGET_HH
#define TIMERANGEWIDGET_HH

#include <QWidget>
#include <QLabel>
#include <QDateEdit>

class TimeRangeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TimeRangeWidget(QWidget *parent = nullptr);
    void setFormat(QString format);
    void setTitle(QString title);
    std::vector<std::string> getTimeRange();
    void setMinimum(QString min);
    void setMaximum(QString max);
    void setMaxTimeRangeLenght(int lenght);

private slots:
    void resetTimeFrame(QDate date);

private:
    bool isValidTimeRange();

    QLabel *title_ = new QLabel;
    QDateEdit *fromDateEdit_ = new QDateEdit;
    QDateEdit *toDateEdit_ = new QDateEdit;
    QString format_ = "dd.MM.yyyy";
    QDateTime maxDate_;
    QDateTime minDate_;
    int timeRangeLenght_ = 0;
};

#endif // TIMERANGEWIDGET_HH
