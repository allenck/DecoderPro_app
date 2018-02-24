#include "usbview.h"
#include "jtree.h"
#include "usbtreemodel.h"
#include "loggerfactory.h"
#include <qsplitter.h>
#include <QVBoxLayout>
#include <jtextarea.h>
#include "usb_bus.h"
#include "userpreferencesmanager.h"
#include "instancemanager.h"
#include <QMenu>
#include <QMenuBar>

//UsbView::UsbView()
//{

//}

// /*public*/ class UsbView extends JFrame {

// /*private*/ /*static*/ /*final*/ long UsbView::serialVersionUID = 4693554326612734263L;
/*private*/ /*static*/ /*final*/ int UsbView::APP_WIDTH = 600;
/*private*/ /*static*/ /*final*/ int UsbView::APP_HIGHT = 800;

/*public*/ UsbView::UsbView(QWidget* parent)  : JFrame(parent){
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial javax/swing/JFrame."<init>":()V
     * 4: aload_0
     * 5: aconst_null
     * 6: putfield      ch/ntb/usb/usbView/UsbView.jContentPane:Ljavax/swing/JPanel;
     * 9: aload_0
     * 10: aconst_null
     * 11: putfield      ch/ntb/usb/usbView/UsbView.jJMenuBar:Ljavax/swing/JMenuBar;
     * 14: aload_0
     * 15: aconst_null
     * 16: putfield      ch/ntb/usb/usbView/UsbView.commandsMenu:Ljavax/swing/JMenu;
     * 19: aload_0
     * 20: aconst_null
     * 21: putfield      ch/ntb/usb/usbView/UsbView.exitMenuItem:Ljavax/swing/JMenuItem;
     * 24: aload_0
     * 25: aconst_null
     * 26: putfield      ch/ntb/usb/usbView/UsbView.updateMenuItem:Ljavax/swing/JMenuItem;
     * 29: aload_0
     * 30: aconst_null
     * 31: putfield      ch/ntb/usb/usbView/UsbView.usbTree:Ljavax/swing/JTree;
     * 34: aload_0
     * 35: aconst_null
     * 36: putfield      ch/ntb/usb/usbView/UsbView.jSplitPane:Ljavax/swing/JSplitPane;
     * 39: aload_0
     * 40: aconst_null
     * 41: putfield      ch/ntb/usb/usbView/UsbView.jPropertiesArea:Ljavax/swing/JTextArea;
     * 44: aload_0
     * 45: invokespecial ch/ntb/usb/usbView/UsbView.initialize:()V
     * 48: return
     *  */
    // </editor-fold>
 log = LoggerFactory::getLogger("UsbView");
 setTitle(tr("Usb Device Viewer"));
 jSplitPane = new QSplitter();
 //jPropertiesArea = new JTextArea;
 //jPropertiesArea->setTabSize(16);
 pref = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 if(pref->getSaveWindowLocation(QString(this->metaObject()->className())))
 {
  this->move(pref->getWindowLocation(QString(this->metaObject()->className())));
 }
 if(pref->getSaveWindowSize(QString(this->metaObject()->className())))
 {
  this->resize(pref->getWindowSize(QString(this->metaObject()->className())));
 }

 initialize();
}

