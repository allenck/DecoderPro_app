#ifndef SLIPTURNOUTICON_H
#define SLIPTURNOUTICON_H
#include "positionablelabel.h"
#include "namedbeanhandle.h"
#include <QThread>
#include "windowlistener.h"
#include "propertychangelistener.h"

class SlipIconAdder;
class Turnout;
class SlipTurnoutIcon : public PositionableLabel, public PropertyChangeListener
{
    Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
    explicit SlipTurnoutIcon(Editor* editor, QObject *parent = 0);
    /*public*/ void setTurnout(QString pName, int turn);
    /*public*/ void setTurnout(NamedBeanHandle<Turnout*>* to, int turn);
 enum EW
 {
  WEST = 0x01,
  EAST = 0x02,
  LOWERWEST = 0x04,
  LOWEREAST = 0x06
 };
 enum CONFIG
 {
  DOUBLESLIP = 0x00,
  SINGLESLIP = 0x02,
  THREEWAY = 0x04,
  SCISSOR = 0x08
 };
 /*public*/ void setTurnoutType(int slip);
 /*public*/ int getTurnoutType();
 static bool LOWERWESTtoLOWEREAST;// = false;
 static bool UPPERWESTtoUPPEREAST;// = true;
 /*public*/ bool getSingleSlipRoute();
 /*public*/ void setSingleSlipRoute(bool route) ;
 /*public*/ Turnout* getTurnout(int turn);
 /*public*/ NamedBeanHandle <Turnout*>* getNamedTurnout(int turn);
 /*public*/ NamedIcon* getLowerWestToUpperEastIcon();
 /*public*/ void setLowerWestToUpperEastIcon(NamedIcon* i);
 /*public*/ NamedIcon* getUpperWestToLowerEastIcon();
 /*public*/ void setUpperWestToLowerEastIcon(NamedIcon* i) ;
 /*public*/ NamedIcon* getLowerWestToLowerEastIcon();
 /*public*/ void setLowerWestToLowerEastIcon(NamedIcon* i);
 /*public*/ NamedIcon* getUpperWestToUpperEastIcon();
 /*public*/ void setUpperWestToUpperEastIcon(NamedIcon* i);
 /*public*/ NamedIcon* getInconsistentIcon();
 /*public*/ void setInconsistentIcon(NamedIcon* i);
 /*public*/ NamedIcon* getUnknownIcon();
 /*public*/ void setUnknownIcon(NamedIcon* i);
 /*public*/ int maxHeight() override;
 /*public*/ int maxWidth() override;
 /*public*/ QString getNameString() override;
 /*public*/ bool getTristate();
 /*public*/ void setScale(double s) override;
 /*public*/ void rotate(int deg) override ;
 /*public*/ QString getLWUEText();
 /*public*/ QString getUWLEText();
 /*public*/ QString getLWLEText();
 /*public*/ QString getUWUEText();
 /*public*/ void setLWUEText(QString txt);
 /*public*/ void setUWLEText(QString txt);
 /*public*/ void setLWLEText(QString txt);
 /*public*/ void setUWUEText(QString txt);
 /*public*/ void doMouseClicked(QGraphicsSceneMouseEvent* e) override;
 /*public*/ bool showPopUp(QMenu* popup) override;
 /*public*/ bool setTextEditMenu(QMenu* popup) override;
 /*public*/ void slipTurnoutTextEdit(QString name);
 /*public*/ void dispose() override;
 /*public*/ bool setEditIconMenu(QMenu* popup) override;
 /*public*/ QString getGroupName() override;

 QObject* self() override {return (QObject*)this;}
 QObject* pself() override{return (QObject*)this;}

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e) override;
 /*public*/ void setTristate(bool set);

