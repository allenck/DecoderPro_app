#ifndef PANEPROGPANE_H
#define PANEPROGPANE_H

#include <QWidget>
#include "itemlistener.h"
#include <QtXml>
#include <QHBoxLayout>
#include "logger.h"
#include "jtogglebutton.h"
#include <QGridLayout>
#include <QScrollArea>
//#include "panecontainer.h"
#include "propertychangesupport.h"
#include "qualifieradder.h"
#include "libPr3_global.h"

class JPanel;
class HardcopyWriter;
class PaneContainer;
class FnMapPanelESU;
class Attribute;
class RosterEntry;
class GridGlobals;
class Qualifier;
class QTableView;
class CvTableModel;
class IndexedCvTableModel;
class VariableTableModel;
//class PaneContainer;
class VariableValue;
class CvValue;
class PropertyChangeEvent;
class GridBagConstraints;
class FnMapPanel;
class PropertychangeListener;
class LIBPR3SHARED_EXPORT PaneProgPane : public QWidget //, public PaneContainer
{
    Q_OBJECT
public:
    explicit PaneProgPane(QWidget *parent = 0);
    /*public*/ PaneProgPane(PaneContainer* container, QString name, QDomElement pane,
                            CvTableModel* cvModel, /*IndexedCvTableModel* icvModel,*/
                            VariableTableModel* varModel, QDomElement modelElem, RosterEntry* rosterEntry, QWidget *parent = 0);
    virtual ~PaneProgPane() {}
    /*public*/ QString getName();
    /*public*/ QString toString() ;
    void enableReadButtons();
    void enableConfirmButtons();
    /*public*/ int countOpsNeeded(bool read, bool changes);
    /*public*/ QSet<int>* makeOpsNeededSet(bool read, bool changes, QSet<int>* set);
    void enableButtons(bool stat);
    /*public*/ bool readPaneChanges() ;
    /*public*/ void prepReadPane(bool onlyChanges);
    /*public*/ bool readPaneAll() ;
    void setToRead(bool justChanges, bool startProcess) ;
    void setToWrite(bool justChanges, bool startProcess);
    void executeRead(VariableValue* var);
    void executeWrite(VariableValue* var) ;
    bool nextRead() ;
    bool nextConfirm() ;
    /*public*/ bool writePaneChanges() ;
    /*public*/ bool writePaneAll();
    /*public*/ void prepWritePane(bool onlyChanges);
    bool nextWrite();
    /*public*/ void prepConfirmPane(bool onlyChanges);
    /*public*/ bool confirmPaneChanges();
    /*public*/ bool confirmPaneAll();
    /*public*/ bool isBusy();
    /*public*/ void replyWhileProgrammingVar();
    /*public*/ void replyWhileProgrammingCV() ;
    /*public*/ void replyWhileProgrammingIndxCV();
    void restartProgramming();
    //@SuppressWarnings("unchecked")
    /*public*/ virtual QWidget *newColumn(QDomElement element, bool showStdName, QDomElement modelElem);
    /*public*/ QWidget* newRow(QDomElement element, bool showStdName, QDomElement modelElem);
    /*public*/ virtual void newVariable( QDomElement var, QWidget* col,
                             QGridLayout* g, GridBagConstraints* cs, bool showStdName);
    /*public*/ QWidget* getRepresentation(QString name, QDomElement var);
    QWidget* getRep(int i, QString format) ;
    /*public*/ void dispose() ;
    /*public*/ bool includeInPrint();
//    /*public*/ void printPane(HardcopyWriter w);
    void addPropertyChangeListener(PropertyChangeListener* l);
    void removePropertyChangeListener(PropertyChangeListener* l);
    /*public*/ QWidget* newGrid(QDomElement  element, bool showStdName, QDomElement  modelElem);
    /*public*/ QWidget* newGridItem(QDomElement  element, bool showStdName, QDomElement  modelElem, GridGlobals* globs);
    /*public*/ void printPane(HardcopyWriter* w);


signals:
  void notifyPropertyChange(PropertyChangeEvent *e);

public slots:
  void On_readChangesButton_clicked();
  void On_readAllButton_clicked();
  void On_writeChangesButton_clicked();
  void On_writeAllButton_clicked();
  void On_confirmChangesButtonClicked();
  void On_confirmAllButtonClicked();
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void includeInPrint(bool inc);

private:
  QString mName;// = "";
  Logger* log;
  /** list of fnMapping objects to dispose */
  QList<FnMapPanel*>* fnMapList;// = new QList<FnMapPanel*>();
  QList<FnMapPanelESU*>* fnMapListESU;// = new ArrayList<FnMapPanelESU>();
  /** list of JPanel objects to removeAll */
  QList<QWidget*>* panelList;// = new QList<QWidget*>();
  /*private*/ void prepGlassPane(JToggleButton* activeButton);
  bool justChanges;
  // reference to variable being programmed (or NULL if none)
  VariableValue* _programmingVar = nullptr;
  CvValue* _programmingCV = nullptr;
  VariableValue* _programmingIndexedCV = nullptr;
  bool _read = true;

