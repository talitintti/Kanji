#include "graphicsitemword.h"
#include <QApplication>

GraphicsItemWord::GraphicsItemWord(Word *word) : data(word) {
    this->setToolTip(data->getId());
}

QRect GraphicsItemWord::GetRectFitToText(QString text) const {
    QFont current_font = QApplication::font();
    QFontMetrics fm(current_font);
    QRect bounding_rect(fm.boundingRect(text));
    bounding_rect.adjust(-5,-5, 5, 5);

    return bounding_rect;
}

QRectF GraphicsItemWord::boundingRect() const
{
    QString word_text = data->getCharacters();
    auto rect = GetRectFitToText(word_text);

    return rect;
}

void GraphicsItemWord::paint(QPainter *painter,
                             const QStyleOptionGraphicsItem *option,
                             QWidget *widget)
{
    //painter->setBrush(Qt::gray);
    //painter->drawRect(boundingRect());

    painter->setPen(Qt::white);

    QString word_text = data->getCharacters();
    QRect bounding_rect = GetRectFitToText(word_text);

    painter->drawText(bounding_rect, Qt::AlignCenter, word_text);
    painter->drawEllipse(bounding_rect);

}
