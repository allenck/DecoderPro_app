#ifndef ANALOGCLOCK2DISPLAY_H
#define ANALOGCLOCK2DISPLAY_H
//#include "positionablejcomponent.h"
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QActionGroup>
#include <QSignalMapper>
#include "positionableicon.h"
#include "liblayouteditor_global.h"
#include "linkingobject.h"
#include "positionablejcomponent.h"

class PropertyChangeEvent;
class Timebase;
class NamedIcon;
class LIBLAYOUTEDITORSHARED_EXPORT AnalogClock2Display : public PositionableJComponent, public LinkingObject
{
 Q_OBJECT
 Q_INTERFACES(LinkingObject)
public:
    //explicit AnalogClock2Display(QWidget *parent = 0);
    /*public*/ AnalogClock2Display(Editor* editor, QObject *parent=0);
    /*public*/ AnalogClock2Display(Editor* editor, QString url, QObject *parent=0);
    ~AnalogClock2Display();
    /*public*/ Positionable* deepClone();
    /*public*/ Positionable* finishClone(Positionable* p);
    /*public*/ int getFaceWidth() ;
    /*public*/ int getFaceHeight();
    /*public*/ bool setScaleMenu(QMenu* popup);
    /*public*/ QString getNameString();
    /*public*/ void setScale(double scale);
    void addRateMenuEntry(QMenu* menu, /*final*/ int newrate);
    /*public*/ void paint(QGraphicsScene* g);
    /*public*/ void setSize(int x);
    /*public*/ void resize();
//    /*public*/ void update();
    /*public*/ bool getRun() ;
    /*public*/ void setRun(bool next);
    void cleanup();
    /*public*/ void dispose();
    /*public*/ bool updateScene();
    /*public*/ QString getURL();
    /*public*/ void setULRL(QString u);
    /*public*/ bool setLinkMenu(QMenu* popup);
    /*public*/ void doMouseClicked(QGraphicsSceneMouseEvent* event);
    /*public*/ void setFont(QFont);
    QObject* jself() {return (QObject*)this;}
    /*public*/ void setBorder(Border* border) override {this->_border = border;}
    /*public*/ Border* getBorder() {return _border;}
    /*public*/ void setEnabled(bool b) {QWidget::setEnabled(b);}
signals:

public slots:
    /*public*/ void update();
    void actActivated();
    void rateChange(int);
    void propertyChange(PropertyChangeEvent*);

private:
    Timebase* clock;
    double rate;
    double minuteAngle;
    double hourAngle;
    QString amPm;

    // Define common variables
    QImage logo;
    QImage scaledLogo;
    QImage clockFace;
    NamedIcon* jmriIcon;
    NamedIcon* scaledIcon;
    NamedIcon* clockIcon;

    QVector<int> hourX;// = {
//         -12, -11, -25, -10, -10, 0, 10, 10, 25, 11, 12};
    QVector<int>  hourY;// = {
//         -31, -163, -170, -211, -276, -285, -276, -211, -170, -163, -31};
    QVector<int>  minuteX;// = {
//         -12, -11, -24, -11, -11, 0, 11, 11, 24, 11, 12};
    QVector<int>  minuteY;// = {
//         -31, -261, -266, -314, -381, -391, -381, -314, -266, -261, -31};
    QVector<int>  scaledHourX;// = new int[hourX.length];
    QVector<int>  scaledHourY;// = new int[hourY.length];
    QVector<int>  scaledMinuteX;// = new int[minuteX.length];
    QVector<int>  scaledMinuteY;// = new int[minuteY.length];
    QVector<int>  rotatedHourX;// = new int[hourX.length];
    QVector<int>  rotatedHourY;// = new int[hourY.length];
    QVector<int>  rotatedMinuteX;// = new int[minuteX.length];
    QVector<int>  rotatedMinuteY;// = new int[minuteY.length];

    QGraphicsPolygonItem* hourHand;
    QGraphicsPolygonItem* scaledHourHand;
    QGraphicsPolygonItem* minuteHand;
    QGraphicsPolygonItem* scaledMinuteHand;
    //QGraphicsItemGroup* _item;
    int minuteHeight;
    int hourHeight;
    double scaleRatio;
    int faceSize;
    int panelWidth;
    int panelHeight;
    int size;
    int logoWidth;
    int logoHeight;

    // centreX, centreY are the coordinates of the centre of the clock
    int centreX;
    int centreY;

    QString _url;
    Border* _border = nullptr;

 Logger* log;
 void common();

 QActionGroup* rateButtonGroup;// = null;
 QSignalMapper* mapper;
 QAction* runMenu;// = NULL;;
 double toRadians(double degrees);
 int dotX(double radius, double angle);
 int dotY(double radius, double angle);
 /*private*/ void scaleFace();
 QGraphicsScene* g;
};

#endif // ANALOGCLOCK2DISPLAY_H
