#ifndef TIMERANGEDIALOG_HH
#define TIMERANGEDIALOG_HH

#include <QDialog>
#include <QCalendarWidget>
#include <QWidget>

namespace Ui {
class TimeRangeDialog;
}

class TimeRangeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TimeRangeDialog(QWidget *parent = nullptr);
    ~TimeRangeDialog();

private:

    void setUp();

    Ui::TimeRangeDialog *ui;
    //QCalendarWidget* start_day_calendar_;
    //QCalendarWidget* end_day_calendar_;
};

#endif // TIMERANGEDIALOG_HH
