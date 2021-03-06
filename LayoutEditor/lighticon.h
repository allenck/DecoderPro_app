#ifndef LIGHTICON_H
#define LIGHTICON_H
#include "positionableicon.h"
#include "abstractnamedbean.h"
#include "propertychangelistener.h"

class QGraphicsSceneMouseEvent;
class Light;
class PropertyChangeEvent;
class LightIcon : public PositionableIcon, public PropertyChangeListener
{
    Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
    //explicit LightIcon(QObject *parent = 0);
    /*public*/ LightIcon(Editor* editor, QObject *parent = 0);
    /*public*/ Positionable* deepClone() override;
    /*public*/ Positionable* finishClone(Positionable* p) override;
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
    /*public*/ int maxHeight() override;
    /*public*/ int maxWidth() override;
    int lightState();
//    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ QString getNameString() override;
    /*public*/ void setScale(double s) override;
    /*public*/ void rotate(int deg) override;
    void displayState(int state) override;
    /*public*/ void dispose() override;
    NamedIcon* getIcon(int state);
    NamedIcon* getIcon(QString sState);
    /*public*/ bool updateScene() override;
    QObject* self() override {return (QObject*)this;}

signals:

public slots:
    /*public*/ void doMouseClicked(QGraphicsSceneMouseEvent* e) override;
    void propertyChange(QString propertyName, int old, int now);
    void propertyChange(PropertyChangeEvent* e) override;
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
    /*protected*/ void rotateOrthogonal() override;

    /*protected*/ void edit() override;

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
