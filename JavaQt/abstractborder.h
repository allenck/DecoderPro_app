#ifndef ABSTRACTBORDER_H
#define ABSTRACTBORDER_H
#include "border.h"
#include <QWidget>

class AbstractBorder : public Border
{
public:
 AbstractBorder(QObject* parent = nullptr);
 /*public*/ virtual Insets* getBorderInsets(QWidget* c);
 /*public*/ virtual Insets* getBorderInsets(QWidget* c, Insets* insets);
 /*public*/ virtual bool isBorderOpaque();
 /*public*/ virtual QRect getInteriorRectangle(QWidget* c, int x, int y, int width, int height);
 /*public*/ static QRect getInteriorRectangle(QWidget* c, Border* b, int x, int y, int width, int height);
 /*public*/ virtual int getBaseline(QWidget c, int width, int height);

};

#endif // ABSTRACTBORDER_H
