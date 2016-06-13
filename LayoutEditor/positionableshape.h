#ifndef POSITIONABLESHAPE_H
#define POSITIONABLESHAPE_H
#include "positionablejcomponent.h"
#include "liblayouteditor_global.h"

class EditScene;
class DrawFrame;
class LIBLAYOUTEDITORSHARED_EXPORT PositionableShape : public PositionableJComponent
{
    Q_OBJECT
public:
    //explicit PositionableShape(QWidget *parent = 0);
    /*public*/ PositionableShape(Editor* editor, QWidget *parent = 0);
    /*public*/ PositionableShape(Editor* editor, QGraphicsItem* shape, QWidget *parent);
    /*public*/ virtual void makeShape();
    /*public*/ void setLineColor(QColor c);
    /*public*/ QColor getLineColor();
    /*public*/ void setFillColor(QColor c);
    /*public*/ QColor getFillColor();
    /*public*/ void setAlpha(int a);
    /*public*/ int getAlpha() ;
    /*public*/ void setLineWidth(int w);
    /*public*/ int getLineWidth();
    /*public*/ void paint(EditScene* g) ;
    /*public*/ Positionable* deepClone();
    /*public*/ Positionable* finishClone(Positionable* p);
    /*public*/ QSize getSize(QSize rv);
    /*public*/ void updateSize();
    /*public*/ int maxWidth() ;
    /*public*/ int maxHeight();
    /*public*/ bool showPopUp(QMenu* popup);
    /*public*/ bool setRotateMenu(QMenu* popup);
    /*public*/ bool setScaleMenu(QMenu* popup);
    /*public*/ int getDegrees();
    /*public*/ virtual bool setEditItemMenu(QMenu* popup);

signals:

public slots:
    void OnCancel_clicked();

private:
    /*protected*/ QGraphicsItem*	_shape;
    /*protected*/ QColor	_lineColor;// = Color.black;
    /*protected*/ QColor	_fillColor;
    /*protected*/ int	_alpha;// = 255;
    /*protected*/ int	_lineWidth;// = 1;
    /*protected*/ int		_degrees;
//    /*protected*/ AffineTransform _transform;
    void init();
    DrawFrame* _editFrame;
    /*protected*/ void setEditParams();
    /*protected*/ QWidget* makeDoneButtonPanel() ;
protected slots:
    /*protected*/ void editItem() ;
friend class PositionableRectangle;
friend class PositionableCircle;
friend class PositionableEllipse;
friend class PositionableRoundRect;
friend class Editor;
};

#endif // POSITIONABLESHAPE_H
