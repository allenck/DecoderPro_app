#ifndef TITLEDBORDER_H
#define TITLEDBORDER_H
#include "abstractborder.h"
#include "jlabel.h"

class TitledBorder : public AbstractBorder
{
 Q_OBJECT
public:
 TitledBorder(QWidget *parent = nullptr);
 /**
  * Use the default vertical orientation for the title text.
  */
 enum VERTICALPOSITION
 {
  DEFAULT_POSITION        = 0,
 /** Position the title above the border's top line. */
  ABOVE_TOP               = 1,
 /** Position the title in the middle of the border's top line. */
  TOP                     = 2,
 /** Position the title below the border's top line. */
  BELOW_TOP               = 3,
 /** Position the title above the border's bottom line. */
  ABOVE_BOTTOM            = 4,
 /** Position the title in the middle of the border's bottom line. */
  BOTTOM                  = 5,
 /** Position the title below the border's bottom line. */
  BELOW_BOTTOM            = 6
 };
 /**
  * Use the default justification for the title text.
  */
 enum JUSTIFICATION
 {
  DEFAULT_JUSTIFICATION   = 0,
 /** Position title text at the left side of the border line. */
  LEFT                    = 1,
 /** Position title text in the center of the border line. */
  CENTER                  = 2,
 /** Position title text at the right side of the border line. */
  RIGHT                   = 3,
 /** Position title text at the left side of the border line
  *  for left to right orientation, at the right side of the
  *  border line for right to left orientation.
  */
  LEADING = 4,
 /** Position title text at the right side of the border line
  *  for left to right orientation, at the left side of the
  *  border line for right to left orientation.
  */
  TRAILING = 5
 };

 /*public*/ TitledBorder(QString title, QWidget* parent = 0);
 /*public*/ TitledBorder(Border* border, QWidget *parent = 0);
 /*public*/ TitledBorder(Border* border, QString title, QWidget *parent = 0);
 /*public*/ TitledBorder(Border* border, QString title, int titleJustification,int titlePosition, QWidget* parent = 0);
 /*public*/ TitledBorder(Border* border,
                     QString title,
                     int titleJustification,
                     int titlePosition,
                     QFont *titleFont, QWidget *parent = 0);
 /*public*/ TitledBorder(Border* border,
                     QString title,
                     int titleJustification,
                     int titlePosition,
                     QFont* titleFont,
                     QColor titleColor, QWidget* parent = 0);
 /*public*/ void setTitleJustification(int titleJustification);
 /*public*/ void setTitlePosition(int titlePosition);
#if 1
 /*public*/ Insets* getBorderInsets(QWidget* c, Insets* insets);
 /*public*/ bool isBorderOpaque();
 /*public*/ QString getTitle();
 /*public*/ Border* getBorder();
 /*public*/ int getTitlePosition();
 /*public*/ int getTitleJustification();
 /*public*/ QFont *getTitleFont();
 /*public*/ QColor getTitleColor();
 /*public*/ void setTitle(QString title);
 /*public*/ void setBorder(Border* border);
 /*public*/ void setTitleFont(QFont *titleFont);
 /*public*/ void setTitleColor(QColor titleColor);
 /*public*/ QSize getMinimumSize(QWidget *c);
 /*public*/ int getBaseline(QWidget *c, int width, int height);
 /*public*/ void paintBorder(QWidget* c, QPainter* g, int x, int y, int width, int height);
#endif
 QWidget* self() {return (QWidget*)this;}

private:
 /*private*/ /*final*/ JLabel* label;
 void common(Border* border,
              QString title,
              int titleJustification,
              int titlePosition,
              QFont* titleFont,
              QColor titleColor);
#if 1
 /*private*/ int getPosition();
 /*private*/ int getJustification(QWidget* c);
 /*private*/ QColor getColor(QWidget* c);
 /*private*/ JLabel* getLabel(QWidget* c);
 /*private*/ static Insets* getBorderInsets(Border* border, QWidget* c, Insets* insets);


#endif
protected:
 /*protected*/ QString title;
 /*protected*/ Border* border;
 /*protected*/ int titlePosition;
 /*protected*/ int titleJustification;
 /*protected*/ QFont* titleFont;
 /*protected*/ QColor titleColor;
 // Space between the border and the component's edge
 static /*protected*/ /*final*/ int EDGE_SPACING;// = 2;

 // Space between the border and text
 static /*protected*/ /*final*/ int TEXT_SPACING;// = 2;

 // Horizontal inset of text that is left or right justified
 static /*protected*/ /*final*/ int TEXT_INSET_H;// = 5;

#if 1
 /*protected*/ QFont *getFont(QWidget* c);
#endif

};

#endif // TITLEDBORDER_H
