#include "imageindexeditor.h"
#include "catalogtreenode.h"
#include "editor.h"
#include <QMenu>
#include <QMenuBar>
#include "catalogtreemanager.h"
#include "shutdownmanager.h"
#include "swingshutdowntask.h"
#include "instancemanager.h"
#include <QMessageBox>
#include "itempalette.h"
#include "defaultcatalogtreemanager.h"
#include "fileutil.h"
#include "catalogpanel.h"
#include "defaultshutdownmanager.h"
#include "shutdowntask.h"
#include "inputdialog.h"
#include "defaultcatalogtreemanagerxml.h"
#include "dataflavor.h"
#include "directorysearcher.h"
#include "catalogtreemodel.h"
#include "joptionpane.h"

//ImageIndexEditor::ImageIndexEditor(QWidget *parent) :
//    JmriJFrame(parent)
//{
//}
/**
 * A JFrame for creating and editing an Image Index.  This is a singleton class.
 * <P>
 *
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author			Pete Cressman  Copyright 2009
 *
 */
///*public*/ final class ImageIndexEditor extends JmriJFrame {


//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.catalog->CatalogBundle");

    /*public*/ /*static*/ /*final*/ QString ImageIndexEditor::IconDataFlavorMime = /*DataFlavor::javaJVMLocalObjectMimeType*/ QString("text/plain")+
               ";class=jmri.jmrit.catalog.NamedIcon";


//    private ImageIndexEditor() {
//        super();
//    }
/*static*/ ImageIndexEditor* ImageIndexEditor::_instance = NULL;
/*static*/ bool  ImageIndexEditor::_indexChanged = false;
/*static*/ ShutDownTask* 	ImageIndexEditor::_shutDownTask = NULL;

/*private*/ ImageIndexEditor::ImageIndexEditor(QString name, QWidget *parent) : JmriJFrame(name,false, parent)
{
 //super(name);
    log = new Logger("ImageIndexEditor");
}

/*public*/ /*static*/ ImageIndexEditor* ImageIndexEditor::instance(Editor* editor) {
    if (_instance == NULL) {
        _instance = new ImageIndexEditor(tr("Edit/Create Image Index"));
        _instance->init(editor);
    }
    return _instance;
}

