#ifndef DIAGRAMCOMPONENT_H
#define DIAGRAMCOMPONENT_H
#include "jcomponent.h"
#include "qwidget.h"

class Insets;
class ColorPanel;
class BufferedImage;
class DiagramComponent : public QWidget, public JComponent
{
 Q_OBJECT
 Q_INTERFACES(JComponent)
public:
 DiagramComponent(ColorPanel* panel, bool diagram);
 /*public*/ void mousePressEvent(QMouseEvent* event);
 /*public*/ void mouseReleaseEvent(QMouseEvent* event);
 /*public*/ void mouseClicked(QMouseEvent* event);
 /*public*/ void mouseEntered(QMouseEvent* event);
 /*public*/ void mouseExited(QMouseEvent* event);
 /*public*/ void mouseMoveEvent(QMouseEvent* event);
 /*public*/ void mouseDragged(QMouseEvent* event);

 /*public*/ bool  isOpaque();
 /*public*/ QColor getBackground();
 /*public*/ void setBackground(QColor c);
 /*public*/ QFont getFont();
 /*public*/ void setOpaque(bool b);
 /*public*/ void setFont(QFont f);
 QObject* jself(){return (QObject*)this;}

private:
 /*private*/ /*final*/ ColorPanel* panel;
 /*private*/ /*final*/ bool diagram;

 /*private*/ /*final*/ Insets* insets;// = new Insets(0, 0, 0, 0);

 /*private*/ int width;
 /*private*/ int height;

 /*private*/ QVector<int> array;
 /*private*/ BufferedImage* image;
 /*private*/ static int getValue(float value, int min, int max);
 /*private*/ static float getValue(int value, int min, int max);
 /*public*/ void paintEvent(QPaintEvent *event);

protected:
 /*protected*/ void paintComponent(QPainter *painter);

};

#endif // DIAGRAMCOMPONENT_H
