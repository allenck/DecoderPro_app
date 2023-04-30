#ifndef TREEEDITOR_H
#define TREEEDITOR_H

//#include "logixng/clipboardeditor.h"
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
#include "treepane.h"

class TreeEditor_run9a;
class EditCommentDialog;
class TreeEditor_run7b;
class TreeEditor_run7c;
class TreeEditor_run5;
class TreeEditor_run6;
class TreeEditor_run3;
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

  public slots:
  void executeRun3(TreeEditor_run3* ta);
  void executeRun5(TreeEditor_run5* ta);
  void executeRun6(TreeEditor_run6* ta);
  void executeRun7b(TreeEditor_run7b* ta);
  void executeRun7c(TreeEditor_run7c* ta);
  void executeRun8a(QStringList* errors);
  void executeRun8b(JmriException* ex);
  void executeRun9a(TreeEditor_run9a* ta);


 private:
  static Logger* log;
  /*private*/ /*final*/ LogixNGPreferences* _prefs = (DefaultLogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences");
    /*MutableObject<String>*/QString commentStr;

  ClipboardEditor* _clipboardEditor = nullptr;

  /*private*/ QPointer<JDialog> _renameSocketDialog = nullptr;
  /*private*/ QPointer<JDialog> _selectItemTypeDialog = nullptr;
  /*private*/ QPointer<JDialog> _addItemDialog = nullptr;
  /*private*/ QPointer<JDialog> _editActionExpressionDialog = nullptr;
  /*private*/ QPointer<JDialog> _editLocalVariablesDialog = nullptr;
  /*private*/ QPointer<JDialog> _changeUsernameDialog = nullptr;
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
  /*private*/ JButton* _create=nullptr;
  /*private*/ JButton* _edit=nullptr;

  /*private*/ SwingConfiguratorInterface* _addSwingConfiguratorInterface= nullptr;
  /*private*/ SwingConfiguratorInterface* _addSwingConfiguratorInterfaceMaleSocket=nullptr;
  /*private*/ SwingConfiguratorInterface* _editSwingConfiguratorInterface=nullptr;
  /*private*/ /*final*/ QList<QHash<SwingConfiguratorInterface*, Base*> > _swingConfiguratorInterfaceList = QList<QHash<SwingConfiguratorInterface*, Base*> >();

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
  /*final*/ /*protected*/ void makeAddEditFrame(bool addOrEdit, FemaleSocket* femaleSocket, JButton* button, QString* commentStr);
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
 friend class TreeEditor_run7;
 friend class TreeEditor_run7b;
 friend class TreeEditor_run7c;
 friend class ConditionalNGEditor;
 friend class TE_WindowAdapter;
 friend class TE_WindowAdapter2;
 friend class TE_WindowAdapter3;
 friend class TreeEditor_run8;
 friend class TreeEditor_run9;
 friend class TE_WindowAdapter4;
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
friend class TreeEditor_run9;
}; // TEPopupMenu

class TEClipboardListener : public QObject, public ClipboardEventListener
{
  Q_OBJECT
  TreeEditor* te;
 public:
  TEClipboardListener(TreeEditor* te) {this->te = te;}
  void clipboardEventOccurred()override;
  QObject* self() override {return (QObject*)this;}
};

class TreeEditor_run0b : public ThreadAction
{
    Q_OBJECT
    TreeEditor* _treeEditor;
    TEPopupMenu* _menu;
public:
    TreeEditor_run0b(TreeEditor* _treeEditor, TEPopupMenu* _menu) {
      this->_treeEditor = _treeEditor;
      this->_menu = _menu;
    }
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
 TEPopupMenu* _menu;
public:
    TreeEditor_run0(FemaleSocket* _currentFemaleSocket, TreeEditor* _treeEditor, TEPopupMenu* _menu)  {
        this->_currentFemaleSocket = _currentFemaleSocket;
        this->_treeEditor = _treeEditor;
        this->_menu = _menu;
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
        ThreadingUtil::runOnGUIEventually(new TreeEditor_run0b(_treeEditor, _menu));
    }
};



class TreeEditor_run1 : public ThreadAction
{
  Q_OBJECT
  TreeEditor* treeEditor;
  QString commentStr;
  FemaleSocket* femaleSocket;
  TreePath* path;
  AbstractBase* object;
 public:
  TreeEditor_run1(TreePath* path, FemaleSocket* femaleSocket,QString commentStr, TreeEditor* treeEditor) {
   this->path = path;
   this->treeEditor = treeEditor;
   this->commentStr = commentStr;
   this->femaleSocket= femaleSocket;
  }
  void run();