/*private*/ void ImageIndexEditor::init(Editor* /*editor*/) {
    QMenuBar* menuBar = new QMenuBar();
    QMenu* findIcon = new QMenu(tr("File"));
    menuBar->addMenu(findIcon);
    QAction* storeItem = new QAction(tr("Store Image Index"),this);
    findIcon->addAction(storeItem);
//    storeItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                storeImageIndex();
//            }
//    });
    connect(storeItem, SIGNAL(triggered()), this, SLOT(storeImageIndex()));

    findIcon->addSeparator();
    QAction* openItem = new QAction(tr("Open a File System Directory"), this);
//    openItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                DirectorySearcher.instance().openDirectory(false);
//            }
//        });
    findIcon->addAction(openItem);
    connect(openItem, SIGNAL(triggered()), this, SLOT(openItem_triggered()));
    QMenu* editMenu = new QMenu(tr("Edit"));
    menuBar->addMenu(editMenu);
    QAction* addItem = new QAction(tr("Add Node"),this);
//    addItem.addActionListener (new ActionListener () {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                addNode();
//            }
//        });
    connect(addItem, SIGNAL(triggered()), this, SLOT(addNode()));
    editMenu->addAction(addItem);
    QAction* renameItem = new QAction(tr("Rename Node"), this);
//    renameItem.addActionListener (new ActionListener () {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                renameNode();
//            }
//        });
    editMenu->addAction(renameItem);
    connect(renameItem, SIGNAL(triggered()), this, SLOT(renameNode()));
    QAction* deleteItem = new QAction(tr("Delete Node"), this);
//    deleteItem.addActionListener (new ActionListener () {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                deleteNode();
//            }
//        });
    connect(deleteItem, SIGNAL(triggered()), this, SLOT(deleteNode()));
    editMenu->addAction(deleteItem);
    setMenuBar(menuBar);

    addHelpMenu("package.jmri.jmrit.catalog->ImageIndex", true);

    QWidget* mainPanel = new QWidget();
    mainPanel->setLayout(new QVBoxLayout(mainPanel/*, BoxLayout.Y_AXIS*/));
    QWidget* labelPanel = new QWidget();
    labelPanel->setLayout(new QHBoxLayout());
//    QString msg = java.text.MessageFormat.format(
//                       tr("dragIcons"),
//                       new Object[] {tr("defaultCatalog"), tr("ImageIndex")});
    QString msg = tr("Drag icons from the %1 viewing panel to nodes in the %2 tree.").arg("Default Catalogues:").arg("Image Index:");
    labelPanel->layout()->addWidget(new QLabel(msg/*, SwingConstants.LEFT*/));
    mainPanel->layout()->addWidget(labelPanel);
    QWidget* catalogsPanel = new QWidget();
    catalogsPanel->setLayout(new QHBoxLayout(catalogsPanel/*, BoxLayout.X_AXIS*/));
    catalogsPanel->layout()->addWidget(makeCatalogPanel());
//    catalogsPanel->layout()->addWidget(new JSeparator(SwingConstants.VERTICAL));
    QFrame* line = new QFrame(/*centralwidget()*/this);
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    catalogsPanel->layout()->addWidget(line);
    catalogsPanel->layout()->addWidget(makeIndexPanel());
    mainPanel->layout()->addWidget(catalogsPanel);
    if(centralWidget()== NULL)
    {
        QWidget* centralWidget = new QWidget();
        centralWidget->setLayout(new QVBoxLayout());
        setCentralWidget(centralWidget);
    }
    centralWidget()->layout()->addWidget(mainPanel);

    // when this window closes, check for saving
//    addWindowListener(new java.awt.event.WindowAdapter() {
//        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//            DirectorySearcher.instance().close();
//            checkImageIndex();
//        }
//    });
    addWindowListener(new IIEWindowListener(this));
    //setLocation(10, 200);
    pack();
    setVisible(true);
}

IIEWindowListener::IIEWindowListener(ImageIndexEditor *iie) { this->iie = iie;}
void IIEWindowListener::windowClosing(QCloseEvent *)
{
 DirectorySearcher::instance()->close();
 iie->checkImageIndex();
}

void ImageIndexEditor::openItem_triggered()
{
 DirectorySearcher::instance()->openDirectory(false);
}

/*public*/ /*static*/ /*final*/ /*synchronized*/ void ImageIndexEditor::indexChanged(bool changed)
{
 _indexChanged = changed;
ShutDownManager* sdm;
 if ((sdm =(ShutDownManager*)InstanceManager::getOptionalDefault("ShutDownManager"))!=NULL)
 {
  if (changed)
  {
   if (_shutDownTask == NULL) {
       _shutDownTask = (ShutDownTask*)new SwingShutDownTask("DecoderPro Decoder Window Check",
               tr("Do you want to want to save these changes?\n                           Select \"No\" and no further messages will be posted."),
               tr("Save & Quit"), NULL);

//                {
//                    /*public*/ bool checkPromptNeeded() {
//                        return !_indexChanged;
//                    }
//                    /*public*/ bool doPrompt() {
//                        storeImageIndex();
//                        return true;
//                    }
//                };
   }
   sdm->_register(_shutDownTask);
  }
 }
}
/*public*/ /*static*/ bool ImageIndexEditor::isIndexChanged() {
    return _indexChanged;
}

/**
*  Called from window close of Icon Editors
*/
/*public*/ /*static*/ bool ImageIndexEditor::checkImageIndex()
{
 if (_indexChanged)
 {
  int result = JOptionPane::showConfirmDialog(NULL, tr("Do you want to want to save these changes?\nSelect \"No\" and no further messages will be posted."),tr("Question"), JOptionPane::YES_NO_CANCEL_OPTION, JOptionPane::QUESTION_MESSAGE);
  if (result == JOptionPane::YES_OPTION) {
      storeImageIndex();
      return true;
  } else if (result == JOptionPane::NO_OPTION) {
      indexChanged(false);
  }
 }
 return false;
}

