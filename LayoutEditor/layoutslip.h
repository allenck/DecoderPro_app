#ifndef LAYOUTSLIP_H
#define LAYOUTSLIP_H
#include "layoutturnout.h"
#include "instancemanager.h"
#include "liblayouteditor_global.h"
#include <QComboBox>

class TestState;
class JmriBeanComboBox;
class InstanceManager;
/*static*/ class LIBLAYOUTEDITORSHARED_EXPORT TurnoutState
{
 public:
 int turnoutA;// = Turnout::CLOSED;
 int turnoutB;// = Turnout::CLOSED;
 QComboBox* turnoutABox;
 QComboBox* turnoutBBox;

 TurnoutState(int turnoutA, int turnoutB)
 {
  turnoutA = Turnout::CLOSED;
  turnoutB = Turnout::CLOSED;
  turnoutABox = NULL;
  turnoutBBox = NULL;

  this->turnoutA = turnoutA;
  this->turnoutB = turnoutB;
 }

 int getTurnoutAState()
 {
  return turnoutA;
 }

 int getTurnoutBState()
 {
  return turnoutB;
 }

 void setTurnoutAState(int state)
 {
  turnoutA = state;
 }

 void setTurnoutBState(int state){
    turnoutB = state;
 }

 QComboBox* getComboA();

 QComboBox* getComboB();

 int getTestTurnoutAState()
 {
  if(turnoutABox->currentIndex()==0)
      return Turnout::CLOSED;
  return Turnout::THROWN;
 }

 int getTestTurnoutBState()
 {
  if(turnoutBBox->currentIndex()==0)
   return Turnout::CLOSED;
  return Turnout::THROWN;
 }

 void updateStatesFromCombo()
 {
  if(turnoutABox==NULL || turnoutBBox==NULL)
  {
   return;
  }
  if(turnoutABox->currentIndex()==0)
  {
   turnoutA= Turnout::CLOSED;
  }
  else
  {
   turnoutA=Turnout::THROWN;
  }
  if(turnoutBBox->currentIndex()==0)
  {
   turnoutB= Turnout::CLOSED;
  }
  else
  {
   turnoutB=Turnout::THROWN;
  }
 }

 bool equals(TurnoutState* ts)
 {
    if(ts->getTurnoutAState()!=this->getTurnoutAState())
        return false;
    if(ts->getTurnoutBState()!=this->getTurnoutBState())
        return false;
    return true;
 }

};

class LIBLAYOUTEDITORSHARED_EXPORT LayoutSlip : public LayoutTurnout
{
    Q_OBJECT
public:
    //explicit LayoutSlip(QObject *parent = 0);
    /**
     * constructor method
     */
    /*public*/ LayoutSlip(QString id, QPointF c, double rot, LayoutEditor* myPanel, int type);
    /*public*/ void setTurnoutType(int slipType);
 /*public*/ void setSlipType(int slipType);
    /*public*/ int getSlipType();
    /*public*/ int getSlipState();
    /*public*/ QString getTurnoutBName() ;
    /*public*/ Turnout* getTurnoutB();
    /*public*/ void setTurnoutB(QString tName);
    /*public*/ QString getDisplayName();
    /**
     * Toggle slip states if clicked on, physical turnout exists, and
     *    not disabled
     */
    /*public*/ void toggleState();

