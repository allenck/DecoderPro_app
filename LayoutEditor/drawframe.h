#ifndef DRAWFRAME_H
#define DRAWFRAME_H
#include "jmrijframe.h"
#include "windowlistener.h"

class QVBoxLayout;
class ControlPanelEditor;
class ChangeEvent;
class PositionableShape;
class QColor;
class QSlider;
class QRadioButton;
class QColorDialog;
class QSize;
class QPoint;
class ShapeDrawer;
class DrawFrame : public JmriJFrame
{
    Q_OBJECT
public:
    //explicit DrawFrame(QWidget *parent = 0);
    /*public*/ DrawFrame(QString which, QString _title, ShapeDrawer* parent);
    /*public*/ QSize getSize(QSize rv);
    /*public*/ QPoint getLocation(QPoint rv);
    QVBoxLayout* panelLayout;
signals:

public slots:
    /*public*/ void stateChanged(/*ChangeEvent* e = 0*/QColor);
    void onSelectionRect(QRectF);
    void onLineColor();
    void onFillColor();
private:
    static int STRUT_SIZE;// = 10;
    static QPoint _loc;// = new Point(100,100);
    static QSize _dim;// = new Dimension(500,500);

    int		_lineWidth;
    QColor 	_lineColor;
    QColor 	_fillColor;
    int 	_alpha;
//	Stroke 	_stroke;
    QColorDialog* _chooser;
    QRadioButton* _lineColorButton;
    QRadioButton* _fillColorButton;
    QSlider* 	_lineSlider;
    QSlider*		_fillSlider;
    ControlPanelEditor* editor;

protected:
    /*protected*/ ShapeDrawer* _parent;
    /*protected*/ QWidget* makePanel();
    /*protected*/ virtual void setPositionableParams(PositionableShape* ps);
    /*protected*/ void setDrawParams();
    /*protected*/ void closingEvent();
    /*abstract*/ /*protected*/ virtual void makeFigure() {}
    /*abstract*/ /*protected*/ virtual void updateFigure(PositionableShape* /*pos*/) {}
    /*protected*/ virtual QWidget* makeParamsPanel();
    /*protected*/ virtual void setDisplayParams(PositionableShape* ps);

friend class DrawRectangle;
friend class ShapeDrawer;
friend class PositionableShape;
friend class DrawCircle;
friend class DrawEllipse;
friend class DrawRoundRect;
friend class DFWindowListener;

};
class DFWindowListener : public WindowListener
{
 Q_OBJECT
 DrawFrame* frame;
public:
 DFWindowListener(DrawFrame* frame);
 void windowClosing(QCloseEvent *e);
};
#endif // DRAWFRAME_H