/*private*/ void UsbView::initialize()
{
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: iconst_3
     * 2: invokevirtual ch/ntb/usb/usbView/UsbView.setDefaultCloseOperation:(I)V
     * 5: aload_0
     * 6: aload_0
     * 7: invokespecial ch/ntb/usb/usbView/UsbView.getJJMenuBar:()Ljavax/swing/JMenuBar;
     * 10: invokevirtual ch/ntb/usb/usbView/UsbView.setJMenuBar:(Ljavax/swing/JMenuBar;)V
     * 13: aload_0
     * 14: sipush        600
     * 17: sipush        800
     * 20: invokevirtual ch/ntb/usb/usbView/UsbView.setSize:(II)V
     * 23: aload_0
     * 24: aload_0
     * 25: invokespecial ch/ntb/usb/usbView/UsbView.getJContentPane:()Ljavax/swing/JPanel;
     * 28: invokevirtual ch/ntb/usb/usbView/UsbView.setContentPane:(Ljava/awt/Container;)V
     * 31: aload_0
     * 32: ldc           USB View
     * 34: invokevirtual ch/ntb/usb/usbView/UsbView.setTitle:(Ljava/lang/String;)V
     * 37: aload_0
     * 38: new           ch/ntb/usb/usbView/UsbView$1
     * 41: dup
     * 42: aload_0
     * 43: invokespecial ch/ntb/usb/usbView/UsbView$1."<init>":(Lch/ntb/usb/usbView/UsbView;)V
     * 46: invokevirtual ch/ntb/usb/usbView/UsbView.addWindowListener:(Ljava/awt/event/WindowListener;)V
     * 49: return
     *  */
    // </editor-fold>
 resize(APP_WIDTH,APP_HIGHT);
 QWidget* treePanel = new QWidget();
 treePanel->setMinimumWidth( 300);
 QVBoxLayout* treePanelLayout = new QVBoxLayout(treePanel);
 usbTree = getUsbTree();

 treePanelLayout->addWidget(usbTree);
 jSplitPane->addWidget(treePanel);

 getContentPane()->layout()->addWidget(jSplitPane);

 jContentPane = getContentPane();
 jPropertiesArea = getJPropertiesArea();
 jSplitPane->addWidget(jPropertiesArea);
 getJJMenuBar()->addMenu(getFileMenu());
 adjustSize();
}

/*private*/ QWidget* UsbView::getJContentPane() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/usbView/UsbView.jContentPane:Ljavax/swing/JPanel;
     * 4: ifnonnull     45
     * 7: aload_0
     * 8: new           javax/swing/JPanel
     * 11: dup
     * 12: invokespecial javax/swing/JPanel."<init>":()V
     * 15: putfield      ch/ntb/usb/usbView/UsbView.jContentPane:Ljavax/swing/JPanel;
     * 18: aload_0
     * 19: getfield      ch/ntb/usb/usbView/UsbView.jContentPane:Ljavax/swing/JPanel;
     * 22: new           java/awt/BorderLayout
     * 25: dup
     * 26: invokespecial java/awt/BorderLayout."<init>":()V
     * 29: invokevirtual javax/swing/JPanel.setLayout:(Ljava/awt/LayoutManager;)V
     * 32: aload_0
     * 33: getfield      ch/ntb/usb/usbView/UsbView.jContentPane:Ljavax/swing/JPanel;
     * 36: aload_0
     * 37: invokespecial ch/ntb/usb/usbView/UsbView.getJSplitPane:()Ljavax/swing/JSplitPane;
     * 40: ldc           Center
     * 42: invokevirtual javax/swing/JPanel.add:(Ljava/awt/Component;Ljava/lang/Object;)V
     * 45: aload_0
     * 46: getfield      ch/ntb/usb/usbView/UsbView.jContentPane:Ljavax/swing/JPanel;
     * 49: areturn
     *  */
    // </editor-fold>
 QWidget* pane = new QWidget();
 QVBoxLayout* paneLayout = new QVBoxLayout(pane);
 paneLayout->addWidget(jPropertiesArea);

 return pane;
}

