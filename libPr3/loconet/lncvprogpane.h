#ifndef LNCVPROGPANE_H
#define LNCVPROGPANE_H
#include "lnpanel.h"
#include "loconetlistener.h"
#include "jtogglebutton.h"
#include "jbutton.h"
#include "jtextfield.h"
#include "jcheckbox.h"
#include "jtable.h"
#include "lncvprogtablemodel.h"
#include "jlabel.h"
#include "jtextarea.h"
#include "tablerowsorter.h"

class LncvProgPane : public LnPanel, public LocoNetListener
{
  Q_OBJECT
  Q_INTERFACES(LocoNetListener)
 public:
  Q_INVOKABLE LncvProgPane(QWidget* parent = nullptr);
  ~LncvProgPane() {}
  LncvProgPane(const LncvProgPane& ): LnPanel() {}
  ///*public*/ static /*final*/ int ROW_HEIGHT;// = (new JButton("X").getPreferredSize().height)*9/10;
  /*public*/ QString getHelpTarget() override;
  /*public*/ QString getTitle() override;
  /*public*/ void initComponents() override;
  /*public*/ /*synchronized*/ void initComponents(LocoNetSystemConnectionMemo* memo) override;
  /*public*/ void copyEntry(int art, int mod);
  /*public*/ void allProgFinished(QString error);
  /*public*/ void dispose() override;

 public slots:
  /*public*/ void allProgButtonActionPerformed();
  /*public*/ void modProgButtonActionPerformed();
  /*public*/ void readButtonActionPerformed();
  /*public*/ void writeButtonActionPerformed();
  /*public*/ /*synchronized*/ void message(LocoNetMessage* l) override;

 private:
  static Logger* log;
  /*private*/ LocoNetSystemConnectionMemo* memo = nullptr;
  bool writeConfirmed = false;
  /*private*/ /*final*/ QString rawDataCheck = /*this.getClass().getName()*/QString("jmri.jmrix.swing.lncvprog.LncvProgPane") + ".RawData"; // NOI18N
  /*private*/ UserPreferencesManager* pm = nullptr;
  /*private*/ /*transient*/ TableRowSorter/*<LncvProgTableModel*>*/* sorter;
  /*private*/ LncvDevicesManager* lncvdm = nullptr;

  /*private*/ bool allProgRunning = false;
  /*private*/ int moduleProgRunning = -1; // stores module address as int during moduleProgramming session, -1 = no session
  /*private*/ int inDomain(QString entry, int max);

 protected:
  /*protected*/ JToggleButton* allProgButton = new JToggleButton();
  /*protected*/ JToggleButton* modProgButton = new JToggleButton();
  /*protected*/ JButton* readButton = new JButton(tr("Read"));
  /*protected*/ JButton* writeButton = new JButton(tr("Write"));
  /*protected*/ JTextField* articleField = new JTextField(4);
  /*protected*/ JTextField* addressField = new JTextField(4);
  /*protected*/ JTextField* cvField = new JTextField(4);
  /*protected*/ JTextField* valueField = new JTextField(4);
  /*protected*/ JCheckBox* rawCheckBox = new JCheckBox(tr("Show Raw"));
  /*protected*/ JTable* moduleTable = nullptr;
  /*protected*/ LncvProgTableModel* moduleTableModel = nullptr;
  /*protected*/ JPanel* tablePanel = nullptr;
  /*protected*/ JLabel* statusText1 = new JLabel();
  /*protected*/ JLabel* statusText2 = new JLabel();
  /*protected*/ JLabel* articleFieldLabel = new JLabel(tr("Article Number:"), JLabel::RIGHT);
  /*protected*/ JLabel* addressFieldLabel = new JLabel(tr("ModuleAddress"), JLabel::RIGHT);
  /*protected*/ JLabel* cvFieldLabel = new JLabel(tr("%1").arg(tr("Cv")), JLabel::RIGHT);
  /*protected*/ JLabel* valueFieldLabel = new JLabel(tr("%1").arg(tr("Value")), JLabel::RIGHT);
  /*protected*/ JTextArea* result = new JTextArea(6,50);
  /*protected*/ QString reply = "";
  /*protected*/ int art;
  /*protected*/ int adr = 1;
  /*protected*/ int cv = 0;
  /*protected*/ int val;
  /*protected*/ JPanel* initNotesPanel();
  /*protected*/ JPanel* initStatusPanel();
  /*protected*/ JPanel* initButtonPanel();
  /*protected*/ QString getArticleEntry();
  /*protected*/ QString getAddressEntry();
  /*protected*/ QString getMonitorContents();
  /*protected*/ void setCvFields(int cvNum, int cvVal);
  /*protected*/ /*synchronized*/ LncvDevice* getModule(int i);

  friend class LncvProgPaneTest;
};
Q_DECLARE_METATYPE(LncvProgPane)
#endif // LNCVPROGPANE_H
