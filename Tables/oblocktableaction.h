#ifndef OBLOCKTABLEACTION_H
#define OBLOCKTABLEACTION_H
#include "abstracttableaction.h"
#include "libtables_global.h"
#include "jpanel.h"
#include "jtabbedpane.h"
#include "oblockmanager.h"
#include "oblocktablemodel.h"
#include "instancemanager.h"
#include "portaltablemodel.h"
#include "signaltablemodel.h"
#include "blockportaltablemodel.h"
#include "oblockmanager.h"
#include "oblocktableframe.h"
#include "portaleditframe.h"
#include "signaleditframe.h"
#include "jtextfield.h"
#include "spinnernumbermodel.h"
#include "jcheckbox.h"
#include "actionlistener.h"

class TableFrames;
class LIBTABLESSHARED_EXPORT OBlockTableAction : public AbstractTableAction
{
 Q_OBJECT
public:
 explicit OBlockTableAction(QObject *parent = 0);
 /*public*/ OBlockTableAction(QString actionName, QObject *parent);
 ~OBlockTableAction() {}
 OBlockTableAction(const OBlockTableAction&) : AbstractTableAction() {}
 /*public*/ void setManager(/*@Nonnull*/ Manager/*<OBlock>*/* om) override;
 /*public*/ void addToFrame(/*@Nonnull*/ BeanTableFrame/*<OBlock>*/* f) override;
 /*public*/ JPanel* getPanel() override;
 /*public*/ void setMenuBar(BeanTableFrame/*<OBlock>*/* f) override;
 /*public*/ QString getClassDescription() override;

signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = 0) override;
 /*public*/ void propertyChange(PropertyChangeEvent* e);

private:
 void common();
 // basic table models
     OBlockTableModel* oblocks;
     PortalTableModel* portals;
     SignalTableModel* _signals;
     BlockPortalTableModel* blockportals;
     // tables created on demand inside TableFrames:
     // - BlockPathTable(block)
     // - PathTurnoutTable(block)


     OBlockTableFrame* otf;
     OBlockTablePanel* otp;

     // edit frames
     //OBlockEditFrame oblockFrame; // instead we use NewBean util + Edit
     PortalEditFrame* portalFrame;
     SignalEditFrame* signalFrame;

     /*private*/ void initTableFrames();
     TableFrames* tf = nullptr;
     JTextField* startAddress = new JTextField(10);
     JTextField* userName = new JTextField(40);
     SpinnerNumberModel* rangeSpinner = new SpinnerNumberModel(1, 1, 100, 1); // maximum 100 items
     JSpinner* numberToAddSpinner = new JSpinner(rangeSpinner);
     JCheckBox* rangeBox = new JCheckBox(tr("Add a sequential range"));
     JCheckBox* autoSystemNameBox = new JCheckBox(tr("Automatically generate System Name"));
     JLabel* statusBar = new JLabel(tr("Enter a Hardware Address and (optional) User Name."), JLabel::LEADING);
     UserPreferencesManager* pref;
     JmriJFrame* addOBlockFrame = nullptr;
     // for prefs persistence
     QString systemNameAuto = getClassName() + ".AutoSystemName";
     void handleCreateException(QString sysName);
     void status(QString message, bool warn);
     static Logger* log;
 private slots:
     void cancelObPressed(/*ActionEvent e*/);
     void createObPressed(/*ActionEvent e*/);

 protected:
     /*protected*/ bool _tabbed = false; // updated from prefs
     /*protected*/ JPanel* dataPanel;
     /*protected*/ JTabbedPane* dataTabs;
     /*protected*/ bool init = false;
     /*protected*/ OBlockManager* oblockManager = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
     /*protected*/ PortalManager* portalManager = (PortalManager*)InstanceManager::getDefault("PortalManager");
     // /*protected*/ bool _includeAddButton = true;
     /*protected*/ void createModel() override; // Tabbed
     /*protected*/ void setTitle()override;
     /*protected*/ QString getClassName() override;
     /*protected*/ QString helpTarget();


 protected slots:
     /*protected*/ void addPressed(/*ActionJEvent* e = 0*/) override;
     /*protected*/ void addOBlockPressed(ActionEvent* e = 0);
     void addSignalPressed(ActionEvent* e =0);
     void addPortalPressed(ActionEvent* e =0);

     friend class OTAOkActionListener;
     friend class OTACancelListener;
     friend class OBlockTableActionTest;
};

class OTAOBlockTableFrame : public OBlockTableFrame
{
  Q_OBJECT
  OBlockTableAction* act;
 public:
  OTAOBlockTableFrame(OBlockTablePanel* otp, QString helptarget, OBlockTableAction* act) : OBlockTableFrame(otp, helptarget)
  {
   this->act = act;
  }

   /**
    * Include "Add OBlock..." and "Add XYZ..." buttons
    */
   //@Override
   void extras()  override{
       act->addToFrame(this); //creates multiple sets, wrong level to call
   }
};

//ActionListener okListener = this::createObPressed;
//ActionListener cancelListener = this::cancelObPressed;
class OTAOkActionListener : public ActionListener
{
 Q_OBJECT
 public:
 OBlockTableAction* act;
 OTAOkActionListener(OBlockTableAction* act){this->act = act;}
 public slots:
 void actionPerformed() {act->createObPressed();}
};

class OTACancelListener : public ActionListener
{
 Q_OBJECT
 public:
 OBlockTableAction* act;
 OTACancelListener(OBlockTableAction* act){this->act = act;}
 public slots:
 void actionPerformed() {act->cancelObPressed();}
};

Q_DECLARE_METATYPE(OBlockTableAction)
#endif // OBLOCKTABLEACTION_H
