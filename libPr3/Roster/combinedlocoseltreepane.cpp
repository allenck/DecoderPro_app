#include "combinedlocoseltreepane.h"
#include <QBoxLayout>
#include <QRadioButton>
#include <QLabel>
#include <QTreeView>
#include "decoderfile.h"
#include "decoderindexfile.h"
#include "instancemanager.h"
#include <QButtonGroup>
#include "flowlayout.h"
#include "treenode.h"
#include "rosterentry.h"
#include "roster.h"
#include "jtogglebutton.h"
#include "fileutil.h"
#include "treepath.h"
#include <QSizePolicy>
#include "globalrosterentrycombobox.h"
#include <QItemSelectionModel>
#include <QPushButton>
#include "globalprogrammermanager.h"
#include "defaultprogrammermanager.h"

CombinedLocoSelTreePane::CombinedLocoSelTreePane(QWidget *parent) :
    CombinedLocoSelPane(parent)
{
 common();
 init();
}
/**
 * Provide GUI controls to select a known loco and/or new decoder.
 * <P>
 * This is an extension of the CombinedLocoSelPane class to use
 * a JTree instead of a JComboBox for the decoder selection.
 * The loco selection (Roster manipulation) parts are unchanged.
 * <P>
 * The JComboBox implementation always had to have selected entries, so
 * we added dummy "select from .." items at the top & used those to
 * indicate that there was no selection in that box.
 * Here, the lack of a selection indicates there's no selection.
 *
 * @author			Bob Jacobsen   Copyright (C) 2001, 2002
 * @version			$Revision: 22618 $
 */
///*public*/ class CombinedLocoSelTreePane extends CombinedLocoSelPane  {

/*public*/ CombinedLocoSelTreePane::CombinedLocoSelTreePane(QLabel* s, ProgModeSelector* selector, QWidget *parent)
    : CombinedLocoSelPane(s, selector, parent)
{
 //super(s);
 this->common();
 //init();
}
void CombinedLocoSelTreePane::common()
{
 showAll = new QRadioButton();
 showMatched = new QRadioButton();
 log = new Logger("CombinedLocoSelTreePane");
 selectedPath =  QStringList();
 dTree = NULL;
 // NOTE: The following hack makes sure that the tree control is present because layoutCoderSelection is not being overridden in CombinedLocoSelPane!
 QVBoxLayout* lay = (QVBoxLayout*)layout();
 int c = lay->count();
 for(int i=0; i < c; i++)
 {
  QLayoutItem* o = lay->itemAt(i);
  if(o->widget() != NULL && o->widget()->objectName() =="pane1a")
  {
   lay->insertWidget(i,layoutDecoderSelection(),0, Qt::AlignCenter);
   o->widget()->setVisible(false);
   lay->removeWidget(o->widget());
   //delete o->widget();
   break;
  }
 }
}

//    /*public*/ CombinedLocoSelTreePane() {
//            super();
//    }

/**
 * Create the panel used to select the decoder
 */