/*private*/ QMenuBar* UsbView::getJJMenuBar() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/usbView/UsbView.jJMenuBar:Ljavax/swing/JMenuBar;
     * 4: ifnonnull     30
     * 7: aload_0
     * 8: new           javax/swing/JMenuBar
     * 11: dup
     * 12: invokespecial javax/swing/JMenuBar."<init>":()V
     * 15: putfield      ch/ntb/usb/usbView/UsbView.jJMenuBar:Ljavax/swing/JMenuBar;
     * 18: aload_0
     * 19: getfield      ch/ntb/usb/usbView/UsbView.jJMenuBar:Ljavax/swing/JMenuBar;
     * 22: aload_0
     * 23: invokespecial ch/ntb/usb/usbView/UsbView.getFileMenu:()Ljavax/swing/JMenu;
     * 26: invokevirtual javax/swing/JMenuBar.add:(Ljavax/swing/JMenu;)Ljavax/swing/JMenu;
     * 29: pop
     * 30: aload_0
     * 31: getfield      ch/ntb/usb/usbView/UsbView.jJMenuBar:Ljavax/swing/JMenuBar;
     * 34: areturn
     *  */
    // </editor-fold>
 if(menuBar() == NULL)
  setMenuBar(new QMenuBar());
 return menuBar();
}

/*private*/ QMenu* UsbView::getFileMenu()
{
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/usbView/UsbView.commandsMenu:Ljavax/swing/JMenu;
     * 4: ifnonnull     51
     * 7: aload_0
     * 8: new           javax/swing/JMenu
     * 11: dup
     * 12: invokespecial javax/swing/JMenu."<init>":()V
     * 15: putfield      ch/ntb/usb/usbView/UsbView.commandsMenu:Ljavax/swing/JMenu;
     * 18: aload_0
     * 19: getfield      ch/ntb/usb/usbView/UsbView.commandsMenu:Ljavax/swing/JMenu;
     * 22: ldc           Commands
     * 24: invokevirtual javax/swing/JMenu.setText:(Ljava/lang/String;)V
     * 27: aload_0
     * 28: getfield      ch/ntb/usb/usbView/UsbView.commandsMenu:Ljavax/swing/JMenu;
     * 31: aload_0
     * 32: invokespecial ch/ntb/usb/usbView/UsbView.getUpdateMenuItem:()Ljavax/swing/JMenuItem;
     * 35: invokevirtual javax/swing/JMenu.add:(Ljavax/swing/JMenuItem;)Ljavax/swing/JMenuItem;
     * 38: pop
     * 39: aload_0
     * 40: getfield      ch/ntb/usb/usbView/UsbView.commandsMenu:Ljavax/swing/JMenu;
     * 43: aload_0
     * 44: invokespecial ch/ntb/usb/usbView/UsbView.getExitMenuItem:()Ljavax/swing/JMenuItem;
     * 47: invokevirtual javax/swing/JMenu.add:(Ljavax/swing/JMenuItem;)Ljavax/swing/JMenuItem;
     * 50: pop
     * 51: aload_0
     * 52: getfield      ch/ntb/usb/usbView/UsbView.commandsMenu:Ljavax/swing/JMenu;
     * 55: areturn
     *  */
    // </editor-fold>
 QMenu* fileMenu = new QMenu();
 QAction* act = new QAction("Expand All", this);
 fileMenu->addAction(act);
 return fileMenu;
}

/*private*/ QMenu* UsbView::getExitMenuItem() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/usbView/UsbView.exitMenuItem:Ljavax/swing/JMenuItem;
     * 4: ifnonnull     42
     * 7: aload_0
     * 8: new           javax/swing/JMenuItem
     * 11: dup
     * 12: invokespecial javax/swing/JMenuItem."<init>":()V
     * 15: putfield      ch/ntb/usb/usbView/UsbView.exitMenuItem:Ljavax/swing/JMenuItem;
     * 18: aload_0
     * 19: getfield      ch/ntb/usb/usbView/UsbView.exitMenuItem:Ljavax/swing/JMenuItem;
     * 22: ldc           Exit
     * 24: invokevirtual javax/swing/JMenuItem.setText:(Ljava/lang/String;)V
     * 27: aload_0
     * 28: getfield      ch/ntb/usb/usbView/UsbView.exitMenuItem:Ljavax/swing/JMenuItem;
     * 31: new           ch/ntb/usb/usbView/UsbView$2
     * 34: dup
     * 35: aload_0
     * 36: invokespecial ch/ntb/usb/usbView/UsbView$2."<init>":(Lch/ntb/usb/usbView/UsbView;)V
     * 39: invokevirtual javax/swing/JMenuItem.addActionListener:(Ljava/awt/event/ActionListener;)V
     * 42: aload_0
     * 43: getfield      ch/ntb/usb/usbView/UsbView.exitMenuItem:Ljavax/swing/JMenuItem;
     * 46: areturn
     *  */
    // </editor-fold>
 return NULL;
}

