#ifndef WARRANTTABLEACTION_H
#define WARRANTTABLEACTION_H

#include <QObject>
#include "../Tables/tablesframe.h"
#include "abstracttablemodel.h"
#include "abstractaction.h"
#include "swingshutdowntask.h"
#include "opsessionlog.h"
#include "shutdownmanager.h"
#include "warranttableframe.h"
#include "jdialog.h"
#include "liblayouteditor_global.h"
#include "actionlistener.h"
#include "instancemanager.h"

class OPath;
class WTAShutDownTask;
class OpSessionLog;
class NXFrame;
class TrackerTableAction;
class WarrantTableFrame;
class WarrantTableModel;
class WarrantManager;
class Warrant;
class WarrantFrame;
class OBlock;
class JTextArea;
class JDialog;
class QMenu;
class LIBLAYOUTEDITORSHARED_EXPORT WarrantTableAction : public AbstractAction
{
    Q_OBJECT
public:
    explicit WarrantTableAction(QObject *parent = 0);
    static int STRUT_SIZE;// = 10;
    static QMenu* _warrantMenu;
    /*public*/ WarrantTableAction(QString menuOption, QObject *parent = 0);
    ~WarrantTableAction() {}
    /*public*/ static WarrantTableAction* getDefault();
    WarrantTableAction(const WarrantTableAction& other) :AbstractAction(other.text(), other.parent()) {}
    /*public*/ QString checkPathPortals(OBlock* b);
    /*public*/ bool showPathPortalErrors(JTextArea *ta);
    /*synchronized*/ /*public*/ QMenu* makeWarrantMenu(bool edit);
    static /*final*/ QString halt;// = tr("Halt");
    static /*final*/ QString resume;// = tr("Resume");
    static /*final*/ QString abort;// = tr("Abort");
    static /*final*/ QStringList controls;// = {halt, resume, abort};
    /*public*/ void actionPerformed(JActionEvent* e = 0) override;
//    /*synchronized*/ /*public*/ static void closeWarrantFrame(QString key);
    /*synchronized*/ static /*public*/ void mouseClickedOnBlock(OBlock* block);
    /*public*/ static bool checkSharedTurnouts(OBlock* block);
    /*public*/ bool errorCheck();

 public slots:
    /*synchronized*/ /*public*/ void openWarrantFrame(QString key);
    void setStatusText(QString msg, QColor c);
    //void actionPerformed(QString);
signals:

public slots:
    //void On_Ok_clicked();
private:
    /*private*/ static QHash <QString, WarrantFrame*>* _frameMap;// = new HashMap <String, WarrantFrame> ();
    /*private*/ static WarrantTableAction* _instance;
    /*private*/ static QMap <QString, Warrant*> _warrantMap;// = new HashMap <String, Warrant> ();
    ///*private*/ static JTextArea* _textArea;
    /*private*/ static bool _hasErrors;// = false;
    /*private*/ static JDialog* _errorDialog;
    static JTextField*  _startWarrant;// = new JTextField(30);
    static JTextField*  _endWarrant;// = new JTextField(30);
    static JTextField*  _status;// = new JTextField(90);
    static QColor _background;
    QString menuOption;
    //static WarrantTableAction* editWarrantAction;
    Logger* log;
    /*private*/ void concatenate();
    void common();
    QString command;

    /*private*/ static WarrantTableFrame* _tableFrame;
    /*private*/ static OpSessionLog* _log;
    /*private*/ static bool _edit;
    static ShutDownTask*     _shutDownTask;
    /*private*/ static bool sharedTO(OPath* myPath, OPath* path);
    void on_createWarrant_triggered();
    /*private*/ bool _logging = false;

protected:
    /*protected*/ static TrackerTableAction* _trackerTable;
    /*synchronized*/ /*protected*/ static void portalNameChange(QString oldName, QString newName);
    /*synchronized*/ /*protected*/ static void pathNameChange(OBlock* block, QString oldName, QString newName);

