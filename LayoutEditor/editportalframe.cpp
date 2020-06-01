#include "editportalframe.h"
#include "oblock.h"
#include "controlpaneleditor.h"
#include "circuitbuilder.h"
#include "borderlayout.h"
#include "flowlayout.h"
#include <QPushButton>
#include <QSizePolicy>
#include "jtextfield.h"
#include "portalicon.h"
#include "portal.h"
#include "indicatortrack.h"
#include <QMessageBox>
#include "borderfactory.h"
#include "joptionpane.h"
#include <QListView>
#include "portallist.h"
#include "portalmanager.h"
#include "instancemanager.h"
#include "oblockmanager.h"
#include <QStringList>
#include <QVariant>
#include "vptr.h"
#include "box.h"
#include "joptionpane.h"
#include "dataflavor.h"
/**
 * <P>
 * @author  Pete Cressman Copyright: Copyright (c) 2011
 *
 */

// /*public*/ class EditPortalFrame extends jmri.util.JmriJFrame implements ListSelectionListener {


    //static java.util.ResourceBundle rbcp = ControlPanelEditor.rbcp;
/*static*/ int EditPortalFrame::STRUT_SIZE = 10;
/*static*/ bool EditPortalFrame::_firstInstance = true;
/*static*/ QPoint EditPortalFrame::_loc = QPoint();
/*static*/ QSize EditPortalFrame::_dim = QSize();

/* Ctor for fix a portal error  */
/*public*/ EditPortalFrame::EditPortalFrame(QString title, CircuitBuilder* parent, OBlock* block, Portal* portal, PortalIcon *icon)
 :   EditFrame()
{
 common(title, parent, block);
 QString name = portal->getName();
 _portalName->setText(name);
 _adjacentBlock = portal->getOpposingBlock(block);

 QString sb;// = new StringBuilder();
 if (icon != nullptr) {
     setSelected(icon);
 } else {
     sb.append(tr("Portal %1 needs an icon to indicate direction of warrants.").arg(name));
     sb.append("\n");
 }
 if (_canEdit) {
     QString msg = _parent->checkForPortals(block, "BlockPaths");
     if (msg.length() > 0) {
         sb.append(msg);
         sb.append("\n");
         sb.append(tr("portalIconPosA portal icon should touch both Blocks of the Portal\nIf the blocks are not adjacent, drag a second icon to the other block.ition"));
         sb.append("\n");
     } else {
         msg = _parent->checkForPortalIcons(block, "DirectionArrow");
         if (msg.length() > 0) {
             sb.append(msg);
             sb.append("\n");
         }
     }
 }
 if (sb.length() > 0) {
     JOptionPane::showMessageDialog(this, sb,
             tr("Track Circuit Incomplete"), JOptionPane::INFORMATION_MESSAGE);
 }
}

/*public*/ EditPortalFrame::EditPortalFrame(QString title, CircuitBuilder* parent, OBlock* block)
 : EditFrame(title, parent, block)
{
 common(title, parent, block);
 //super(title, parent, block);
 pack();
 QString msg = _parent->checkForTrackIcons(block, "BlockPortals");
 if (msg.length() > 0) {
     _canEdit = false;
     JOptionPane::showMessageDialog(this, msg,
             tr("Track Circuit Incomplete"), JOptionPane::INFORMATION_MESSAGE);
 }
}

/*private*/ void EditPortalFrame::common(QString title, CircuitBuilder* parent, OBlock* block)
{
}

//@Override
/*protected*/ JPanel* EditPortalFrame::makeContentPanel() {
    JPanel* portalPanel = new JPanel();
    portalPanel->setLayout(new QVBoxLayout());//portalPanel, BoxLayout.Y_AXIS));

    JPanel* panel = new JPanel(new FlowLayout());
    panel->layout()->addWidget(new JLabel(tr("Portals into and out of circuit  %1").arg(_homeBlock->getDisplayName())));
    portalPanel->layout()->addWidget(panel);
    _portalName = new JTextField();
    _portalList = new PortalList(_homeBlock, this);
    _portalList->addListSelectionListener((ListSelectionListener*)this);
    portalPanel->layout()->addWidget(/*new JScrollPane*/(_portalList));

    QPushButton* clearButton = new QPushButton(tr("Clear Selection"));
//    clearButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
    connect(clearButton, &QPushButton::clicked, [=]{
            clearListSelection();
//        }
    });
    panel = new JPanel(new FlowLayout());
    panel->layout()->addWidget(clearButton);
    portalPanel->layout()->addWidget(panel);
    portalPanel->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE));

    panel = new JPanel();
    panel->layout()->addWidget(CircuitBuilder::makeTextBoxPanel(
            false, _portalName, "portalName", true, nullptr));
    _portalName->resize(QSize(300, _portalName->sizeHint().height()));
    _portalName->setToolTip(tr("Enter text to create a Portal or change a portal name."));
    portalPanel->layout()->addWidget(panel);

    panel = new JPanel(new FlowLayout());
    QPushButton* changeButton = new QPushButton(tr("Change Name"));
