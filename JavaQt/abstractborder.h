#ifndef ABSTRACTBORDER_H
#define ABSTRACTBORDER_H
#include "border.h"
#include <QWidget>

class AbstractBorder : public QWidget, public Border
{
 Q_OBJECT
 Q_INTERFACES(Border)

public:
 AbstractBorder(QWidget *parent = nullptr);
 ///*public*/ virtual Insets* getBorderInsets(QWidget* c);
 /*public*/ virtual Insets* getBorderInsets(QWidget* c, Insets* insets= nullptr);
 /*public*/ virtual bool isBorderOpaque();
 /*public*/ virtual QRect getInteriorRectangle(QWidget* c, int x, int y, int width, int height);
 /*public*/ static QRect getInteriorRectangle(QWidget* c, Border* b, int x, int y, int width, int height);
 /*public*/ virtual int getBaseline(QWidget c, int width, int height);
 void virtual adjustLayout(QLayout* layout) {} // subclasses can adjust layout

private:
 \
protected:
};

#endif // ABSTRACTBORDER_H