    /*protected*/ static WarrantFrame* _openFrame;
    /*protected*/ static NXFrame* _nxFrame;
//    /*synchronized*/ /*protected*/ static void closeWarrantFrame(WarrantFrame* frame);
    /*protected*/ void closeWarrantFrame();
    /*protected*/ void editWarrantFrame(Warrant* w);
    /*synchronized*/ /*protected*/ void updateWarrantMenu();
    /*protected*/ QAction* makeLogMenu();
    /*protected*/ void closeNXFrame();
    /*protected*/ void makeWarrantFrame(Warrant* startW, Warrant* endW);
    /*protected*/ NXFrame* makeNXFrame();
    /*synchronized*/ /*protected*/ void writetoLog(QString text);


    friend class CreateWarrantFrame;
    friend class WarrantTableFrame;
    friend class WarrantTableModel;
    friend class StartLogActionListener;
    friend class StopLogActionListener;
    friend class WTAShutDownTask;
    friend class WarrantFrame;
    friend class TableFrame;
    friend class EditWarrantActionListener;
    friend class MyListener;
    friend class Portal;
    friend class OPath;
};
Q_DECLARE_METATYPE(WarrantTableAction)

class MyListener : /*java.awt.event.WindowAdapter implements*/ public ActionListener
{
 Q_OBJECT
 JDialog* _errorDialog;

public:
 MyListener(JDialog* _errorDialog) { this->_errorDialog = _errorDialog;}
//       /*  java.awt.Window _w;
//         myListener(java.awt.Window w) {
//             _w = w;
//         }  */
 /*public*/ void actionPerformed(JActionEvent* /*e*/)
 {
     _errorDialog->dispose();
 }
};
/*static*/ class CreateWarrantFrame : public JFrame
{
 Q_OBJECT
 WarrantTableAction* parent;
 JTextField* _sysNameBox;
 JTextField* _userNameBox;

 Warrant* _startW;
 Warrant* _endW;
public:
    /*public*/ CreateWarrantFrame(WarrantTableAction* parent = 0);
    /*public*/ void initComponents();
    void concatenate(Warrant* startW, Warrant* endW) ;
private slots:
    void makeWarrant();
};

//class WarrantTableFrame  : public JmriJFrame // implements ActionListener
//{
// Q_OBJECT
// /*private*/ WarrantTableModel*     _model;
// WarrantTableAction* parent;

//public:
//    /*public*/ WarrantTableFrame(WarrantTableAction* parent);
//};

class EditWarrantActionListener : public QObject
{
 Q_OBJECT
 QSignalMapper* editWarrantMapper;
 WarrantTableAction* act;
public:
 EditWarrantActionListener(QSignalMapper* editWarrantMapper, WarrantTableAction* act);
public slots:
 void on_editWarrantMapper(QString);
 void on_createNXWarrantAct();
};
class WTAShutDownTask  : public SwingShutDownTask
{
 Q_OBJECT

public:
 WTAShutDownTask(QString name, QString warning, QString action, QWidget* component, QObject* parent = 0) : SwingShutDownTask(name, warning, action, component, parent) {}
 /*public*/ bool checkPromptNeeded()
 {
  WarrantTableAction::_log->close();
  WarrantTableAction::_log = NULL;
  return true;
 }

};




class CreateNXWarrantActionListener : public ActionListener
{
 Q_OBJECT

public:

public slots:
 void actionPerformed(JActionEvent */*e */= 0)
 {
  WarrantTableFrame::nxAction();
 }
};
//class CreateNewWarrantActionListener : public ActionListener
//{
// Q_OBJECT

//public:

//public slots:
// void actionPerformed(ActionEvent *e = 0)
// {
//  CreateWarrantFrame* f = new CreateWarrantFrame();
//  try
//  {
//   f->initComponents();
//  } catch (Exception ex ) {/*bogus*/ }
//  f->setVisible(true);
// }
//};


#endif // WARRANTTABLEACTION_H