//    changeButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
        connect(changeButton, &QPushButton::clicked, [=]{
            changePortalName();
//        }
    });
    changeButton->setToolTip(tr("Enter another name to change the name of a selection in the above list."));
    panel->layout()->addWidget(changeButton);

    QPushButton* deleteButton = new QPushButton(tr("Delete Portal"));
//    deleteButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
    connect(deleteButton, &QPushButton::clicked, [=]{
            deletePortal();
//        }
    });
    deleteButton->setToolTip(tr("Delete the selected portal and its icon."));
    panel->layout()->addWidget(deleteButton);
    portalPanel->layout()->addWidget(panel);

    panel = new JPanel();
    panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));
    portalPanel->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE));
    JLabel* l = new JLabel(tr("To make a new Portal, enter text into the Portal Name box,"));
    l->setAlignment(Qt::AlignLeft);
    panel->layout()->addWidget(l);
    l = new JLabel(tr("then drag the icon below to the panel to create both the Portal and its icon."));
    l->setAlignment(Qt::AlignLeft);
    panel->layout()->addWidget(l);
    panel->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE / 2));
    l = new JLabel(tr("To make an icon for a Portal in the list, select it from the list,"));
    l->setAlignment(Qt::AlignLeft);
    panel->layout()->addWidget(l);
    l = new JLabel(tr("then drag the icon below to its position between the circuits on the panel."));
    l->setAlignment(Qt::AlignLeft);
    panel->layout()->addWidget(l);
    JPanel* p = new JPanel(new FlowLayout());
    p->layout()->addWidget(panel);
    portalPanel->layout()->addWidget(p);

    portalPanel->layout()->addWidget(makeDndIconPanel());
    portalPanel->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE));
    portalPanel->layout()->addWidget(makeDoneButtonPanel());
    return portalPanel;
}

//@Override
/*protected*/ void EditPortalFrame::clearListSelection() {
    _portalList->clearSelection();
    _portalName->setText("");
    _parent->_editor->highlight(nullptr);
}

//@Override
/*public*/ void EditPortalFrame::valueChanged(ListSelectionEvent* e) {
    if (askForNameChange()) {
        return;
    }
    Portal* portal = VPtr<Portal>::asPtr(_portalList->getSelectedValue());
    if (portal != nullptr) {
        _portalName->setText(portal->getName());
        hightLightIcon(portal);
        _currentPortal = portal;
    } else {
        _portalName->setText("");
    }
}

/*private*/ void EditPortalFrame::hightLightIcon(Portal* portal) {
    QList<PortalIcon*>* piArray = _parent->getPortalIconMap(portal);
    if (piArray->isEmpty()) {
        _parent->_editor->highlight(nullptr);
    } else {
        PortalIcon* icon = piArray->value(0);
        icon->setStatus(PortalIcon::VISIBLE);
        _parent->_editor->highlight(icon);
    }
}

/*private*/ bool EditPortalFrame::askForNameChange() {
    QString name = _portalName->text();
    if (_currentPortal != nullptr && _currentPortal->getName() != (name)) {
        if (name.length() > 0) {
            int answer = JOptionPane::showConfirmDialog(this, tr("Do you want to change Portal name \"%1\" to \"%2\"?").arg(_currentPortal->getName()).arg(name),
                    tr("Make Portal"), JOptionPane::YES_NO_OPTION, JOptionPane::QUESTION_MESSAGE);
            if (answer == JOptionPane::YES_OPTION) {
                setName(_currentPortal, name);
                return true;
            }
        }
    }
    return false;
}

