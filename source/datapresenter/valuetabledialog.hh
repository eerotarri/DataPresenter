#ifndef VALUETABLEDIALOG_HH
#define VALUETABLEDIALOG_HH

#include <QDialog>
#include <QWidget>

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

    void setUp();

    Ui::ValueTableDialog *ui;
};

#endif // VALUETABLEDIALOG_HH
