#ifndef SIGNALHEADICON_H
#define SIGNALHEADICON_H
#include "positionableicon.h"
#include <QButtonGroup>
#include "namedbeanhandle.h"
#include "Signal/signalhead.h"
#include "swingpropertychangesupport.h"
//#include "actionlistener.h"


//class NamedBeanHandle<SignalHead*>;
//class ActionListener;
class SignalHead;
class NamedBean;
class PropertyChangeEvent;
class SignalHeadItemPanel;
class LIBLAYOUTEDITORSHARED_EXPORT SignalHeadIcon : public PositionableIcon, public PropertyChangeListener
{
    Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 public:
    //explicit SignalHeadIcon(QObject *parent = 0);
    QVector<QString> _validKey;
    /*public*/ SignalHeadIcon(Editor* editor, Positionable *parent = 0);
    /*public*/ Positionable* deepClone() override;
    /*public*/ Positionable* finishClone(Positionable* p) override;
    /*public*/ void setSignalHead(NamedBeanHandle<SignalHead*>* sh);
    /*public*/ void setSignalHead(QString pName);
    /*public*/ NamedBeanHandle <SignalHead*>* getNamedSignalHead();
    /*public*/ SignalHead* getSignalHead();
    /*public*/ NamedBean* getNamedBean() override;
    /*public*/ void setIcon(QString state, NamedIcon* icon);
    /*public*/ int headState();
    /*public*/ QString getNameString() override;
    /*public*/ bool showPopUp(QMenu* popup) override;
#if 0 // not needed since scaling and rotating is done by QT's QGraphicsScene ACK
    /*public*/ void setScale(double s) ;
    /*public*/ void rotate(int deg);
#endif
    /*public*/ void displayState(int state) override;
    /*public*/ bool setEditItemMenu(QMenu* popup) override;
    void updateItem();
    /*public*/ bool setEditIconMenu(QMenu* popup) override;
    void updateSignal() ;
    /*public*/ void setClickMode(int mode);
    /*public*/ int getClickMode();
    /*public*/ void setLitMode(bool mode);
    /*public*/ bool getLitMode();
    /*public*/ void doMouseClicked(QGraphicsSceneMouseEvent* e)  override;
    /*public*/ void performMouseClicked(QGraphicsSceneMouseEvent* e);
    /*public*/ void dispose() override;
    QObject* self() override {return (QObject*)this;}

 signals:

 public slots:
    void on_changeAspectAct_toggled3(bool bState);
    void on_cycle3AspectsAct_toggled(bool);
    void on_alternateLitAct_toggled(bool);
    void on_alternateHeldAct_toggled(bool);
    void on_showAppearanceAct_toggled(bool);
    void on_showDarkIconAct_toggled(bool);
    void on_editLogicAction_triggered();
    /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
    //    private SignalHead mHead;
    /*private*/ NamedBeanHandle<SignalHead*>* namedHead;

    QMap<QString, NamedIcon*>* _saveMap;
    Logger* log;
    /*private*/ bool isValidState(QString key);
    QButtonGroup* litButtonGroup;// = NULL;
    SignalHeadItemPanel* _itemPanel;
    /*private*/ void setIcons(QMap<QString, NamedIcon *> *map);
    SwingPropertyChangeSupport* pcs;
    void addPropertyChangeListener(PropertyChangeListener*);
    void removePropertyChangeListener(PropertyChangeListener*);
 protected:
#if 0 // not needed since scaling and rotating is done by QT's QGraphicsScene
    /*protected*/ void rotateOrthogonal();
#endif
    ///*protected*/ void editItem();
    /*protected*/ int clickMode;// = 3;
    /*protected*/ bool litMode;// = false;
 protected slots:
    /*protected*/ void editItem();
    /*protected*/ void edit();
    friend class SHIconDragJLabel;
    friend class AddIconActionListener;
};

class SHIAddIconActionListener : public QObject, public ActionListener
{
  Q_OBJECT
  Q_INTERFACES(ActionListener)
 SignalHeadIcon* parent;
public:
SHIAddIconActionListener(SignalHeadIcon* parent) {
  this->parent = parent;
 }
 QObject* self() override {return (QObject*)this;}
 public slots:
 void actionPerformed(JActionEvent */*e*/ = 0)override
 {
  parent->updateSignal();
 }
};


class MyActionListener : public QObject, public ActionListener
{
  Q_OBJECT
  Q_INTERFACES(ActionListener)
  SignalHeadIcon* shi;
 public:
  MyActionListener(SignalHeadIcon* shi)
  {
   this->shi = shi;
  }
  QObject* self() override {return (QObject*)this;}
public slots:
  /*public*/ void actionPerformed(JActionEvent* /*a*/ = 0)override
  {
   shi->updateItem();
  }
};

#endif // SIGNALHEADICON_H
