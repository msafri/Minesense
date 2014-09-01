#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QWidget>
#include <QVector>
#include <QGraphicsSimpleTextItem>
#include "data.h"
#include "selectableellipse.h"

class View;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QWidget *parent, View *v) : QGraphicsView(parent), view(v) { }

protected:
    void wheelEvent(QWheelEvent *);

private:
    View *view;
};

/* This is the View class of MVC pattern. */

class View : public QObject
{
    Q_OBJECT
public:
    explicit View(QWidget *parent);
    GraphicsView *view() const;
    ~View();

    void SetData(QVector<DataPoint_t> dp);
    void ClearData();
    void UpdateView();

private:
    void CreateAxis();

private:
    QGraphicsScene *scene;
    GraphicsView *graphicsView;
    QVector<float> xAxis;
    QVector<int> yAxis;
    QVector<QGraphicsLineItem*> lines;
    QVector<SelectableCircle*> circs;
    QGraphicsSimpleTextItem* ptCoord;

signals:
    void DataChanged(int,float,int);
};

#endif // VIEW_H