/*private*/ QMenu* UsbView::getUpdateMenuItem()
{
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/usbView/UsbView.updateMenuItem:Ljavax/swing/JMenuItem;
     * 4: ifnonnull     56
     * 7: aload_0
     * 8: new           javax/swing/JMenuItem
     * 11: dup
     * 12: invokespecial javax/swing/JMenuItem."<init>":()V
     * 15: putfield      ch/ntb/usb/usbView/UsbView.updateMenuItem:Ljavax/swing/JMenuItem;
     * 18: aload_0
     * 19: getfield      ch/ntb/usb/usbView/UsbView.updateMenuItem:Ljavax/swing/JMenuItem;
     * 22: ldc           Update
     * 24: invokevirtual javax/swing/JMenuItem.setText:(Ljava/lang/String;)V
     * 27: aload_0
     * 28: getfield      ch/ntb/usb/usbView/UsbView.updateMenuItem:Ljavax/swing/JMenuItem;
     * 31: bipush        116
     * 33: iconst_0
     * 34: iconst_1
     * 35: invokestatic  javax/swing/KeyStroke.getKeyStroke:(IIZ)Ljavax/swing/KeyStroke;
     * 38: invokevirtual javax/swing/JMenuItem.setAccelerator:(Ljavax/swing/KeyStroke;)V
     * 41: aload_0
     * 42: getfield      ch/ntb/usb/usbView/UsbView.updateMenuItem:Ljavax/swing/JMenuItem;
     * 45: new           ch/ntb/usb/usbView/UsbView$3
     * 48: dup
     * 49: aload_0
     * 50: invokespecial ch/ntb/usb/usbView/UsbView$3."<init>":(Lch/ntb/usb/usbView/UsbView;)V
     * 53: invokevirtual javax/swing/JMenuItem.addActionListener:(Ljava/awt/event/ActionListener;)V
     * 56: aload_0
     * 57: getfield      ch/ntb/usb/usbView/UsbView.updateMenuItem:Ljavax/swing/JMenuItem;
     * 60: areturn
     *  */
    // </editor-fold>
 return NULL;
}

void UsbTreeView::rowsInserted(const QModelIndex &parent, int start, int end)
{
 if(!QTreeView::isExpanded(parent))
  expand(parent);
 QAbstractItemView::rowsInserted(parent, start, end);
}