/*public*/ /*static*/ void ImageIndexEditor::storeImageIndex() // SLOT[]
{
    Logger* log = new Logger("ImageIndexEditor");
    ItemPalette::storeIcons();

    if (log->isDebugEnabled()) log->debug("Start writing CatalogTree info");
    try {
        //new DefaultCatalogTreeManagerXml()::writeCatalogTrees();
        DefaultCatalogTreeManagerXml* xml = new DefaultCatalogTreeManagerXml();
        xml->writeCatalogTrees();
        indexChanged(false);
    }
    //catch (org.jdom.JDOMException jde) { log->error("Exception writing CatalogTrees: "+jde); }
    catch (IOException ioe) { log->error("Exception writing CatalogTrees: "+ioe.getMessage()); }
}

/*private*/ QWidget* ImageIndexEditor::makeCatalogPanel() {
    _catalog = new CatalogPanel(tr("Default Catalogs:"), tr("Select a directory to view its images"),true);
    _catalog->init(false, true);
    CatalogTreeManager* manager = (CatalogTreeManager*)InstanceManager::getDefault("CatalogTreeManager");
    QStringList sysNames = ((DefaultCatalogTreeManager*)manager)->getSystemNameList();
    if (!sysNames.isEmpty()) {
        for (int i=0; i<sysNames.size(); i++) {
            QString systemName = sysNames.at(i);
            if (systemName.startsWith("IF")) {
                _catalog->addTree( ((DefaultCatalogTreeManager*)manager)->getBySystemName(systemName));
            }
        }
    }
    _catalog->createNewBranch("IFJAR", "Program Directory", FileUtil::getProgramPath()+ "resources"+QDir::separator());
    FileUtil::createDirectory(FileUtil::getUserFilesPath() + "resources");
    _catalog->createNewBranch("IFPREF", "Preferences Directory", FileUtil::getUserFilesPath() + "resources"+QDir::separator());
    return _catalog;
}

/*private*/ QWidget*  ImageIndexEditor::makeIndexPanel() {
    _index = new CatalogPanel(tr("Image Index:"), "Select a node, then use the Edit menu to add or edit subNodes", true);
    _index->init(true, false);

    bool found = false;
CatalogTreeManager* manager = (CatalogTreeManager*)InstanceManager::getDefault("CatalogTreeManager");    QStringList sysNames = ((DefaultCatalogTreeManager*)manager)->getSystemNameList();
    if (!sysNames.isEmpty()) {
        for (int i=0; i<sysNames.size(); i++) {
            QString systemName = sysNames.at(i);
            if (systemName.startsWith("IX")) {
                _index->addTree(((DefaultCatalogTreeManager*)manager)->getBySystemName(systemName));
                found = true;
            }
        }
    }
    if (!found) {
        _index->createNewBranch("IXII", tr("Image Index"), /*FileUtil::getPreferencesPath()+*/"ImageIndexRoot");
    }
   return _index;
}

void ImageIndexEditor::addNode()
{
 //CatalogTreeNode* selectedNode = _index->getSelectedNode();
 CatalogTreeNode* selectedNode = _index->getSelectedNode();
 if (selectedNode == NULL)
 {
//  JOptionPane.showMessageDialog(this, tr("selectAddNode"),
//                                      tr("info"), JOptionPane.INFORMATION_MESSAGE);
     QMessageBox::information(this, tr("Information"), tr("Select a node where you want to add a child node."));
    }
  else
 {
#if 1
        QString name = JOptionPane::showInputDialog(this, tr("Please enter a name for the node you want to add."),
                                      tr("Question"), JOptionPane::QUESTION_MESSAGE);
        if (name != NULL) {
            if(!_index->insertNodeIntoModel(name, selectedNode)) {
                JOptionPane::showMessageDialog(this,
                                    tr("The name \"%1}\" is a duplicate. Node names\nin the path to the root must be unique.").arg(name),
                                    tr("error"), JOptionPane::ERROR_MESSAGE);
            }
        }
#else
        QString name;
        InputDialog* dlg = new InputDialog(tr("Please enter a name for the node you want to add."),name);
        if(dlg->exec() == QDialog::Accepted)
        {
         name = dlg->value();
        }
        if(name == "")
        {
         if(!_index->insertNodeIntoModel(name, selectedNode))
         {
             QMessageBox::critical(this, tr("Error"), tr("The name \"%1}\" is a duplicate. Node names\n                                                        in the path to the root must be unique.").arg(name));
         }
        }
#endif
 }
 //invalidate();
}