/*protected*/ void EditPortalFrame::setSelected(PortalIcon* icon) {
    if (!canEdit()) {
        return;
    }
    Portal* portal = icon->getPortal();
    _portalList->setSelectedValue(portal->getName(), true);
    _parent->_editor->highlight(icon);

}




#if 0
/*private*/ static class PortalCellRenderer extends JLabel implements ListCellRenderer {

    /*public*/ Component getListCellRendererComponent(
       JList list,              // the list
       Object value,            // value to display
       int index,               // cell index
       boolean isSelected,      // is the cell selected
       boolean cellHasFocus)    // does the cell have focus
    {
         String s = ((Portal)value).getDescription();
         setText(s);
         if (isSelected) {
             setBackground(list.getSelectionBackground());
             setForeground(list.getSelectionForeground());
         } else {
             setBackground(list.getBackground());
             setForeground(list.getForeground());
         }
         setEnabled(list.isEnabled());
         setFont(list.getFont());
         setOpaque(true);
         return this;
    }
}

/*private*/ void clearListSelection() {
    _portalList.clearSelection();
    _portalName.setText(NULL);
    _parent._editor.highlight(NULL);
}

/*public*/ void valueChanged(ListSelectionEvent e) {
    Portal portal = (Portal)_portalList.getSelectedValue();
    if (portal!=NULL) {
        _portalName.setText(portal.getName());
        _parent._editor.highlight(_parent.getPortalIconMap().get(portal.getName()));
    } else {
        _portalName.setText(NULL);
    }
}
#endif
#if 0
//class odelodel extends AbstractListModel {
    /*public*/ int PortalListModel::getSize() {
        return frame->_homeBlock->getPortals().size();
    }
    /*public*/ QObject* PortalListModel::getElementAt(int index) {
        return frame->_homeBlock->getPortals().value(index);
    }
    /*public*/ void PortalListModel::dataChange() {
        frame->fireContentsChanged(this, 0, 0);
    }
//}
#endif
/************************* end setup **************************/


/*private*/ void EditPortalFrame::changePortalName() {
    Portal* portal = VPtr<Portal>::asPtr(_portalList->getSelectedValue());
    QString oldName = portal->getName();
    QString name = _portalName->text();
    if (name==NULL || name.trimmed().length()==0 ) {
        JOptionPane::showMessageDialog(this, tr("Select a Portal from the above list. Enter the name change and press \"%1\".").arg(
                        tr("Make Portal"), JOptionPane::INFORMATION_MESSAGE));
        return;
    }
    setName(portal, name);
}

/*private*/ void EditPortalFrame::setName(Portal* portal, QString name) {
    QString msg = portal->setName(name);
    if (msg.isNull()) {
        _portalList->dataChange();
        hightLightIcon(portal);
    } else {
        JOptionPane::showMessageDialog(this, msg,
                tr("Make Portal"), JOptionPane::INFORMATION_MESSAGE);
    }
}



/*private*/ void EditPortalFrame::deletePortal() {
    QString name = _portalName->text();
    Portal* portal = VPtr<Portal>::asPtr(_portalList->getSelectedValue());
    if (portal == nullptr) {
     PortalManager* portalMgr = (PortalManager*)InstanceManager::getDefault("PortalManager");
     portal = portalMgr->getPortal(name);
 }
 if (portal == nullptr) {
     return;
 }
 if (!_suppressWarnings) {
  QVariantList vl = QVariantList() << tr("Yes") << tr("No") << tr("Cancel");
     int val = JOptionPane::showOptionDialog(this, tr("Delete portal \"%1\" and its icon?\nDeleting a portal modifies all paths using the portal.").arg(portal->getName()),
             tr("Warning"), JOptionPane::YES_NO_CANCEL_OPTION,
             JOptionPane::QUESTION_MESSAGE, QIcon(),
             vl,
             tr("No")); // default NO
     if (val == 2) {
         return;
     }
     if (val == 1) { // suppress future warnings
         _suppressWarnings = true;
     }
 }
 if (portal->dispose()) {
     _portalList->dataChange();
     _portalName->setText("");
     OBlock* oppBlock = portal->getOpposingBlock(_homeBlock);
     QList<PortalIcon*> removeList = QList<PortalIcon*>(*_parent->getPortalIconMap(portal));
     for (PortalIcon* icon : removeList) {
         _parent->getCircuitIcons(oppBlock)->removeOne(icon);
         icon->remove();  // will call _parent.deletePortalIcon(icon)
     }
 }
}

