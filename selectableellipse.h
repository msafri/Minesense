#ifndef SELECTABLEELLIPSE_H
#define SELECTABLEELLIPSE_H

#include <QGraphicsItem>

class SelectableCircle : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit SelectableCircle(const QColor &color, float x, float y, float radius,
                              int idx, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    float x;
    float y;
    int itemIdx;
    float radius;
    QColor color;
    bool moveItem;
    QVector<QPointF> stuff;

signals:
    void ItemMoved(int, float, int);

};

#endif // SELECTABLEELLIPSE_H
