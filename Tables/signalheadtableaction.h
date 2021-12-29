#ifndef SIGNALHEADTABLEACTION_H
#define SIGNALHEADTABLEACTION_H

#include <QObject>
#include <QFrame>
#include "jcheckbox.h"
#include "jcombobox.h"
#include "jlabel.h"
#include <QStringList>
#include <QList>
#include "flowlayout.h"
#include "logger.h"
#include <QMenu>
#include "abstracttableaction.h"
#include "libtables_global.h"
#include "beantabledatamodel.h"
#include "jspinner.h"
#include "borderfactory.h"

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
    /*public*/ void setEnabled(bool newValue) override;
    /*public*/ void dispose() override;
    Q_INVOKABLE /*public*/ QString getClassDescription() override;
    /*public*/ void dccSignalPanel();

    QObject* self() override {return (QObject*)this;}

signals:
    void propertyChange(PropertyChangeEvent *) override;
public slots:
    void typeChanged();
    void okPressed(JActionEvent* e = nullptr);
    void cancelPressed(JActionEvent*  e = nullptr);
    /*private*/ void cancelNewPressed(JActionEvent*  e = nullptr);
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
  JComboBox* typeBox;
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
  JLabel* systemNameLabel = new JLabel("");
  JLabel* userNameLabel = new JLabel("");
  void hideAllOptions();
  QString gbStyleSheet;
  JPanel* v1Panel = new JPanel();
  JPanel* v2Panel = new JPanel();
  JPanel* v3Panel = new JPanel();
  JPanel* v4Panel = new JPanel();
  JPanel* v5Panel = new JPanel();
  JPanel* v6Panel = new JPanel();
  JPanel* v7Panel = new JPanel();
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
  QComboBox* prefixBox = new QComboBox();
  QLabel* prefixBoxLabel = new QLabel("System : ");
  QLabel* vtLabel;// = new QLabel("");
  /*private*/ /*final*/ Border* blackline = BorderFactory::createLineBorder(Qt::black);
  /*private*/ TitledBorder* v1Border = BorderFactory::createTitledBorder(blackline);
  /*private*/ TitledBorder* v2Border = BorderFactory::createTitledBorder(blackline);
  /*private*/ TitledBorder* v3Border = BorderFactory::createTitledBorder(blackline);
  /*private*/ TitledBorder* v4Border = BorderFactory::createTitledBorder(blackline);
  /*private*/ TitledBorder* v5Border = BorderFactory::createTitledBorder(blackline);
  /*private*/ TitledBorder* v6Border = BorderFactory::createTitledBorder(blackline);
  /*private*/ TitledBorder* v7Border = BorderFactory::createTitledBorder(blackline);
  FlowLayout* defaultFlow;// = new QFormLayout();
  static Logger* log;
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
  void ukAspectChange(bool edit);


  // variables for edit of Signal Heads
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


  JPanel* ev1Panel;// = new JPanel();
  JPanel* ev2Panel;// = new JPanel();
  JPanel* ev3Panel;// = new JPanel();
  JPanel* ev4Panel;// = new JPanel();
  JPanel* ev5Panel;// = new JPanel();
  JPanel* ev6Panel;// = new JPanel();
  JPanel* ev7Panel;// = new JPanel();

  /*private*/ /*final*/ TitledBorder* ev1Border = BorderFactory::createTitledBorder(blackline);
  /*private*/ /*final*/ TitledBorder* ev2Border = BorderFactory::createTitledBorder(blackline);
  /*private*/ /*final*/ TitledBorder* ev3Border = BorderFactory::createTitledBorder(blackline);
  /*private*/ /*final*/ TitledBorder* ev4Border = BorderFactory::createTitledBorder(blackline);
  /*private*/ /*final*/ TitledBorder* ev5Border = BorderFactory::createTitledBorder(blackline);
  /*private*/ /*final*/ TitledBorder* ev6Border = BorderFactory::createTitledBorder(blackline);
  /*private*/ /*final*/ TitledBorder* ev7Border = BorderFactory::createTitledBorder(blackline);

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
  JPanel* _dccSignalPanel;
  JSpinner* dccAspect;
  /*private*/ /*final*/ JCheckBox* dccOffSetAddress = new JCheckBox(tr("OffSet Address"));
  /*private*/ /*final*/ JLabel* dccPacketSendCount = new JLabel(tr("Send Count"));
  /*private*/ /*final*/ JSpinner* dccPacketSendCountSpinner = new JSpinner();
  /*private*/ QVector<JSpinner*> dccAspectEdt;


  /*private*/ int turnoutStateFromBox(QComboBox* box);
  /*private*/ void setTurnoutStateInBox(QComboBox* box, int state, QList<int> iTurnoutStates);
  int signalheadTypeFromBox(QComboBox* box);
  void setSignalheadTypeInBox (QComboBox* box, int state, QList<int>iSignalheadTypes);
  void handleMergSignalDriverOkPressed();

protected:
 /*protected*/ Turnout* getTurnoutFromPanel(BeanSelectCreatePanel* bp, QString reference);
 /*protected*/ Turnout* updateTurnoutFromPanel(BeanSelectCreatePanel* bp, QString reference, Turnout* oldTurnout, QString title);
 /*protected*/ QString getClassName();
 /*protected*/ void setTitle();
 /*protected*/ QString helpTarget()override;
 /*protected*/ void createModel()override;

 protected slots:
  /*protected*/ void addPressed(JActionEvent* /*e*/);


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
    /*public*/ int columnCount(const QModelIndex &parent) const override;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    /*public*/ int getPreferredWidth(int col) override;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
    /*public*/ QVariant data(const QModelIndex &index, int role) const override;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    /*public*/ QString getValue(QString name) const override;
    /*public*/ AbstractManager* getManager() override;
    /*public*/ NamedBean* getBySystemName(QString name) const override;
    /*public*/ NamedBean* getByUserName(QString name) override;
    /*public*/ void clickOn(NamedBean* t) override;
    /*public*/ QPushButton* configureButton() override;
    /*public*/ void configureTable(JTable *table) override;
    /*public*/ bool matchPropertyName(PropertyChangeEvent* e) override;

private:
    Logger* log;
protected:
    /*protected*/ QString getMasterClassName() override;
    /*protected*/ QString getBeanType() override;
};



#endif // SIGNALHEADTABLEACTION_H