void ImageIndexEditor::renameNode() {
    CatalogTreeNode* selectedNode = _index->getSelectedNode();
    if (selectedNode == NULL)
    {
        JOptionPane::showMessageDialog(this, tr("Please enter a name for the node."), tr("Info"), JOptionPane::INFORMATION_MESSAGE);
    }
    else
    {
#if 1
     QString name = JOptionPane::showInputDialog(this, tr("Please enter a new name for the node."), selectedNode->getUserObject());
     if (name != NULL)
     {
      if (!_index->nodeChange(selectedNode, name)){
          JOptionPane::showMessageDialog(this, tr("The name \"%1\" is a duplicate. Node names\nin the path to the root must be unique.").arg(name),tr("error"), JOptionPane::ERROR_MESSAGE);
      }
     }
#else
       QString name;
       InputDialog* dlg = new InputDialog(tr("Please enter a new name for the node."),name);
       if(dlg->exec() == QDialog::Accepted)
       {
        name = dlg->value();
       }
       if(name == "")
       {
        if(!_index->insertNodeIntoModel(name, selectedNode))
        {
            QMessageBox::critical(this, tr("Error"), tr("The name \"%1\" is a duplicate. Node names\nin the path to the root must be unique.").arg(name));
        }
#endif
    }
//    invalidate();
}

void ImageIndexEditor::deleteNode() {
    CatalogTreeNode* selectedNode = _index->getSelectedNode();
    if (selectedNode == NULL)
    {
//        JOptionPane.showMessageDialog(this, tr("selectDeleteNode"),
//                                      tr("info"), JOptionPane.INFORMATION_MESSAGE);
        QMessageBox::information(this, tr("Info"), tr("Select the node you want to delete."));
    }
    else
    {
        int numNodes = countSubNodes(selectedNode);
        int numIcons = countIcons(selectedNode);
//        int response = JOptionPane.showConfirmDialog(this, java.text.MessageFormat.format(
//                                tr("confirmDeleteNode"), new Object[]
//                                    {(String)selectedNode.getUserObject(), Integer.valueOf(numNodes), Integer.valueOf(numIcons)}),
//                                    tr("question"), JOptionPane.YES_NO_OPTION,
//                                                    JOptionPane.QUESTION_MESSAGE);
//        if (response == JOptionPane.YES_OPTION) {
//            _index.removeNodeFromModel(selectedNode);
//        }
        switch(QMessageBox::question(this, tr("Question"), tr("Delete node, %1, its %2 subnodes, and all %3 image indices?").arg(selectedNode->getUserObject().toString()).arg(numNodes).arg(numIcons)))
        {
        case QMessageBox::Yes:
            _index->removeNodeFromModel(selectedNode);
        default:
            break;
        }
    }
}

//@SuppressWarnings("unchecked")
/*private*/ int ImageIndexEditor::countSubNodes(CatalogTreeNode* node)
{
 int cnt = 0;
 QVectorIterator<TreeNode*> it(*node->children());
 while(it.hasNext())
 {
  CatalogTreeNode* item = (CatalogTreeNode*)it.next();
//  QFileInfo dir(item->path);
//  if(dir.isDir())
   cnt += countSubNodes(item) + 1;
 }
 return cnt;
}

/*private*/ int ImageIndexEditor::countIcons(CatalogTreeNode* node)
{
 int cnt = 0;
 QVectorIterator<TreeNode*> it(*node->children());
 while(it.hasNext())
 {
  TreeNode* item = it.next();
//  QFileInfo dir(item->path);
//  if(dir.isDir())
   cnt += countIcons((CatalogTreeNode*)item);
//  else
//    cnt++;
 }
 cnt += node->getNumLeaves();
 return cnt;
}

