#ifndef TURNOUTICON_H
#define TURNOUTICON_H
#include "positionableicon.h"
#include "namedbeanhandle.h"

class TableItemPanel;
class Turnout;
class LIBLAYOUTEDITORSHARED_EXPORT TurnoutIcon : public PositionableIcon, public PropertyChangeListener
{
    Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
 //explicit TurnoutIcon(QObject *parent = 0);
 /*public*/ TurnoutIcon(Editor* editor, QObject *parent = 0);
 /*public*/ Positionable* deepClone() override ;
 /*public*/ Positionable* finishClone(Positionable* p) override;
 /*public*/ void setTurnout(QString pName);
 /*public*/ void setTurnout(NamedBeanHandle<Turnout*>* to);
 /*public*/ Turnout* getTurnout();
 /*public*/ NamedBeanHandle <Turnout*>* getNamedTurnout();
 /*public*/ NamedBean* getNamedBean() override;
 /*public*/ void setIcon(QString name, NamedIcon* icon);
 /*public*/ NamedIcon* getIcon(QString state);
 /*public*/ NamedIcon* getIcon(int state);
 /*public*/ QString getFamily();
 /*public*/ void setFamily(QString family);
 /*public*/ int maxHeight() override;
 /*public*/ int maxWidth() override;
 int turnoutState();
 /*public*/ QString getStateName(int state) ;
 /*public*/ QString getNameString() override;
 /*public*/ void setTristate(bool set) ;
 /*public*/ bool getTristate();
 /*public*/ bool showPopUp(QMenu* popup) override;
 void addTristateEntry(QMenu* popup);
 /*public*/ void setScale(double s)  override;
 /*public*/ void rotate(int deg) override;
 /*public*/ void displayState(int state) override;
 int getType();
 void setType(int type);
 /*public*/ void dispose() override;
 /*public*/ bool setEditItemMenu(QMenu* popup) override;
 /*public*/ bool setEditIconMenu(QMenu* popup) override;
 /*public*/ bool getMomentary();
 /*public*/ bool getDirectControl();
 /*public*/ QString getGroupName() override;
 QObject* self() override {return (QObject*)this;}

signals:

public slots:
 void on_tristateItem_toggled(bool);
 /*public*/ void propertyChange(PropertyChangeEvent* e) ;
 /*public*/ void doMouseClicked(QGraphicsSceneMouseEvent* e);
 /*public*/ void setMomentary(bool m);
 /*public*/ void setDirectControl(bool m);

private:
 Logger* log;
 // the associated Turnout object
 //Turnout turnout = NULL;
 /*private*/ NamedBeanHandle<Turnout*>* namedTurnout;// = NULL;
 /*private*/ bool tristate;// = false;
 int _type;
protected:
 /*protected*/ QHash <int, NamedIcon*>* _iconStateMap;          // state int to icon
 /*protected*/ QHash <QString, int>* _name2stateMap;       // name to state
 /*protected*/ QHash <int, QString>* _state2nameMap;       // state to name
 QString  _iconFamily;
 /*protected*/ void rotateOrthogonal();
 /*protected*/ QHash<int, NamedIcon *> *cloneMap(QHash<int, NamedIcon *> *map,                                                         TurnoutIcon* pos);
 TableItemPanel* _itemPanel;
 bool momentary;// = false;
 bool directControl;// = false;
 QAction* momentaryItem;
 QAction* directControlItem;
 void alternateOnClick();

protected slots:
 /*protected*/ virtual void editItem();
 void updateTurnout();
 void updateItem();
 /*protected*/ virtual void edit();


friend class PositionableLabel;
friend class UpdateTurnoutActionListener;
friend class AddTurnoutIconActionListener;

};
class UpdateTurnoutActionListener : public ActionListener
{
 Q_OBJECT
 TurnoutIcon* turnoutIcon;
public:
 UpdateTurnoutActionListener(TurnoutIcon* turnoutIcon)
 {
  this->turnoutIcon = turnoutIcon;
 }

public slots:
 void actionPerformed(JActionEvent */*e*/ = 0)
 {
  turnoutIcon->updateItem();
 }
};
class AddTurnoutIconActionListener : public ActionListener
{
 Q_OBJECT
 TurnoutIcon* turnoutIcon;
public:
 AddTurnoutIconActionListener(TurnoutIcon* turnoutIcon)
 {
  this->turnoutIcon = turnoutIcon;
 }

public slots:
 void actionPerformed(JActionEvent */*e*/ = 0)
 {
  turnoutIcon->updateTurnout();
 }
};

#endif // TURNOUTICON_H
