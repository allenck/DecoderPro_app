#ifndef DRAWROUNDRECT_H
#define DRAWROUNDRECT_H
#include "drawrectangle.h"

class JTextField;
class DrawRoundRect : public DrawRectangle
{
    Q_OBJECT
public:
   // explicit DrawRoundRect(QWidget *parent = 0);
    /*public*/ DrawRoundRect(QString which, QString _title, ShapeDrawer* parent);
    /*public*/ QString getClassName();

signals:

public slots:
private:
    JTextField*	_radiusText;
    int 		_radius;			// corner radius
protected:
    /*protected*/ virtual QWidget* makeParamsPanel(PositionableShape* p);
    /*protected*/ void makeFigure();
    /*protected*/ void setPositionableParams(PositionableShape* p);
    /*protected*/ virtual void setDisplayParams(PositionableShape* p) ;
    /*protected*/ virtual void updateFigure(PositionableShape* p);

};

#endif // DRAWROUNDRECT_H
