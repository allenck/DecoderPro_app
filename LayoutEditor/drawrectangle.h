#ifndef DRAWRECTANGLE_H
#define DRAWRECTANGLE_H
#include "drawframe.h"

class JTextField;
class DrawRectangle : public DrawFrame
{
    Q_OBJECT
public:
    //explicit DrawRectangle(QWidget *parent = 0);
    /*public*/ DrawRectangle(QString which, QString _title, ShapeDrawer* parent);

signals:

public slots:
    void widthEdited(QString);
    void heightEdited(QString);
private:
    int _width;
    int _height;
    JTextField* _widthText;
    JTextField* _heightText;
protected:
    /*protected*/ virtual QWidget* makeParamsPanel(PositionableShape* ps);
    /*protected*/ virtual void makeFigure();
    ///*protected*/ void setPositionableParams(PositionableShape* p);
    /*protected*/ virtual void setDisplayParams(PositionableShape* p);
    ///*protected*/ virtual void updateFigure(PositionableShape* p);
friend class DrawRoundRect;
};

#endif // DRAWRECTANGLE_H