//@Override
/*protected*/ void EditPortalFrame::closingEvent(bool close) {
    QString sb;// = new StringBuffer();
    QString msg = _parent->checkForPortals(_homeBlock, "BlockPaths");
    if(msg.length() > 0) {
        sb.append(msg);
        sb.append("\n");
    }
    if (_canEdit) {
        msg = _parent->checkForPortalIcons(_homeBlock, "BlockPaths");
        if(msg.length() > 0) {
            sb.append(msg);
            sb.append("\n");
        }
    }
    EditFrame::closingEvent(close, sb);
}

/**
* Called after click on portal icon
*/
/*protected*/ QString EditPortalFrame::checkPortalIconForUpdate(PortalIcon* icon, bool moved)
{
 Portal* portal = icon->getPortal();
 if (portal == nullptr)
 {
      _parent->deletePortalIcon(icon);
      log->error("Removed PortalIcon without Portal");
      return nullptr;
 }
  QString name = portal->getName();
  OBlock* fromBlock = portal->getFromBlock();
  OBlock* toBlock = portal->getToBlock();
  if (!_homeBlock->equals(fromBlock) && !_homeBlock->equals(toBlock)) {
      _adjacentBlock = nullptr;
     return showIntersectMessage(nullptr, icon, moved);
  }

  if (_homeBlock->equals(fromBlock)) {
      _adjacentBlock = toBlock;
  } else {
      _adjacentBlock = fromBlock;
  }

  OBlock* block = findAdjacentBlock(icon);
  if (log->isDebugEnabled()) {
      log->debug(tr("checkPortalIconForUpdate(%1): _homeBlock= \"%2\" _adjacentBlock= \"%3\" findAdjacentBlock= \"%4\"").arg(
              moved).arg(_homeBlock->getDisplayName()).arg((_adjacentBlock==nullptr?"null":_adjacentBlock->getDisplayName())).arg(
                      (block==nullptr?"null":block->getDisplayName())));
  }
  if (_adjacentBlock == nullptr) { // maybe first time
      if (block != nullptr) {
          bool valid;
          if (_homeBlock->equals(fromBlock)) {
              valid = portal->setToBlock(block, true);
          } else {
              valid = portal->setFromBlock(block, true);
          }
          log->debug(tr("Adjacent block change of null to %1 is %2 valid.").arg(
                  block->getDisplayName()).arg((valid?"":"NOT")));
          _adjacentBlock = block;
      }
  } else {
      if (block != nullptr) {
          if (moved) {
              if (!block->equals(_adjacentBlock)) {
                  int result = JOptionPane::showConfirmDialog(this, tr("Do you want to change Portal \"%1\" connections to be between circuits \"%2\" and \"%3\"?").arg(
                          name).arg(_homeBlock->getDisplayName()).arg(block->getDisplayName()),
                          tr("Make Portal"), JOptionPane::YES_NO_OPTION,
                          JOptionPane::QUESTION_MESSAGE);
                  if (result == JOptionPane::YES_OPTION) {
                      bool valid;
                      if (_homeBlock->equals(fromBlock)) {
                          valid = portal->setToBlock(block, true);
                      } else {
                          valid = portal->setFromBlock(block, true);
                      }
                      log->debug(tr("Adjacent block change of %1 to %2 is %3 valid.").arg(
                              _adjacentBlock->getDisplayName()).arg(block->getDisplayName()).arg((valid?"":"NOT")));
                      _adjacentBlock = block;
                  }
              }
          }
      } else {
          // icon not positioned over another block
          if (_homeBlock->equals(fromBlock)) {
              if (toBlock != nullptr) {
                  return showIntersectMessage(toBlock, icon, moved);
              }
          } else {
              if (fromBlock != nullptr) {
                  return showIntersectMessage(fromBlock, icon, moved);
              }
          }
      }
  }

  QList<PortalIcon*>* piArray = _parent->getPortalIconMap(portal);
  bool checkHomeBlock = true;
  if (piArray->size() > 0) {
      if (_parent->iconIntersectsBlock(icon, _homeBlock)) {
          block = _adjacentBlock;
      } else {
          block = _homeBlock;
      }
      for (PortalIcon* ic : *piArray) {
          if (ic != (icon) && _parent->iconIntersectsBlock(ic, block)) {
              if (_parent->iconIntersectsBlock(ic, fromBlock) && _parent->iconIntersectsBlock(ic, toBlock)) {
                  _parent->deletePortalIcon(icon);
//                       _parent._editor.highlight(ic);
                 return tr("Duplicate PortalIcon. See highlighted icon. %1").arg(name);
              }
              // ic is a companion icon for non-contiguous blocks and it covers _homeBlock
              checkHomeBlock = false;
          }
      }
  }

  if (checkHomeBlock && !_parent->iconIntersectsBlock(icon, _homeBlock)) {
      return showIntersectMessage(_homeBlock, icon, moved);
  }

  setSelected(icon);
  return nullptr;
}

