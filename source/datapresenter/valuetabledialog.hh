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

    /**
     * @brief Add given values for given gas to the valueTableItems.
     * @param gas which had given values
     * @param values must be added in table
     */
    void setValues(QString gas, std::vector<std::vector<double>> values);

    /**
     * @brief Sets all values in valueTable to be -
     */
    void resetValues();

private:

    /**
     * @brief Adds needed rows and columns to the valueTable.
     */
    void setup();

    /**
     * @brief Sets ValueTableItems to each row and column in valueTable.
     */
    void setItems();

    Ui::ValueTableDialog *ui;
    QTableWidget *tableWidget_ = nullptr;
    std::vector<std::vector<std::vector<QTableWidgetItem *>>> items_;
};

#endif // VALUETABLEDIALOG_HH