  // busy during read, write operations
  /*private*/ bool _busy = false;
  /*private*/ int retry = 0;
  /*private*/ QWidget* addDccAddressPanel(QDomElement e);
  bool print = false;
  PropertyChangeSupport* changeSupport;
  QString LAST_GRIDX;
  QString LAST_GRIDY;
  void setCvListFromTable();
  QVector<Attribute*> getAttributeList(QDomElement e);
  bool isCvTablePane;// = false;
  QDomElement pane;
  QDomElement modelElem;

private slots:
  void ctorContinue();

protected:
  /*protected*/ CvTableModel* _cvModel;
  /*protected*/ IndexedCvTableModel* _indexedCvModel;
  /*protected*/ VariableTableModel* _varModel;
  /*protected*/ PaneContainer* container;

  bool _cvTable;

  /*protected*/ QFrame* bottom;
  QHBoxLayout* hLayout_bottom;

//    static final java.util.ResourceBundle rbt = jmri.jmrit.symbolicprog.SymbolicProgBundle.bundle();

    /*transient*/ ItemListener* l1;
    /*protected*/ /*transient*/ ItemListener* l2;
    /*transient*/ ItemListener* l3;
    /*protected*/ /*transient*/ ItemListener* l4;
    /*transient*/ ItemListener* l5;
    /*transient*/ ItemListener* l6;
    /**
     * This remembers the variables on this pane for the Read/Write sheet
     * operation.  They are stored as a list of Integer objects, each of which
     * is the index of the Variable in the VariableTable.
     */
    QList<int>* varList;// = new QList<int>();
    int varListIndex;
    /**
     * This remembers the CVs on this pane for the Read/Write sheet
     * operation.  They are stored as a list of Integer objects, each of which
     * is the index of the CV in the CVTable. Note that variables are handled
     * separately, and the CVs that are represented by variables are not
     * entered here.  So far (sic), the only use of this is for the cvtable rep.
     */
    /*protected*/ QList<int>* cvList;// = new qList<int>();
    /*protected*/ int cvListIndex;
    /**
     * This remembers the indexed CVs on this pane for the Read/Write sheet
     * operation.  They are stored as a list of Integer objects, each of which
     * is the index of the indexed CV in the VariableTable. This is done so that
     * we can read/write them as a variable.  So far (sic), the only use of this is
     * for the IndexedCvTable rep.
     */
    QList<int>* indexedCvList;
    // = new QList<int>();/*protected*/
    JToggleButton* readChangesButton;//  = new JToggleButton(rbt.getString("ButtonReadChangesSheet"));
    /*protected*/ JToggleButton* readAllButton;//      = new JToggleButton(rbt.getString("ButtonReadFullSheet"));
    /*protected*/ JToggleButton* writeChangesButton;// = new JToggleButton(rbt.getString("ButtonWriteChangesSheet"));
    /*protected*/ JToggleButton* writeAllButton;//     = new JToggleButton(rbt.getString("ButtonWriteFullSheet"));
    JToggleButton* confirmChangesButton;// = new JToggleButton(rbt.getString("ButtonConfirmChangesSheet"));
    JToggleButton* confirmAllButton;//     = new JToggleButton(rbt.getString("ButtonConfirmFullSheet"));

    int indexedCvListIndex;
    /*protected*/ void setBusy(bool busy);
    /*protected*/ void stopProgramming();
    /*protected*/ QWidget* newGroup(QDomElement  element, bool showStdName, QDomElement  modelElem);
    /*protected*/ void newGridGroup(QDomElement  element, /*final*/ QWidget* c, QGridLayout* g, GridGlobals* globs, bool showStdName, QDomElement  modelElem);
    /*protected*/ RosterEntry* rosterEntry;
    /*protected*/ void makeLabel(QDomElement e, QWidget* c, QGridLayout* g, GridBagConstraints* cs);
    /*protected*/ void makeSoundLabel(QDomElement e, QWidget* c, QGridLayout* g, GridBagConstraints* cs);
    void makeCvTable(GridBagConstraints* cs, QGridLayout* g, QWidget* c);
    void pickFnMapPanel(QWidget* c, QGridLayout* g, GridBagConstraints* cs, QDomElement modelElem);
    /*protected*/ void firePropertyChange(QString propertyName,
                                          QVariant oldValue, QVariant newValue);


 friend class PaneProgFrame;
 friend class ThisProgPane;
 friend class PaneProgPaneTest;
};
class MyQualifierAdder : public QualifierAdder
{
    Q_OBJECT
    PaneProgPane* self;
    QWidget* c;
public:
    MyQualifierAdder(QWidget* c, PaneProgPane* self);
    protected:
      /*protected*/ Qualifier* createQualifier(VariableValue* var, QString relation, QString value) override;
      /*protected*/ void addListener(PropertyChangeListener* qc) override;
};
#endif // PANEPROGPANE_H
