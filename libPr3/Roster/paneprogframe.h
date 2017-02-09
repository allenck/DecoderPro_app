#ifndef PANEPROGFRAME_H
#define PANEPROGFRAME_H

#include "../../LayoutEditor/jmrijframe.h"
#include <QtXml>
#include "logger.h"
#include <QCloseEvent>
#include <QLabel>
#include <QMenu>
//#include "panecontainer.h"
#include "swingshutdowntask.h"


namespace Ui {
class PaneProgFrame;
}

class RosterMediaPane;
class FunctionLabelsPane;
class DecoderFile;
class RosterEntry;
class Programmer;
class CvTableModel;
class IndexedCvTableModel;
class VariableTableModel;
class ResetTableModel;
class PropertyChangeEvent;
class ShutDownTask;
class VariableValue;
class JToggleButton;
class BusyGlassPane;
class DecoderDirtyTask;
class FileDirtyTask;
class RosterEntryPane;
class PaneProgPane;
#include "libPr3_global.h"
class LIBPR3SHARED_EXPORT PaneProgFrame : public JmriJFrame //, PaneContainer
{
    Q_OBJECT

public:
    //explicit ProgramPanel(QWidget *parent = 0);
    PaneProgFrame(DecoderFile* pDecoderFile, RosterEntry* pRosterEntry, QString frameTitle, QString programmerFile, Programmer* pProg, bool opsMode, QWidget* parent = 0);
    ~PaneProgFrame();
    /*public*/ static bool isIncludedFE(QDomElement e, QDomElement aModelElement, RosterEntry* aRosterEntry, QString extraIncludes, QString extraExcludes);
    /*public*/ void windowClosing(QCloseEvent* e = 0);
    void readConfig(QDomElement root, RosterEntry* r);
    void updateDccAddress();
    /*public*/ void newPane(QString name, QDomElement pane, QDomElement modelElem, bool enableEmpty);
    /*public*/ BusyGlassPane* getBusyGlassPane();
    /*public*/ void prepGlassPane(JToggleButton* activeButton) ;
    /*public*/ void paneFinished();
    /*public*/ void enableButtons(bool stat);
    /*public*/ bool isBusy();
    /**
     * invoked by "Read Changes" button, this sets in motion a
     * continuing sequence of "read changes" operations on the
     * panes. Each invocation of this method reads one pane; completion
     * of that request will cause it to happen again, reading the next pane, until
     * there's nothing left to read.
     * <P>
     * @return true if a read has been started, false if the operation is complete.
     */
    /*public*/ bool readChanges();
    /*public*/ bool readAll() ;
    bool doRead();
    /*public*/ bool writeAll();
    /*public*/ bool writeChanges();
    bool doWrite() ;
    /*public*/ void printPanes(/*final*/ bool preview);

    /*public*/ void dispose();
    /*public*/ static void setShowEmptyPanes(bool yes);
    /*public*/ static bool getShowEmptyPanes();
    static bool showEmptyPanes;// = true;
    /*public*/ RosterEntry* getRosterEntry();
    /*public*/ QList<QWidget*> getPaneList();
    void virtual addHelp();
    /*public*/ QSize getPreferredSize();
    /*public*/ QSize getMaximumSize();
    void enableReadButtons();
    static int iLabel;
    static bool  getShowCvNumbers();
    /*public*/ static void setShowCvNumbers(bool yes);

public slots:
    void on_btnReadChangesAllSheets_clicked();
    void on_btnWriteChangesAllSheets_Clicked();
    void on_btnReadAllSheets();
    void on_btnWriteAllSheets();
    void on_actionSave_triggered();
    void on_tabWidget_currentChanged(int);
    void on_btnStore_clicked();
    /**
     * get notification of a variable property change in the pane, specifically "busy" going to
     * false at the end of a programming operation
     * @param e Event, used to find source
     */
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ bool storeFile();
    void OnDccNews(PropertyChangeEvent* );

private:
    Ui::PaneProgFrame *ui;
    bool _opsMode;
    QLabel* progStatus;
    CvTableModel* cvModel;
    IndexedCvTableModel* iCvModel;
    VariableTableModel* variableModel;
    ResetTableModel* resetModel;
    Programmer* mProgrammer;
    RosterEntry* _rosterEntry;
    QString filename;
    QString pProgrammerFile;
    /**
     * Data element holding the 'model' element representing the decoder type
     */
    QDomElement modelElem;// = null;

