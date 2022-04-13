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

signals:

private:
    QLabel *title_ = new QLabel;
    QDateEdit *fromDateEdit_ = new QDateEdit;
    QDateEdit *toDateEdit_ = new QDateEdit;
    QString format_ = "dd.MM.yyyy";

};

#endif // TIMERANGEWIDGET_HH
