#include "catalogpanel.h"
#include <QVBoxLayout>
#include "catalogtree.h"
#include "defaulttreemodel.h"
#include "catalogtreemanager.h"
#include "instancemanager.h"
#include "defaultcatalogtreemanager.h"
#include "abstractcatalogtree.h"
#include <QRadioButton>
#include <QScrollArea>
#include <QButtonGroup>
#include "catalogtreenode.h"
#include "imageindexeditor.h"
#include <QVBoxLayout>
#include "catalogtreemodel.h"
#include "fileutil.h"
#include "borderlayout.h"
#include "catalogtreemodel.h"
#include "gridbagconstraints.h"
#include "namedicon.h"
#include "jlabel.h"
#include "dragjlabel.h"
#include "dataflavor.h"
#include <QDropEvent>
#include <QMimeData>
#include <QGridLayout>
#include <QTableWidget>
#include <QHeaderView>
#include "catalogtreeleaf.h"
#include "jtree.h"
#include "namedicon.h"
#include "joptionpane.h"
#include "imagepanel.h"
#include "drawsquares.h"
#include <QComboBox>
#include "flowlayout.h"
#include "iconitempanel.h"
#include <QMenu>

//CatalogPanel::CatalogPanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 * Create a QWidget* containing trees of resources to replace default icons.
 * The panel also displays image files files contained in a node of a tree.
 * Drag and Drop is implemented to drag a display of an icon to the
 * display of an icon that may be added to the panel.
 * <P>
 * This panel is used in the Icon Editors and also in the ImageIndex Editor.
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
// /*public*/ class CatalogPanel extends QWidget* implements MouseListener {

/*public*/ /*static*/ /*final*/ double CatalogPanel::ICON_SCALE = 0.15;
/*public*/ /*static*/ /*final*/ int CatalogPanel::ICON_WIDTH = 100;
/*public*/ /*static*/ /*final*/ int CatalogPanel::ICON_HEIGHT = 100;
/*static*/ QColor    CatalogPanel::_grayColor =  QColor(235,235,235);
/*static*/ QColor    CatalogPanel::_darkGrayColor = QColor(150, 150, 150);
    //static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.catalog->CatalogBundle");

/*public*/ CatalogPanel::CatalogPanel(QWidget *parent) : QWidget(parent)
{
 common();
 _model =new DefaultTreeModel(new CatalogTreeNode("mainRoot"));
 //_model = new CatalogTreeModel();
}

/*public*/ CatalogPanel::CatalogPanel(QString label1, QString label2, bool addButtonPanel, QWidget *parent) : QWidget(parent)
{
 //super(true);
 common();
 QVBoxLayout* thisLayout;
 setLayout(thisLayout = new QVBoxLayout(this/*, BoxLayout.Y_AXIS*/));
 QVBoxLayout* pLayout = new QVBoxLayout;
 QHBoxLayout* p1Layout = new QHBoxLayout;
 p1Layout->addWidget(new QLabel(label1),0,Qt::AlignLeft /*BorderLayout::West*/);
 pLayout->addLayout(p1Layout);
 QHBoxLayout* p2Layout = new QHBoxLayout;
 p2Layout->addWidget(new QLabel(label2), 0, Qt::AlignLeft/*BorderLayout::West*/);
 pLayout->addLayout(p2Layout);
// p->setMaximumSize(p->size());
 thisLayout->addLayout(p1Layout);
 if (addButtonPanel)
 {
  thisLayout->addWidget(makeButtonPanel(),0, Qt::AlignBottom); //BorderLayout.SOUTH); // add the background chooser
         }
}
CatalogPanel::~CatalogPanel()
{
 delete log;
 if(_model)
  delete _model;
}

void CatalogPanel::common()
{
 _grayColor =  QColor(235,235,235);
 _currentBackground = _grayColor;
 _previewLabel = new QLabel();
 _branchModel = new QList <CatalogTree*>();
 log = new Logger("CatalogPanel");
 log->setDebugEnabled(true);
 _noMemory = false;
 _model = nullptr;
 _preview = nullptr;
 colorChoice =  QList<QColor>() <<QColor(Qt::white) << _grayColor << _darkGrayColor;

}
#if 0
/*public*/ void setToolTipText(QString tip) {
    if (_dTree!=NULL) {
        _dTree.setToolTipText(tip);
    }
    if (_treePane!=NULL) {
        _treePane.setToolTipText(tip);
    }
    super.setToolTipText(tip);
}
#endif
/*public*/ void CatalogPanel::init(bool treeDnD, bool dragIcons)
{
 _model =new DefaultTreeModel(new CatalogTreeNode("mainRoot"));

 if (treeDnD)
 {   // index editor (right pane)
   _dTree = new JTree(_model); // new DropJTree(_model);
   _noDrag = true;
   _dTree->setDragEnabled(true);
   _dTree->setSelectionMode(QAbstractItemView::ExtendedSelection);
   _dTree->setDropIndicatorShown(true);
   _dTree->setAcceptDrops(true);
  }
  else
  {    // Catalog (left pane index editor or all icon editors)
   _dTree = new JTree(_model);
   _noDrag = false;
//        _dTree->setDragEnabled(true);
//   _dTree->setSelectionMode(QAbstractItemView::ExtendedSelection);
   _dTree->setAcceptDrops(false);
  }
 _treeDnd = treeDnD;
 _dragIcons = dragIcons;
 log->debug(tr("CatalogPanel.init _treeDnd= %1, _dragIcons= %2").arg(_treeDnd?"true":"false").arg( _dragIcons?"true":"false"));

  _dTree->setIndentation(10);
  _dTree->setAnimated(true);
  _dTree->setHeaderHidden(true);
  _dTree->setItemsExpandable(true);
  _dTree->setRootIsDecorated(true);
  _dTree->setSelectionMode(QAbstractItemView::SingleSelection);
  //connect(_dTree, SIGNAL(clicked(QModelIndex)), this, SLOT(on_tree_clicked(QModelIndex)));
//  _dTree.addTreeSelectionListener((TreeSelectionEvent e) -> {
//      updatePanel();
//  });
  _dTree->addTreeSelectionListener(new CPLTreeSelectionListener(this));
  _dTree->setMaximumHeight(120);
  QSizePolicy sp = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
  sp.setHorizontalStretch(0);
  sp.setVerticalStretch(0);
  sp.setHeightForWidth(_dTree->hasHeightForWidth());
  _dTree->setSizePolicy(sp);

#if 0
    DefaultTreeCellRenderer renderer = new DefaultTreeCellRenderer();
    renderer.setLeafIcon(renderer.getClosedIcon());
    _dTree.setCellRenderer(renderer);
    _dTree.setRootVisible(false);
    _dTree.setShowsRootHandles(true);
    _dTree.setScrollsOnExpand(true);
    //_dTree.setDropMode(DropMode.ON);
    _dTree.getSelectionModel().setSelectionMode(DefaultTreeSelectionModel.SINGLE_TREE_SELECTION);

    _dTree.addTreeSelectionListener(new TreeSelectionListener() {
        /*public*/ void valueChanged(TreeSelectionEvent e) {
            updatePanel();
        }
    });
    _dTree.setExpandsSelectedPaths(true);
#endif
//    _treePane = new JScrollPane(_dTree);
//    _treePane.getViewport().setPreferredSize(new Dimension(250, 200));
    layout()->addWidget(/*_treePane*/_dTree);
    setupPanel();
}
CPLTreeSelectionListener::CPLTreeSelectionListener(CatalogPanel *cp) {this->cp = cp;}
void CPLTreeSelectionListener::valueChanged(TreeSelectionEvent * /*e*/)
{
 cp->updatePanel();
}

