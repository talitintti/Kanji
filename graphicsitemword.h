#ifndef GRAPHICSITEMWORD_H
#define GRAPHICSITEMWORD_H

#include <qgraphicsitem.h>
#include <word.h>
#include <QPainter>

class GraphicsItemWord : public QGraphicsItem {
public:
    GraphicsItemWord(Word* data) : data(data) {}

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
private:
    Word* data; // Pointer to the data object
};

#endif // GRAPHICSITEMWORD_H
