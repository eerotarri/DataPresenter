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
    QStringList headers_row = { "Min", "Max", "Average"};
    QStringList headers_column = { "Hyytiälä", "Kumpula", "Värriö"};

    ui->valueTable->setRowCount(3);
    ui->valueTable->setColumnCount(3);
    ui->valueTable->setHorizontalHeaderLabels(headers_row);
    ui->valueTable->setVerticalHeaderLabels(headers_column);

    // Tällee saadaan arvoja ruutuihin
    QTableWidgetItem* item = new QTableWidgetItem();
    ui->valueTable->setItem(1, 1, item);
    item->setText("moi");

    // sulkee muokkausoikeudet
    ui->valueTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
