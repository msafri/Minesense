#include "selectableellipse.h"

#include <QtWidgets>

SelectableCircle::SelectableCircle(const QColor &color, float x, float y, float radius,
                                   int idx, QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    this->x = x;
    this->y = y;
    this->itemIdx = idx;
    this->color = color;
    this->radius = radius;

    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
}

QRectF SelectableCircle::boundingRect() const
{
    return QRectF(x-5*radius, y-5*radius, 10*radius+80, 10*radius+40);
    //return QRectF(-radius, -radius, 50*radius, 50*radius);
}

QPainterPath SelectableCircle::shape() const
{
    QPainterPath path;
    path.addEllipse(QPointF(x, y), radius, radius);
    return path;
}

void SelectableCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QColor fillColor = color;
    float r = radius;
    if (option->state & QStyle::State_MouseOver)
        r = radius * 3;

    QBrush b = painter->brush();
    painter->setBrush(fillColor);
    painter->drawEllipse(QPointF(x, y), r, r);

    if (this->isSelected()) {
        QFont font("Times", 10);
        font.setBold(true);
        font.setStyleStrategy(QFont::ForceOutline);
        painter->setFont(font);
        painter->save();
        //painter->scale(1, -1);

        painter->drawText(x+10,y+10, QString::number((double)x,'g',2) + ", " + QString::number(y));
        painter->restore();
    }
}

void SelectableCircle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->isSelected()) {
        moveItem = true;
    }

    QGraphicsItem::mousePressEvent(event);
    update();
}

void SelectableCircle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->moveItem) {
        this->y = (int) event->pos().y();
        prepareGeometryChange();
        update();
        emit ItemMoved(itemIdx, x, (int) y);
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void SelectableCircle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    moveItem = false;
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
