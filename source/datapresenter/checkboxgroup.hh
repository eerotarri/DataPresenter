#ifndef CHECKBOXGROUP_HH
#define CHECKBOXGROUP_HH

#include <set>
#include <QGroupBox>

class CheckBoxGroup : public QGroupBox
{
    Q_OBJECT
public:
    explicit CheckBoxGroup(QGroupBox *parent = nullptr);

    /**
     * @brief Set items in the checkbox group
     * @param items vector contains items, what we want in the same checkbox group
     */
    void setItems(std::vector<std::string> items);

    /**
     * @brief Makes items vector from checked checboxes
     * @return items
     */
    std::vector<std::string> getCheckedItems();

signals:

private slots:

    /**
     * @brief Adds checked or delete unchecked checkbox item in checkedBoxes_
     * @param state tells is it checked or unchecked
     */
    void checkBoxStateChanged(int state);

private:
    std::set<std::string> checkedBoxes_ = {};

};

#endif // CHECKBOXGROUP_HH
