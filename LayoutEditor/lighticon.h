#ifndef LIGHTICON_H
#define LIGHTICON_H
#include "positionableicon.h"
#include "abstractnamedbean.h"

class QGraphicsSceneMouseEvent;
class Light;
class PropertyChangeEvent;
class LightIcon : public PositionableIcon
{
    Q_OBJECT
public:
    //explicit LightIcon(QObject *parent = 0);
    /*public*/ LightIcon(Editor* editor, QObject *parent = 0);
    /*public*/ Positionable* deepClone();
    /*public*/ Positionable* finishClone(Positionable* p);
    /*public*/ void setLight(QString pName);
    /*public*/ void setLight(Light* to);
    /*public*/ Light* getLight();
    /*public*/ NamedIcon* getOffIcon();
    /*public*/ void setOffIcon(NamedIcon* i) ;
    /*public*/ NamedIcon* getOnIcon();
    /*public*/ void setOnIcon(NamedIcon* i) ;
    /*public*/ NamedIcon* getInconsistentIcon();
    /*public*/ void setInconsistentIcon(NamedIcon* i);
    /*public*/ NamedIcon* getUnknownIcon();
    /*public*/ void setUnknownIcon(NamedIcon* i) ;
    /*public*/ int maxHeight();
    /*public*/ int maxWidth();
    int lightState();
//    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ QString getNameString();
    /*public*/ void setScale(double s);
    /*public*/ void rotate(int deg);
    void displayState(int state);
    /*public*/ void dispose();
    NamedIcon* getIcon(int state);
    NamedIcon* getIcon(QString sState);
    /*public*/ bool updateScene();

signals:

public slots:
    /*public*/ void doMouseClicked(QGraphicsSceneMouseEvent* e);
    void propertyChange(QString propertyName, int old, int now);
    void propertyChange(PropertyChangeEvent* e);
    void updateLight();
private:
    // the associated Light object
    Light* light;// = null;
    Logger* log;
    // display icons
    QString offLName;// = "resources/icons/smallschematics/tracksegments/os-lefthand-east-closed.gif";
    NamedIcon* off;// = new NamedIcon(offLName, offLName);
    QString onLName;// = "resources/icons/smallschematics/tracksegments/os-lefthand-east-thrown.gif";
    NamedIcon* on;// = new NamedIcon(onLName, onLName);
    QString inconsistentLName;// = "resources/icons/smallschematics/tracksegments/os-lefthand-east-error.gif";
    NamedIcon* inconsistent;// = new NamedIcon(inconsistentLName, inconsistentLName);
    QString unknownLName;// = "resources/icons/smallschematics/tracksegments/os-lefthand-east-unknown.gif";
    NamedIcon* unknown;// = new NamedIcon(unknownLName, unknownLName);
    /*protected*/ void rotateOrthogonal();

    /*protected*/ void edit();

};
class LightIconActionListener : public ActionListener
{
 Q_OBJECT
 LightIcon* icon;
public:
 LightIconActionListener(LightIcon*);
public slots:
 void actionPerformed(JActionEvent *e = 0);
};

#endif // LIGHTICON_H
