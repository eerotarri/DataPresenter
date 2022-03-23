#include "valuetabledialog.hh"
#include "ui_valuetabledialog.h"

ValueTableDialog::ValueTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ValueTableDialog)
{
    ui->setupUi(this);

    setUp();
}

ValueTableDialog::~ValueTableDialog()
{
    delete ui;
}

void ValueTableDialog::setUp()
{
    QTableWidget *tableWidget = new QTableWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);
    layout->addWidget(tableWidget);

    QStringList headers_row = { "Min", "Max", "Average"};
    QStringList headers_column = { "Hyytiälä", "Kumpula", "Värriö"};

    tableWidget->setRowCount(3);
    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels(headers_row);
    tableWidget->setVerticalHeaderLabels(headers_column);

    // Tällee saadaan arvoja ruutuihin
    QTableWidgetItem* item = new QTableWidgetItem();
    tableWidget->setItem(1, 1, item);
    item->setText("moi");

    // sulkee muokkausoikeudet
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