/*public*/ void CatalogPanel::updatePanel()
{
 if (log->isDebugEnabled()) log->debug(QString("updatePanel: _dTree.isSelectionEmpty()= ")+(_dTree->currentIndex().isValid()?"no":"yes") + ", _dTree.getSelectionPath() is NULL " +((_dTree->currentIndex().data().toString()==nullptr)?"yes":"no"));
 if (!_dTree->isSelectionEmpty() && _dTree->getSelectionPath()!=nullptr ) {
 {
//  try
//  {
   _previewLabel->setText(setIcons());
  }
//   catch (OutOfMemoryError oome) {
//       resetPanel();
//       if (log->isDebugEnabled()) log->debug("setIcons threw OutOfMemoryError "+oome);
//   }
 }
 else
 {
  _previewLabel->setText(" ");
 }
}

/**
* Create a new model and add it to the main root
*/
/*public*/ void CatalogPanel::createNewBranch(QString systemName, QString userName, QString path)
{
 CatalogTreeManager* manager = (CatalogTreeManager*)InstanceManager::getDefault("CatalogTreeManager");
 CatalogTree* tree = manager->getBySystemName(systemName);
 if (tree == nullptr)
 {
  tree = manager->newCatalogTree(systemName, userName);
  tree->insertNodes(path);
 }
 addTree(tree);

}

/**
*  Extend the Catalog by adding a tree to the root.
*/
/*public*/ void CatalogPanel::addTree(CatalogTree* tree)
{

 QString name = tree->getSystemName();
 for (int i=0; i<_branchModel->size(); i++)
 {
  if (name == (_branchModel->at(i)->getSystemName()))
  {
   return;
  }
 }

  addTreeBranch((CatalogTreeNode*)tree->getRoot());
 _branchModel->append(tree);
 _model->reload();
}

/**
* Recursively add the branch nodes to display tree
*/
//@SuppressWarnings("unchecked")
/*private*/ void CatalogPanel::addTreeBranch(CatalogTreeNode* node)
{
 if (log->isDebugEnabled())
 {
  log->debug("addTreeBranch called for node= "+node->toString()+
                  ", has "+QString::number(node->getChildCount())+" children");
 }
    //String name = node.toString();
    CatalogTreeNode* root = (CatalogTreeNode*)_model->getRoot();
    QVectorIterator<CatalogTreeNode*>* e = (QVectorIterator<CatalogTreeNode*>*)node->children();
    while (e->hasNext()) {
        CatalogTreeNode* n = e->next();
        addNode(root, n);
    }
}

/**
* Clones the node and adds to parent.
*/
//@SuppressWarnings("unchecked")
/*private*/ void CatalogPanel::addNode(CatalogTreeNode* parent, CatalogTreeNode* n)
{
 CatalogTreeNode* node = new CatalogTreeNode(n->getUserObject().toString());
 node->setLeaves(n->getLeaves());
 parent->add(node);
 QVectorIterator<CatalogTreeNode*>* e = (QVectorIterator<CatalogTreeNode*>*)n->children();
 while (e->hasNext())
 {
  CatalogTreeNode* nChild = e->next();
  addNode(node, nChild);
 }
}
/**
* The tree held in the CatalogTreeManager must be kept in sync with the
* tree displayed as the Image Index.  Required in order to save
* the Index to disc.
*/
/*private*/ CatalogTreeNode* CatalogPanel::getCorrespondingNode(CatalogTreeNode* node)
{
 QVector<TreeNode*>* nodes = node->getPath();
 CatalogTreeNode* cNode = nullptr;
 for (int i=0; i<_branchModel->size(); i++)
 {
  CatalogTreeNode* cRoot = (CatalogTreeNode*)_branchModel->at(i)->getRoot();
  cNode = match(cRoot, nodes, 1);
  if (cNode != nullptr)
  {
   break;
  }
 }
 return cNode;
}

/**
*  Find the corresponding node in a CatalogTreeManager tree with a
* displayed node.
*/
//@SuppressWarnings("unchecked")
/*private*/ CatalogTreeNode* CatalogPanel::match(CatalogTreeNode* cRoot, QVector<TreeNode*>* nodes, int idx)
{
 if (idx == nodes->size())
 {
  return cRoot;
 }
 QVectorIterator<CatalogTreeNode*>* e = (QVectorIterator<CatalogTreeNode*>*)cRoot->children();
 CatalogTreeNode* result = nullptr;
 while (e->hasNext())
 {
  CatalogTreeNode* cNode = e->next();
  if (((CatalogTreeNode*)nodes->at(idx))->toString()==(cNode->toString()))
  {
   result = match(cNode, nodes, idx+1);
   break;
  }
 }
 return result;
}

