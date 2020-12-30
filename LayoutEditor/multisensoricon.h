#ifndef MULTISENSORICON_H
#define MULTISENSORICON_H
#include "positionablelabel.h"
#include "namedbeanhandle.h"

class MultiSensorItemPanel;
class PropertyChangeEvent;
class Sensor;
//class NamedBeanHandle;
class MultiSensorIconEntry;
class Editor;
/*static*/ class MultiSensorIconEntry
{
public:
  /*static*/ NamedBeanHandle<Sensor*>* namedSensor;
  /*static*/ NamedIcon* icon;
    MultiSensorIconEntry(NamedIcon* icon, NamedBeanHandle<Sensor*>* namedSensor);
};
class MultiSensorIcon : public PositionableLabel
{
    Q_OBJECT
public:

    //explicit MultiSensorIcon(QObject *parent = 0);
    /*public*/ MultiSensorIcon(Editor* editor, QObject *parent = 0);
    /*public*/ void setUpDown(bool b);
    /*public*/ bool getUpDown();
    /*public*/ Positionable* deepClone()override;
    /*public*/ Positionable* finishClone(Positionable* p)override;
    /*public*/ void addEntry(NamedBeanHandle<Sensor*>* sensor, NamedIcon* icon);
    /*public*/ void addEntry(QString pName, NamedIcon* icon);
    /*public*/ int getNumEntries();
    /*public*/ QList<Sensor*> getSensors();
    /*public*/ QString getSensorName(int i);
    /*public*/ NamedIcon* getSensorIcon(int i);
    /*public*/ QString getFamily();
    /*public*/ void setFamily(QString family);
    /*public*/ NamedIcon* getInactiveIcon();
    /*public*/ NamedIcon* getInconsistentIcon() ;
    /*public*/ NamedIcon* getUnknownIcon();
    /*public*/ QString getNameString() override;
    /*public*/ void setScale(double s) override;
    /*public*/ void rotate(int deg)override;
    /*public*/ bool setEditItemMenu(QMenu* popup)override;
    /*public*/ bool setEditIconMenu(QMenu* popup)override;
    /*public*/ void displayState();
    /*public*/ int maxHeight()override;
    /*public*/ int maxWidth()override;
    /*public*/ void performMouseClicked(QGraphicsSceneMouseEvent* e, int xx, int yy);
    /*public*/ void doMouseClicked(QGraphicsSceneMouseEvent* e)override;
    /*public*/ void dispose()override;
    /*static*/ class Entry
    {
    public:
        Entry(NamedIcon* icon,NamedBeanHandle<Sensor*>* namedSensor)
        {
            this->namedSensor = namedSensor;
            this->icon = icon;
        }
         NamedBeanHandle<Sensor*>* namedSensor;
         NamedIcon* icon;
    };
 /*public*/ QString getGroupName()override;

public slots:
    // update icon as state of turnout changes
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    void updateItem();
    /*public*/ void setInactiveIcon(NamedIcon* i);
    /*public*/ void setInconsistentIcon(NamedIcon* i);
    /*public*/ void setUnknownIcon(NamedIcon* i);
signals:

public slots:
    void updateSensor();

private:
    QString  _iconFamily;
    bool updown;// = false;
    QList<Entry*>* entries;// = new QList<Entry>();
    // display icons
    QString inactiveName;// = "resources/icons/USS/plate/levers/l-inactive.gif";
    NamedIcon* inactive;// = new NamedIcon(inactiveName, inactiveName);

    QString inconsistentName;// = "resources/icons/USS/plate/levers/l-inconsistent.gif";
    NamedIcon* inconsistent;// = new NamedIcon(inconsistentName, inconsistentName);

    QString unknownName;// = "resources/icons/USS/plate/levers/l-unknown.gif";
    NamedIcon* unknown;// = new NamedIcon(unknownName, unknownName);
    Logger* log;
    MultiSensorItemPanel* _itemPanel;
    int displaying;// = -1;
    bool buttonLive();
    class AddIconActionListener : public ActionListener
    {
     MultiSensorIcon* parent;
    public:
     AddIconActionListener(MultiSensorIcon* parent)
     {
      this->parent = parent;
     }
     void actionPerformed(JActionEvent */*e*/ = 0)
     {
      parent->updateSensor();
     }
    };

protected:
    /*protected*/ void rotateOrthogonal()override;
protected slots:
    /*protected*/ void edit()override;
    /*protected*/ void editItem();

friend class MultiSensorIconWidget;
friend class MultiSensorIconAdder;
};
class UIActionListener : public ActionListener
{
 Q_OBJECT
 MultiSensorIcon* parent;
public:
 UIActionListener(MultiSensorIcon* parent)
 {
  this->parent = parent;
 }
public slots:
 void actionPerformed(JActionEvent * = 0) { parent->updateItem();}
};

#endif // MULTISENSORICON_H
