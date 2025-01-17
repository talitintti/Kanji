#include "graphicsitemword.h"
#include <QApplication>

GraphicsItemWord::GraphicsItemWord(Word *word) : data(word) {
    this->setToolTip(data->getEnglishEquivalent());
}

QRectF GraphicsItemWord::boundingRect() const
{
    return QRectF(0, 0, 100, 50); // Define the item's bounding rectangle
}

void GraphicsItemWord::paint(QPainter *painter,
                             const QStyleOptionGraphicsItem *option,
                             QWidget *widget)
{
    //painter->setBrush(Qt::gray);
    //painter->drawRect(boundingRect());

    painter->setPen(Qt::white);

    QString word_text = data->getCharacters();
    QFont current_font = QApplication::font();
    QFontMetrics fm(current_font);
    QRect bounding_rect(fm.boundingRect(word_text));
    bounding_rect.adjust(-5,-5, 5, 5);

    painter->drawText(bounding_rect, Qt::AlignCenter, word_text);
    painter->drawEllipse(bounding_rect);

}