/**
*  Find the corresponding CatalogTreeManager tree to the displayed
* branch
*/
/*private*/ CatalogTree* CatalogPanel::getCorespondingModel(CatalogTreeNode* node)
{
 QVector<TreeNode*>* nodes = node->getPath();
 CatalogTree* model = nullptr;
 for (int i=0; i<_branchModel->size(); i++)
 {
  model = _branchModel->at(i);
  CatalogTreeNode* cRoot = (CatalogTreeNode*)model->getRoot();
  if (match(cRoot, nodes, 1) != nullptr)
  {
   break;
  }
 }
 return model;
}

/**
*  Insert a new node into the displayed tree.
*/
//@SuppressWarnings("unchecked")
/*public*/ bool CatalogPanel::insertNodeIntoModel(QString name, CatalogTreeNode *parent)
{
 if (!nameOK(parent, name)) {
     return false;
 }
 int index = 0;
 QVectorIterator<TreeNode*> e(*parent->children());
 while (e.hasNext()) {
     TreeNode* n = e.next();
     if (name < ((CatalogTreeNode*)n)->toString()) {
         break;
     }
     index++;
 }
 CatalogTreeNode* newChild = new CatalogTreeNode(name);
 _model->insertNodeInto(newChild, parent, index);
 CatalogTreeNode* cParent = getCorrespondingNode(parent);
 CatalogTreeNode* node = new CatalogTreeNode(name);
 AbstractCatalogTree* tree = (AbstractCatalogTree*) getCorespondingModel(parent);
 tree->insertNodeInto(node, cParent, index);
 ((ImageIndexEditor*)InstanceManager::getDefault("ImageIndexEditor"))->indexChanged(true);
 return true;
}

/**
*  Delete a node from the displayed tree.
*/
/*public*/ void CatalogPanel::removeNodeFromModel(CatalogTreeNode* node) {
    AbstractCatalogTree* tree = (AbstractCatalogTree*)getCorespondingModel(node);
    tree->removeNodeFromParent(getCorrespondingNode(node));
    _model->removeNodeFromParent(node);
    ImageIndexEditor::indexChanged(true);
}


#if 1
/**
* Make a change to a node in the displayed tree. Either its name
* or the contents of its leaves (image references)
*/
/*public*/ bool CatalogPanel::nodeChange(CatalogTreeNode* node, QString name) {
    CatalogTreeNode* cNode = getCorrespondingNode(node);
    cNode->setLeaves(node->getLeaves());
    AbstractCatalogTree* tree = (AbstractCatalogTree*)getCorespondingModel(node);

    cNode->setUserObject(name);
    node->setUserObject(name);
    tree->nodeChanged(cNode);
    _model->nodeChanged(node);
    updatePanel();
    ImageIndexEditor::indexChanged(true);
    updatePanel();
    return true;
}
#endif
/**
*  Node names in the path to the root must be unique
*/
/*private*/ bool CatalogPanel::nameOK(CatalogTreeNode* node, QString name)
{
 QVector<TreeNode*>* nodes = node->getPath();
 for (int i=0; i<nodes->size(); i++)
 {
  if (name==(((CatalogTreeNode*)nodes->at(i))->toString()))
  {
   return false;
  }
 }
 return true;
}
#if 0
/**
*  Only call when log->isDebugEnabled() is true
*
/*public*/ void enumerateTree() {T
    CatalogTreeNode root = (CatalogTreeNode)_model.getRoot();
    log->debug("enumerateTree called for root= "+root.toString()+
                  ", has "+root.getChildCount()+" children");
    Enumeration e =root.depthFirstEnumeration();
    while (e.hasMoreElements()) {
        CatalogTreeNode n = (CatalogTreeNode)e.nextElement();
        log->debug("nodeName= "+n.getUserObject()+" has "+n.getLeaves().size()+" leaves.");
    }
}
#endif