    // operational instance variables (not saved between sessions)

//    /*final*/ /*public*/ const static int UNKNOWN = /*Turnout::UNKNOWN*/0x01;
//    /*final*/ /*public*/ const static int STATE_AC;// = 0x02;
//    /*final*/ /*public*/ const static int STATE_BD;// = 0x04;
//    /*final*/ /*public*/ const static int STATE_AD;// = 0x06;
//    /*final*/ /*public*/ const static int STATE_BC;// = 0x08;
    enum STATES
    {
     UNKNOWN = 0x01,
     STATE_AC = 0x02,
     STATE_BD = 0x04,
     STATE_AD = 0x06,
     STATE_BC = 0x08
    };
    /*public*/ int currentState;// = UNKNOWN;
    /*public*/ QPointF getCoordsCenter();
    /*public*/ QPointF getCoordsA() ;
    /*public*/ QPointF getCoordsB() ;
    /*public*/ QPointF getCoordsC();
    /*public*/ QPointF getCoordsD();
    /*public*/ void reCheckBlockBoundary();
    void removeSML(QString signalMast);
    /**
     * Methods to test if mainline track or not
     *  Returns true if either connecting track segment is mainline
     *  Defaults to not mainline if connecting track segments are missing
     */
    /*public*/ bool isMainline();
    /**
     * Modify coordinates methods
     */;
    /*public*/ void setCoordsCenter(QPointF p);
    /*public*/ void setCoordsA(QPointF p);
    /*public*/ void setCoordsB(QPointF p);
    /*public*/ void setCoordsC(QPointF p);
    /*public*/ void setCoordsD(QPointF p);
    /*public*/ void scaleCoords(float xFactor, float yFactor);
    double round (double x);
    /*public*/ void setObjects(LayoutEditor* p);
    void drawSlipState(int state, QPainter* painter);
    /**
     * Clean up when this object is no longer needed.  Should not
     * be called while the object is still displayed; see remove()
     */
    void dispose();
    /**
     * Removes this object from display and persistance
     */
    void remove();
    void disableSML(QString signalMast);
    /**
     * "active" means that the object is still displayed, and should be stored.
     */
    /*public*/ bool isActive();
    /*public*/ bool singleSlipStraightEqual();
    /*public*/ int getTurnoutState(Turnout* turn, int state);
    /*public*/ int getTurnoutState(int state);
    /*public*/ int getTurnoutBState(int state);
    /*public*/ void setTurnoutStates(int state, QString turnStateA, QString turnStateB);
    //Internal call to update the state of the slip depending upon the turnout states.
    /*public*/ QVector<QString>* getBlockBoundaries();

signals:
    
public slots:
  void on_removeAction_triggered();
  void on_rotate_triggered();
  void updateState();
  void OnEditAction();
  void on_setSignalsAct_triggered();
  void on_setSignalMastsAct_triggered();
  void on_setSensorsAct_triggered();
  /*public*/ void toggleStateTest();
  void slipEditDonePressed(ActionEvent* a = 0);
  void slipEditCancelPressed(ActionEvent* a = 0);

private:
    /*private*/ QString turnoutBName;//="";
    /*private*/ NamedBeanHandle<Turnout*>* namedTurnoutB;// = NULL;
    /*private*/ PropertyChangeListener* mTurnoutListener;// = NULL;
    void init();
    void setTurnoutState(TurnoutState* ts);
    /**
     * Activate/Deactivate turnout to redraw when turnout state changes
     */
    /*private*/ void activateTurnout();
    /*private*/ void deactivateTurnout();
    /*private*/ void updateBlockInfo();
    QMenu* popup;// = NULL;
    LayoutEditorTools* tools;// = NULL;
 Logger log;
 int testState;// = UNKNOWN;
 bool active;// = true;
 QHash <int, TurnoutState*>* turnoutStates;// = new QHash<int, TurnoutState>(4);
 // variables for Edit slip Crossing pane
 QPushButton* slipEditDone;
 QPushButton* slipEditCancel;
 QPushButton* turnoutEditBlock;
 bool editOpen;// = false;
 /*private*/ JmriBeanComboBox* turnoutAComboBox;
 /*private*/ JmriBeanComboBox* turnoutBComboBox;
 TestState* testPanel;

protected:
 /*protected*/ void showPopUp(QGraphicsSceneMouseEvent* e, bool editable);
 /*protected*/ void editLayoutSlip(LayoutTurnout* o);

friend class LoadXml;
friend class LayoutEditor;
friend class TestState;
};

class SampleStates : public QWidget
{
 Q_OBJECT
 int state;
 LayoutSlip* parent;
public:
// Methods, constructors, fields.
    SampleStates(int state, LayoutSlip* parent);
    /*public*/ void paintEvent(QPaintEvent* event);
};
class TestState : public QWidget
{
 Q_OBJECT
 LayoutSlip* parent;
public:
 TestState(LayoutSlip* parent);
 /*public*/ void paintEvent(QPaintEvent* event) ;
};

#endif // LAYOUTSLIP_H
