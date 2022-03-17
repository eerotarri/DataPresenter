#include "yearselectdialog.hh"
#include "ui_yearselectdialog.h"

YearSelectDialog::YearSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YearSelectDialog)
{
    ui->setupUi(this);
}

YearSelectDialog::~YearSelectDialog()
{
    delete ui;
}

void YearSelectDialog::on_selectButton_clicked()
{
    // toPlainText() antaa tekstin textEditistä
    //if( is_valid_inputs() ){
        // lähettää arvot eteenpäin
  //  }
}

bool YearSelectDialog::is_valid_inputs(int &start_year, int &end_year)
{

}
