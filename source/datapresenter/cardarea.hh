#ifndef CARDAREA_HH
#define CARDAREA_HH

#include "chartcard.hh"

#include <QWidget>
#include <QGridLayout>

class CardArea : public QWidget
{
    Q_OBJECT
public:
    explicit CardArea(QWidget *parent = nullptr);

    /**
     * @brief Adds new CartCard to the area.
     * @param newCard pointer to the card which must be added in view
     */
    void addCard(ChartCard *newCard);

    /**
     * @brief Sends all card dispalyed in the view.
     * @return vector of pointers to the dispalayed cards
     */
    std::vector<ChartCard*> getCards();

    /**
     * @brief Deletes all cards dispalyed in the view.
     */
    void clearArea();

signals:

private:
    QGridLayout *cardAreaLayout_ = new QGridLayout();
    std::vector<ChartCard*> cards_ = {};

};

#endif // CARDAREA_HH
