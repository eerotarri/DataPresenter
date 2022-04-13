#ifndef CHECKBOXGROUP_HH
#define CHECKBOXGROUP_HH

#include <set>
#include <QGroupBox>

class CheckBoxGroup : public QGroupBox
{
    Q_OBJECT
public:
    explicit CheckBoxGroup(QGroupBox *parent = nullptr);
    void setItems(std::vector<std::string> items);
    std::vector<std::string> getCheckedItems();

signals:

private slots:
    void checkBoxStateChanged(int state);

private:
    std::set<std::string> checkedBoxes_ = {};

};

#endif // CHECKBOXGROUP_HH