 signals:
  void startRun3(TreeEditor_run3* ta);

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
  AbstractBase* object;
  public:
  TreeEditor_run3(AbstractBase* object, FemaleSocket* femaleSocket,TreePath* path, TreeEditor* treeEditor) {
   this->object = object;
   this->femaleSocket = femaleSocket;
   this->path = path;
   this->treeEditor = treeEditor;}
  void run();
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
  void run();

  signals:
  void doRun5(TreeEditor_run5*);
  void doRun6(TreeEditor_run6*);

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
  void run();
};

class TreeEditor_run7 : public ThreadAction
{
    Q_OBJECT
    TreeEditor* te;
    MaleSocket* maleSocket;
    FemaleSocket* femaleSocket;
    TreePath* path;
public:
    TreeEditor_run7(FemaleSocket* femaleSocket, TreePath* path, MaleSocket* maleSocket, TreeEditor* te) {
        this->femaleSocket = femaleSocket;
        this->path = path;
        this->maleSocket = maleSocket;
     this->te = te;
    }
    void run();
signals:
    void doRun7b(TreeEditor_run7b*);
    void doRun7c(TreeEditor_run7c*);

};
class TreeEditor_run7b : public ThreadAction
{
    Q_OBJECT
    TreeEditor* te;
    QString uname;
public:
    TreeEditor_run7b(QString uname, TreeEditor* te) {
     this->uname = uname;
     this->te = te;
    }
    void run();
};

class TreeEditor_run7c : public ThreadAction
{
    Q_OBJECT
    TreeEditor* te;
    FemaleSocket* femaleSocket;
    TreePath* path;
public:
    TreeEditor_run7c(FemaleSocket* femaleSocket, TreePath* path, TreeEditor* te) {
     this->te = te;
        this->femaleSocket = femaleSocket;
        this->path = path;
    }
    void run();
};


// handle 'copy'
class TreeEditor_run8 : public ThreadAction
{
    Q_OBJECT
    FemaleSocket* _currentFemaleSocket;
    TreeEditor* te;
public:
    TreeEditor_run8(FemaleSocket* _currentFemaleSocket, TreeEditor* te) {
        this->_currentFemaleSocket = _currentFemaleSocket;
        this->te = te;
    }
    void run();
signals:
    void doRun8a(QStringList* errors);
    void doRun8b(JmriException* ex);
};

// handle 'paste'
class TreeEditor_run9 : public ThreadAction
{
    Q_OBJECT
    TEPopupMenu* _menu;;
    TreeEditor* te;
public:
    TreeEditor_run9(FemaleSocket* _currentFemaleSocket, TreeEditor* te) {
        this->_menu = _menu;
        this->te = te;
    }
    void run();
signals:
    void doRun9a(TreeEditor_run9a* ta);
};

class TreeEditor_run9a : public ThreadAction
{
    Q_OBJECT
    TreePane* _treePane;
    FemaleSocket* _currentFemaleSocket;
    TreePath* _currentPath;
public:
    TreeEditor_run9a(TreePane* _treePane, FemaleSocket* _currentFemaleSocket, TreePath* _currentPath){
        this->_treePane = _treePane;
        this->_currentFemaleSocket = _currentFemaleSocket;
        this->_currentPath = _currentPath;
    }
    void run()
    {
        _treePane->_femaleRootSocket->registerListeners();
        _treePane->updateTree(_currentFemaleSocket, _currentPath->getPath());
   }
};

class TE_WindowAdapter : public WindowAdapter
{
    Q_OBJECT
    TreeEditor* te;
public:
    TE_WindowAdapter(TreeEditor* te) { this->te = te;}
    void windowClosing(QEvent* e)
    {
        te->cancelRenameSocketPressed(nullptr);
    }
};

class TE_WindowAdapter2 : public WindowAdapter
{
    Q_OBJECT
    TreeEditor* te;
public:
    TE_WindowAdapter2(TreeEditor* te) { this->te = te;}
    void windowClosing(QEvent* e)
    {
        te->cancelAddPressed(nullptr);
    }
};
class TE_WindowAdapter3 : public WindowAdapter
{
    Q_OBJECT
    TreeEditor* te;
public:
    TE_WindowAdapter3(TreeEditor* te) {
        this->te = te;}
    void windowClosing(QEvent* e)
    {
        te->_changeUsernameDialog->setVisible(false);
        te->_changeUsernameDialog->dispose();
        te->_changeUsernameDialog = nullptr;

    }
};
class TE_WindowAdapter4 : public WindowAdapter
{
    Q_OBJECT
    TreeEditor* te;
    bool addOrEdit;
public:
    TE_WindowAdapter4(bool addOrEdit, TreeEditor* te) { this->addOrEdit = addOrEdit; this->te = te;}
    void windowClosing(QEvent* e)
    {
        if (addOrEdit) {
            te->cancelCreateItem(nullptr);
        } else {
            te->cancelEditPressed(nullptr);
        }

    }
};

#endif // TREEEDITOR_H