/**
* Setup a display pane for a tree that shows only directory nodes (no file leaves)
* The leaves (icon images) will be displayed in this panel.
*/
/*private*/ void CatalogPanel::setupPanel()
{
 QWidget* previewPanel = new QWidget();
 previewPanel->setObjectName("previewPanel");
 QVBoxLayout* previewPanelLayout;
 previewPanel->setLayout(previewPanelLayout = new QVBoxLayout(previewPanel/*, BoxLayout.Y_AXIS*/));
 previewPanelLayout->setObjectName("previewPanelLayout");
 //previewPanelLayout->setMargin(0);
 //previewPanel->setContentsMargins(0,0,0,0);
// QWidget* p = new QWidget();
// p->setObjectName("p");
// p->setLayout(new QHBoxLayout(p/*, BoxLayout.X_AXIS*/));
 QHBoxLayout* pLayout = new QHBoxLayout;
 pLayout->addWidget(_previewLabel);
 previewPanelLayout->addLayout(pLayout);
 _preview = new ImagePanel();
 _preview->setObjectName("preview");
 QScrollArea* js = new QScrollArea;
 _preview->setMinimumSize(300,200);
 QSizePolicy spPreview(QSizePolicy::Expanding, QSizePolicy::Expanding);
 spPreview.setHorizontalStretch(1);
 spPreview.setVerticalStretch(1);
 spPreview.setHeightForWidth(_preview->sizePolicy().hasHeightForWidth());
 _preview->setSizePolicy(spPreview);

 js->setToolTip(tr("Drag an icon from the Preview to replace an icon in the item group"));
 js->setBackgroundRole(QPalette::Dark);
 js->setWidget(_preview);
 js->setWidgetResizable(true);
 previewPanelLayout->addWidget(js);
// previewPanel->layout()->addWidget(_preview);
// _preview->setMinimumSize( QSize(250, 200));
 QRadioButton* whiteButton = new QRadioButton(tr("White")/*,false*/);
 QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
 sizePolicy.setHorizontalStretch(0);
 sizePolicy.setVerticalStretch(0);
 sizePolicy.setHeightForWidth(whiteButton->sizePolicy().hasHeightForWidth());
 whiteButton->setSizePolicy(sizePolicy);
 QRadioButton* grayButton = new QRadioButton(tr("Light Gray")/*,true*/);
 grayButton->setChecked(true);
 grayButton->setSizePolicy(sizePolicy);
 QRadioButton* darkButton = new QRadioButton(tr("Dark Gray")/*,false*/);
 darkButton->setSizePolicy(sizePolicy);
//    whiteButton.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                _currentBackground = Color.white;
//                setBackground(_preview);
//            }
//        });
 connect(whiteButton, SIGNAL(clicked()), this, SLOT(whiteButtonClicked()));
//    grayButton.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                _currentBackground = _grayColor;
//                setBackground(_preview);
//            }
//        });
 connect(grayButton, SIGNAL(clicked()), this, SLOT(grayButtonClicked()));
//    darkButton.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                _currentBackground = new Color(150,150,150);
//                setBackground(_preview);
//            }
//        });
 connect(darkButton, SIGNAL(clicked()), this, SLOT(darkButtonClicked()));
 QWidget* backgroundPanel = new QWidget();
 backgroundPanel->setObjectName("backgroundPanel");
 backgroundPanel->setContentsMargins(0,0,0,0);
 QVBoxLayout* bpl;
 backgroundPanel->setLayout(bpl = new QVBoxLayout(backgroundPanel/*, BoxLayout.Y_AXIS*/));
 bpl->setContentsMargins(0,0,0,0);
 bpl->setMargin(0);
 QWidget* pp = new QWidget();
 pp->setLayout(new QHBoxLayout());
 pp->layout()->addWidget(new QLabel(tr("Set Background")));
 backgroundPanel->layout()->addWidget(pp);
 QWidget* buttonPanel = new QWidget();
 QHBoxLayout* btpl;
 buttonPanel->setLayout(btpl = new QHBoxLayout);//(buttonPanel/*, BoxLayout.X_AXIS*/));
 buttonPanel->setContentsMargins(0,0,0,0);
 btpl->setMargin(0);
 btpl->setContentsMargins(0,0,0,0);
 QButtonGroup* selGroup = new QButtonGroup();
 selGroup->addButton(whiteButton);
 selGroup->addButton(grayButton);
 selGroup->addButton(darkButton);
 buttonPanel->layout()->addWidget(whiteButton);
 buttonPanel->layout()->addWidget(grayButton);
 buttonPanel->layout()->addWidget(darkButton);
 backgroundPanel->layout()->addWidget(buttonPanel);
 //backgroundPanel->setMaximumSize(backgroundPanel->size());
 previewPanelLayout->addWidget(backgroundPanel);
 layout()->addWidget(previewPanel);
}
void CatalogPanel::whiteButtonClicked()
{
 _currentBackground = QColor(Qt::white);
 setBackground(_preview);

}
void CatalogPanel::darkButtonClicked()
{
 _currentBackground =  QColor(150,150,150);
 setBackground(_preview);
}
void CatalogPanel::grayButtonClicked()
{
 _currentBackground = _grayColor;
 setBackground(_preview);
}


/*public*/ void CatalogPanel::setBackground(QWidget* container)
{
//    container.setBackground(_currentBackground);
//    Component[] comp = container.getComponents();
//    for (int i=0; i<comp.length; i++){
//        comp[i].setBackground(_currentBackground);
//        if (comp[i] instanceof java.awt.Container) {
//            setBackground((Container)comp[i]);
//        }
//    }
//    container.invalidate();
 container->setStyleSheet(QString("QWidget {background-color : rgb(%1,%2,%3); font-size : 7pt; }").arg(_currentBackground.red()).arg(_currentBackground.green()).arg(_currentBackground.blue()));
}

/**
 * Create panel element containing a "View on:" drop down list.
 * Employs a normal JComboBox, no Panel Background option.
 * @see jmri.jmrit.catalog.PreviewDialog#setupPanel()
 *
 * @return the JPanel with label and drop down
 */
/*private*/ QWidget* CatalogPanel::makeButtonPanel() {
    // create array of backgrounds
    if (_backgrounds == nullptr) {
        _backgrounds = new QVector<BufferedImage*>(4);
        for (int i = 0; i <= 2; i++) {
            _backgrounds->replace(i, DrawSquares::getImage(300, 400, 10, colorChoice[i], colorChoice[i]));
        }
        _backgrounds->replace(3, DrawSquares::getImage(300, 400, 10, QColor(Qt::white), _grayColor));
    }
    QComboBox* bgColorBox = new QComboBox();
    bgColorBox->addItem(tr("White"));
    bgColorBox->addItem(tr("LightGray"));
    bgColorBox->addItem(tr("DarkGray"));
    bgColorBox->addItem(tr("Checkers")); // checkers option
    bgColorBox->setCurrentIndex(0); // start as "White"
//    bgColorBox.addActionListener((ActionEvent e) -> {
//        // load background image
//        _preview.setImage(_backgrounds[bgColorBox.getSelectedIndex()]);
//        log.debug("Catalog setImage called");
//        _preview.setOpaque(false);
//        _preview.invalidate();
//    });
    connect(bgColorBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onBgColorBox(int)));
    QWidget* backgroundPanel = new QWidget();
    backgroundPanel->setLayout(new QVBoxLayout());//backgroundPanel, BoxLayout.Y_AXIS));
    QWidget* pp = new QWidget();
    pp->setLayout(new FlowLayout(/*FlowLayout.CENTER*/));
    pp->layout()->addWidget(new QLabel(tr("setBackground")));
    pp->layout()->addWidget(bgColorBox);
    backgroundPanel->layout()->addWidget(pp);
    backgroundPanel->setMaximumSize(backgroundPanel->sizeHint());
    return backgroundPanel;
}

void CatalogPanel::onBgColorBox(int index)
{
 // load background image
 _preview->setImage(_backgrounds->at(index));
 log->debug("Catalog setImage called");
 //_preview.setOpaque(false);
 _preview->update();

}
/**
 * Allows ItemPalette to set the preview panel background to match that of
 * the icon set being edited.
 *
 * @return Preview panel
 */
/*public*/ ImagePanel* CatalogPanel::getPreviewPanel() {
    return _preview;
}

