#ifndef TITLEDBORDER_H
#define TITLEDBORDER_H
#include "abstractborder.h"
#include <QLabel>

class TitledBorder : public AbstractBorder
{
public:
 TitledBorder(QObject* parent = nullptr);
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
 /*public*/ TitledBorder(QString title, QObject* parent = 0);
 /*public*/ TitledBorder(Border* border, QObject* parent = 0);
 /*public*/ TitledBorder(Border* border, QString title, QObject* parent = 0);
 /*public*/ TitledBorder(Border* border, QString title, int titleJustification,int titlePosition, QObject* parent = 0);
 /*public*/ TitledBorder(Border* border,
                     QString title,
                     int titleJustification,
                     int titlePosition,
                     QFont titleFont, QObject* parent = 0);
 /*public*/ TitledBorder(Border* border,
                     QString title,
                     int titleJustification,
                     int titlePosition,
                     QFont titleFont,
                     QColor titleColor, QObject* parent = 0);
 /*public*/ void setTitleJustification(int titleJustification);
 /*public*/ void setTitlePosition(int titlePosition);

private:
 /*private*/ /*final*/ QLabel* label;
 void common(Border* border,
              QString title,
              int titleJustification,
              int titlePosition,
              QFont titleFont,
              QColor titleColor);
protected:
 /*protected*/ QString title;
 /*protected*/ Border* border;
 /*protected*/ int titlePosition;
 /*protected*/ int titleJustification;
 /*protected*/ QFont titleFont;
 /*protected*/ QColor titleColor;
 // Space between the border and the component's edge
 static /*protected*/ /*final*/ int EDGE_SPACING;// = 2;

 // Space between the border and text
 static /*protected*/ /*final*/ int TEXT_SPACING;// = 2;

 // Horizontal inset of text that is left or right justified
 static /*protected*/ /*final*/ int TEXT_INSET_H;// = 5;

};

#endif // TITLEDBORDER_H
