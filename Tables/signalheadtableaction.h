#ifndef SIGNALHEADTABLEACTION_H
#define SIGNALHEADTABLEACTION_H

#include <QObject>
#include <QFrame>
#include <QComboBox>
#include <QLabel>
#include <QStringList>
#include <QList>
#include <QGroupBox>
#include <QFormLayout>
#include "logger.h"
#include <QMenu>
#include "abstracttableaction.h"
#include "libtables_global.h"

class PropertyChangeEvent;
class ActionEvent;
class BeanSelectCreatePanel;
class JTextField;
class JmriJFrame;
class Turnout;
class SignalHead;
class NamedBeanHandleManager;

class LIBTABLESSHARED_EXPORT SignalHeadTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    //explicit SignalHeadTableAction(QObject *parent = 0);
    /*public*/ SignalHeadTableAction(QString s="Signal Table", QObject *parent = 0);
    ~SignalHeadTableAction() {}
    SignalHeadTableAction(const SignalHeadTableAction& that) : AbstractTableAction(that.text(), that.parent()) {}
    /*protected*/ void addPressed(ActionEvent* e=0);
    /*public*/ void setEnabled(bool newValue);
    /*public*/ void dispose();
    /*public*/ QString getClassDescription();
signals:
    void propertyChange(PropertyChangeEvent *);
public slots:
    void typeChanged();
    void okPressed(ActionEvent* e = 0);
    void cancelPressed(ActionEvent*  e = 0);
    void updatePressed(ActionEvent* e = 0);
    void on_editMenuWindow_aboutToShow();
    void on_addMenuWindow_aboutToShow();
    static QString getName();