/*protected*/ void CatalogPanel::resetPanel()
{
//    _selectedImage = NULL;
 if (_preview == nullptr)
 {
  return;
 }
//    Component[] comp = _preview.getComponents();
//    for (int i=0; i<comp.length; i++) {
//        comp[i].removeMouseListener(this);
//    }
 QObjectList l = _preview->children();
 foreach(QObject* o, l)
 {
  if(qobject_cast<QWidget*>(o) !=nullptr)
   delete o;
 }
 if(_preview->layout())
     delete _preview->layout();
//    _preview.removeAll();
//    setBackground(_preview);
//    _preview.repaint();
}
// called by palette.IconItemPanel to get user's selection from catalog
/*public*/ NamedIcon* CatalogPanel::getIcon() {
    if (_selectedImage != nullptr) {
//        return _selectedImage->getIcon();
    }
    return nullptr;
}

// called by palette.IconItemPanel when selection is made for its iconMap
/*public*/ void CatalogPanel::deselectIcon() {
    if (_selectedImage !=nullptr) {
//        _selectedImage.setBorder(null);
        _selectedImage = nullptr;
    }
}

/*protected*/ void CatalogPanel::setSelection(CPIconDisplayPanel* panel) {
    if (_parent == nullptr) {
        return;
    }
    if (_selectedImage != nullptr && panel!=(_selectedImage)) {
        deselectIcon();
    }
    if (panel != nullptr) {
//        panel.setBorder(BorderFactory.createLineBorder(Color.red, 2));
        _selectedImage = panel;
    } else {
        deselectIcon();
    }
    _parent->deselectIcon();
}

#if 0
/*public*/ class MemoryExceptionHandler implements Thread.UncaughtExceptionHandler {
    /*public*/ void uncaughtException(Thread t, Throwable e) {
        _noMemory = true;
        log->error("Exception from setIcons: "+e, e);
    }
}

#endif
/**
*  Display the icons in the preview panel
*/
/*protected*/ QString CatalogPanel::setIcons() /*throws OutOfMemoryError*/
{
 resetPanel();
 CatalogTreeNode* node = getSelectedNode();
 if (node == nullptr) {
     return nullptr;
 }
 QVector<CatalogTreeLeaf*>* leaves = node->getLeaves();

 if (leaves == nullptr || leaves->isEmpty()) {
     return nullptr;
 }
 int numCol = 1;
 while (numCol * numCol < leaves->size()) {
     numCol++;
 }
 if (numCol > 1) {
     numCol--;
 }
 int numRow = leaves->size() / numCol;
 bool newCol = false;
 _noMemory = false;
 // VM launches another thread to run ImageFetcher.
 // This handler will catch memory exceptions from that thread
 //Thread.setDefaultUncaughtExceptionHandler(new MemoryExceptionHandler());
 QGridLayout* gridbag = new QGridLayout();
 gridbag->setMargin(0);
 _preview->setLayout(gridbag);
//_preview->setLayout(new QVBoxLayout);
 GridBagConstraints c;// = GridBagConstraints();
 c.fill = GridBagConstraints::NONE;
 c.anchor = GridBagConstraints::CENTER;
 c.weightx = 1.0;
 c.weighty = 1.0;
 c.gridy = 0;
 c.gridx = -1;
 for (int i=0; i<leaves->size(); i++)
 {
  if (_noMemory)
  {
   continue;
  }
  CatalogTreeLeaf* leaf = leaves->at(i);
  NamedIcon* icon = new NamedIcon(leaf->getPath(), leaf->getName());
  double scale = icon->reduceTo(ICON_WIDTH, ICON_HEIGHT, ICON_SCALE);
//  int w = icon->getIconWidth();
  int h = icon->getIconHeight();
  if (_noMemory)
  {
   continue;
  }
  if (c.gridx < numCol)
  {
   c.gridx++;
  }
  else if (c.gridy < numRow)
  { //start next row
   c.gridy++;
   if (!newCol)
   {
    c.gridx=0;
   }
//   maxRowHeight = 0;
  }
  else if (!newCol)
  { // start new column
   c.gridx++;
   numCol++;
   c.gridy = 0;
   newCol = true;
  }
  else
  {  // start new row
   c.gridy++;
   numRow++;
   c.gridx = 0;
   newCol = false;
//   maxRowHeight = 0;
  }
  c.insets = new Insets(5, 5, 0, 0);

//            JLabel image = NULL;
  DragJLabel* nameLabel = nullptr;
  if (_noDrag)
  {
//                image = new JLabel();
   nameLabel = new DragJLabel(/*info.fileName()*/nullptr);
  }
  else
  {
//            try {
//                    image = new DragJLabel(new DataFlavor(ImageIndexEditor.IconDataFlavorMime));
      //DataFlavor* flavor = new DataFlavor(ImageIndexEditor::IconDataFlavorMime);
   DataFlavor* flavor = new DataFlavor(icon,"NamedIcon");
   flavor->setMimeTypeParameter("path", icon->getURL());
   nameLabel = new DragJLabel(flavor);
//     }
//     catch (java.lang.ClassNotFoundException cnfe) {
//                cnfe.printStackTrace();
//                continue;
//            }
  }
  connect(nameLabel, SIGNAL(showPopUp(NamedIcon*)), this, SLOT(showPopUp(NamedIcon*)));

//            image.setOpaque(true);
//            image.setName(leaf.getName());
//            image.setBackground(_currentBackground);
  nameLabel->setText(leaf->getName());
//  nameLabel->setName(info.fileName());
  nameLabel->setMinimumHeight(h+20);
//    nameLabel->setBackground(_currentBackground);
  nameLabel->setIcon(icon);
  nameLabel->setVisible(true);
  nameLabel->setToolTip(QFileInfo(icon->getURL()).fileName());

  QWidget* p = new QWidget();
  QVBoxLayout* pl;
  p->setLayout(pl = new QVBoxLayout);
  p->setContentsMargins(0,0,0,0);
//            QWidget* iPanel = new QWidget();
//            iPanel.add(image);
//            p.add(iPanel);
  pl->addWidget(nameLabel,0,Qt::AlignTop | Qt::AlignHCenter);
  QLabel* label = new QLabel(tr("scale %1:1").arg(printDbl(scale,2)));
  pl->addWidget(label,0,Qt::AlignBottom);
  p->setMinimumHeight(h+60 + label->sizeHint().height());
  p->setMinimumWidth(label->sizeHint().width());
//    if (_noDrag) {
//     p.addMouseListener(this);
//    }
  //gridbag.setConstraints(p, c);
  gridbag->addWidget(p, c.gridy, c.gridx, 1,1);
//  int hRow = gridbag->rowMinimumHeight(c.gridy);
//  if(h+20 > hRow)
//  maxRowHeight = qMax(maxRowHeight, h);
//  if(h+20 > maxRowHeight)
//   gridbag->setRowMinimumHeight(c.gridy, /*h+20*/h+60 + label->sizeHint().height());
  if (_noMemory)
  {
   continue;
  }
  //_preview->layout()->addWidget(p);
//  if (log->isDebugEnabled())
//  {
//   log->debug(nameLabel->getName()+" inserted at ("+QString::number(c.gridx)+", "+QString::number(c.gridy)+
//                          ") w= "+QString::number(icon->getIconWidth())+", h= "+QString::number(icon->getIconHeight()));
//  }
 }
 c.gridy++;
 c.gridx++;
 QLabel* bottom = new QLabel();
 bottom->setLayout(new QHBoxLayout);
 gridbag->addWidget(bottom, c.gridy, c.gridx,1,1);
 //_preview->layout()->addWidget(bottom);
    //_preview->layout()->addWidget(bottom);

    //Thread.setDefaultUncaughtExceptionHandler(new jmri.util.exceptionhandler.UncaughtExceptionHandler());
 packParentFrame(this);
 return tr("Node \"%1\" has %2 image files.").arg(node->getUserObject().toString()).arg(leaves->size());
}

