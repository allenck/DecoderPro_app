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
    WarrantTableAction(const WarrantTableAction& other) :AbstractAction(other.text(), other.parent()) {}
    /*public*/ static void initPathPortalCheck();
    /*public*/ static void checkPathPortals(OBlock* b);
    /*public*/ static bool showPathPortalErrors();
    /*synchronized*/ /*public*/ static QMenu* makeWarrantMenu(bool edit, QObject* parent);
    static /*final*/ QString halt;// = tr("Halt");
    static /*final*/ QString resume;// = tr("Resume");
    static /*final*/ QString abort;// = tr("Abort");
    static /*final*/ QStringList controls;// = {halt, resume, abort};
    /*public*/ void actionPerformed(ActionEvent* e = 0);
    /*synchronized*/ /*public*/ static void updateWarrantMenu(QObject* parent);
    /*synchronized*/ /*public*/ static void closeWarrantFrame(QString key);
    /*synchronized*/ static /*public*/ void mouseClickedOnBlock(OBlock* block);
    /*public*/ static bool checkSharedTurnouts(OBlock* block);

 public slots:
    /*synchronized*/ /*public*/ static void openWarrantFrame(QString key);
    void setStatusText(QString msg, QColor c);
    //void actionPerformed(QString);
signals:

public slots:
    //void On_Ok_clicked();
private:
    /*private*/ static QHash <QString, WarrantFrame*>* _frameMap;// = new HashMap <String, WarrantFrame> ();
    /*private*/ static WarrantTableAction* _instance;
    /*private*/ static QMap <QString, Warrant*> _warrantMap;// = new HashMap <String, Warrant> ();
    /*private*/ static JTextArea* _textArea;
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
    static WarrantTableAction* getInstance();
    /*private*/ static OpSessionLog* _log;
    /*private*/ static bool _edit;
    static ShutDownTask*     _shutDownTask;
    /*private*/ static bool sharedTO(OPath* myPath, OPath* path);
    void on_createWarrant_triggered();

protected:
    /*protected*/ static TrackerTableAction* _trackerTable;
    /*synchronized*/ /*protected*/ static void portalNameChange(QString oldName, QString newName);
    /*synchronized*/ /*protected*/ static void pathNameChange(OBlock* block, QString oldName, QString newName);

    /*protected*/ static WarrantFrame* _openFrame;
    /*protected*/ static NXFrame* _nxFrame;
    /*protected*/ static QAction* makeLogMenu();
    /*synchronized*/ /*protected*/ static void writetoLog(QString text);
    /*synchronized*/ /*protected*/ static void newWarrantFrame(WarrantFrame* frame);
    /*synchronized*/ /*protected*/ static void closeWarrantFrame(WarrantFrame* frame);


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
 /*public*/ void actionPerformed(ActionEvent* e)
 {
     WarrantTableAction::getInstance()->_hasErrors = false;
     WarrantTableAction::getInstance()->_textArea = NULL;
     _errorDialog->close();
 }
//         /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//             _hasErrors = false;
//             _textArea = NULL;
//             _errorDialog.dispose();
//         }
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

public:
 EditWarrantActionListener(QSignalMapper* editWarrantMapper);
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

class StartLogActionListener : public ActionListener
{
 Q_OBJECT

public:
 StartLogActionListener()
 {
  WarrantTableAction::_log = OpSessionLog::getInstance();
//  if (!WarrantTableAction::_log->showFileChooser(OpSessionLog::getInstance()))
//  {
//   WarrantTableAction::_log = NULL;
//   return;
//  }
  if (WarrantTableAction::_shutDownTask == NULL)
  {
   WarrantTableAction::_shutDownTask = new WTAShutDownTask("PanelPro Save default icon check", NULL, NULL, NULL, (QObject*)this);
//      {
//          public bool checkPromptNeeded() {
//              _log.close();
//              _log = NULL;
//              return true;
//          }
//      };
   InstanceManager::shutDownManagerInstance()->_register(WarrantTableAction::_shutDownTask);
  }
  WarrantTableAction::updateWarrantMenu( this);
}


public slots:
 void actionPerformed(ActionEvent *e = 0)
 {
  WarrantTableAction::_log = OpSessionLog::getInstance();
   if (!WarrantTableAction::_log->showFileChooser(WarrantTableFrame::getInstance()))
   {
    WarrantTableAction::_log = NULL;
    return;
   }
#if 0 // TODO:
   if (WarrantTableAction::_shutDownTask == NULL) {
       WarrantTableAction::_shutDownTask = new SwingShutDownTask("PanelPro Save default icon check",
               NULL, NULL, NULL)
       {
           public boolean checkPromptNeeded() {
               _log.close();
               _log = NULL;
               return true;
           }
       };
       jmri.InstanceManager.shutDownManagerInstance().register(_shutDownTask);
   }
#endif
   WarrantTableAction::updateWarrantMenu(NULL);
  }
};

class StopLogActionListener : public ActionListener
{
 Q_OBJECT

public:
 StopLogActionListener() {}

public slots:
 void actionPerformed(ActionEvent *e = 0)
 {
  WarrantTableAction::_log->close();
  InstanceManager::shutDownManagerInstance()->deregister(WarrantTableAction::_shutDownTask);
  WarrantTableAction::_shutDownTask = NULL;
  WarrantTableAction::_log = NULL;
  WarrantTableAction::updateWarrantMenu(this);

 }

};
class CreateNXWarrantActionListener : public ActionListener
{
 Q_OBJECT

public:

public slots:
 void actionPerformed(ActionEvent *e = 0)
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
