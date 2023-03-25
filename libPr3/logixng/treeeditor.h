#ifndef TREEEDITOR_H
#define TREEEDITOR_H

#include "logixng/defaultlogixngmanager.h"
#include "treeviewer.h"
//#include "femalesocket.h"
#include "defaultlogixngpreferences.h"
#include "instancemanager.h"
#include "jdialog.h"
#include "jtextfield.h"
#include "jcombobox.h"
#include "jlabel.h"
#include "jcheckbox.h"
#include "jbutton.h"
#include "defaultcomboboxmodel.h"
#include "comparator.h"
#include "swingconfiguratorinterface.h"
#include <QMenu>
#include "jmenuitem.h"
#include "threadingutil.h"
#include "clipboardeventlistener.h"
#include "abstractfemalesocket.h"
#include "joptionpane.h"
#include "threadingutil.h"
#include "runtimeexception.h"
#include "treepane.h"

class TreeEditor_run2;
class TEPopupMenu;
class FemaleSocket;
class ClipboardEventListener;
class ClipboardEditor;
class JTree;
class TreePath;
class PopupMenu;
class SortedComboBoxModel;
class LocalVariableTableModel;
class TreeEditor : public TreeViewer
{
  Q_OBJECT
 public:
  // Enums used to configure TreeEditor
  /*public*/  enum class EnableClipboard { EnableClipboard, DisableClipboard };
  /*public*/  enum class EnableRootRemoveCutCopy { EnableRootRemoveCutCopy, DisableRootRemoveCutCopy };
  /*public*/  enum class EnableRootPopup { EnableRootPopup, DisableRootPopup };
  /*public*/  enum class EnableExecuteEvaluate { EnableExecuteEvaluate, DisableExecuteEvaluate };
  TreeEditor(/*@Nonnull*/ AbstractFemaleSocket *femaleRootSocket,
             EnableClipboard enableClipboard,
             EnableRootRemoveCutCopy enableRootRemoveCutCopy,
             EnableRootPopup enableRootPopup,
             EnableExecuteEvaluate enableExecuteEvaluate,
             QWidget *parent = nullptr);
  /*final*/ /*public*/  void initComponents()override final;
  /*final*/ /*public*/  void openClipboard();
  QString getClassName() override{return "jmri.jmrit.logixng.tools.TreeEditor";}
  static TreeEditor* instance();

