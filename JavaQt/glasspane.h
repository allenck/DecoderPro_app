#ifndef GLASSPANE_H
#define GLASSPANE_H

#include <QWidget>

class GlassPane : public QWidget
{
 Q_OBJECT
public:
 explicit GlassPane(QWidget *contentPane, QWidget *parent = nullptr);
 /*public*/ void dispose();

signals:

public slots:
private:
 QWidget *contentPane;
 void paintEvent(QPaintEvent* /*event*/);
 void mouseMoveEvent(QMouseEvent *event);
 void mousePressEvent(QMouseEvent * event);
 void mouseReleaseEvent(QMouseEvent * event);

};

#endif // GLASSPANE_H