/*protected*/ QWidget* CombinedLocoSelTreePane::layoutDecoderSelection()
{
 QWidget* pane1a = new QWidget(/*new BorderLayout()*/);
 QHBoxLayout* pane1aLayout = new QHBoxLayout;
 pane1a->setLayout(pane1aLayout);
 pane1aLayout->addWidget(new QLabel(tr("Decoder Installed:")), 0, Qt::AlignTop);
 // create the list of manufacturers; get the list of decoders, and add elements
 this->bShowFiles = true;
 dModel = new InvisibleTreeModel(bShowFiles);
 dModel->createNewNode("Root", "title","tooltip");
 dTree = new QTreeView(/*dModel*/);
 dTree->setModel(dModel);
 //dTree->setMinimumSize(400, 400);
 dTree->setMinimumWidth(600);
 dRoot = dModel->getRoot();
 QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
 sizePolicy.setVerticalStretch(0);
 sizePolicy.setHorizontalStretch(0);
 sizePolicy.setHeightForWidth(dTree->sizePolicy().hasHeightForWidth());
 dTree->setSizePolicy(sizePolicy);
//    {
//        /*public*/ String getToolTipText(MouseEvent evt) {
//            if (getRowForLocation(evt.getX(), evt.getY()) == -1) return NULL;
//            TreePath curPath = getPathForLocation(evt.getX(), evt.getY());
//            return ((DecoderTreeNode)curPath.getLastPathComponent()).getToolTipText();
//        }
//    };
 dTree->setToolTip("Select decoder");

 QList<DecoderFile*> decoders = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->matchingDecoderList("", "", "", "", "", "");
 int len = decoders.size();
 DecoderTreeNode* mfgElement = NULL;
 DecoderTreeNode* familyElement = NULL;
 QMap<QString, DecoderTreeNode*> familyNameNode =  QMap<QString, DecoderTreeNode*>();
 for (int i = 0; i<len; i++)
 {
  DecoderFile* decoder = decoders.at(i);
  QString mfg = decoder->getMfg();
  QString family = decoder->getFamily();
  QString model = decoder->getModel();
  if( log->isDebugEnabled()) log->debug(" process "+mfg+"/"+family+"/"+model
                    +" on nodes "
                    +(mfgElement==NULL ? "<NULL>":mfgElement->toString()+"("+QString::number(mfgElement->childCount())+")")+"/"
                    +(familyElement==NULL ? "<NULL>":familyElement->toString()+"("+QString::number(familyElement->childCount())+")")
                );
  // build elements
  if (mfgElement==NULL || mfg!=(mfgElement->toString()) )
  {
   // need new mfg node
   QList<QVariant> data;
   data << mfg;
   mfgElement = new DecoderTreeNode(data, mfg,
                "CV8 = "+((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->mfgIdFromName(mfg), "", dRoot);
   //dModel.insertNodeInto(mfgElement, dRoot, dRoot->childCount());
   dRoot->appendChild(mfgElement);
   familyNameNode =  QMap<QString, DecoderTreeNode*>();
   familyElement = NULL;
  }
  QString famComment = decoders.at(i)->getFamilyComment();
  QString verString = decoders.at(i)->getVersionsAsString();
  QString hoverText = "";
  if (famComment == "" || famComment == NULL)
  {
   if (verString != "")
   {
    hoverText = "CV7=" + verString;
   }
  }
  else
  {
   if (verString == "")
   {
    hoverText = famComment;
   }
   else
   {
    hoverText = famComment + "  CV7=" + verString;
   }
  }
  if (familyElement==NULL || (family!=(familyElement->toString()) && !familyNameNode.contains(family) ))
  {
   // need new family node - is there only one model? Expect the
   // family element, plus the model element, so check i+2
   // to see if its the same, or if a single-decoder family
   // appears to have decoder names separate from the family name
   if ( (i+2>=len) ||
            decoders.at(i+2)->getFamily()==(family) ||
            decoders.at(i+1)->getModel()!=(family)
        )
   {
    // normal here; insert the new family element & exit
    log->debug("normal family update case: "+family);
    QList<QVariant> data;
    data << family;
    familyElement = new DecoderTreeNode(data, family,
                                            hoverText,
                                            decoders.at(i)->titleString(),mfgElement);
    //dModel.insertNodeInto(familyElement, mfgElement, mfgElement->childCount());
    mfgElement->appendChild(familyElement);
    familyNameNode.insert(family, familyElement);
    continue;
   }
   else
   {
    // this is short case; insert decoder entry (next) here
    log->debug("short case, i="+QString::number(i)+" family="+family+" next "+
                decoders.at(i+1)->getModel() );
    if (i+1 > len) log->error("Unexpected single entry for family: "+family);
    family = decoders.at(i+1)->getModel();
    QList<QVariant> data;
    data << family;
    familyElement = new DecoderTreeNode(data, family,
                                        hoverText,
                                        decoders.at(i)->titleString(),mfgElement);
    //dModel.insertNodeInto(familyElement, mfgElement, mfgElement->childCount());
    mfgElement->appendChild(familyElement);
    familyNameNode.insert(family, familyElement);
    i = i+1;
    continue;
   }
  }
  // insert at the decoder level, except if family name is the same
  if (family!=(model))
  {
   if(familyNameNode.contains(family))
    familyElement = familyNameNode.value(family);
//   dModel->insertNodeInto(new DecoderTreeNode(model,                                                    hoverText, decoders->at(i)->titleString()),familyElement, familyElement->childCount());
   QList<QVariant> data;
   data << model;
   DecoderTreeNode* node = new DecoderTreeNode(data, model, hoverText, decoders.at(i)->titleString(),familyElement);
   familyElement->appendChild(node);
  }
 }  // end of loop over decoders

 // build the tree GUI
// //pane1a.add(new JScrollPane(dTree), BorderLayout.CENTER);
 pane1aLayout->addWidget(dTree, 0, Qt::AlignHCenter);
// dTree.expandPath(new TreePath(dRoot));

// dTree.setRootVisible(false);
// dTree.setShowsRootHandles(true);
// dTree.setScrollsOnExpand(true);
// dTree.setExpandsSelectedPaths(true);

// dTree.getSelectionModel().setSelectionMode(DefaultTreeSelectionModel.SINGLE_TREE_SELECTION);
 // tree listener
 connect(dTree, SIGNAL(clicked(QModelIndex)), this, SLOT(OnTreeSelection(QModelIndex)));
// dTree.addTreeSelectionListener(dListener = new TreeSelectionListener() {
//        /*public*/ void valueChanged(TreeSelectionEvent e) {
//            if (!dTree.isSelectionEmpty() && dTree.getSelectionPath()!=NULL &&
//                    // can't be just a mfg, has to be at least a family
//                    dTree.getSelectionPath().getPathCount()>2 &&
//                    // can't be a multiple decoder selection
//                    dTree.getSelectionCount()<2) {
//                // decoder selected - reset and disable loco selection
//                log->debug("Selection event with "+dTree.getSelectionPath().toString());
//                if (locoBox != NULL) locoBox.setSelectedIndex(0);
//                go2.setEnabled(true);
//                go2.setRequestFocusEnabled(true);
//                go2.requestFocus();
//                go2.setToolTipText(tr("TipClickToOpen"));
//            } else {
//                // decoder not selected - require one
//                go2.setEnabled(false);
//                go2.setToolTipText(tr("TipSelectLoco"));
//            }
//        }
//    });

//      Mouselistener for doubleclick activation of proprammer
//    dTree.addMouseListener(new MouseAdapter(){
//        /*public*/ void mouseClicked(MouseEvent me){
//         // Clear any status messages and ensure the tree is in single path select mode
//         if (_statusLabel != NULL) _statusLabel.setText(tr("StateIdle"));
//         dTree.getSelectionModel().setSelectionMode(DefaultTreeSelectionModel.SINGLE_TREE_SELECTION);

//         if (me.getClickCount() == 2){
//             if (go2.isEnabled() && ((TreeNode)dTree.getSelectionPath().getLastPathComponent()).isLeaf()) go2.doClick();
//            }
//         }
//        } );

 viewButtons = new QWidget();
 FlowLayout* viewButtonsLayout = new FlowLayout;
 viewButtons->setLayout(viewButtonsLayout);
 iddecoder = addDecoderIdentButton();
 if (iddecoder!=NULL)
 {
  viewButtonsLayout->addWidget(iddecoder);
 }
 if (InstanceManager::getNullableDefault("GlobalProgrammerManager") != nullptr
         && ((DefaultProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager"))->isGlobalProgrammerAvailable())
 {
  showAll = new QRadioButton(tr("All"));
  showAll->setChecked(true);
  showMatched = new QRadioButton(tr("Matched Only"));
  QButtonGroup* group = new QButtonGroup();
  group->addButton(showAll);
  group->addButton(showMatched);
  viewButtonsLayout->addWidget(showAll);
  viewButtonsLayout->addWidget(showMatched);

  pane1aLayout->addWidget(viewButtons, 0, Qt::AlignBottom);
//  showAll.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                if (dModel.isActivatedFilter()) {
//                    dModel.activateFilter(false);
//                    dModel.reload();
//                    for(TreePath path:selectedPath){
//                        dTree.expandPath(path);
//                        dTree.addSelectionPath(path);
//                        dTree.scrollPathToVisible(path);
//                    }
//                  }
//                }
//            }
//        );
  connect(showAll, SIGNAL(clicked()), this, SLOT(On_showAll_clicked()));
//  showMatched.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                if (!dModel.isActivatedFilter()) {
//                    dModel.activateFilter(true);
//                    dModel.reload();
//                    for(TreePath path:selectedPath){
//                        dTree.expandPath(path);
//                        dTree.scrollPathToVisible(path);
//                    }
//                  }
//                }
//            }
//        );
  connect(showMatched, SIGNAL(clicked()), this, SLOT(On_showMatched_clicked()));
 }

 return pane1a;
}
void CombinedLocoSelTreePane::OnTreeSelection(QModelIndex index)
{
 DecoderTreeNode *item = static_cast<DecoderTreeNode*>(index.internalPointer());
 if (locoBox != NULL) locoBox->setCurrentIndex(0);
 if(item->childCount() == 0)
 {
  go2->setEnabled(true);
  log->debug(QString("go2 ") + (go2->isEnabled()?"enabled":"disabled"));
//     go2.setRequestFocusEnabled(true);
//     go2.requestFocus();
  go2->setFocus();
  go2->setToolTip(tr("Click to open the programmer"));
  _statusLabel->setText(go2->toolTip());
 }
 else
 {
  // decoder not selected - require one
  go2->setEnabled(false);
  go2->setToolTip(tr("Select a locomotive or decoder to enable"));
 }
}

void CombinedLocoSelTreePane::On_showAll_clicked()
{
// if (dModel->isActivatedFilter())
// {
//    dModel->activateFilter(false);
//    dModel->beginResetModel();
//    dModel->endResetModel();
//    foreach(TreePath* path,selectedPath){
//        dTree->expandPath(path);
//        dTree->addSelectionPath(path);
//        dTree->scrollPathToVisible(path);
//    }
//  }
}

void CombinedLocoSelTreePane::On_showMatched_clicked()
{
//    if (!dModel.isActivatedFilter()) {
//        dModel.activateFilter(true);
//        dModel.reload();
//        for(TreePath path:selectedPath){
//            dTree.expandPath(path);
//            dTree.scrollPathToVisible(path);
//        }
//      }
}

//@SuppressWarnings("unchecked")
/*public*/ void CombinedLocoSelTreePane::resetSelections()
{
#if 0
    Enumeration<DecoderTreeNode*> e = dRoot.breadthFirstEnumeration();
    while (e.hasMoreElements()) {
        e.nextElement().setVisible(false);
    }
    dModel.activateFilter(false);
    dModel.reload();
    showAll.setSelected(true);
    selectedPath = new ArrayList<TreePath>();
    dTree.expandPath(new TreePath(dRoot));
    dTree.setExpandsSelectedPaths(true);
    int row = dTree.getRowCount() - 1;
    while (row >= 0) {
      dTree.collapseRow(row);
      row--;
      }
#endif
}

/**
 * Decoder identify has matched one or more specific types
 */
//@SuppressWarnings("unchecked")
void CombinedLocoSelTreePane::updateForDecoderTypeID(QList<DecoderFile*>* pList)
{
 // find and select the first item
 if (log->isDebugEnabled())
 {
  QString buf =  QString("Identified "+QString::number(pList->size())+" matches: ");
  for (int i = 0 ; i< pList->size(); i++)
   buf.append(pList->at(i)->getModel()+":");
  log->debug(buf/*.toString()*/);
 }
 if (pList->size()<=0)
 {
  log->error("Found empty list in updateForDecoderTypeID, should not happen");
  return;
 }
 dTree->clearSelection();
 // If there are multiple matches change tree to allow multiple selections by the program
 // and issue a warning instruction in the status bar
 if (pList->size()>1)
 {
  //dTree.getSelectionModel().setSelectionMode(DefaultTreeSelectionModel.DISCONTIGUOUS_TREE_SELECTION);
  dTree->setSelectionMode(QAbstractItemView::MultiSelection);
  if(_statusLabel != NULL)
  _statusLabel->setText(tr("Multiple possible Decoders detected - Manually select from highlighted Decoders or Family"));
 }
 else //dTree.getSelectionModel().setSelectionMode(DefaultTreeSelectionModel.SINGLE_TREE_SELECTION);
  dTree->setSelectionMode(QAbstractItemView::SingleSelection);

 QList<DecoderTreeNode*> selectedNode =  QList<DecoderTreeNode*>();
 QList<DecoderTreeNode*> mfgNode =  QList<DecoderTreeNode*>();
 QList<DecoderTreeNode*> modelNode =  QList<DecoderTreeNode*>();
 QList<DecoderTreeNode*> familyNode =  QList<DecoderTreeNode*>();
 QItemSelectionModel * selectionModel = new QItemSelectionModel(dModel);
 QModelIndex first;
 QModelIndex last;

 // Select the decoder(s) in the tree
 for (int i=0; i < pList->size(); i++)
 {

  DecoderFile* f = pList->at(i);
  QString findMfg = f->getMfg();
  QString findFamily = f->getFamily();
  QString findModel = f->getModel();
#if 0
        Enumeration<DecoderTreeNode*> e = dRoot.breadthFirstEnumeration();
        while (e.hasMoreElements()) {
            //log->debug(node.getPath().toString());
            DecoderTreeNode* node = e.nextElement();
            // convert path to comparison string
            QList<TreeNode*> list = node.getPath();
            if (list.length == 3) {
                node.setVisible(true);
                // check for match to mfg, model, model
                if (list[1].toString()==(findMfg)
                    && list[2].toString()==(findModel))
                        {
                            if(!mfgNode.contains(list[1]))
                                mfgNode.add((DecoderTreeNode)list[1]);
                            if(!modelNode.contains(list[2]))
                                modelNode.add((DecoderTreeNode)list[2]);
                            TreePath path = new TreePath(node.getPath());
                            dTree.expandPath(path);
                            dTree.addSelectionPath(path);
                            dTree.scrollPathToVisible(path);
                            selectedNode.add(node);
                            selectedPath.add(path);
                            break;
                        }
            } else if (list.length == 4 ) {
                // check for match to mfg, family, model
                if (list[1].toString()==(findMfg)
                    && list[2].toString()==(findFamily)
                    && list[3].toString()==(findModel))
                        {
                            if(!mfgNode.contains(list[1]))
                                mfgNode.add((DecoderTreeNode)list[1]);
                            if(!modelNode.contains(list[3]))
                                modelNode.add((DecoderTreeNode)list[3]);
                            if(!familyNode.contains(list[2]))
                                familyNode.add((DecoderTreeNode)list[2]);
                            TreePath path = new TreePath(node.getPath());
                            dTree.expandPath(path);
                            dTree.addSelectionPath(path);
                            dTree.scrollPathToVisible(path);
                            selectedNode.add(node);
                            selectedPath.add(path);
                            break;
                        }
            } else {
                node.setVisible(false);
            }
        }
#else
  for(int row = 0; row < dTree->model()->rowCount(); row ++)
  {
   QModelIndex index = dModel->index(row,0);
   DecoderTreeNode *item = static_cast<DecoderTreeNode*>(index.internalPointer());
   if(item->data(0) == findMfg)
    dTree->expand(index);
   QList<DecoderTreeNode*> families = item->children();
   int familyRow = 0;
   foreach(DecoderTreeNode* family, families)
   {
    QModelIndex nextFamilyIndex = index.child(familyRow++, 0);
    DecoderTreeNode* familyItem = static_cast<DecoderTreeNode*>(nextFamilyIndex.internalPointer());
    QList<DecoderTreeNode*> models = family->children();
    int modelRow = 0;
    foreach(DecoderTreeNode* model, models)
    {
     if(item->data(0) == findMfg && family->data(0)==findFamily && model->data(0)== findModel)
     {
      QModelIndex nextModelIndex = nextFamilyIndex.child(modelRow, 0);
      DecoderTreeNode* nextmodelItem = static_cast<DecoderTreeNode*>(nextModelIndex.internalPointer());
      dTree->setCurrentIndex(nextModelIndex);
      model->setVisible(true);
      if(first.isValid())
       last = nextModelIndex;
      else
       first = nextModelIndex;
     }
     modelRow++;
    }
   }
  }
#endif
 }
 selectionModel->select(QItemSelection(first, last), QItemSelectionModel::SelectCurrent);
 QModelIndexList l = selectionModel->selectedIndexes();
 dTree->setSelectionModel(selectionModel);

 foreach(DecoderTreeNode* node, mfgNode)
 {
#if 0
        node->setVisible(true);
        Enumeration<DecoderTreeNode*> e = node.breadthFirstEnumeration();
        while (e.hasMoreElements())
        {
            DecoderTreeNode subnode = e.nextElement();
            if(subnode!=node)
            {
                subnode.setVisible(false);
    }
   }
#endif
  }
  foreach(DecoderTreeNode* node, familyNode)
  {
   node->setVisible(true);
  }
  foreach(DecoderTreeNode* node,modelNode)
  {
   node->setVisible(true);
  }
  foreach(DecoderTreeNode* node, selectedNode)
  {
   node->setVisible(true);
  }

  if(showMatched->isChecked())
  {
//   dModel.activateFilter(true);
//   dModel.reload();
//   for(TreePath path:selectedPath)
//   {
//    dTree.expandPath(path);
//    dTree.scrollPathToVisible(path);
  }
 }


/**
 * Decoder identify has not matched specific types, but did
 * find manufacturer match
 * @param pMfg Manufacturer name. This is passed to save time,
 *              as it has already been determined once.
 * @param pMfgID Manufacturer ID number (CV8)
 * @param pModelID Model ID number (CV7)
 */
//@SuppressWarnings("unchecked")
void CombinedLocoSelTreePane::updateForDecoderMfgID(QString pMfg, int pMfgID, int pModelID)
{
 QString msg = "Found mfg "+QString::number(pMfgID)+" ("+pMfg+") version "+QString::number(pModelID)+"; no such decoder defined";
 log->warn(msg);
 _statusLabel->setText(msg);
    // find this mfg to select it
 dTree->clearSelection();
    //Enumeration<DecoderTreeNode*> e = dRoot.breadthFirstEnumeration();
 QListIterator<DecoderTreeNode*> e(dRoot->children());
 QList<DecoderTreeNode*> selected =  QList<DecoderTreeNode*>();
 selectedPath = QStringList();
 while (e.hasNext())
 {
  //DecoderTreeNode* node = e.nextElement();
  DecoderTreeNode* node = e.next();
  if(node->parent()!=NULL && node->parent()->toString()==("Root")){
  if (node->toString()==(pMfg))
  {
   //TreePath* path =  TreePath(node->getPath());
   QString path = node->getPath();
//                dTree.expandPath(path);
//                dTree.addSelectionPath(path);
//                dTree.scrollPathToVisible(path);
   selectedPath.append(path);
   node->setVisible(true);
   selected.append(node);
  }
 }
  else
  {
   node->setVisible(false);
  }
 }
 foreach(DecoderTreeNode* node, selected)
 {
  node->setVisible(true);
  //Enumeration<DecoderTreeNode*> es = node.breadthFirstEnumeration();
  QListIterator<DecoderTreeNode*> es(node->children());

  while(es.hasNext())
  {
   es.next()->setVisible(true);
  }
 }
 if(showMatched->isChecked())
 {
//        dModel.activateFilter(true);
//        dModel.reload();
 }
}


/**
 * Decoder identify did not match anything, warn and clear selection
 */
void CombinedLocoSelTreePane::updateForDecoderNotID(int pMfgID, int pModelID) {
    QString msg = "Found mfg "+QString::number(pMfgID)+" version "+QString::number(pModelID)+"; no such manufacterer defined";
    log->warn(msg);
    _statusLabel->setText(msg);
    dTree->clearSelection();
}

/**
 *  Set the decoder selection to a specific decoder from a selected Loco.
 *  <P>
 *  This must not trigger an update event from the Tree selection, so
 *  we remove and replace the listener.
 */
//@SuppressWarnings("unchecked")
void CombinedLocoSelTreePane::setDecoderSelectionFromLoco(QString loco)
{
    // if there's a valid loco entry...
    RosterEntry* locoEntry = Roster::getDefault()->entryFromTitle(loco);
    if ( locoEntry == NULL) return;
//    dTree->removeTreeSelectionListener(dListener);
    dTree->clearSelection();
    // get the decoder type, it has to be there (assumption!),
    QString modelString = locoEntry->getDecoderModel();
    QString familyString = locoEntry->getDecoderFamily();
    QString titleString = DecoderFile::titleString(modelString, familyString);

    // find the decoder mfg
    ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->fileFromTitle(titleString)->getMfg();

    // close the entire GUI (not currently done, users want left open)
    //collapseAll();

    // find this one to select it
    //Enumeration<DefaultMutableTreeNode> e = dRoot.breadthFirstEnumeration();
 QListIterator<DecoderTreeNode*> e(dRoot->children());

 while (e.hasNext())
 {
  DecoderTreeNode* node = e.next();
  DecoderTreeNode* parentNode = node->parent();
  if (node->toString()==(modelString)
            && parentNode->toString()==(familyString))
  {
   QString path = node->getPath();
//   dTree->addSelectionPath(path);
//            dTree.scrollPathToVisible(path);
   break;
  }
 }
 // and restore the listener
 //dTree->addTreeSelectionListener(dListener);
}

/**
 * Convert the decoder selection UI result into a name.
 * @return The selected decoder type name, or NULL if none selected.
 */
/*protected*/ QString CombinedLocoSelTreePane::selectedDecoderType()
{
 if (!isDecoderSelected()) return NULL;
 else
 {
  //return ((DecoderTreeNode*)dTree->getLastSelectedPathComponent())->getTitle();
  QString type = ((DecoderTreeNode*)dTree->currentIndex().internalPointer())->title;
  return type;
 }
}

/**
 * Has the user selected a decoder type, either manually or
 * via a successful event?
 * @return true if a decoder type is selected
 */
bool CombinedLocoSelTreePane::isDecoderSelected()
{
 //return !dTree->isSelectionEmpty();
 return dTree->currentIndex().isValid();
}
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(CombinedLocoSelTreePane.class.getName());


//}
#if 0
/**
* The following has been taken from an example given in..
* http://www.java2s.com/Code/Java/Swing-Components/DecoderTreeNodeTreeExample.htm
* with extracts from http://www.codeguru.com/java/articles/143.shtml
*
*/
//class InvisibleTreeModel : public DefaultTreeModel {

/*protected*/ bool filterIsActive;

/*public*/ InvisibleTreeModel::InvisibleTreeModel(TreeNode* root, QObject *parent) : DefaultTreeModel(root, false, parent)
{
 //this(root, false);
 DefaultTreeModel(root, false);
 this->filterIsActive = false;
}

/*public*/ InvisibleTreeModel::InvisibleTreeModel(TreeNode* root, bool asksAllowsChildren, QObject *parent) : DefaultTreeModel(root, asksAllowsChildren, parent)
{
 //this(root, false, false);
 DefaultTreeModel(root, asksAllowsChildren);
 this->filterIsActive = false;
}

/*public*/ InvisibleTreeModel::InvisibleTreeModel(TreeNode* root, bool asksAllowsChildren,
  bool filterIsActive) : DefaultTreeModel(root, asksAllowsChildren, parent)
{
    DefaultTreeModel(root, asksAllowsChildren);
    this->filterIsActive = filterIsActive;
}

/*public*/ void InvisibleTreeModel::activateFilter(bool newValue) {
    filterIsActive = newValue;
}

/*public*/ bool InvisibleTreeModel::isActivatedFilter() {
return filterIsActive;
}

/*public*/ QObject* InvisibleTreeModel::getChild(QObject* parent, int index) {
    if (filterIsActive)
    {
        //if (parent instanceof DecoderTreeNode)
        if(qobject_cast<DecoderTreeNode*>(parent) !=NULL)
        {
          return ((DecoderTreeNode*) parent)->getChildAt(index,
              filterIsActive);
        }
    }
    return ((TreeNode*) parent)->getChildAt(index);
}

/*public*/ int InvisibleTreeModel::getChildCount(QObject* parent) {
    if (filterIsActive) {
        //if (parent instanceof DecoderTreeNode)
        if(qobject_cast<DecoderTreeNode*>(parent) !=NULL)
        {
            return ((DecoderTreeNode*) parent)->getChildCount(filterIsActive);
        }
    }
    return ((TreeNode*) parent)->getChildCount();
}
//};
#else
InvisibleTreeModel::InvisibleTreeModel(bool bShowFiles, QObject *parent) :
    QAbstractItemModel(parent)
{
 Q_UNUSED(parent);
 log  = new Logger("InvisibleTreeModel");
 QList<QVariant> rootData; // Define the number of columns in the model.
 rootData<<"Name";
 rootItem = new DecoderTreeNode(rootData, "", "", "", NULL);
 filter = QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Drives | QDir::Hidden;
 this->bShowFiles = bShowFiles;
 if(bShowFiles)
 {
  filter |= QDir::Files;
  nameFilters << "*.png" << "*.gif" << "*.jpg";
 }
 //setSupportedDragActions(Qt::DropAction);
}
InvisibleTreeModel::~InvisibleTreeModel()
{
 delete rootItem;
 delete log;
}
QModelIndex InvisibleTreeModel::index(int row,int column,const QModelIndex &parent)  const
{
 if (!hasIndex(row,column,parent))
  return QModelIndex();
 DecoderTreeNode *parentItem;
 if (!parent.isValid())
  parentItem = rootItem;
 else
  parentItem = static_cast<DecoderTreeNode*>(parent.internalPointer());
 DecoderTreeNode *childItem = parentItem->child(row);
 if (childItem)
  return createIndex(row,column,childItem);
 else
  return QModelIndex();
}
QModelIndex InvisibleTreeModel::parent(const QModelIndex &index) const
{
 if (!index.isValid())
  return QModelIndex();
 DecoderTreeNode *childItem = static_cast<DecoderTreeNode*>(index.internalPointer());
 DecoderTreeNode *parentItem = childItem->parent();
 if (parentItem == rootItem)
  return QModelIndex();
 return createIndex(parentItem->row(),0,parentItem);
}
int InvisibleTreeModel::rowCount(const QModelIndex &parent) const
{
 DecoderTreeNode *parentItem;
 if (parent.column() > 0)
  return 0;
 if (!parent.isValid())
  parentItem = rootItem;
 else
  parentItem = static_cast<DecoderTreeNode*>(parent.internalPointer());
 return parentItem->childCount();
}
int InvisibleTreeModel::columnCount(const QModelIndex &parent) const
{
 if (parent.isValid())
  return static_cast<DecoderTreeNode*>(parent.internalPointer())->columnCount();
 else
  return rootItem->columnCount();
}
QVariant InvisibleTreeModel::data(const QModelIndex &index,int role) const
{
 if (!index.isValid())
  return QVariant();
 DecoderTreeNode *item = static_cast<DecoderTreeNode*>(index.internalPointer());
 if(role == Qt::ToolTipRole)
  return item->toolTip;
 if (role != Qt::DisplayRole)
  return QVariant();
 return item->data(index.column());
}
Qt::ItemFlags InvisibleTreeModel::flags(const QModelIndex &index) const
{
 Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

 if (index.isValid())
  return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
 else
  return Qt::ItemIsDropEnabled | defaultFlags;
}
QVariant InvisibleTreeModel::headerData(int section,Qt::Orientation orientation,
int role) const
{
 if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
  return rootItem->data(section);
 return QVariant();
}
bool InvisibleTreeModel::createNewNode(QString title, QString name, QString toolTip)
{
// QDir dir(path);
//// if(!dir.exists())
////     return false;
// dir.setFilter(filter);
// dir.setNameFilters(nameFilters);
// if(dir.dirName() == "." || dir.dirName() == "..") return false;
 QList<QVariant> data;
 data << QVariant(title);
 DecoderTreeNode* item = new DecoderTreeNode(data, name, toolTip, title, rootItem);
 rootItem->appendChild(item);
 //processChildNode(name,item);
 //resetModel();
 return true;
}
void InvisibleTreeModel::processChildNode(QString name, QStringList familyList, DecoderTreeNode* parent)
{

 foreach(QString family, familyList)
 {
  QList<QVariant> data;
  data << QVariant(family) << "";
  DecoderTreeNode* item = new DecoderTreeNode(data, name, "","??", parent);
  parent->appendChild(item);
  //processChildNode(path+dirName+QDir::separator(),item);
 }
}
//void InvisibleTreeModel::setFilter(QDir::Filters filter)
//{
// beginResetModel();
// this->filter = filter;
// endResetModel();
//}
void InvisibleTreeModel::resetModel()
{
 beginResetModel();
 endResetModel();
}
QStringList InvisibleTreeModel::getFilter() { return nameFilters;}
QList<DecoderTreeNode*> DecoderTreeNode::children() { return childItems;}

void InvisibleTreeModel::removeNode(DecoderTreeNode *parent)
{
 beginResetModel();
 QListIterator<DecoderTreeNode*> it(parent->children());
 while(it.hasNext())
 {
  DecoderTreeNode* item = it.next();
  if(item != NULL)
   removeChild(item);
 }
 endResetModel();
}
/*private*/ void InvisibleTreeModel::removeChild(DecoderTreeNode *parent)
{
 QListIterator<DecoderTreeNode*> it(parent->children());
 while(it.hasNext())
 {
  DecoderTreeNode* item = it.next();
  if(item != NULL)
   removeChild(item);
 }
}
#if 0
bool InvisibleTreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
 QStringList l = data->formats();
 QString s_data = data->text();
 log->debug(s_data + " row= "+ QString::number(row)+ " column= "+QString::number(column));
 if(s_data.startsWith("DataFlavor["))
 {
  QString params=s_data.mid(11, s_data.length()-12);
  QStringList sl = params.split(";");
  foreach(QString s, sl)
  {
   QStringList pair = s.split("=");
   if(pair.at(0)=="path")
   {
    if(column == -1)
    {
      QFileInfo info(pair.at(1));
      QList<QVariant> data;
      beginResetModel();
      data << QVariant(info.baseName());
      QList<DecoderTreeNode*> l = rootItem->children();
      QString path = pair.at(1);
      if(path.startsWith("preference:"))
          path = FileUtil::getUserFilesPath()+path.mid(11);
      DecoderTreeNode* item = new DecoderTreeNode(data, path, l.at(0));
      l.at(0)->appendChild(item);
      processChildNode(pair.at(1),item);
      endResetModel();
    }
   }
  }
  return true;
 }
 return false;
}

Qt::DropActions InvisibleTreeModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}
QStringList InvisibleTreeModel::mimeTypes() const
{
    QStringList types;
    types << "application/vnd.text.list" << "text/plain";
    return types;
}
QMimeData *InvisibleTreeModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (const QModelIndex &index, indexes) {
        if (index.isValid()) {
            QString text = data(index, Qt::DisplayRole).toString();
            stream << text;
        }
    }

    mimeData->setData("application/vnd.text.list", encodedData);
    return mimeData;
}
#endif
DecoderTreeNode*  InvisibleTreeModel::getRoot() {return rootItem;}
#endif
#if 0
/*public*/ DecoderTreeNode::DecoderTreeNode(QString str, QString toolTipText, QString title,QObject *parent) {
    this(str);
    this->toolTipText = toolTipText;
    this->title = title;
}
/*public*/ QString DecoderTreeNode::getTitle() {
    return title;
}
/*public*/ QString DecoderTreeNode::getToolTipText() {
    return toolTipText;
}

/*public*/ DecoderTreeNode::DecoderTreeNode(QObject* userObject,QObject *parent) {
    this(userObject, true, false);
}

/*public*/ DecoderTreeNode::DecoderTreeNode(QObject* userObject, bool allowsChildren,
    bool isVisible, QObject *parent) {
    super(userObject, allowsChildren);
    this.isVisible = isVisible;
}

/*public*/ TreeNode* DecoderTreeNode::getChildAt(int index, bool filterIsActive) {
    if (!filterIsActive) {
        return super.getChildAt(index);
    }
    if (children == NULL) {
        throw ArrayIndexOutOfBoundsException("node has no children");
    }

    int realIndex = -1;
    int visibleIndex = -1;
    Enumeration<?> e = children.elements();
    while (e.hasMoreElements()) {
        DecoderTreeNode node = (DecoderTreeNode) e.nextElement();
        if (node.isVisible()) {
            visibleIndex++;
        }
        realIndex++;
        if (visibleIndex == index) {
            return (TreeNode) children.elementAt(realIndex);
        }
    }

    throw  ArrayIndexOutOfBoundsException("index unmatched");
    //return (TreeNode)children.elementAt(index);
}

/*public*/ int DecoderTreeNode::getChildCount(bool filterIsActive) {
    if (!filterIsActive) {
        return super->childCount();
    }
    if (children == NULL) {
        return 0;
    }

    int count = 0;
    Enumeration<?> e = children.elements();
    while (e.hasMoreElements()) {
        DecoderTreeNode node = (DecoderTreeNode) e.nextElement();
        if (node.isVisible()) {
            count++;
        }
    }

    return count;
}

/*public*/ void DecoderTreeNode::setVisible(boolean visible) {
    this.isVisible = visible;
}

/*public*/ bool DecoderTreeNode::isVisible() {
    return _isVisible;
}
};
#else
//DecoderTreeNode::DecoderTreeNode(const QList<QVariant> &data, QString path, DecoderTreeNode *parent)
//{
// parentItem = parent;
// itemData = data;
// this->path = path;
//}
DecoderTreeNode::DecoderTreeNode(const QList<QVariant> &data, QString name, QString toolTip, QString title, DecoderTreeNode *parent)
{
 parentItem = parent;
 itemData = data;
 this->name = name;
 this->title = title;
 this->toolTip = toolTip;
 _isVisible = true;
 childItems = QList<DecoderTreeNode*>();
}

DecoderTreeNode::~DecoderTreeNode()
{
 qDeleteAll(childItems);
}
void DecoderTreeNode::appendChild(DecoderTreeNode *item)
{
 childItems.append(item);
}
void DecoderTreeNode::clear()
{
 childItems.clear();
}
DecoderTreeNode *DecoderTreeNode::child(int row)
{
 return childItems.value(row);
}
int DecoderTreeNode::childCount() const
{
 return childItems.count();
}
int DecoderTreeNode::row() const
{
 if (parentItem)
  return parentItem->childItems.indexOf(const_cast<DecoderTreeNode*>(this));
 return 0;
}
int DecoderTreeNode::columnCount() const
{
 return itemData.count();
}
QVariant DecoderTreeNode::data(int column) const
{
 return QVariant(itemData.value(column));
}
DecoderTreeNode *DecoderTreeNode::parent()
{
 return parentItem;
}
QString DecoderTreeNode::toString()
{
 return name; // TODO:
}
void DecoderTreeNode::setVisible(bool bVisible) {_isVisible = bVisible;}
QString DecoderTreeNode::getPath() { return name;}
#endif
