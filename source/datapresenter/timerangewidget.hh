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

    /**
     * @brief Sets dateEdits'/date selectors' formats
     * @param format tells which format want displayed
     */
    void setFormat(QString format);

    /**
     * @brief Sets title over the date selectors
     * @param title
     */
    void setTitle(QString title);

    /**
     * @brief Makes time frame from selected times
     * @return time frame
     */
    std::vector<std::string> getTimeRange();
    void setTimeRange(std::string start, std::string end, std::string format);

    /**
     * @brief Sets the smallest possible date
     * @param min
     */
    void setMinimum(QString min);

    /**
     * @brief Sets the biggest possible date
     * @param max
     */
    void setMaximum(QString max);

    /**
     * @brief Sets max time range lenght
     * @param lenght
     */
    void setMaxTimeRangeLenght(int lenght);

private slots:

    /**
     * @brief Edits the minimum and maximum dates
     * @param date
     */
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