 private:
  static Logger* log;
  /*private*/ /*final*/ LogixNGPreferences* _prefs = (DefaultLogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences");

  ClipboardEditor* _clipboardEditor = nullptr;

  /*private*/ JDialog* _renameSocketDialog = nullptr;
  /*private*/ JDialog* _selectItemTypeDialog = nullptr;
  /*private*/ JDialog* _addItemDialog = nullptr;
  /*private*/ JDialog* _editActionExpressionDialog = nullptr;
  /*private*/ JDialog* _editLocalVariablesDialog = nullptr;
  /*private*/ JDialog* _changeUsernameDialog = nullptr;
  /*private*/ /*final*/ JTextField* _socketNameTextField = new JTextField(20);
  /*private*/ /*final*/ JTextField* _systemName = new JTextField(20);
  /*private*/ /*final*/ JTextField* _addUserName = new JTextField(20);
  /*private*/ /*final*/ JTextField* _usernameField = new JTextField(50);
  /*private*/ /*static*/ class SwingConfiguratorInterfaceComparator : public Comparator {
      //@SuppressWarnings("unchecked")
  public:
      /*public*/ int compare(SwingConfiguratorInterface* o1, SwingConfiguratorInterface* o2);
  };

//  /*private*/ /*final*/ Comparator<SwingConfiguratorInterface> _swingConfiguratorComboBoxComparator
//          = (SwingConfiguratorInterface* o1, SwingConfiguratorInterface o2) -> o1.toString().compareTo(o2.toString());

//  /*private*/ /*final*/ SortedComboBoxModel/*<SwingConfiguratorInterface>*/* _swingConfiguratorComboBoxModel
//          = new SortedComboBoxModel(_swingConfiguratorComboBoxComparator);

  /*private*/ /*final*/ JComboBox/*<Category>*/* _categoryComboBox = new JComboBox();
  /*private*/ /*final*/ JComboBox/*<SwingConfiguratorInterface>*/* _swingConfiguratorComboBox = new JComboBox(/*_swingConfiguratorComboBoxModel*/); // TODO:
  /*private*/ /*final*/ JLabel* _renameSocketLabel = new JLabel(tr("Socket name") + ":");  // NOI18N
  /*private*/ /*final*/ JCheckBox* _autoSystemName = new JCheckBox(tr("Automatically generate System Name"));   // NOI18N
  /*private*/ /*final*/ JLabel* _sysNameLabel = new JLabel(tr("System Name") + ":");  // NOI18N
  /*private*/ /*final*/ JLabel* _userNameLabel = new JLabel(tr("User Name") + ":");   // NOI18N
  /*private*/ /*final*/ QString _systemNameAuto = getClassName()+".AutoSystemName";             // NOI18N
  /*private*/ /*final*/ JLabel* _categoryLabel = new JLabel(tr("Category") + ":");  // NOI18N
  /*private*/ /*final*/ JLabel* _typeLabel = new JLabel(tr("Type") + ":");   // NOI18N
  /*private*/ JButton* _create;
  /*private*/ JButton* _edit;

  /*private*/ SwingConfiguratorInterface* _addSwingConfiguratorInterface;
  /*private*/ SwingConfiguratorInterface* _addSwingConfiguratorInterfaceMaleSocket;
  /*private*/ SwingConfiguratorInterface* _editSwingConfiguratorInterface;
  /*private*/ /*final*/ QList<QMap<SwingConfiguratorInterface*, Base*> > _swingConfiguratorInterfaceList = QList<QMap<SwingConfiguratorInterface*, Base*> >();

  /*private*/ LocalVariableTableModel* _localVariableTableModel;

  /*private*/ /*final*/ bool _enableClipboard;
  /*private*/ /*final*/ bool _disableRootRemoveCutCopy;
  /*private*/ /*final*/ bool _disableRootPopup;
  /*private*/ /*final*/ bool _enableExecuteEvaluate;
  /*private*/ void runOnConditionalNGThreadOrGUIThreadEventually(ConditionalNG* conditionalNG, ThreadAction* ta);
  /*private*/ bool checkFemaleSocketOperation(
    FemaleSocket* femaleSocket,
    bool parentIsSystem,
    bool itemIsSystem,
    QString command);
   AbstractFemaleSocket* femaleRootSocket=nullptr;
   static QPointer<TreeEditor> _instance;//= nullptr;

 protected:
  /*protected*/ bool _showReminder = false;
  /*final*/ /*protected*/ void renameSocketPressed(FemaleSocket* femaleSocket, TreePath* path);
  /*final*/ /*protected*/ void addPressed(FemaleSocket* femaleSocket, TreePath* path);
  /*final*/ /*protected*/ void createAddFrame(FemaleSocket* femaleSocket, TreePath* path,
                                              SwingConfiguratorInterface* swingConfiguratorInterface);
  /*final*/ /*protected*/ void editPressed(FemaleSocket* femaleSocket, TreePath* path);
  /*final*/ /*protected*/ void makeAddEditFrame(
    bool addOrEdit,
    FemaleSocket* femaleSocket,
    JButton* button,
    /*MutableObject<String>*/QString commentStr);
  /*final*/ /*protected*/ void editLocalVariables(FemaleSocket* femaleSocket, TreePath* path);
  /*final*/ /*protected*/ void changeUsername(FemaleSocket* femaleSocket, TreePath* path);
  /*final*/ /*protected*/ void autoSystemName();
  /*final*/ /*protected*/ void cancelRenameSocketPressed(JActionEvent* e =nullptr);
  /*final*/ /*protected*/ void cancelAddPressed(JActionEvent* e=nullptr);
  /*final*/ /*protected*/ void cancelCreateItem(JActionEvent* e = nullptr);
  /*final*/ /*protected*/ void cancelEditPressed(JActionEvent* e =nullptr);
  /*protected*/ void executeEvaluate(SwingConfiguratorInterface* swi, MaleSocket* maleSocket);

 friend class TEClipboardListener;
 friend class PopupMenu;
 friend class DeleteBeanWorker2;
 friend class TEPopupMenu;
 friend class DeleteBeanWorker2;
 friend class TreeEditor_run1;
 friend class TreeEditor_run3;
 friend class TreeEditor_run4;
 friend class TreeEditor_run5;
 friend class ConditionalNGEditor;

#if 0
 class TEClipboardListener : public ClipboardEventListener
 {
   Q_OBJECT
   TreeEditor* te;
  public:
   TEClipboardListener(TreeEditor* te)
   {
    //_clipboardEditor->clipboardData.forEach((key, value) -> {
    foreach(QString key, te->_clipboardEditor->clipboardData){
        if (key == ("Finish")) {                  // NOI18N
            te->_clipboardEditor = nullptr;
        }
    }
   }
   QObject* self() override {return (QObject*)this;}
 };
#endif
};
 // This class is copied from BeanTableDataModel
 /*private*/ class DeleteBeanWorker2 : public QObject//: public SwingWorker<void, void> {
 {
   Q_OBJECT
     /*private*/ /*final*/ FemaleSocket* _currentFemaleSocket;
     /*private*/ /*final*/ TreePath* _currentPath;
     MaleSocket* _maleSocket;
     TEPopupMenu* treeEditor;

  public:
     /*public*/  DeleteBeanWorker2(FemaleSocket* currentFemaleSocket, TreePath* currentPath, TEPopupMenu* treeEditor);
     /*public*/  int getDisplayDeleteMsg();
     /*public*/  void setDisplayDeleteMsg(int boo);
     /*public*/  void doDelete();
     /*public*/  void doInBackground();
     /*protected*/ void done();
 };


/*private*/ /*static*/ /*final*/ class SortedComboBoxModel/*<E>*/ :  public DefaultComboBoxModel/*<E>*/ {
 Q_OBJECT
    /*private*/ /*final*/ Comparator/*<E>*/* comparator;
 public:
    /*
     *  Create an empty model that will use the specified Comparator
     */
  /*public*/  SortedComboBoxModel(/*@Nonnull*/ Comparator/*<E>*/* comparator) : DefaultComboBoxModel(){}
    /*public*/  void addElement(QString element);
    /*public*/  void insertElementAt(QString element, int index) ;
};
/*protected*/ class TEPopupMenu : public QMenu, public  ActionListener {
 Q_OBJECT
  Q_INTERFACES(ActionListener)
  /*private*/ static /*final*/ QString ACTION_COMMAND_RENAME_SOCKET;// = "rename_socket";
  /*private*/ static /*final*/ QString ACTION_COMMAND_ADD;// = "add";
  /*private*/ static /*final*/ QString ACTION_COMMAND_REMOVE;// = "remove";
  /*private*/ static /*final*/ QString ACTION_COMMAND_EDIT;// = "edit";
  /*private*/ static /*final*/ QString ACTION_COMMAND_CUT;// = "cut";
  /*private*/ static /*final*/ QString ACTION_COMMAND_COPY;// = "copy";
  /*private*/ static /*final*/ QString ACTION_COMMAND_PASTE;// = "paste";
  /*private*/ static /*final*/ QString ACTION_COMMAND_ENABLE;// = "enable";
  /*private*/ static /*final*/ QString ACTION_COMMAND_DISABLE;// = "disable";
  /*private*/ static /*final*/ QString ACTION_COMMAND_LOCK;// = "lock";
  /*private*/ static /*final*/ QString ACTION_COMMAND_UNLOCK;// = "unlock";
  /*private*/ static /*final*/ QString ACTION_COMMAND_LOCAL_VARIABLES;// = "local_variables";
  /*private*/ static /*final*/ QString ACTION_COMMAND_CHANGE_USERNAME;// = "change_username";
  /*private*/ static /*final*/ QString ACTION_COMMAND_EXECUTE_EVALUATE;// = "execute_evaluate";
//        /*private*/ static final String ACTION_COMMAND_EXPAND_TREE = "expandTree";
/*private*/ /*final*/ JTree* _tree;
//        /*private*/ final FemaleSocketTreeModel _model;
/*private*/ FemaleSocket* _currentFemaleSocket = nullptr;
/*private*/ TreePath* _currentPath = nullptr;

/*private*/ JMenuItem* menuItemRenameSocket;
/*private*/ JMenuItem* menuItemAdd = nullptr;
/*private*/ JMenuItem* menuItemRemove;
/*private*/ JMenuItem* menuItemEdit;
/*private*/ JMenuItem* menuItemCut;
/*private*/ JMenuItem* menuItemCopy;
/*private*/ JMenuItem* menuItemPaste;
/*private*/ /*final*/ QMap<FemaleSocketOperation::TYPES, JMenuItem*> menuItemFemaleSocketOperation
        = QMap<FemaleSocketOperation::TYPES, JMenuItem*>();
/*private*/ JMenuItem* menuItemEnable;
/*private*/ JMenuItem* menuItemDisable;
/*private*/ JMenuItem* menuItemLock;
/*private*/ JMenuItem* menuItemUnlock;
/*private*/ JMenuItem* menuItemLocalVariables;
/*private*/ JMenuItem* menuItemChangeUsername;
/*private*/ JMenuItem* menuItemExecuteEvaluate;
//        /*private*/ JMenuItem* menuItemExpandTree;
TreeEditor* editor;
 /*private*/ void openPopupMenu(QContextMenuEvent* evt);

public:
 TEPopupMenu(TreeEditor* editor);
/*public*/  void actionPerformed(JActionEvent* e = nullptr)override;

QObject* self() override {return(QObject*)this;}
TreeEditor* instance();

private:
/*private*/ void init();
/*private*/ void showPopup(int x, int y, FemaleSocket* femaleSocket, TreePath* path);
/*private*/ bool abortEditAboutSystem(Base* b);
/*private*/ bool checkFemaleSocketOperation(
  FemaleSocket* femaleSocket,
  bool parentIsSystem,
  bool itemIsSystem,
  QString command);
  QPointer<TreeEditor> _instance = nullptr;

 protected:

friend class TreePane;
friend class TreeEditor;
friend class DeleteBeanWorker2;
friend class ConditionalNGEditor;
friend class JTreeOperator;
friend class TreeEditor_run0b;
};

class TEClipboardListener : public QObject, public ClipboardEventListener
{
  Q_OBJECT
  TreeEditor* te;
 public:
  TEClipboardListener(TreeEditor* te) {this->te = te;}
  void clipboardEventOccurred()override
  {
#if 0
   //_clipboardEditor->clipboardData.forEach((key, value) -> {
   foreach(QString key, te->_clipboardEditor->clipboardData){
       if (key == ("Finish")) {                  // NOI18N
           te->_clipboardEditor = nullptr;
       }
   }
#endif
  }
  QObject* self() override {return (QObject*)this;}
};

class TreeEditor_run0b : public ThreadAction
{
    Q_OBJECT
    TreeEditor* _treeEditor;
    TEPopupMenu* _menu;
public:
    TreeEditor_run0b(TreeEditor* _treeEditor) {this->_treeEditor = _treeEditor;}
    void run()
    {
        _treeEditor->_treePane->_femaleRootSocket->registerListeners();
        _treeEditor->_treePane->updateTree(_menu->_currentFemaleSocket, _menu->_currentPath->getPath());

    }
};

class TreeEditor_run0 : public ThreadAction
{
 Q_OBJECT
 FemaleSocket* _currentFemaleSocket;
 TreeEditor* _treeEditor;
public:
    TreeEditor_run0(FemaleSocket* _currentFemaleSocket, TreeEditor* _treeEditor)  {
        this->_currentFemaleSocket = _currentFemaleSocket;
        this->_treeEditor = _treeEditor;
    }
    void run()
    {
        Clipboard* clipboard =
                ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->getClipboard();
        QList<QString>* errors = new QList<QString>();
        MaleSocket* maleSocket = _currentFemaleSocket->getConnectedSocket();
        _currentFemaleSocket->_disconnect();
        if (!clipboard->add(maleSocket, errors)) {
            JOptionPane::showMessageDialog(nullptr,
                    errors->join("<br>"),//String.join("<br>", errors),
                    tr("Error"),
                    JOptionPane::ERROR_MESSAGE);
        }
//        ThreadingUtil::runOnGUIEventually(() -> {
//            _treePane._femaleRootSocket.registerListeners();
//            _treePane.updateTree(_currentFemaleSocket, _currentPath.getPath());
//        });
        ThreadingUtil::runOnGUIEventually(new TreeEditor_run0b(_treeEditor));
    }
};


class TreeEditor_run2 : public RunnableWithBase
{
  Q_OBJECT
  TreePane* _treePane;
  Base* b;