    QDomElement decoderRoot;// = null;
    QDomElement programmerRoot;// = null;
    Logger* log;
    QVector<int> defaultCvValues;
    QVector<QString> defaultCvNumbers;
    QVector<int> defaultIndexedCvValues;
    RosterEntryPane* _rPane;
    QMenu* resetMenu;
    bool justChanges;
    /*private*/ bool _busy;// = false;
    /*private*/ void setBusy(bool stat);
    bool _read;// = true;
    PaneProgPane* _programmingPane;// = null;
    JToggleButton* readChangesButton;// = new JToggleButton(rbt.getString("ButtonReadChangesAllSheets"));
    JToggleButton* writeChangesButton;// = new JToggleButton(rbt.getString("ButtonWriteChangesAllSheets"));
    JToggleButton* readAllButton;// = new JToggleButton(rbt.getString("ButtonReadAllSheets"));
    JToggleButton* writeAllButton;// = new JToggleButton(rbt.getString("ButtonWriteAllSheets"));
    ShutDownTask* decoderDirtyTask;
    ShutDownTask* fileDirtyTask;
    QList<QWidget*> paneList;
    // hold refs to variables to check dccAddress
    VariableValue* primaryAddr;// = NULL;
    VariableValue* extendAddr;// = NULL;
    VariableValue* addMode;// = NULL;
    BusyGlassPane*       glassPane;
    QWidget* modePane;
    QWidget* tempPane; // passed around during construction
    FunctionLabelsPane* _flPane;
    RosterMediaPane* _rMPane;

    QList<QWidget*>    activeComponents;// = new ArrayList<JComponent>();
    int paneListIndex;
    QFrame* bottom;
    QDomNodeList decoderPaneList;
    void closeEvent(QCloseEvent *);
    void setProgrammingGui(QWidget* pane);
    static bool showCvNumbers;// = false;

protected:
    /*protected*/ void loadDecoderFromLoco(RosterEntry* r);
    /*protected*/ void loadDecoderFile(DecoderFile* df, RosterEntry* re);
    /*protected*/ void loadProgrammerFile(RosterEntry* r);
    /*protected*/ bool checkDirtyDecoder() ;
    /*protected*/ bool checkDirtyFile();
    /*protected*/ void handleDirtyFile();
    /*protected*/ void saveDefaults();
    /*protected*/ QWidget* makeInfoPane(RosterEntry* r);
    /*abstract*/ /*protected*/ virtual QWidget* getModePane() {return NULL;}
    /*protected*/ QWidget* makeFunctionLabelPane(RosterEntry* r);
    /*protected*/ QWidget* makeMediaPane(RosterEntry* r);
    /*protected*/ virtual void pickProgrammerMode(/*@NonNull*/ QDomElement programming);
    /*protected*/ void resetStatus(int newStatus);

protected slots:
    /*protected*/ void installComponents();
    /*protected*/ void resetToDefaults();

 friend class DecoderDirtyTask;
 friend class FileDirtyTask;
 friend class PaneServiceProgFrame;
};
class DecoderDirtyTask : public SwingShutDownTask
{
 Q_OBJECT
public:
    DecoderDirtyTask(QString name, QString warning, QString action, QWidget* component, QObject *parent = 0)
        : SwingShutDownTask(name, warning, action,component, parent)
    {

    }
    /*public*/ bool checkPromptNeeded() { return !((PaneProgFrame*)component)->checkDirtyDecoder(); }
};
class FileDirtyTask : public SwingShutDownTask
{
 Q_OBJECT
public:
    FileDirtyTask(QString name, QString warning, QString action, QWidget* component, QObject *parent = 0)
        : SwingShutDownTask(name, warning, action,component, parent)
    {

    }
    /*public*/ bool checkPromptNeeded() {
        return !((PaneProgFrame*)component)->checkDirtyFile();
    }
    /*public*/ bool doPrompt() {
        bool result = ((PaneProgFrame*)component)->storeFile(); // storeFile false if failed, abort shutdown
        return result;
    }
};
#endif // PANEPROGFRAME_H
