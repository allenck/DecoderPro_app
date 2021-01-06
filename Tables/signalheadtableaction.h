#ifndef SIGNALHEADTABLEACTION_H
#define SIGNALHEADTABLEACTION_H

#include <QObject>
#include <QFrame>
#include <QComboBox>
#include <QLabel>
#include <QStringList>
#include <QList>
#include <QGroupBox>
#include "flowlayout.h"
#include "logger.h"
#include <QMenu>
#include "abstracttableaction.h"
#include "libtables_global.h"
#include "beantabledatamodel.h"

class PropertyChangeEvent;
class JActionEvent;
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
    Q_INVOKABLE explicit SignalHeadTableAction(QObject *parent = 0);
    Q_INVOKABLE /*public*/ SignalHeadTableAction(QString s, QObject *parent);
    ~SignalHeadTableAction() {}
    SignalHeadTableAction(const SignalHeadTableAction& that) : AbstractTableAction(that.text(), that.parent()) {}
    /*protected*/ void addPressed(ActionEvent* e=0);
    /*public*/ void setEnabled(bool newValue);
    /*public*/ void dispose();
    Q_INVOKABLE /*public*/ QString getClassDescription();
signals:
    void propertyChange(PropertyChangeEvent *);
public slots:
    void typeChanged();
    void okPressed(JActionEvent* e = nullptr);
    void cancelPressed(JActionEvent*  e = nullptr);
    void updatePressed(JActionEvent* e = nullptr);
    //void on_editMenuWindow_aboutToShow();
    //void on_addMenuWindow_aboutToShow();
    static QString getName();

private:
    /*private*/ JTextField* systemNameTextField;// = new JTextField(5);
    /*private*/ JTextField* userNameTextField;// = new JTextField(10);
    /*private*/ JTextField* ato1TextField;// = new JTextField(5);
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
 /*private*/ QString tripleOutput;// = Bundle.getMessage("StringTripleOutput");
 /*private*/ QString tripleTurnout;// = Bundle.getMessage("StringTripleTurnout");
 /*private*/ QString doubleTurnout;// = Bundle.getMessage("StringDoubleTurnout");
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
 /*private*/ QGroupBox* v1Border;// = BorderFactory.createTitledBorder(blackline);
 /*private*/ QGroupBox* v2Border;// = BorderFactory.createTitledBorder(blackline);
 /*private*/ QGroupBox* v3Border;// = BorderFactory.createTitledBorder(blackline);
 /*private*/ QGroupBox* v4Border;// = BorderFactory.createTitledBorder(blackline);
 /*private*/ QGroupBox* v5Border;// = BorderFactory.createTitledBorder(blackline);
 /*private*/ QGroupBox* v6Border;// = BorderFactory.createTitledBorder(blackline);
 /*private*/ QGroupBox* v7Border;// = BorderFactory.createTitledBorder(blackline);
 FlowLayout* defaultFlow;// = new QFormLayout();
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

 /*private*/ int turnoutStateFromBox(QComboBox* box);
 /*private*/ void setTurnoutStateInBox(QComboBox* box, int state, QList<int> iTurnoutStates);
 int signalheadTypeFromBox(QComboBox* box);
 void setSignalheadTypeInBox (QComboBox* box, int state, QList<int>iSignalheadTypes);

protected:
 /*protected*/ Turnout* getTurnoutFromPanel(BeanSelectCreatePanel* bp, QString reference);
 /*protected*/ Turnout* updateTurnoutFromPanel(BeanSelectCreatePanel* bp, QString reference, Turnout* oldTurnout, QString title);
 /*protected*/ QString getClassName();
 /*protected*/ void setTitle();
 /*protected*/ QString helpTarget();
 /*protected*/ void createModel();


friend class SignalHeadWidget;
friend class SHBeanTableDataModel;
};
Q_DECLARE_METATYPE(SignalHeadTableAction)

class SHBeanTableDataModel : public BeanTableDataModel
{
 Q_OBJECT
    SignalHeadTableAction* self;
public:
    SHBeanTableDataModel(SignalHeadTableAction* self);
    enum COLUMNS
    {
     LITCOL = NUMCOLUMN,
     HELDCOL = LITCOL+1,
     EDITCOL = HELDCOL+1
    };
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
    /*public*/ QString getValue(QString name) const;
    /*public*/ Manager* getManager();
    /*public*/ NamedBean* getBySystemName(QString name) const;
    /*public*/ NamedBean* getByUserName(QString name);
    /*public*/ void clickOn(NamedBean* t);
    /*public*/ QPushButton* configureButton();
    /*public*/ void configureTable(JTable *table);
    /*public*/ bool matchPropertyName(PropertyChangeEvent* e);

private:
    Logger* log;
protected:
    /*protected*/ QString getMasterClassName();
    /*protected*/ QString getBeanType();
};



#endif // SIGNALHEADTABLEACTION_H