/*private*/ UsbTreeView* UsbView::getUsbTree() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/usbView/UsbView.usbTree:Ljavax/swing/JTree;
     * 4: ifnonnull     91
     * 7: invokestatic  ch/ntb/usb/LibusbJava.usb_init:()V
     * 10: invokestatic  ch/ntb/usb/LibusbJava.usb_find_busses:()I
     * 13: pop
     * 14: invokestatic  ch/ntb/usb/LibusbJava.usb_find_devices:()I
     * 17: pop
     * 18: invokestatic  ch/ntb/usb/LibusbJava.usb_get_busses:()Lch/ntb/usb/Usb_Bus;
     * 21: astore_1
     * 22: aload_0
     * 23: new           ch/ntb/usb/usbView/UsbTreeModel
     * 26: dup
     * 27: aload_1
     * 28: aload_0
     * 29: getfield      ch/ntb/usb/usbView/UsbView.jPropertiesArea:Ljavax/swing/JTextArea;
     * 32: invokespecial ch/ntb/usb/usbView/UsbTreeModel."<init>":(Lch/ntb/usb/Usb_Bus;Ljavax/swing/JTextArea;)V
     * 35: putfield      ch/ntb/usb/usbView/UsbView.treeModel:Lch/ntb/usb/usbView/UsbTreeModel;
     * 38: aload_0
     * 39: new           javax/swing/JTree
     * 42: dup
     * 43: aload_0
     * 44: getfield      ch/ntb/usb/usbView/UsbView.treeModel:Lch/ntb/usb/usbView/UsbTreeModel;
     * 47: invokespecial javax/swing/JTree."<init>":(Ljavax/swing/tree/TreeModel;)V
     * 50: putfield      ch/ntb/usb/usbView/UsbView.usbTree:Ljavax/swing/JTree;
     * 53: aload_0
     * 54: aload_0
     * 55: getfield      ch/ntb/usb/usbView/UsbView.usbTree:Ljavax/swing/JTree;
     * 58: invokevirtual ch/ntb/usb/usbView/UsbView.expandAll:(Ljavax/swing/JTree;)V
     * 61: aload_0
     * 62: getfield      ch/ntb/usb/usbView/UsbView.usbTree:Ljavax/swing/JTree;
     * 65: aload_0
     * 66: getfield      ch/ntb/usb/usbView/UsbView.treeModel:Lch/ntb/usb/usbView/UsbTreeModel;
     * 69: invokevirtual javax/swing/JTree.addTreeSelectionListener:(Ljavax/swing/event/TreeSelectionListener;)V
     * 72: aload_0
     * 73: invokespecial ch/ntb/usb/usbView/UsbView.getJTestAppPopup:()V
     * 76: aload_0
     * 77: getfield      ch/ntb/usb/usbView/UsbView.usbTree:Ljavax/swing/JTree;
     * 80: new           ch/ntb/usb/usbView/UsbView$4
     * 83: dup
     * 84: aload_0
     * 85: invokespecial ch/ntb/usb/usbView/UsbView$4."<init>":(Lch/ntb/usb/usbView/UsbView;)V
     * 88: invokevirtual javax/swing/JTree.addMouseListener:(Ljava/awt/event/MouseListener;)V
     * 91: aload_0
     * 92: getfield      ch/ntb/usb/usbView/UsbView.usbTree:Ljavax/swing/JTree;
     * 95: areturn
     *  */
    // </editor-fold>
 UsbTreeView* tree = new UsbTreeView();
 Usb_Bus* rootBus = new Usb_Bus();
 treeModel = new UsbTreeModel(rootBus, jPropertiesArea,tree);
 tree->setModel( treeModel);
 tree->setShowsRootHandles(true);
 tree->setRootIsDecorated(true);
 tree->setColumnWidth(0,150);
 tree->setAnimated(true);
 QFont f = tree->font();
 f.setPointSize(8);
 tree->setFont(f);
 connect(tree, SIGNAL(clicked(QModelIndex)), this, SLOT(On_clicked(QModelIndex)));
 treeModel->reload();
 return tree;
}

