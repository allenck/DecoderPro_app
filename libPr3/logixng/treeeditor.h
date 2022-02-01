#ifndef TREEEDITOR_H
#define TREEEDITOR_H

#include "treeviewer.h"
#include "femalesocket.h"
#include "logixngpreferences.h"
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
//#include "clipboardeditor.h"

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
  TreeEditor(/*@Nonnull*/ FemaleSocket* femaleRootSocket,
             EnableClipboard enableClipboard,
             EnableRootRemoveCutCopy enableRootRemoveCutCopy,
             EnableRootPopup enableRootPopup,
             EnableExecuteEvaluate enableExecuteEvaluate,
             QWidget *parent = nullptr);
  /*final*/ /*public*/  void initComponents()override final;
  /*final*/ /*public*/  void openClipboard();
  QString getClassName() override{return "jmri.jmrit.logixng.tools.TreeEditor";}
 private:
  static Logger* log;
  /*private*/ /*final*/ LogixNGPreferences* _prefs = (LogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences");

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

 /*private*/ /*static*/ /*final*/ class SortedComboBoxModel/*<E>*/ :public DefaultComboBoxModel/*<E>*/ {
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
 /*protected*/ class PopupMenu : public QMenu, public  ActionListener {
  Q_OBJECT
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
 /*private*/ FemaleSocket* _currentFemaleSocket;
 /*private*/ TreePath* _currentPath;

 /*private*/ JMenuItem* menuItemRenameSocket;
 /*private*/ JMenuItem* menuItemAdd;
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
 public:
 PopupMenu(TreeEditor* editor);
 /*public*/  void actionPerformed(JActionEvent* e = nullptr)override;

 QObject* self() override {return(QObject*)this;}

 private:
 /*private*/ void init();
 /*private*/ void showPopup(int x, int y, FemaleSocket* femaleSocket, TreePath* path);
 /*private*/ bool abortEditAboutSystem(Base* b);

  protected:

 friend class TreePane;
 friend class TreeEditor;
 };
};
#endif // TREEEDITOR_H
