#include "view.h"
#include <QWheelEvent>
#include <QTransform>

void GraphicsView::wheelEvent(QWheelEvent *e)
{
    double scaleFactor = 1.15;

    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    if (e->delta() > 0) {
        this->scale(scaleFactor, scaleFactor);
    }
    else
        this->scale(1/scaleFactor, 1/scaleFactor);
    e->accept();
}


View::View(QWidget *parent) :
    scene(NULL),
    graphicsView(NULL)
{
    graphicsView = new GraphicsView(parent, this);
    graphicsView->scale(1, -1);

    scene = new QGraphicsScene();
    graphicsView->setScene(scene);

    this->CreateAxis();
}

void View::CreateAxis()
{
    scene->setBackgroundBrush(Qt::lightGray);

    QPen pen;  // creates a default pen

    pen.setWidth(3);
    pen.setBrush(Qt::black);
    scene->addLine(-120, 0, 3200, 0, pen);
    scene->addLine(0, -80, 0, 1100, pen);

    ptCoord = new QGraphicsSimpleTextItem();
    ptCoord->setText("0, 0");
    ptCoord->setFont(QFont("Times", 10));
    ptCoord->setPos(20,20);
    ptCoord->setVisible(false);
    QTransform transform;
    transform.scale(1,-1);
    ptCoord->setTransform(transform);
    scene->addItem(ptCoord);

    // Axis ticks
    QFont font("Times", 10);
    QGraphicsSimpleTextItem *txtItem;
    QPen axLPen;
    axLPen.setStyle(Qt::DotLine);

    // X Axis
    for (int idx = -100; idx < 3200; idx+=100) {
        scene->addLine(idx, -5, idx, 5, pen);
        scene->addLine(idx, -80, idx, 1100, axLPen);

        txtItem = scene->addSimpleText(QString::number(idx),font);
        txtItem->setPos(idx-15,-20);
        QTransform tr = txtItem->transform();
        tr.scale(1,-1);
        txtItem->setTransform(tr);
    }
    // Y Axis
    for (int idx = -50; idx < 1100; idx+=50) {
        scene->addLine(-5, idx, 5, idx, pen);
        scene->addLine(-120, idx, 3200, idx, axLPen);

        txtItem = scene->addSimpleText(QString::number(idx),font);
        txtItem->setPos(-45,idx+10);
        QTransform tr = txtItem->transform();
        tr.scale(1,-1);
        txtItem->setTransform(tr);
    }
}

View::~View()
{
    if (scene)
        delete scene;

    if (graphicsView)
        delete graphicsView;
}

GraphicsView *View::view() const
{
    return graphicsView;
}

void View::SetData(QVector<DataPoint_t> dps)
{
    ClearData();

    for (int idx = 0; idx < dps.size(); idx++)
    {
        xAxis.append(dps[idx].energy);
        yAxis.append(dps[idx].count);
    }
}

void View::ClearData() {
    xAxis.clear();
    yAxis.clear();
    lines.clear();
    circs.clear();
    delete scene;

    scene = new QGraphicsScene();
    graphicsView->setScene(scene);

    this->CreateAxis();
}

void View::UpdateView()
{
    QPen penLine;
    penLine.setBrush(QBrush(Qt::blue));
    penLine.setColor(Qt::blue);
    penLine.setWidth(2);

    for (int idx = 0; idx < xAxis.size(); idx++)
    {
        float x1 = xAxis[idx]*100;
        float y1 = yAxis[idx];

        if (idx < xAxis.length()-1) {
            float x2 = xAxis[idx+1]*100;
            float y2 = yAxis[idx+1];
            lines.append(scene->addLine(x1,y1,x2,y2,penLine));
        }

        SelectableCircle *scirc = new SelectableCircle(Qt::red, x1, y1, 2, idx);
        scene->addItem(scirc);
        circs.append(scirc);

        scirc->setSelected(false);
        connect(scirc, &SelectableCircle::ItemMoved, [=](int itemIdx, float x, int y) {
            yAxis[itemIdx] = y;
            emit DataChanged(itemIdx, xAxis[itemIdx], y);

            // change the lines at point x
            for (QGraphicsLineItem *line:lines) {
                QLineF lpos = line->line();
                if (lpos.x1() == x) {
                    lpos.setP1(QPointF(x, y));
                }
                else if (lpos.x2() == x) {
                    lpos.setP2(QPointF(x, y));
                }

                line->setLine(lpos);
            }
        });
    }
}
