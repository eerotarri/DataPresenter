#include "checkboxgroup.hh"

#include <QVBoxLayout>
#include <QCheckBox>

CheckBoxGroup::CheckBoxGroup( QGroupBox *parent)
    : QGroupBox{parent}
{
}

void CheckBoxGroup::setItems(std::vector<std::string> items)
{
    QVBoxLayout *groupBoxLayout = new QVBoxLayout;
    this->setLayout(groupBoxLayout);
    for( std::string &item : items )
    {
        QString itemName = QString::fromUtf8(item.c_str());

        QCheckBox *itemCheckBox = new QCheckBox;
        itemCheckBox->setText(itemName);

        connect(itemCheckBox, SIGNAL(stateChanged(int)), this, SLOT(checkBoxStateChanged(int)));

        groupBoxLayout->addWidget(itemCheckBox);
    }

    this->setMaximumHeight(35*items.size());
}

std::vector<std::string> CheckBoxGroup::getCheckedItems()
{
    std::vector<std::string> items(checkedBoxes_.begin(), checkedBoxes_.end());
    return items;
}

void CheckBoxGroup::checkBoxStateChanged(int state)
{
    QCheckBox *checkbox = qobject_cast<QCheckBox*>(sender());
    std::string name = checkbox->text().toStdString();

    if ( state == Qt::Checked ){
        checkedBoxes_.insert(name);
    }
    else {
        checkedBoxes_.erase(name);
    }
}
