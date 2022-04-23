#include "cardarea.hh"
#include <QDebug>

CardArea::CardArea(QWidget *parent)
    : QWidget{parent}
{
    this->setLayout(cardAreaLayout_);
}

void CardArea::addCard(ChartCard *newCard)
{
    cardAreaLayout_->addWidget(newCard);
    cards_.push_back(newCard);
}

std::vector<ChartCard *> CardArea::getCards()
{
    return cards_;
}

void CardArea::clearArea()
{
    for ( ChartCard* card_ptr : cards_ ){
        delete card_ptr;
    }

    cards_.clear();
}
