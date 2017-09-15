#ifndef DRAWCIRCLE_H
#define DRAWCIRCLE_H
#include "drawframe.h"

class JTextField;
class DrawCircle : public DrawFrame
{
    Q_OBJECT
public:
    //explicit DrawCircle(QWidget *parent = 0);
    /*public*/ DrawCircle(QString which, QString _title, ShapeDrawer* parent);

signals:

public slots:
private:
    //JTextField*	_radiusText;
    int 		_radius;			// corner radius
    void setDisplayWidth(int w);
    void setDisplayHeight(int h);
    JTextField* _diameterText;

protected:
    /*protected*/ virtual QWidget* makeParamsPanel(PositionableShape* ps);
    /*protected*/ void makeFigure() ;
    ///*protected*/ void setPositionableParams(PositionableShape* p);
    ///*protected*/ void setDisplayParams(PositionableShape* p);
    ///*protected*/ void updateFigure(PositionableShape* p);

};

#endif // DRAWCIRCLE_H
