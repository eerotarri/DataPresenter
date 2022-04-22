#include "valuetabledialog.hh"
#include "ui_valuetabledialog.h"

#include <QDebug>

ValueTableDialog::ValueTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ValueTableDialog)
{
    ui->setupUi(this);

    setup();
}

ValueTableDialog::~ValueTableDialog()
{
    delete ui;
}

void ValueTableDialog::resetValues()
{
    for ( std::vector<std::vector<QTableWidgetItem*>> &vVec : items_ ){
        for ( std::vector<QTableWidgetItem*> &sVec : vVec ){
            for ( QTableWidgetItem *item : sVec ){
                item->setText("-");
            }
        }
    }
}

void ValueTableDialog::setValues(QString gas, std::vector<std::vector<double>> values)
{
    int index;

    if ( gas == "NOx" ){
        index = 0;
    }
    else if ( gas == "SO2" ){
        index = 1;
    }
    else {
        index = 2;
    }

    std::vector<std::vector<QTableWidgetItem*>> &gases = items_[index];

    for ( int v = 0; v < 3; ++v ){

        for ( int s = 0; s < 3; ++s ){
            gases[v][s]->setText(QString::number(values[s][v], 'f', 2));
        }
    }
}

void ValueTableDialog::setup()
{
    tableWidget_ = new QTableWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);
    layout->addWidget(tableWidget_);

    QStringList headers_row = { "Min", "Max", "Average"};
    QStringList headers_column = { "NOx Hyytiälä", "NOx Kumpula", "NOx Värriö",
                                    "SO2 Hyytiälä", "SO2 Kumpula", "SO2 Värriö",
                                    "CO2 Hyytiälä", "CO2 Kumpula", "CO2 Värriö"};

    tableWidget_->setRowCount(9);
    tableWidget_->setColumnCount(3);
    tableWidget_->setHorizontalHeaderLabels(headers_row);
    tableWidget_->setVerticalHeaderLabels(headers_column);

    this->setMinimumWidth(450);
    this->setMinimumHeight(350);

    setItems();
    resetValues();

    tableWidget_->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ValueTableDialog::setItems()
{
    std::vector<QTableWidgetItem *> sValues = {};
    std::vector<std::vector<QTableWidgetItem *>> vValues = {};
    std::vector<std::vector<std::vector<QTableWidgetItem *>>> gValues = {};

    int row = 0;
    for ( int g = 0; g < 3; g++ ){

        for ( int v = 0; v < 3; v++ ){

            for ( int s = 0; s < 3; s++){
                QTableWidgetItem* item = new QTableWidgetItem();
                item->setTextAlignment( Qt::AlignCenter);
                tableWidget_->setItem(row, s, item);
                sValues.push_back(item);
            }
            vValues.push_back(sValues);
            sValues.clear();
            ++row;
        }
        gValues.push_back(vValues);
        vValues.clear();
    }
    items_ = gValues;
    gValues.clear();
}
