#include "graphicsitemword.h"

QRectF GraphicsItemWord::boundingRect() const
{
    return QRectF(0, 0, 100, 50); // Define the item's bounding rectangle
}

void GraphicsItemWord::paint(QPainter *painter,
                             const QStyleOptionGraphicsItem *option,
                             QWidget *widget)
{
    //painter->setBrush(Qt::gray);
    painter->drawRect(boundingRect());

    painter->setPen(Qt::white);
    painter->drawText(boundingRect(), Qt::AlignCenter, data->getCharacters());
}
