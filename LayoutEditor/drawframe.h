#ifndef DRAWFRAME_H
#define DRAWFRAME_H
#include "jmrijframe.h"
#include "windowlistener.h"

class DFWindowListener;
class QComboBox;
class JTextField;
class QGraphicsSceneMouseEvent;
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
    explicit DrawFrame(QWidget *parent = 0);
    /*public*/ DrawFrame(QString which, QString _title, ShapeDrawer* parent);
    /*public*/ QSize getSize(QSize rv);
    /*public*/ QPoint getLocation(QPoint rv);
    QVBoxLayout* panelLayout;
signals:

public slots:
    /*public*/ void stateChanged(/*ChangeEvent* e = 0*/QColor);
    //void onSelectionRect(QRectF, QGraphicsSceneMouseEvent*);
    void onLineColor();
    void onFillColor();
    void On_hideShape();
    void On_changeLevel();

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
    //QSlider*		_fillSlider;
    QSlider* _alphaSlider;
    JTextField* _sensorName;// = new JTextField(30);
    QRadioButton* _hideShape;
    QRadioButton* _changeLevel;
    QComboBox* _levelComboBox;
    /*private*/ PositionableShape* _originalShape;       // saved for use if cancelled
    /*private*/ QWidget* makeDoneButtonPanel();
    // these 2 methods update the JTextfields when mouse moves handles
    virtual void setDisplayWidth(int w);
    virtual void setDisplayHeight(int h);
    /*private*/ void alphaChange();
    DFWindowListener* listener;

private slots:
    void On_sensorName_editingFinished();
    void On_doneButton();
    void On_cancelButton();
    void On_alphaSlider_valueChanged(int);
    /*private*/ void widthChange();


protected:
    /*protected*/ PositionableShape* _shape;       // for use while editing
    /*protected*/ ShapeDrawer* _parent;
    ///*protected*/ bool _editing;
    /*protected*/ QWidget* makePanel();
    ///*protected*/ virtual void setPositionableParams(PositionableShape* ps);
    /*protected*/ void setDrawParams();
    /*protected*/ virtual void closingEvent(bool);
    /*abstract*/ /*protected*/ virtual bool makeFigure(QGraphicsSceneMouseEvent*) {return false;}
    /*abstract*/ /*protected*/ virtual void updateFigure(PositionableShape* /*pos*/) {}
    /*protected*/ virtual QWidget* makeParamsPanel(PositionableShape* ps);
    /*protected*/ virtual void setDisplayParams(PositionableShape* ps);
    /*protected*/ QWidget* makeSensorPanel();
    /*protected*/ void makeCopy(PositionableShape* ps);
    /*protected*/ void updateShape();


friend class DrawRectangle;
friend class ShapeDrawer;
friend class PositionableShape;
friend class DrawCircle;
friend class DrawEllipse;
friend class DrawRoundRect;
friend class DFWindowListener;
friend class DrawPolygon;
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