private:
    /*private*/ SlipTurnoutIcon* s;
    // the associated Turnout object
    /*private*/ NamedBeanHandle<Turnout*>* namedTurnoutWest;// = NULL;
    /*private*/ NamedBeanHandle<Turnout*>* namedTurnoutWestLower;// = NULL;
    /*private*/ NamedBeanHandle<Turnout*>* namedTurnoutEast;// = NULL;
    /*private*/ NamedBeanHandle<Turnout*>* namedTurnoutEastLower;// = NULL;
    /*private*/ bool debug;// = false;
    Logger* log;
    //true for double slip, false for single.
    int turnoutType;// = DOUBLESLIP;
    bool singleSlipRoute;// = false;
    // display icons
    QString lowerWestToUpperEastLName;// = "program:resources/icons/smallschematics/tracksegments/os-slip-lower-west-upper-east.gif";
    NamedIcon* lowerWestToUpperEast;// = new NamedIcon(lowerWestToUpperEastLName, lowerWestToUpperEastLName);
    QString upperWestToLowerEastLName;// = "program:resources/icons/smallschematics/tracksegments/os-slip-upper-west-lower-east.gif";
    NamedIcon* upperWestToLowerEast;// = new NamedIcon(upperWestToLowerEastLName, upperWestToLowerEastLName);
    QString lowerWestToLowerEastLName;// = "program:resources/icons/smallschematics/tracksegments/os-slip-lower-west-lower-east.gif";
    NamedIcon* lowerWestToLowerEast;// = new NamedIcon(lowerWestToLowerEastLName, lowerWestToLowerEastLName);
    QString upperWestToUpperEastLName;// = "program:resources/icons/smallschematics/tracksegments/os-slip-upper-west-upper-east.gif";
    NamedIcon* upperWestToUpperEast;// = new NamedIcon(upperWestToUpperEastLName, upperWestToUpperEastLName);
    QString inconsistentLName;// = "program:resources/icons/smallschematics/tracksegments/os-slip-error-full.gif";
    NamedIcon* inconsistent;// = new NamedIcon(inconsistentLName, inconsistentLName);
    QString unknownLName;// = "resources/icons/smallschematics/tracksegments/os-slip-unknown-full.gif";
    NamedIcon* unknown;// = new NamedIcon(unknownLName, unknownLName);
    int turnoutState();
    /*private*/ bool tristate;// = false;

    QAction* tristateItem;// = NULL;
    void addTristateEntry(QMenu* popup);
    void displayState(int state);
    QString lowerWestToUpperEastText;// = tr("LowerWestToUpperEast");
    QString upperWestToLowerEastText;// = tr("UpperWestToLowerEast");
    QString lowerWestToLowerEastText;// = tr("LowerWestToLowerEast");
    QString upperWestToUpperEastText;// = tr("UpperWestToUpperEast");
    /*private*/ void doDoubleSlipMouseClick();
    /*private*/ void doSingleSlipMouseClick();
    /*private*/ void do3WayMouseClick();
    bool firstStraight;// = false;
    /*private*/ void doScissorMouseClick();
    QHash <Turnout*, int>* _turnoutSetting;// = new QHash <Turnout*, int>();
    bool busy;// = false;
    /*private*/ void setSlip();
    SlipIconAdder* _iconEditor;

private slots:
    /*private*/ void setUpperWestToLowerEast();
    /*private*/ void setLowerWestToUpperEast();
    /*private*/ void setUpperWestToUpperEast();
    /*private*/ void setLowerWestToLowerEast();
    void on_slipTurnoutTextEdit();
    void updateTurnout();

protected:
    /*protected*/ void rotateOrthogonal();
    /*protected*/ QHash<Turnout*, int>* getTurnoutSettings();
    /*protected*/ void reset();
    /*protected*/ void setSlipBusy();
    /*protected*/ void setSlipNotBusy();
    /*protected*/ bool isSlipBusy();
protected slots:
    /*protected*/ void edit();

 friend class SetSlipThread;
 friend class SlipTurnoutActionListener;
 friend class STOWindowListener;
};

class SetSlipThread : public QThread
{
public:
    /*public*/ SetSlipThread(SlipTurnoutIcon* aSlip);
    /*public*/ void run();

private:
    SlipTurnoutIcon* s;
};

class SlipTurnoutActionListener : public QObject, public ActionListener
{
 Q_OBJECT
    Q_INTERFACES(ActionListener)
 SlipTurnoutIcon* sti;
public:
 SlipTurnoutActionListener(SlipTurnoutIcon* sti) { this->sti = sti;}
 QObject* self() override {return (QObject*)this;}
public slots:
 void actionPerformed(JActionEvent */*e*/ = 0) override{ sti->updateTurnout();}
};

class STOWindowListener : public WindowListener
{
 Q_OBJECT
 SlipTurnoutIcon* parent;
public:
 STOWindowListener(SlipTurnoutIcon* parent);
 void windowClosing(QCloseEvent *e);
};

#endif // SLIPTURNOUTICON_H
