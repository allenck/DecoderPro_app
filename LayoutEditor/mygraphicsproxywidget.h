#ifndef MYGRAPHICSPROXYWIDGET_H
#define MYGRAPHICSPROXYWIDGET_H

#include <QGraphicsProxyWidget>

class MyGraphicsProxyWidget : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    explicit MyGraphicsProxyWidget(QGraphicsItem *parent = 0);
 void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
 void mousePressEvent(QGraphicsSceneMouseEvent *event);
 void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
 void keyPressEvent(QKeyEvent *event);
 void keyReleaseEvent(QKeyEvent *event);
signals:

public slots:

};

#endif // MYGRAPHICSPROXYWIDGET_H
