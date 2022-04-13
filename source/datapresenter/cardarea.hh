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
    void addCard(ChartCard *newCard);
    void clearArea();

signals:

private:
    QGridLayout *cardAreaLayout_ = new QGridLayout();
    std::vector<ChartCard*> cards_ = {};

};

#endif // CARDAREA_HH
