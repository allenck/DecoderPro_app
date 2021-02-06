#ifndef PANEPROGDP3ACTION_H
#define PANEPROGDP3ACTION_H
#include "jmriabstractaction.h"
#include "paneprogframe.h"
#include "paneprogpane.h"
#include "dccaddressvarhandler.h"
#include "combinedlocoseltreepane.h"
#include "progservicemodecombobox.h"

#include <QObject>
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT ThisProgPane : public PaneProgPane
{
 Q_OBJECT
/**
*
*/
//private static final long serialVersionUID = 8855795459526662034L;
public:
/*public*/ ThisProgPane(PaneContainer* parent, QString name, QDomElement pane, CvTableModel* cvModel, VariableTableModel* varModel, QDomElement modelElem, RosterEntry* re);
/*public*/ void setCVValue(QString cv, int value);
/*public*/ void setVariableValue(QString variable, int value);
/*public*/ void dispose();
public slots:
 void On_readAllButton_clicked(bool);
 void On_writeAllButton_clicked(bool);

};
class EnumVariableValue;
class ThisProgPane;
class QPushButton;
class DccAddressPanel;
class JTextField;
class QRadioButton;
class DecoderFile;
class RosterEntry;
class JmriJFrame;
//class CombinedLocoSelTreePane;
class ProgModeSelector;
class LIBPR3SHARED_EXPORT PaneProgDp3Action : public JmriAbstractAction, public ProgListener
{
 Q_OBJECT
 Q_INTERFACES(ProgListener)
public:
 PaneProgDp3Action();
    ~PaneProgDp3Action();
    PaneProgDp3Action(const PaneProgDp3Action& other) : JmriAbstractAction(other.text(), other.icon(), (WindowInterface*)other.parent()) {}
    /*public*/ PaneProgDp3Action(QString s, WindowInterface* wi);
    /*public*/ PaneProgDp3Action(QString s, QIcon i, WindowInterface* wi);
    /*public*/ PaneProgDp3Action(QObject* parent);
    /*public*/ PaneProgDp3Action(QString s, QObject* parent);
    /*public*/ void windowClosing(QCloseEvent* we);
    /*public*/ JmriPanel* makePanel() override;
    /*synchronized*/ /*public*/ BusyGlassPane* getBusyGlassPane();
    QObject* self() {return (QObject*)this;}

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ bool isBusy();
    /*public*/ void paneFinished();
private:
    Logger* log;
    QObject *o1, *o2, *o3, *o4;
    JLabel* statusLabel;
    /*final*/ ProgModeSelector* modePane = new ProgServiceModeComboBox();

    void init();
    JmriJFrame* f;
    CombinedLocoSelTreePane* combinedLocoSelTree;
    QString lastSelectedProgrammer;// = this.getClass().getName()+".SelectedProgrammer"; // NOI18N
    QRadioButton* serviceModeProg;
    QRadioButton* editModeProg;
    JTextField* rosterIdField;// = new JTextField(20);
    JTextField* rosterAddressField;// = new JTextField(10);

    RosterEntry* re;

    int teststatus = 0;
    /*synchronized*/ void findDecoderAddress();
    DecoderFile* decoderFile;
    bool shortAddr;// = false;
    int cv29 = 0;
    int cv17 = -1;
    int cv18 = -1;
    int cv19 = 0;
    int cv1 = 0;
    int longAddress;
    QString address = "3";
    QWidget* rosterPanel = NULL;//new QWidget();
    Programmer*          mProgrammer = nullptr;
    CvTableModel*        cvModel      = NULL;
    IndexedCvTableModel* iCvModel     = NULL;
    VariableTableModel*  variableModel;
    DccAddressPanel* dccAddressPanel;
    QDomElement modelElem= QDomElement();
    ThisProgPane* progPane = NULL;
    /*synchronized*/ void setUpRosterPanel();
    bool longMode = false;
    QString newAddr = NULL;
    void updateDccAddress();
    QPushButton* saveBasicRoster;
    bool checkDuplicate();
    void saveRosterEntry() /*throws jmri.JmriException*/;
    // hold refs to variables to check dccAddress
    VariableValue* primaryAddr = NULL;
    VariableValue* extendAddr = NULL;
    EnumVariableValue* addMode = NULL;
    /*public*/ void enableButtons(bool enable);
    /*public*/ void prepGlassPane(JToggleButton* activeButton);
    QString getLocaleAttribute(QDomElement element, QString attrName, QString locale);
    /*final*/ QWidget* bottomPanel;

private slots:
    /*public*/ void actionPerformed(ActionEvent* e = 0);
    //void On_ServiceMode(bool);
    //void On_EditMode();
    //void On_go2();
    /*synchronized*/ /*public*/ void programmingOpReply(int value, int status);
    /*synchronized*/ void finishRead();
    void On_saveBasicRoster();

protected:
    /*protected*/ void startProgrammer(DecoderFile* decoderFile, RosterEntry* re,
                                            QString filename);
    /*protected*/ void openNewLoco();
    /*protected*/ QWidget* layoutRosterSelection();
    /*protected*/ QWidget* layoutDecoderSelection();
    /*protected*/ void selectDecoder(int mfgID, int modelID, int productID);
    /*protected*/ QWidget* createProgrammerSelection();
    /*protected*/ void readCV(QString cv);

 friend class ThisProgPane;
 friend class PPD3CombinedLocoSelTreePane;
 friend class PPD3DccAddressVarHandler;
};

class PPD3CombinedLocoSelTreePane : public CombinedLocoSelTreePane
{
 Q_OBJECT
    /**
     *
     */
   // private static final long serialVersionUID = 587815634507269784L;
 PaneProgDp3Action* pane;
public:
 /*public*/ PPD3CombinedLocoSelTreePane(QLabel *s, ProgModeSelector* selector, PaneProgDp3Action* pane);
public slots:
 void On_go2();
 void On_ServiceMode(bool b);
 void On_EditMode();

private:
 Logger* log;
   protected:
    /*protected*/ void startProgrammer(DecoderFile* decoderFile, RosterEntry* re,
            QString progName);
    /*protected*/ void openNewLoco();
    /*protected*/ QWidget* layoutRosterSelection() ;
    /*protected*/ QWidget* layoutDecoderSelection();
    /*protected*/ void selectDecoder(int mfgID, int modelID, int productID);
    /*protected*/ QWidget* createProgrammerSelection() ;
};

class PPD3PaneProgFrame : public PaneProgFrame
{
 Q_OBJECT
 PPD3CombinedLocoSelTreePane* self;
public:
 PPD3PaneProgFrame(DecoderFile* pDecoderFile, RosterEntry* pRosterEntry, QString frameTitle, QString programmerFile,
                   Programmer* pProg, bool opsMode, PPD3CombinedLocoSelTreePane* parent = 0);

protected:
 /*protected*/ JPanel* getModePane();

};

class PPD3DccAddressVarHandler : DccAddressVarHandler
{
 Q_OBJECT
 PaneProgDp3Action* pane;
public:
    PPD3DccAddressVarHandler(VariableValue* primaryAddr, VariableValue* extendAddr, EnumVariableValue* addMode, PaneProgDp3Action* pane);
public slots:

protected:
    /*protected*/ void doPrimary();
    /*protected*/ void doExtended();
    friend class PaneProgDp3Action;
};

Q_DECLARE_METATYPE(PaneProgDp3Action)
#endif // PANEPROGDP3ACTION_H
