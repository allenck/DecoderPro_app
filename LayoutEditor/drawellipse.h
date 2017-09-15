#ifndef DRAWELLIPSE_H
#define DRAWELLIPSE_H
#include "drawframe.h"

class JTextField;
class DrawEllipse : public DrawFrame
{
    Q_OBJECT
public:
    //explicit DrawEllipse(QWidget *parent = 0);
    /*public*/ DrawEllipse(QString which, QString _title, ShapeDrawer* parent);

signals:

public slots:
private:
    int _width;
    int _height;
    JTextField* _widthText;
    JTextField* _heightText;
protected:
    /*protected*/ QWidget* makeParamsPanel(PositionableShape* p);
    /*protected*/ void makeFigure();
    /*protected*/ void setPositionableParams(PositionableShape* p) ;
    /*protected*/ void setDisplayParams(PositionableShape* p);
    /*protected*/ void updateFigure(PositionableShape* p);

};

#endif // DRAWELLIPSE_H
