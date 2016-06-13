#ifndef BUSYGLASSPANE_H
#define BUSYGLASSPANE_H

#include <QWidget>
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT BusyGlassPane : public QWidget
{
    Q_OBJECT
public:
    //explicit BusyGlassPane(QWidget *parent = 0);
    /*public*/ BusyGlassPane(QList<QWidget*> components, QList<QRect> rectangles, QWidget* contentPane, QWidget* parent);
 /*public*/ void dispose();

signals:

public slots:
private:
//    CBListener listener;
    QList<QWidget*> components;
    QList<QRect> rectangles;
    QWidget* contentPane;
    bool inButton;
    QWidget* component;
    void redispatchMouseEvent(QMouseEvent* e);

protected:
    //overload from QWidget
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // BUSYGLASSPANE_H