/*public*/ /*static*/ CatalogPanel* CatalogPanel::makeDefaultCatalog() {
        // log.debug("CatalogPanel catalog requested");
        return makeDefaultCatalog(true, false, true); // deactivate dragNdrop? (true, true, false)
    }
/*public*/ /*static*/ CatalogPanel* CatalogPanel::makeDefaultCatalog(bool addButtonPanel, bool treeDrop, bool dragIcon)
{
 CatalogPanel* catalog = new CatalogPanel(tr("Catalogues:"), tr("Select a directory to view its images"), addButtonPanel);
 catalog->init(treeDrop, dragIcon);
 CatalogTreeManager* manager = (CatalogTreeManager*)InstanceManager::getDefault("CatalogTreeManager");
 QStringList sysNames = manager->getSystemNameList();
 if (!sysNames .isEmpty())
 {
  for (int i=0; i<sysNames.size(); i++)
  {
   QString systemName = sysNames.at(i);
   if (systemName.at(0) == 'I')
   {
    catalog->addTree( manager->getBySystemName(systemName));
   }
  }
 }
 //catalog->createNewBranch("IFJAR", "Program Directory", "resources");
 catalog->createNewBranch("IFJAR", "Program Directory",FileUtil::getProgramPath()+"resources"+QDir::separator());
 FileUtil::createDirectory(FileUtil::getUserFilesPath() + "resources");
 catalog->createNewBranch("IFPREF", "Preferences Directory", FileUtil::getUserFilesPath() + "resources"+QDir::separator());
 return catalog;
}

/*public*/ /*static*/ JFrame* CatalogPanel::getParentFrame(QWidget* comp)
{
 while (true)
 {
  //if (comp instanceof Frame )
  if(qobject_cast<JFrame*>(comp)!= nullptr)
  {
   return (JFrame*)comp;
  }
  if (comp==nullptr)
  {
   return nullptr;
  }
  comp = (QWidget*)comp->parent();
 }
}

/*public*/ /*static*/ void CatalogPanel::packParentFrame(QWidget* comp)
{
 JFrame* frame = getParentFrame(comp);
 if (frame!=nullptr)
 {
  frame->pack();
 }
}

/**
* Utility
*/
/*public*/ /*static*/ QString CatalogPanel::printDbl(double z, int /*decimalPlaces*/)
{
//    if (Double.isNaN(z) || decimalPlaces > 8)
//    {
//        return Double.toString(z);
//    }
//    else if (decimalPlaces <= 0)
//    {
//        return Integer.toString((int)Math.rint(z));
//    }
//    StringBuffer sb = new StringBuffer();
//    if (z < 0) {
//        sb.append('-');
//    }
//    z = Math.abs(z);
//    int num = 1;
//    int d = decimalPlaces;
//    while (d-- > 0) {
//        num *= 10;
//    }
//    int x = (int)Math.rint(z*num);
//    int ix = x/num;                     // integer part
//    int dx = x - ix*num;
//    sb.append(ix);
//    if (dx == 0) {
//        return sb.toString();
//    }
//    if (decimalPlaces > 0)
//    {
//        sb.append('.');
//        num /= 10;
//        while (num > dx)
//        {
//            sb.append('0');
//            num /= 10;
//        }
//        sb.append(dx);
//    }
//    return sb.toString() ;
    return QString("%1").arg(z,0,'g',2);
}
#if 0
/**
*/
/*public*/ void setSelectedNode(String[] names) {
    _dTree.setExpandsSelectedPaths(true);
    CatalogTreeNode[] path = new CatalogTreeNode[names.length];
    for (int i=0; i<names.length; i++) {
        path[i] = new CatalogTreeNode(names[i]);
    }
    _dTree.setSelectionPath(new TreePath(path));
}

/**
*/
/*public*/ void scrollPathToVisible(String[] names) {
    _dTree.setExpandsSelectedPaths(true);
    CatalogTreeNode[] path = new CatalogTreeNode[names.length];
    for (int i=0; i<names.length; i++) {
        path[i] = new CatalogTreeNode(names[i]);
    }
    _dTree.scrollPathToVisible(new TreePath(path));
}

#endif
/**
* Return the node the user has selected.
*/
///*public*/ CatalogTreeNode* CatalogPanel::getSelectedNode() {

//    if (!_dTree.isSelectionEmpty() && _dTree.getSelectionPath()!=NULL ) {
//        // somebody has been selected
//        if (log->isDebugEnabled()) log->debug("getSelectedNode with "+
//                                            _dTree.getSelectionPath().toString());
//        TreePath* path = _dTree.getSelectionPath();
//        return (CatalogTreeNode*)path.getLastPathComponent();
//    }