/*private*/ void UsbView::getJTestAppPopup() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: new           javax/swing/JPopupMenu
     * 4: dup
     * 5: invokespecial javax/swing/JPopupMenu."<init>":()V
     * 8: putfield      ch/ntb/usb/usbView/UsbView.testAppPopup:Ljavax/swing/JPopupMenu;
     * 11: aload_0
     * 12: new           javax/swing/JPopupMenu
     * 15: dup
     * 16: invokespecial javax/swing/JPopupMenu."<init>":()V
     * 19: putfield      ch/ntb/usb/usbView/UsbView.endpointPopup:Ljavax/swing/JPopupMenu;
     * 22: new           javax/swing/JMenuItem
     * 25: dup
     * 26: ldc           Start a test application using this interface
     * 28: invokespecial javax/swing/JMenuItem."<init>":(Ljava/lang/String;)V
     * 31: astore_1
     * 32: aload_1
     * 33: new           ch/ntb/usb/usbView/UsbView$5
     * 36: dup
     * 37: aload_0
     * 38: invokespecial ch/ntb/usb/usbView/UsbView$5."<init>":(Lch/ntb/usb/usbView/UsbView;)V
     * 41: invokevirtual javax/swing/JMenuItem.addActionListener:(Ljava/awt/event/ActionListener;)V
     * 44: aload_0
     * 45: getfield      ch/ntb/usb/usbView/UsbView.testAppPopup:Ljavax/swing/JPopupMenu;
     * 48: aload_1
     * 49: invokevirtual javax/swing/JPopupMenu.add:(Ljavax/swing/JMenuItem;)Ljavax/swing/JMenuItem;
     * 52: pop
     * 53: return
     *  */
    // </editor-fold>
}

/*private*/ QSplitter* UsbView::getJSplitPane() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/usbView/UsbView.jSplitPane:Ljavax/swing/JSplitPane;
     * 4: ifnonnull     74
     * 7: aload_0
     * 8: new           javax/swing/JSplitPane
     * 11: dup
     * 12: invokespecial javax/swing/JSplitPane."<init>":()V
     * 15: putfield      ch/ntb/usb/usbView/UsbView.jSplitPane:Ljavax/swing/JSplitPane;
     * 18: aload_0
     * 19: getfield      ch/ntb/usb/usbView/UsbView.jSplitPane:Ljavax/swing/JSplitPane;
     * 22: iconst_0
     * 23: invokevirtual javax/swing/JSplitPane.setOrientation:(I)V
     * 26: aload_0
     * 27: getfield      ch/ntb/usb/usbView/UsbView.jSplitPane:Ljavax/swing/JSplitPane;
     * 30: iconst_1
     * 31: invokevirtual javax/swing/JSplitPane.setContinuousLayout:(Z)V
     * 34: aload_0
     * 35: getfield      ch/ntb/usb/usbView/UsbView.jSplitPane:Ljavax/swing/JSplitPane;
     * 38: sipush        400
     * 41: invokevirtual javax/swing/JSplitPane.setDividerLocation:(I)V
     * 44: aload_0
     * 45: getfield      ch/ntb/usb/usbView/UsbView.jSplitPane:Ljavax/swing/JSplitPane;
     * 48: aload_0
     * 49: aload_0
     * 50: invokespecial ch/ntb/usb/usbView/UsbView.getJPropertiesArea:()Ljavax/swing/JTextArea;
     * 53: invokespecial ch/ntb/usb/usbView/UsbView.createScrollPane:(Ljava/awt/Component;)Ljavax/swing/JScrollPane;
     * 56: invokevirtual javax/swing/JSplitPane.setBottomComponent:(Ljava/awt/Component;)V
     * 59: aload_0
     * 60: getfield      ch/ntb/usb/usbView/UsbView.jSplitPane:Ljavax/swing/JSplitPane;
     * 63: aload_0
     * 64: aload_0
     * 65: invokespecial ch/ntb/usb/usbView/UsbView.getUsbTree:()Ljavax/swing/JTree;
     * 68: invokespecial ch/ntb/usb/usbView/UsbView.createScrollPane:(Ljava/awt/Component;)Ljavax/swing/JScrollPane;
     * 71: invokevirtual javax/swing/JSplitPane.setTopComponent:(Ljava/awt/Component;)V
     * 74: aload_0
     * 75: getfield      ch/ntb/usb/usbView/UsbView.jSplitPane:Ljavax/swing/JSplitPane;
     * 78: areturn
     *  */
    // </editor-fold>
 return NULL;
}

