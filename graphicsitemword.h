#ifndef GRAPHICSITEMWORD_H
#define GRAPHICSITEMWORD_H

#include <QPainter>
#include <qgraphicsitem.h>
#include <word.h>

class GraphicsItemWord : public QGraphicsItem
{
public:
    GraphicsItemWord(Word *);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    Word *data; // Pointer to the data object
    QRect GetRectFitToText(QString text) const;
};

#endif // GRAPHICSITEMWORD_H