 public:
  TreeEditor_run2(/*Base* b, */TreePane* _treePane) {/*this->b = b;*/ this->_treePane = _treePane;}

  void run(Base* b);
};

class TreeEditor_run3 : public ThreadAction
{
  Q_OBJECT
  TreeEditor* treeEditor;
  TreePath* path;
  FemaleSocket* femaleSocket;
 public:
  TreeEditor_run3(FemaleSocket* femaleSocket,TreePath* path, TreeEditor* treeEditor) {
   this->femaleSocket = femaleSocket;
   this->path = path;
   this->treeEditor = treeEditor;}
  void run();
};

class TreeEditor_run1 : public ThreadAction
{
  Q_OBJECT
  TreeEditor* treeEditor;
  QString commentStr;
  FemaleSocket* femaleSocket;
  TreePath* path;
 public:
  TreeEditor_run1(TreePath* path, FemaleSocket* femaleSocket,QString commentStr, TreeEditor* treeEditor) {
   this->path = path;
   this->treeEditor = treeEditor;
   this->commentStr = commentStr;
   this->femaleSocket= femaleSocket;
  }
  void run()
  {
   QList<QString>* errorMessages = new QList<QString>();

   bool isValid = true;

   if (!treeEditor->_prefs->getShowSystemUserNames()
           || (treeEditor->_systemName->text().isEmpty() && treeEditor->_autoSystemName->isSelected())) {
       treeEditor->_systemName->setText(treeEditor->_addSwingConfiguratorInterface->getAutoSystemName());
   }

   if (treeEditor->_addSwingConfiguratorInterface->getManager()
           ->validSystemNameFormat(treeEditor->_systemName->text()) != Manager::NameValidity::VALID) {
       isValid = false;
       errorMessages->append(tr("Invalid System Name \"%1\"").arg(treeEditor->_systemName->text()));
   }

   isValid &= treeEditor->_addSwingConfiguratorInterface->validate(errorMessages);

   if (isValid) {
       MaleSocket* socket;
       if (treeEditor->_addUserName->text().isEmpty()) {
           socket = treeEditor->_addSwingConfiguratorInterface->createNewObject(treeEditor->_systemName->text(), "");
       } else {
           socket = treeEditor->_addSwingConfiguratorInterface->createNewObject(treeEditor->_systemName->text(), treeEditor->_addUserName->text());
       }
       treeEditor->_addSwingConfiguratorInterfaceMaleSocket->updateObject(socket);
 //                    for (Map.Entry<SwingConfiguratorInterface, Base> entry : _swingConfiguratorInterfaceList) {
 //                        entry.getKey().updateObject(entry.getValue());
 //                    }
       socket->setComment(commentStr/*.getValue()*/);
       try {
           femaleSocket->_connect(socket);
       } catch (SocketAlreadyConnectedException* ex) {
           throw new RuntimeException(ex);
       }
 #if 1
//       femaleSocket->forEntireTree((Base b) -> {
//           b.addPropertyChangeListener(_treePane);
//       });
       femaleSocket->forEntireTree(new TreeEditor_run2( treeEditor->_treePane));

       ThreadingUtil::runOnGUIEventually(/*() -> {*/ new TreeEditor_run3(femaleSocket, path, treeEditor));
//           _addSwingConfiguratorInterface.dispose();
//           _addItemDialog.dispose();
//           _addItemDialog = null;

//           for (TreeModelListener l : _treePane.femaleSocketTreeModel.listeners) {
//               TreeModelEvent tme = new TreeModelEvent(
//                       femaleSocket,
//                       path.getPath()
//               );
//               l.treeNodesChanged(tme);
//           }
//           _treePane._tree.expandPath(path);
//           _treePane._tree.updateUI();

//           InstanceManager.getOptionalDefault(UserPreferencesManager.class).ifPresent((prefMgr) -> {
//               prefMgr.setCheckboxPreferenceState(_systemNameAuto, _autoSystemName.isSelected());
//           });
//       });
   } else {
       QString errorMsg;// = new StringBuilder();
       for (QString s : *errorMessages) {
           if (errorMsg.length() > 0) errorMsg.append("<br>");
           errorMsg.append(s);
       }
       JOptionPane::showMessageDialog(nullptr,
               tr("<html>Invalid data entered<br><br>%1").arg(errorMsg),
               tr("Data is not valid"),
               JOptionPane::ERROR_MESSAGE);
#endif
  }
 }
};
class TreeEditor_run5 : public ThreadAction
{
  Q_OBJECT
  TreeEditor* treeEditor;
  FemaleSocket* femaleSocket;
  Base* object;
  QString commentStr;
  TreePath* path;
 public:
  TreeEditor_run5(Base* object, FemaleSocket* femaleSocket, TreePath* path, QString commentStr, TreeEditor* treeEditor)
  {
   this->object = object;
   this->femaleSocket = femaleSocket;
   this->path = path;
   this->commentStr = commentStr;
   this->treeEditor = treeEditor;
  }
  void run();

};

class TreeEditor_run6 : public ThreadAction
{
  Q_OBJECT
  QString errorMsg;
 public:
  TreeEditor_run6(QString errorMsg) {this->errorMsg = errorMsg;}
  void run()
  {
   JOptionPane::showMessageDialog(nullptr,
           tr("<html>Invalid data entered<br><br>%1").arg(errorMsg),
           tr("Data is not valid"),
           JOptionPane::ERROR_MESSAGE);

  }
};

class TreeEditor_run4 : public ThreadAction
{
  Q_OBJECT
  TreeEditor* treeEditor;
  QString commentStr;
  FemaleSocket* femaleSocket;
  TreePath* path;
  Base* object;
 public:
  TreeEditor_run4(TreePath* path, FemaleSocket* femaleSocket, Base* object, QString commentStr, TreeEditor* treeEditor) {
   this->path = path;
   this->treeEditor = treeEditor;
   this->object = object;
   this->commentStr = commentStr;
   this->femaleSocket= femaleSocket;
  }
  void run()
  {
   QList<QString>* errorMessages = new QList<QString>();

   bool isValid = true;

   if (treeEditor->_editSwingConfiguratorInterface->getManager() != nullptr) {
       if (treeEditor->_editSwingConfiguratorInterface->getManager()
               ->validSystemNameFormat(treeEditor->_systemName->text()) != Manager::NameValidity::VALID) {
           isValid = false;
           errorMessages->append(tr("Invalid System Name \"%1\"").arg(treeEditor->_systemName->text()));
       }
   } else {
       treeEditor->log->debug("_editSwingConfiguratorInterface.getManager() returns null");
   }

   isValid &=treeEditor-> _editSwingConfiguratorInterface->validate(errorMessages);

   if (isValid) {
//       ThreadingUtil.runOnGUIEventually(() -> {
//           femaleSocket->unregisterListeners();

////                            Base object = femaleSocket->getConnectedSocket().getObject();
//           if (_addUserName->text().isEmpty()) {
//               ((NamedBean)object).setUserName(null);
//           } else {
//               ((NamedBean)object).setUserName(_addUserName->text());
//           }
//           ((NamedBean)object).setComment(commentStr.getValue());
//           for (Map.Entry<SwingConfiguratorInterface, Base> entry : _swingConfiguratorInterfaceList) {
//               entry.getKey().updateObject(entry.getValue());
//               entry.getKey().dispose();
//           }
//           for (TreeModelListener l : _treePane.femaleSocketTreeModel.listeners) {
//               TreeModelEvent tme = new TreeModelEvent(
//                       femaleSocket,
//                       path.getPath()
//               );
//               l.treeNodesChanged(tme);
//           }
//           _editActionExpressionDialog.dispose();
//           _editActionExpressionDialog = null;
//           _treePane._tree.updateUI();

////                            if (femaleSocket->isActive()) femaleSocket->registerListeners();
//           if (_treePane._femaleRootSocket.isActive()) {
//               _treePane._femaleRootSocket.registerListeners();
//           }
//       });
//    Base* object, FemaleSocket* femaleSocket, TreePath* path, QString commentStr, TreeEditor* treeEditor
    ThreadingUtil::runOnGUIEventually(new TreeEditor_run5(object, femaleSocket, path, commentStr, treeEditor));
   } else {
       QString errorMsg;// = new StringBuilder();
       for (QString s : *errorMessages) {
           if (errorMsg.length() > 0) errorMsg.append("<br>");
           errorMsg.append(s);
       }
//       ThreadingUtil.runOnGUIEventually(() -> {
//           JOptionPane.showMessageDialog(null,
//                   Bundle.getMessage("<html>Invalid data entered<br><br>%1", errorMsg),
//                   Bundle.getMessage("Data is not valid"),
//                   JOptionPane.ERROR_MESSAGE);
//       });
       ThreadingUtil::runOnGUIEventually(new TreeEditor_run6(errorMsg));
   }

  }
};

#endif // TREEEDITOR_H
