#ifndef VALUETABLEDIALOG_HH
#define VALUETABLEDIALOG_HH

#include <QDialog>
#include <QWidget>
#include <QLayout>
#include <QTableWidget>

namespace Ui {
class ValueTableDialog;
}

class ValueTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ValueTableDialog(QWidget *parent = nullptr);
    ~ValueTableDialog();

private:

    void setup();

    Ui::ValueTableDialog *ui;
};

#endif // VALUETABLEDIALOG_HH