/*private*/ QString EditPortalFrame::showIntersectMessage(OBlock* block, PortalIcon* icon, bool moved) {
    QString msg = QString();
    if (block == nullptr) {
        msg = tr("Icon for %1 is not positioned on circuit \"%1\".").arg(_homeBlock->getDisplayName()).arg(icon->getNameString());
    } else {
        QList<Positionable*>* list = _parent->getCircuitIcons(block);
        if (list->isEmpty()) {
            msg = tr("Block circuit (OBlock) \"%1\" needs Indicator Track icons to add a %2 in CircuitBuilder.").arg(block->getDisplayName()).arg(tr("block Portal"));
        } else {
            msg = tr("Icon for %1 is not positioned on circuit \"%1\".").arg(block->getDisplayName()).arg(icon->getNameString());
        }
    }
    if (moved) {
        JOptionPane::showMessageDialog(this, msg,
                tr("Make Portal"), JOptionPane::INFORMATION_MESSAGE);
    }
    return msg;
}

/*
 * If icon is on the home block, find another intersecting block.
 */
/*private*/ OBlock* EditPortalFrame::findAdjacentBlock(PortalIcon* icon) {
    QList<OBlock*> neighbors = QList<OBlock*>();
    OBlockManager* manager = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
    QSet<NamedBean*> oblocks = manager->getNamedBeanSet();
    for (NamedBean* nb : oblocks) {
     OBlock* block = (OBlock*)nb;
        if (block->equals(_homeBlock)) {
            continue;
        }
        if (_parent->iconIntersectsBlock(icon, block)) {
            neighbors.append(block);
        }
    }
    OBlock* block = nullptr;
    if (neighbors.size() == 1) {
        block = neighbors.value(0);
    } else if (neighbors.size() > 1) {
        // show list
        block = neighbors.value(0);
        QVariantList selects = QVariantList();//[neighbors.size()];
        QListIterator<OBlock*> iter(neighbors);// .iterator();
        int i = 0;
        while (iter.hasNext()) {
            selects[i++] = iter.next()->getDisplayName();
        }
        QVariant select = JOptionPane::showInputDialog(this,tr("Choose which block the highlighted portal should connect to \"%1\".").arg(
                _homeBlock->getDisplayName()),tr("Question"),
                JOptionPane::QUESTION_MESSAGE, QIcon(), selects, QVariant());
        if (select != QVariant()) {
            //iter = neighbors.iterator();
         iter.toFront();
            while (iter.hasNext()) {
                block = iter.next();
                if (( select.toString()) == (block->getDisplayName())) {
                    break;
                }
            }
        }
    }
    if (log->isDebugEnabled()) {
        log->debug(tr("findAdjacentBlock: neighbors.size()= %1 return %2").arg(
                neighbors.size()).arg((block == nullptr ? "null" : block->getDisplayName())));
    }
    return block;
}



/********************** DnD *****************************/

/*protected*/ QWidget* EditPortalFrame::makeDndIconPanel() {
 _dndPanel = new JPanel();

 QString fileName = "resources/icons/throttles/RoundRedCircle20.png";
 NamedIcon* icon = new NamedIcon(fileName, fileName);
 JPanel* panel = new JPanel(new FlowLayout());
 panel->setBorder(BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black),
         tr("Portal")));
 try {
     JLabel* label = new EPIconDragJLabel(new DataFlavor(Editor::POSITIONABLE_FLAVOR),this);
     label->setIcon(icon);
     label->setName(tr("Portal"));
     panel->layout()->addWidget(label);
 } catch (ClassNotFoundException cnfe) {
     log->error(tr("Unable to find class supporting %1").arg(Editor::POSITIONABLE_FLAVOR, cnfe.getMessage()));
 }
 _dndPanel->layout()->addWidget(panel);
 return _dndPanel;
}