//    return NULL;
//}
/*public*/ CatalogTreeNode* CatalogPanel::getSelectedNode()
{
 if(_dTree->currentIndex().isValid())
  return (CatalogTreeNode*)_dTree->currentIndex().internalPointer();
 return nullptr;
}


void CatalogPanel::_delete(NamedIcon* icon) {
    CatalogTreeNode* node = getSelectedNode();
    node->deleteLeaf(icon->getName(), icon->getURL());
    updatePanel();
}

void CatalogPanel::rename(NamedIcon* icon)
{
    QString name = JOptionPane::showInputDialog(getParentFrame(this),
                                          tr("newIconName %1").arg(icon->getName()),
                                          JOptionPane::QUESTION_MESSAGE);
    if (name != nullptr && name.length() > 0) {
        CatalogTreeNode* node = getSelectedNode();
        CatalogTreeLeaf* leaf = node->getLeaf(icon->getName(), icon->getURL());
        if (leaf != nullptr) {
            leaf->setName(name);
        }
        //getParentFrame(this).invalidate();
        updatePanel();
    }
}

/**
*  Return the icon selected in the preview panel
*  Save this code in case there is a need to use an alternative
*  icon changing method rather than DnD.
*
public NamedIcon* CatalogPanel::getSelectedIcon() {
    if (_selectedImage != nullptr) {
        QLabel* l = (QLabel*)_selectedImage.getComponent(0);
        // deselect
        //setSelectionBackground(_currentBackground); Save for use as alternative to DnD.
        _selectedImage = NULL;
        return (NamedIcon)l.getIcon();
    }
    return nullptr;
} */

///*private*/ void CatalogPanel::showPopUp(MouseEvent e, NamedIcon* icon) {
/*private*/ void CatalogPanel::showPopUp(NamedIcon* icon)
{
    if (log->isDebugEnabled()) log->debug("showPopUp "+icon->toString());
    QMenu* popup = new QMenu();
    popup->addAction(new QAction(icon->getName(),this));
    popup->addAction(new QAction(icon->getURL(),this));
    popup->addSeparator();

//    popup.add(new AbstractAction(tr("Rename Icon")) {
//            NamedIcon icon;
//            /*public*/ void actionPerformed(ActionEvent e) {
//                rename(icon);
//            }
//            AbstractAction init(NamedIcon i) {
//                icon = i;
//                return this;
//            }
//        }.init(icon));
    QSignalMapper* mapper1 = new QSignalMapper();
    QAction* renameAct = new QAction(tr("Rename Icon"),this);
    mapper1->setMapping(renameAct, icon);
    connect(renameAct, SIGNAL(triggered()), mapper1, SLOT(map()));
    connect(mapper1, SIGNAL(mapped(QObject*)), this, SLOT(rename(QObject*)));
    popup->addSeparator();
    popup->addAction(renameAct);

//    popup.add(new AbstractAction(tr("Delete Icon")) {
//            NamedIcon icon;
//            /*public*/ void actionPerformed(ActionEvent e) {
//                delete(icon);
//            }
//            AbstractAction init(NamedIcon i) {
//                icon = i;
//                return this;
//            }
//        }.init(icon));
    QSignalMapper* mapper2 = new QSignalMapper();
    QAction* deleteAct = new QAction(tr("Delete Icon"), this);
    mapper1->setMapping(renameAct, icon);
    connect(deleteAct, SIGNAL(triggered()), mapper2, SLOT(map()));
    connect(mapper2, SIGNAL(mapped(QObject*)), this, SLOT(_delete(QObject*)));
    popup->addAction(deleteAct);
    //popup.show(e.getComponent(), e.getX(), e.getY());
    popup->exec(QCursor::pos());
}


#if 0
/*public*/ void mouseClicked(MouseEvent e) {
}
/*public*/ void mouseEntered(MouseEvent e) {
}
/*public*/ void mouseExited(MouseEvent e) {
}
/*public*/ void mousePressed(MouseEvent e) {
}
/*public*/ void mouseReleased(MouseEvent e) {
    if (e.isPopupTrigger()) {
        Container con = (Container)e.getSource();
        JLabel label = (JLabel)con.getComponent(0);
        NamedIcon icon = (NamedIcon)label.getIcon();
        showPopUp(e, icon);
    }
}