private:
 BeanSelectCreatePanel* to1;
 BeanSelectCreatePanel* to2;
 BeanSelectCreatePanel* to3;
 BeanSelectCreatePanel* to4;
 BeanSelectCreatePanel* to5;
 BeanSelectCreatePanel* to6;
 BeanSelectCreatePanel* to7;
 JmriJFrame* addFrame;
 QComboBox* typeBox;
 QString acelaAspect;// = tr("Acela Aspect");
 QString se8c4Aspect;// = tr("SE8c 4 Aspect");
 QString quadOutput;// = tr("Quad Output");
 QString tripleTurnout;// = tr("Triple Output");
 QString doubleTurnout;// = tr("Double Output");
 QString virtualHead;// = tr("Virtual");
 QString grapevine;// = tr("Grapevine ");
 QString acela;// = tr("Acela Aspect");
 QString lsDec;// = tr("LDT LS-DEC");
 QString dccSignalDecoder;// = tr("DCC Signal Decoder");
 QString mergSignalDriver;// = tr("Merg Signal Driver");
 QString singleTurnout;// = tr("Single Output");
 QStringList selections;
 QLabel* systemNameLabel;// = new QLabel("");
 QLabel* userNameLabel;// = new QLabel("");
 JTextField* systemName;// = new JTextField(5);
 JTextField* userName;// = new JTextField(10);
 JTextField* ato1;// = new JTextField(5);
 void hideAllOptions();
 QString gbStyleSheet;
 QGroupBox* v1Panel;// = new QWidget();
 QGroupBox* v2Panel;// = new QWidget();
 QGroupBox* v3Panel;// = new QWidget();
 QGroupBox* v4Panel;// = new QWidget();
 QGroupBox* v5Panel;// = new QWidget();
 QGroupBox* v6Panel;// = new QWidget();
 QGroupBox* v7Panel;// = new QWidget();
 QComboBox* s1Box;// = new QComboBox(/*turnoutStates*/);
 QComboBox* s2Box;// = new QComboBox(/*turnoutStates*/);
 QComboBox* s2aBox;// = new QComboBox(/*signalStates*/);
 QComboBox* s3Box;// = new QComboBox(/*turnoutStates*/);
 QComboBox* s3aBox;// = new QComboBox(/*signalStates*/);
 QComboBox* s4Box;// = new QComboBox(/*turnoutStates*/);
 QComboBox* s5Box;// = new QComboBox(/*turnoutStates*/);
 QComboBox* s6Box;// = new QComboBox(/*turnoutStates*/);
 QComboBox* s7Box;// = new QComboBox(/*turnoutStates*/);
 QComboBox* stBox;// = new QComboBox(/*signalheadTypes*/); // Acela signal types
 QComboBox* mstBox;// = new QComboBox(/*ukSignalType*/);
 QComboBox* msaBox;// = new QComboBox(/*ukSignalAspects*/);
 /*final*/ QVector<int> signalStatesValues;/* =  QList<int>() <<
         SignalHead::DARK <<
         SignalHead::RED <<
         SignalHead::LUNAR <<
         SignalHead::YELLOW <<
         SignalHead::GREEN;*/

 QVector<QString> signalStates;/* = new QStringList();
 *signalStates <<
         tr("Dark") <<
         tr("Red") <<
         tr("Lunar") <<
         tr("Yellow"),
         tr("SignalHeadStateGreen");*/

 QString stateThrown;// = InstanceManager.turnoutManagerInstance().getThrownText();
 QString stateClosed;// = InstanceManager.turnoutManagerInstance().getClosedText();
 QStringList turnoutStates;// = QStringList() { stateClosed, stateThrown };
 QList<int> turnoutStateValues;// = Qlist<int>() {Turnout.CLOSED, Turnout.THROWN};

 QString signalheadSingle;// = trg("SINGLE");
 QString signalheadDouble;// = tr("DOUBLE");
 QString signalheadTriple;// = tr("TRIPLE");
 QString signalheadBiPolar;// = tr("BPOLAR");
 QString signalheadWigwag;// = tr("WIGWAG");
 QStringList signalheadTypes;// =  QStringList{signalheadDouble, signalheadTriple,
    //                                     signalheadBiPolar, signalheadWigwag};
 QList<int> signalheadTypeValues;// = QList<int>() <<AcelaNode.DOUBLE, AcelaNode.TRIPLE,
   //                                    AcelaNode.BPOLAR, AcelaNode.WIGWAG;

 QStringList ukSignalAspects;// = QStringList << "2" <<"3" <<"4";
 QStringList ukSignalType;// = QStringList() << "Home" << "Distant";
 QComboBox* prefixBox;// = new QComboBox();
 QLabel* prefixBoxLabel;// = new QLabel("System : ");
 QLabel* vtLabel;// = new QLabel("");
 QFormLayout* defaultFlow;// = new QFormLayout();
 Logger* log;
 int ukSignalAspectsFromBox(QComboBox* box);
 void setUkSignalAspectsFromBox(QComboBox* box, int val);
 QString ukSignalTypeFromBox(QComboBox* box);
 void setUkSignalType(QComboBox* box, QString val);
 bool checkUserName(QString nam);
 NamedBeanHandleManager* nbhm;// = jmri.InstanceManager.getDefault(jmri.NamedBeanHandleManager.class);
 void addTurnoutMessage(QString s1, QString s2);
 bool checkBeforeCreating(QString sysName);
 /*public*/ bool checkIntegerOnly(QString s);
 int signalStateFromBox(QComboBox* box);
 SignalHead* _curSignal;// = NULL;
 void editSignal(SignalHead* head);
 void makeEditSignalWindow();
 QMenu* addWindowMenu;


 // variablws for edit of Signal Heads
 JmriJFrame* editFrame;
 bool editingHead;// = false;
 QString editSysName;
 JTextField* etot;// = new JTextField(5);
 QLabel* signalType;// = new QLabel("XXXX");
 SignalHead* curS;// = NULL;
 QString className;// = "";
 JTextField* eSystemName;// = new JTextField(5);
 JTextField* eUserName;// = new JTextField(10);

 BeanSelectCreatePanel* eto1;
 BeanSelectCreatePanel* eto2;
 BeanSelectCreatePanel* eto3;
 BeanSelectCreatePanel* eto4;
 BeanSelectCreatePanel* eto5;
 BeanSelectCreatePanel* eto6;
 BeanSelectCreatePanel* eto7;


 QGroupBox* ev1Panel;// = new QGroupBox();
 QGroupBox* ev2Panel;// = new QGroupBox();
 QGroupBox* ev3Panel;// = new QGroupBox();
 QGroupBox* ev4Panel;// = new QGroupBox();
 QGroupBox* ev5Panel;// = new QGroupBox();
 QGroupBox* ev6Panel;// = new QGroupBox();
 QGroupBox* ev7Panel;// = new QGroupBox();
 Turnout* et1;// = NULL;
 Turnout* et2;// = NULL;
 Turnout* et3;// = NULL;
 Turnout* et4;// = NULL;
 Turnout* et5;// = NULL;
 Turnout* et6;// = NULL;
 Turnout* et7;// = NULL;


 QLabel* eSystemNameLabel;// = new QLabel("");
 QLabel* eUserNameLabel;// = new QLabel("");
 QLabel* eSysNameLabel;// = new QLabel ("");

 QLabel* evtLabel;// = new QLabel("");
 QComboBox* es1Box;// = new QComboBox(turnoutStates);
 QComboBox* es2Box;// = new QComboBox(turnoutStates);
 QComboBox* es2aBox;// = new QComboBox(signalStates);
 QComboBox* es3Box;// = new QComboBox(turnoutStates);
 QComboBox* es3aBox;// = new QComboBox(signalStates);
 QComboBox* es4Box;// = new QComboBox(turnoutStates);
 QComboBox* es5Box;// = new QComboBox(turnoutStates);
 QComboBox* es6Box;// = new QComboBox(turnoutStates);
 QComboBox* es7Box;// = new QComboBox(turnoutStates);
 QComboBox* estBox;// = new QComboBox(signalheadTypes);
 QComboBox* emstBox;// = new QComboBox(ukSignalType);
 QComboBox* emsaBox;// = new QComboBox(ukSignalAspects);
 void setSignalStateInBox (QComboBox* box, int state);
 QMenu* editWindowMenu;
 bool enabled;
 void noTurnoutMessage(QString s1, QString s2);
 void handleSE8cOkPressed();
 void handleSE8cTypeChanged();
 void handleSE8cEditSignal();
 void handleSE8cUpdatePressed();

protected:
    /*protected*/ Turnout* getTurnoutFromPanel(BeanSelectCreatePanel* bp, QString reference);
     /*protected*/ Turnout* updateTurnoutFromPanel(BeanSelectCreatePanel* bp, QString reference, Turnout* oldTurnout, QString title);
     /*protected*/ QString getClassName();
friend class SignalHeadWidget;
};

#endif // SIGNALHEADTABLEACTION_H