///*public*/ class IconDragJLabel extends DragJLabel {

    /*public*/ EPIconDragJLabel::EPIconDragJLabel(DataFlavor* flavor, EditPortalFrame* frame): DragJLabel(flavor) {
        //super(flavor);
 this->frame = frame;
    }
//@Override
    /*protected*/ bool EPIconDragJLabel::okToDrag() {
        QString name = frame->_portalName->text();
        if (name.isNull() || name.trimmed().length() == 0) {
            JOptionPane::showMessageDialog(this, tr("Enter the name for a new portal or select a portal from the above list."),
                    tr("Make Portal"), JOptionPane::INFORMATION_MESSAGE);
            return false;
        }
        PortalManager* portalMgr = (PortalManager*)InstanceManager::getDefault("PortalManager");
        Portal* portal = portalMgr->getPortal(name);
        if (portal == nullptr) {
            return true;
        }
        OBlock* toBlock = portal->getToBlock();
        OBlock* fromBlock = portal->getFromBlock();
        if (!frame->_homeBlock->equals(fromBlock) && !frame->_homeBlock->equals(toBlock)) {
            JOptionPane::showMessageDialog(this, tr("Portal \"%1\" is incomplete! It must have an OBlock on each side.").arg(name), /*fromBlock, toBlock),*/
                    tr("Make Portal"), JOptionPane::INFORMATION_MESSAGE);
            return false;
        }
        QList<PortalIcon*>* piArray = frame->_parent->getPortalIconMap(portal);
        for (PortalIcon* pi : *piArray) {
            frame->_parent->_editor->highlight(pi);
        }
        switch (piArray->size()) {
            case 0:
                return true;
            case 1:
            {
                PortalIcon* i = piArray->value(0);
                if (frame->_parent->iconIntersectsBlock(i, toBlock) && frame->_parent->iconIntersectsBlock(i,fromBlock)) {
                    JOptionPane::showMessageDialog(this, tr("Portal \"%1\" is defined.  See highlighted icon.").arg(name),
                            tr("Make Portal"), JOptionPane::INFORMATION_MESSAGE);
                    return false;
                }
                if (addSecondIcon) {
                    return true;
                }
                int result = JOptionPane::showConfirmDialog(this, tr("Do you want to add another icon to connect %1 to a non-adjacent block?").arg(name),
                        tr("Make Portal"), JOptionPane::YES_NO_OPTION, JOptionPane::QUESTION_MESSAGE);
                if (result == JOptionPane::YES_OPTION) {
                    addSecondIcon = true;
                    return true;
                }
                break;
            }
            default:
                JOptionPane::showMessageDialog(this, tr("Portal \"%1\" is defined.  See highlighted icon.").arg(name),
                        tr("Make Portal"), JOptionPane::INFORMATION_MESSAGE);
        }
        return false;
    }

    /*public*/ QObject* EPIconDragJLabel::getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException) {
     if (!isDataFlavorSupported(flavor)) {
                 return nullptr;
             }
             if (DataFlavor::stringFlavor->equals(flavor)) {
                 return nullptr;
             }
             QString name = frame->_portalName->text();
             Portal* portal = frame->_homeBlock->getPortalByName(name);
             if (portal == nullptr) {
                 PortalManager* portalMgr = (PortalManager*)InstanceManager::getDefault("PortalManager");
                 portal = portalMgr->createNewPortal(name);
                 portal->setFromBlock(frame->_homeBlock, false);
                 frame->_portalList->dataChange();
             }
             addSecondIcon = false;
             PortalIcon* icon = new PortalIcon(frame->_parent->_editor, portal);
             QList<Positionable*>* group = frame->_parent->getCircuitIcons(frame->_homeBlock);
             group->append(icon);
             frame->_parent->getPortalIconMap(portal)->append(icon);
             frame->_parent->_editor->setSelectionGroup(group);
             icon->setLevel(Editor::MARKERS);
             icon->setStatus(PortalIcon::VISIBLE);
             return icon;
    }
//}

/*public*/ QString EditPortalFrame::getClassName()
{
 return "jmri.jmrit.display.controlPanelEditor.EditPortalFrame";
}