class DropJTree extends JTree implements DropTargetListener {
    DataFlavor dataFlavor;
    DropJTree (TreeModel model) {
        super (model);
        try {
            dataFlavor = new DataFlavor(ImageIndexEditor.IconDataFlavorMime);
        } catch (ClassNotFoundException cnfe) {
            cnfe.printStackTrace();
        }
        new DropTarget(this, DnDConstants.ACTION_COPY_OR_MOVE, this);
        //if (log->isDebugEnabled()) log->debug("DropJTree ctor");
    }
    /*public*/ void dragExit(DropTargetEvent dte) {
        //if (log->isDebugEnabled()) log->debug("DropJTree.dragExit ");
    }
    /*public*/ void dragEnter(DropTargetDragEvent dtde) {
        //if (log->isDebugEnabled()) log->debug("DropJTree.dragEnter ");
    }
    /*public*/ void dragOver(DropTargetDragEvent dtde) {
        //if (log->isDebugEnabled()) log->debug("DropJTree.dragOver ");
    }
    /*public*/ void dropActionChanged(DropTargetDragEvent dtde) {
        //if (log->isDebugEnabled()) log->debug("DropJTree.dropActionChanged ");
    }
    /*public*/ void drop(DropTargetDropEvent e) {
        try {
            Transferable tr = e.getTransferable();
            if(e.isDataFlavorSupported(dataFlavor)) {
                NamedIcon icon = (NamedIcon)tr.getTransferData(dataFlavor);
                Point pt = e.getLocation();
                if (log->isDebugEnabled())
                    log->debug("DropJTree.drop: Point= ("+pt.x+", "+pt.y+")");
                TreePath path = _dTree.getPathForLocation(pt.x, pt.y);
                if (path != NULL) {
                    CatalogTreeNode node = (CatalogTreeNode)path.getLastPathComponent();
                    e.acceptDrop(DnDConstants.ACTION_COPY_OR_MOVE);
                    node.addLeaf(icon.getName(), icon.getURL());
                    nodeChange(node, node.toString());
                    e.dropComplete(true);
                    if (log->isDebugEnabled())
                        log->debug("DropJTree.drop COMPLETED for "+icon.getURL());
                    return;
                }
            }
        } catch(IOException ioe) {
            ioe.printStackTrace();
        } catch(UnsupportedFlavorException ufe) {
            ufe.printStackTrace();
        }
        if (log->isDebugEnabled()) log->debug("DropJTree.drop REJECTED!");
        e.rejectDrop();
    }
}
#endif

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(CatalogPanel.class.getName());
//}
void CatalogPanel::on_tree_clicked(QModelIndex index)
{
 //QString path = model->filePath(index);
 QString path =index.data().toString();
 CatalogTreeNode* item = (CatalogTreeNode*)index.internalPointer();

 qDebug() << tr("selected item: row = %1, col = %2, path = %3").arg(index.row()).arg(index.column()).arg(path);
 //if(model->isDir(index))
 emit newDirectorySelected(item->toString());
 //QFileInfo info(item->path);
 updatePanel();
// if(info.isFile())
// {
//  QIcon icon = QIcon(item->path);
//  ui->tableWidget->clear();
//  ui->tableWidget->setColumnCount(1);
//  ui->tableWidget->setRowCount(1);
//  ui->tableWidget->horizontalHeader()->setHidden(true);
//  ui->tableWidget->verticalHeader()->setHidden(true);
//  QWidget* item = new QWidget();
//  item->setLayout(new QVBoxLayout);
//  QLabel* image = new QLabel;
//  image->resize(100, 100);
//  QString fullname = info.absoluteFilePath();
//  QPixmap pixmap(fullname);
//  if(pixmap.width() > pixmap.height() && pixmap.width() > 100)
//    pixmap = pixmap.scaledToWidth(100);
//  else if(pixmap.height() > 100)
//      pixmap = pixmap.scaledToHeight(100);
//  image->setPixmap( pixmap);
//  QLabel* name = new QLabel(info.fileName());
//  item->layout()->addWidget(image);
//  item->layout()->addWidget(name);
//  ui->tableWidget->setCellWidget(0,0,item);
//  ui->tableWidget->resizeColumnsToContents();
//  ui->tableWidget->resizeRowsToContents();

// }
}
//public class IconDisplayPanel extends JPanel implements MouseListener{
//        String _name;
//        NamedIcon _icon;

        /*public*/ CPIconDisplayPanel::CPIconDisplayPanel(QString leafName, NamedIcon* icon, CatalogPanel* catalogPanel) : JPanel()
{
            //super();
            _name = leafName;
            _icon = icon;
            this->catalogPanel = catalogPanel;
            // setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
            setLayout(new BorderLayout());
//            setOpaque(false);
            if (_name != "") {
                setBorderAndIcon(icon);
            }
//            addMouseListener(new IconListener());
        }

        NamedIcon* CPIconDisplayPanel::getIcon() {
            return _icon;
        }

        void CPIconDisplayPanel::setBorderAndIcon(NamedIcon* icon) {
            if (icon == nullptr) {
                catalogPanel->log->error(tr("IconDisplayPanel: No icon for \"%1\"").arg(_name));
                return;
            }
            try {
                JLabel* image;
                if (catalogPanel->_dragIcons) {
                    image = (JLabel*)new DragJLabel(new DataFlavor(ImageIndexEditor::IconDataFlavorMime));
                } else {
                    image = new JLabel();
                }
//                image.setOpaque(false);
                image->setName(_name);
                image->setToolTip(icon->getName());
                double scale;
                if (icon->getIconWidth() < 1 || icon->getIconHeight() < 1) {
                    image->setText(tr("invisible Icon"));
//   TODO:                 image->setForeground(QColor(Qt::lightGray));
                    scale = 0;
                } else {
                    scale = icon->reduceTo(catalogPanel->ICON_WIDTH, catalogPanel->ICON_HEIGHT, catalogPanel->ICON_SCALE);
                }
                image->setIcon(icon);
//                image.setHorizontalAlignment(JLabel.CENTER);
//                image.addMouseListener(new IconListener());
                ((QVBoxLayout*)layout())->addWidget(image, 0, Qt::AlignTop); //BorderLayout.NORTH);

                QString scaleMessage = tr("scale %1").arg(CatalogPanel::printDbl(scale, 2));
                JLabel* label = new JLabel(scaleMessage);
//                label.setOpaque(false);
//                label.setHorizontalAlignment(JLabel.CENTER);
                ((QVBoxLayout*)layout())->addWidget(label, 0, Qt::AlignCenter); // BorderLayout.CENTER);
                label = new JLabel(_name);
//                label.setOpaque(false);
//                label.setHorizontalAlignment(JLabel.CENTER);
//                label.addMouseListener(new IconListener());
                ((QVBoxLayout*)layout())->addWidget(label, 0, Qt::AlignBottom); //BorderLayout.SOUTH);
//                setBorder(BorderFactory.createEmptyBorder(2,2,2,2));
            } catch (ClassNotFoundException cnfe) {
                catalogPanel->log->error(tr("Unable to find class supporting %1").arg( /*Editor.POSITIONABLE_FLAVOR),*/ cnfe.getMessage()));
            }
        }

        /*public*/ QString CPIconDisplayPanel::getIconName() {
            return _name;
        }
        //@Override
        /*public*/ void CPIconDisplayPanel::mouseClicked(QMouseEvent* event) {
//            if (event.getSource() instanceof JLabel ) {
//                setSelection(this);
//            }
        }
        //@Override
        /*public*/ void mousePressed(QMouseEvent* event) {
        }
        //@Override
        /*public*/ void mouseReleased(QMouseEvent* event) {
        }
        //@Override
        /*public*/ void mouseEntered(QMouseEvent* event) {
        }
        //@Override
        /*public*/ void mouseExited(QMouseEvent* event) {
        }
    //}
