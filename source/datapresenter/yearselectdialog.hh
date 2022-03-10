#ifndef YEARSELECTDIALOG_HH
#define YEARSELECTDIALOG_HH

#include <QDialog>

namespace Ui {
class YearSelectDialog;
}

class YearSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit YearSelectDialog(QWidget *parent = nullptr);
    ~YearSelectDialog();

private slots:
    void on_selectButton_clicked();

private:
    Ui::YearSelectDialog *ui;
    bool is_valid_inputs(int& start_year, int& end_year);
};

#endif // YEARSELECTDIALOG_HH
