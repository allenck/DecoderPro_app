#ifndef DIAGRAMCOMPONENT_H
#define DIAGRAMCOMPONENT_H
#include "jcomponent.h"
#include <QFrame>

class Insets;
class ColorPanel;
class BufferedImage;
class DiagramComponent : public QFrame, public JComponent
{
 Q_OBJECT
 Q_INTERFACES(JComponent)
public:
 DiagramComponent(ColorPanel* panel, bool diagram, QWidget* parent = nullptr);
 /*public*/ void mousePressEvent(QMouseEvent* event)override;
 /*public*/ void mouseReleaseEvent(QMouseEvent* event)override;
 /*public*/ void mouseClicked(QMouseEvent* event);
 /*public*/ void mouseEntered(QMouseEvent* event);
 /*public*/ void mouseExited(QMouseEvent* event);
 /*public*/ void mouseMoveEvent(QMouseEvent* event)override;
 /*public*/ void mouseDragged(QMouseEvent* event);

 /*public*/ bool  isOpaque()override;
 /*public*/ QColor getBackground()override;
 /*public*/ void setBackground(QColor c)override;
 /*public*/ QFont getFont()override;
 /*public*/ void setOpaque(bool b)override;
 /*public*/ void setFont(QFont f)override;
 QWidget* jself()override{return (QWidget*)this;}
 /*public*/ void setBorder(Border* border) override {this->_border = border;}
 /*public*/ Border* getBorder() override{return _border;}


private:
 /*private*/ /*final*/ ColorPanel* panel;
 /*private*/ /*final*/ bool diagram;

 /*private*/ /*final*/ Insets* insets;// = new Insets(0, 0, 0, 0);

 /*private*/ int width = 0;
 /*private*/ int height = 0;

 /*private*/ QVector<int> array;
 /*private*/ BufferedImage* image = nullptr;
 /*private*/ static int getValue(float value, int min, int max);
 /*private*/ static float getValue(int value, int min, int max);
 /*public*/ void paintEvent(QPaintEvent *event);
 Border* _border = nullptr;

protected:
 /*protected*/ void paintComponent();

};

#endif // DIAGRAMCOMPONENT_H
