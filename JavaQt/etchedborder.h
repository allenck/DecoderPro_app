#ifndef ETCHEDBORDER_H
#define ETCHEDBORDER_H
#include "abstractborder.h"
#include "exceptions.h"

class EtchedBorder : public AbstractBorder
{
public:
 EtchedBorder(QWidget *parent = nullptr);
 /*public*/ EtchedBorder(int etchType, QWidget *parent = nullptr);
 /*public*/ EtchedBorder(int etchType, QColor highlight, QColor shadow, QWidget* parent  = nullptr);
 /*public*/ EtchedBorder(QColor highlight, QColor shadow, QWidget* parent= nullptr);
 /*public*/ void paintBorder(QWidget* c, int x, int y, int width,
                         int height);
 /*public*/ Insets* getBorderInsets(QWidget* c);
 enum ETCHTYPE
 {
  RAISED,
  LOWERED
 };

 ///*public*/ Insets* getBorderInsets(QWidget* c);
 /*public*/ Insets* getBorderInsets(QWidget* c, Insets* insets);
 /*public*/ bool isBorderOpaque();
 /*public*/ int getEtchType();
 /*public*/ QColor getHighlightColor(QWidget* c);
 /*public*/ QColor getHighlightColor();
 /*public*/ QColor getShadowColor(QWidget *c);
 /*public*/ QColor getShadowColor();

private:
 static /*final*/ long serialVersionUID;// = 4001244046866360638L;
 /*private*/ /*static*/ void paintEtchedBorder(QWidget *c, int x, int y, int width,
                                       int height, QColor a, QColor b);
 QPainter* g;
 QWidget* self() {return (QWidget*)this;}

protected:
 /**
  * The type of this EtchedBorder, which is either {@link #RAISED}
  * or {@link #LOWERED}.
  */
 /*protected*/ int etchType;


 /**
  * The highlight color, or <code>null</code> to indicate that the
  * color shall be derived from the background of the enclosed
  * component.
  */
 /*protected*/ QColor highlight;


 /**
  * The shadow color, or <code>null</code> to indicate that the
  * color shall be derived from the background of the enclosed
  * component.
  */
 /*protected*/ QColor shadow;

};

#endif // ETCHEDBORDER_H