/*private*/ JTextArea* UsbView::getJPropertiesArea() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/usbView/UsbView.jPropertiesArea:Ljavax/swing/JTextArea;
     * 4: ifnonnull     18
     * 7: aload_0
     * 8: new           javax/swing/JTextArea
     * 11: dup
     * 12: invokespecial javax/swing/JTextArea."<init>":()V
     * 15: putfield      ch/ntb/usb/usbView/UsbView.jPropertiesArea:Ljavax/swing/JTextArea;
     * 18: aload_0
     * 19: getfield      ch/ntb/usb/usbView/UsbView.jPropertiesArea:Ljavax/swing/JTextArea;
     * 22: areturn
     *  */
    // </editor-fold>
 JTextArea* ta = new JTextArea();
 QFont f = ta->font();
 f.setPointSize(8);
 ta->setFont(f);
 ta->setTabSize(16);

 return ta;
}
#if 0
/*private*/ JScrollPane createScrollPane(Component view) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: new           javax/swing/JScrollPane
     * 3: dup
     * 4: aload_1
     * 5: invokespecial javax/swing/JScrollPane."<init>":(Ljava/awt/Component;)V
     * 8: astore_2
     * 9: aload_2
     * 10: areturn
     *  */
    // </editor-fold>
}

/*public*/ static void main(String[] args) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: new           ch/ntb/usb/usbView/UsbView
     * 3: dup
     * 4: invokespecial ch/ntb/usb/usbView/UsbView."<init>":()V
     * 7: astore_1
     * 8: aload_1
     * 9: iconst_1
     * 10: invokevirtual ch/ntb/usb/usbView/UsbView.setVisible:(Z)V
     * 13: return
     *  */
    // </editor-fold>
}
#endif
void UsbView::expandAll(JTree* tree) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: iconst_0
     * 1: istore_2
     * 2: iload_2
     * 3: aload_1
     * 4: invokevirtual javax/swing/JTree.getRowCount:()I
     * 7: if_icmpge     21
     * 10: aload_1
     * 11: iload_2
     * 12: invokevirtual javax/swing/JTree.expandRow:(I)V
     * 15: iinc          2, 1
     * 18: goto          2
     * 21: return
     *  */
    // </editor-fold>
}

void UsbView::On_clicked(QModelIndex index)
{
 DefaultTreeItem *item = static_cast<UsbTreeItem*>(index.internalPointer());
 DeviceFilter f = item->userData.value<DeviceFilter>();
 jPropertiesArea->clear();
 jPropertiesArea->append(tr("Bus:\t%1").arg(f.bus));
 jPropertiesArea->append(tr("Port:\t%1").arg(f.port));
 jPropertiesArea->append(tr("Address:\t%1").arg(f.address));
 jPropertiesArea->append(tr("vid:pid:\t%1:%2").arg((ushort)f.vid,4,16,QLatin1Char('0')).arg((ushort)f.pid,4,16,QLatin1Char( '0' )));
 jPropertiesArea->append(tr("Manufacturer:\t%1").arg(f.manufacturer));
 jPropertiesArea->append(tr("Product:\t%1").arg(f.product));
 jPropertiesArea->append(tr("Serial number:\t%1").arg(f.serialNumber));
 jPropertiesArea->append(tr("Device class:\t%1").arg(f.deviceClass));
 if(f.bHasParent)
 {
  jPropertiesArea->append(tr("Parent:"));
  jPropertiesArea->append(tr("    bus:\t%1").arg(f.parent.bus));
  jPropertiesArea->append(tr("    port:\t%1").arg(f.parent.port));
  jPropertiesArea->append(tr("    address:\t%1").arg(f.parent.address));
  jPropertiesArea->append(QString("  vid:pid:\t%1:%2").arg(f.parent.vid,4,16,QLatin1Char('0')).arg(f.parent.pid,4,16,QLatin1Char('0')));
 }
 jPropertiesArea->append(tr("Has %1 children").arg(item->childCount()));






}
