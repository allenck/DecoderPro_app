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

//EditPortalFrame::EditPortalFrame(QWidget *parent) :
//    JmriJFrame(parent)
//{
//}
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
/*public*/ EditPortalFrame::EditPortalFrame(QString title, CircuitBuilder* parent, OBlock* block, Portal* portal, OBlock* adjacent) :   JmriJFrame((QWidget*)parent)
{
 common();
    //this(title, parent, block, true);
    _adjacentBlock = adjacent;
    QString name = portal->getName();
    _portalName->setText(name);
    _currentPortalName = name;
    _portalName->setText(name);

    if (_parent->getPortalIconMap().value(name) == NULL) {
        PortalIcon* pi = new PortalIcon(_parent->_editor, portal);
        pi->setLevel(Editor::MARKERS);
        pi->setStatus(PortalIcon::VISIBLE);
        _parent->addPortalIcon(pi);
        QList<Positionable*>* list = _parent->getCircuitGroup();
        QListIterator<Positionable*> iter(*list);
        while (iter.hasNext()) {
            Positionable* pos = iter.next();
            //f (pos instanceof IndicatorTrack)
            if(qobject_cast<IndicatorTrack*>(pos)!= NULL)
            {
                int x = pos->getX() + pos->getWidth() / 2;
                int y = pos->getY() + pos->getHeight() / 2;
                pi->setLocation(x, y);
                parent->_editor->putItem(pi);
                break;
            }
        }
    }
}
/*public*/ EditPortalFrame::EditPortalFrame(QString title, CircuitBuilder* parent, OBlock* block, bool update)
{
 common();
    _homeBlock = block;
    _parent = parent;
    setWindowTitle(QString(title).arg(_homeBlock->getDisplayName()));

//    addWindowListener(new java.awt.event.WindowAdapter() {
//        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//            closingEvent();
//        }
//    });
    addHelpMenu("package.jmri.jmrit.display.CircuitBuilder", true);

    QWidget* contentPane = new QWidget();
    contentPane->setLayout(new QVBoxLayout(contentPane/*, BoxLayout.Y_AXIS*/));

    ((QBoxLayout*)contentPane->layout())->addStrut(STRUT_SIZE);
    contentPane->layout()->addWidget(makePortalPanel(update));
    ((QBoxLayout*)contentPane->layout())->addStrut(STRUT_SIZE);

    QWidget* border = new QWidget();
    border->setLayout(new BorderLayout(10));
    border->layout()->addWidget(contentPane);
    //setContentPane(border);
    setCentralWidget(border);
    resize(500, 500);
    pack();
    if (_firstInstance) {
//        setLocationRelativeTo(_parent._editor);
        resize(500,500);
        _firstInstance = false;
    } else {
//        setLocation(_loc);
        resize(_dim);
    }
    setVisible(true);
}

void EditPortalFrame::common()
{
 log = new Logger("EditPortalFrame");
 _portalName = new JTextField();


}

/*private*/ QWidget* EditPortalFrame::MakeButtonPanel() {
    QWidget* buttonPanel = new QWidget();
    buttonPanel->setLayout(new QVBoxLayout);//(buttonPanel/*, BoxLayout.Y_AXIS*/));
    QWidget* panel = new QWidget();
    panel->setLayout(new FlowLayout());

    QPushButton* doneButton = new QPushButton(tr("Done"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setHeightForWidth(doneButton->sizePolicy().hasWidthForHeight());
    doneButton->setSizePolicy(sizePolicy);

//    doneButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                closingEvent();
//            }
//    });
    connect(doneButton, SIGNAL(clicked()), this, SLOT(closingEvent()));
    panel->layout()->addWidget(doneButton);
    buttonPanel->layout()->addWidget(panel);

    panel = new QWidget();
    panel->setLayout(new FlowLayout());
    panel->layout()->addWidget(buttonPanel);

    return panel;
}

/*private*/ QWidget* EditPortalFrame::makePortalPanel(bool update)
{
 QWidget* portalPanel = new QWidget();
 //portalPanel.setLayout(new BoxLayout(portalPanel, BoxLayout.Y_AXIS));
 QVBoxLayout* portalPanelLayout = new QVBoxLayout(portalPanel);
 portalPanelLayout->addStrut(STRUT_SIZE);

 QWidget* panel = new QWidget();
 QHBoxLayout* panelLayout = new QHBoxLayout(panel);
 panelLayout->addWidget(new QLabel(tr("Portals into and out of circuit %1").arg( _homeBlock->getDisplayName())));
 portalPanelLayout->addWidget(panel);
#if 0 // TODO
 _portalList = PortalList(_homeBlock);
 _portalList.addListSelectionListener(this);
 portalPanelLayout->addWidget(new JScrollPane(_portalList));
#endif
 QPushButton* clearButton = new QPushButton(tr("Clear Selection"));
// clearButton.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent a) {
//         clearListSelection();
//     }
// });
 connect(clearButton, SIGNAL(clicked()), this, SLOT(clearListSelection()));
 {
  panel = new QWidget();
  FlowLayout* panelLayout = new FlowLayout(panel);
  panelLayout->addWidget(clearButton);
  portalPanelLayout->addWidget(panel);
  portalPanelLayout->addStrut(STRUT_SIZE);
 }
 {
  panel = new QWidget();
  QVBoxLayout* panelLayout = new QVBoxLayout(panel);
  panelLayout->addWidget(CircuitBuilder::makeTextBoxPanel(
         false, _portalName, "portalName", true, NULL));
  _portalName->resize( QSize(300, _portalName->sizeHint().height()));
  _portalName->setToolTip(tr("Enter a name to create a new portal to OBlock \"%1\".").arg(
         _homeBlock->getDisplayName()));
  portalPanelLayout->addWidget(panel);
 }
 {
  panel = new QWidget();
  FlowLayout* panelLayout = new FlowLayout(panel);
  QPushButton* changeButton = new QPushButton(tr("Change Name"));
//  changeButton.addActionListener(new ActionListener() {
//      public void actionPerformed(ActionEvent a) {
//          changePortalName();
//      }
//  });
  connect(changeButton, SIGNAL(clicked()), this, SLOT(changePortalName()));
  changeButton->setToolTip(tr("name to change the name of a selection in the above list."));
  panelLayout->addWidget(changeButton);

  QPushButton* deleteButton = new QPushButton(tr("Delete Portal"));
  //  deleteButton.addActionListener(new ActionListener() {
  //     public void actionPerformed(ActionEvent a) {
  //         deletePortal();
  //     }
  //  });
  connect(deleteButton, SIGNAL(clicked()), this, SLOT(deletePortal()));
  deleteButton->setToolTip(tr("Delete the selected portal and its icon."));
  panelLayout->addWidget(deleteButton);

  portalPanelLayout->addWidget(panel);
 }
 {
  panel = new QWidget();
  //panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
  QVBoxLayout* panelLayout = new QVBoxLayout(panel);
  portalPanelLayout->addStrut(STRUT_SIZE);
  if (update)
  {
   QLabel* l = new QLabel(tr("A portal icon must touch both blocks of the Portal."));
   l->setAlignment(Qt::AlignLeft);
   panelLayout->addWidget(l);
   l = new JLabel(tr("Drag the highlighted icon to a position straddling the two highlighted Block circuits."));
   l->setAlignment(Qt::AlignLeft);
   panelLayout->addWidget(l);
   QWidget* p = new QWidget();
   QVBoxLayout* pLayout = new QVBoxLayout(p);
   pLayout->addWidget(panel);
   portalPanelLayout->addWidget(p);
  }
  else
  {
   QLabel* l = new QLabel(tr("To make a new portal, enter text into the Portal Name box,"));
   l->setAlignment(Qt::AlignLeft);
   panelLayout->addWidget(l);
   l = new QLabel(tr("below to the panel to create both the portal and its icon."));
   l->setAlignment(Qt::AlignLeft);
   panelLayout->addWidget(l);
   panelLayout->addStrut(STRUT_SIZE / 2);
   l = new QLabel(tr("make an icon for a portal in the list, select it from the list,"));
   l->setAlignment(Qt::AlignLeft);
   panelLayout->addWidget(l);
   l = new QLabel(tr("n below to its position between the circuits on the panel."));
   l->setAlignment(Qt::AlignLeft);
   panelLayout->addWidget(l);
   QWidget* p = new QWidget();
   QVBoxLayout* pLayout = new QVBoxLayout(p);
   panelLayout->addWidget(panel);
   portalPanelLayout->addWidget(p);
#if 0 // TODO
   portalPanelLayout->addWidget(makeDndIconPanel());
#endif
   portalPanelLayout->addStrut(STRUT_SIZE);
  }
 }
 portalPanelLayout->addWidget(MakeButtonPanel());
 return portalPanel;
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

class PortalListModel extends AbstractListModel {
    /*public*/ int getSize() {
        return _homeBlock.getPortals().size();
    }
    /*public*/ Object getElementAt(int index) {
        return _homeBlock.getPortals().get(index);
    }
    /*public*/ void dataChange() {
        fireContentsChanged(this, 0, 0);
    }
}

/************************* end setup **************************/
#endif
/**
* Is location of icon reasonable? if so, add it
*/
/*private*/ bool EditPortalFrame::checkPortalIcon(PortalIcon* icon) {
    QString msg = testPortalIcon(icon);
    if (msg!="") {
//        JOptionPane.showMessageDialog(this, msg,
//                tr("makePortal"), JOptionPane.INFORMATION_MESSAGE);
     QMessageBox::information(this, tr("Make Portal"), msg);
        _parent->_editor->highlight(icon);
        return false;
    }
    return true;
}

/*private*/ QString EditPortalFrame::testPortalIcon(PortalIcon* icon) {
    QList<Positionable*>* list = _parent->getCircuitIcons(_homeBlock);
    QString msg = NULL;
#if 0
    if (list==NULL || list.size()==0) {
        msg = tr("needIcons");
        return msg;
    }
    Portal portal = icon.getPortal();
    boolean ok = false;
    Rectangle homeRect = new Rectangle();
    Rectangle adjRect = new Rectangle();
    Positionable comp = NULL;
    _adjacentBlock = NULL;
    for (int i=0; i<list.size(); i++) {
        if (list.get(i) instanceof IndicatorTrack) {
            homeRect = list.get(i).getBounds(homeRect);
           if (iconIntersectsRect(icon, homeRect)) {
               ok = true;
               break;
            }
        }
    }
    if (!ok) {
        msg = java.text.MessageFormat.format(tr("iconNotOnCircuit"),
                                             icon.getNameString(), _homeBlock.getDisplayName());
        return msg;
    }

    ok = false;
    OBlockManager manager = InstanceManager.oBlockManagerInstance();
    String[] sysNames = manager.getSystemNameArray();
    for (int j = 0; j < sysNames.length; j++) {
        OBlock block = manager.getBySystemName(sysNames[j]);
        if (!block.equals(_homeBlock)) {
            list = _parent.getCircuitIcons(block);
            for (int i=0; i<list.size(); i++) {
                comp = list.get(i);
                if (_parent.isTrack(comp)) {
                    adjRect = comp.getBounds(adjRect);
                    if (iconIntersectsRect(icon, adjRect)) {
                        ok = true;
                        _adjacentBlock = block;
                        break;
                    }
                }
            }
        }
    }
    if (!ok) {
        msg = java.text.MessageFormat.format(tr("iconNotOnAdjacent"),
                                             icon.getNameString(), _homeBlock.getDisplayName());
        return msg;
    }
    if (portal.getToBlock()!=NULL && !_adjacentBlock.equals(portal.getToBlock())
                     && !_adjacentBlock.equals(portal.getFromBlock()) ) {
        msg = java.text.MessageFormat.format(tr("iconNotOnBlocks"),
                                             icon.getNameString(), portal.getFromBlockName(),
                                             _adjacentBlock.getDisplayName());
        return msg;
    }
#endif
    return msg;
}

/**
* Called after click on portal icon
*/
/*protected*/ void EditPortalFrame::checkPortalIconForUpdate(PortalIcon* icon, bool moved) {
    if (!checkPortalIcon(icon)) {
        return;
    }
#if 0 // TODO:
    Portal* portal = icon->getPortal();
    OBlock* block = portal->getToBlock();
    if (block==NULL) {
        portal->setToBlock(_adjacentBlock, false);
    } else {
        if (block != (_homeBlock)) {
            if (changeBlock(block)) {
                portal->setToBlock(_adjacentBlock, true);
            }
        } else {
            block = portal->getFromBlock();
            if (block==NULL) {
                portal->setFromBlock(_adjacentBlock, false);
            } else {
                if (block != (_homeBlock)) {
                    if (changeBlock(block)) {
                        portal->setFromBlock(_adjacentBlock, true);
                    }
                } else {
                    log->error("Portal has Home block "+_homeBlock+" on both sides.");
                }
            }
        }
    }
    _parent->getPortalIconMap().insert(icon->getName(), icon);
    _portalListModel->dataChange();
#endif
}
#if 0
/*private*/ boolean changeBlock(OBlock block) {
    if (block.equals(_adjacentBlock)) {
        return false;     // no change
    }
    //replace block and switch paths to new block.
    int result = JOptionPane.showConfirmDialog(this, java.text.MessageFormat.format(
                    tr("replacePortalBlock"),
                    _homeBlock.getDisplayName(), block.getDisplayName(),
                    _adjacentBlock.getDisplayName()),
                    tr("makePortal"), JOptionPane.YES_NO_OPTION,
                    JOptionPane.QUESTION_MESSAGE);
    if (result==JOptionPane.YES_OPTION) {
        return true;
    }
    return false;
}

/*private*/ void checkPortalIcons() {
    java.util.List<Portal> portals = _homeBlock.getPortals();
    Hashtable<String, PortalIcon> iconMap = _parent.getPortalIconMap();
    if (log.isDebugEnabled()) log.debug("checkPortalIcons: "+_homeBlock.getDisplayName()+
                                        " has "+portals.size()+" portals, iconMap has "+
                                        iconMap.size()+" icons");
    for (int i=0; i<portals.size(); i++) {
        PortalIcon icon = iconMap.get(portals.get(i).getName());
        if (icon==NULL) {
            JOptionPane.showMessageDialog(this, java.text.MessageFormat.format(
                    tr("noPortalIcon"), portals.get(i).getName()),
                    tr("makePortal"), JOptionPane.INFORMATION_MESSAGE);
            return;
        } else if (!checkPortalIcon(icon)) {
            return;
        }
    }
}

/**
* Check if icon is placed on the icons of a block
* Called when EditPortalFrame is closed
*/
static boolean portalIconOK(java.util.List<Positionable> list, PortalIcon icon) {
    if (icon==NULL) {
        return false;
    }
    Rectangle homeRect = new Rectangle();
    for (int i=0; i<list.size(); i++) {
        if (list.get(i) instanceof PortalIcon) {
            continue;
        }
        homeRect = list.get(i).getBounds(homeRect);
        if (iconIntersectsRect(icon, homeRect)) {
            return true;
        }
    }
    return false;
}

static boolean iconIntersectsRect(Positionable icon, Rectangle rect) {
    Rectangle iconRect = icon.getBounds(new Rectangle());
    return (iconRect.intersects(rect));
}

/*private*/ void changePortalName() {
    Portal portal = (Portal)_portalList.getSelectedValue();
    String oldName = portal.getName();
    String name = _portalName.getText();
    if (name==NULL || name.trim().length()==0 ) {
        JOptionPane.showMessageDialog(this, tr("changePortalName"),
                        tr("makePortal"), JOptionPane.INFORMATION_MESSAGE);
        return;
    }
    _parent.changePortalName(oldName, name);		// update maps
    String msg = portal.setName(name);
    if (msg==NULL) {
        _portalListModel.dataChange();
    } else {
        JOptionPane.showMessageDialog(this, msg,
                        tr("makePortal"), JOptionPane.INFORMATION_MESSAGE);
    }
}

/*private*/ void deletePortal() {
    String name = _portalName.getText();
    Portal portal = (Portal)_portalList.getSelectedValue();
    if (portal !=NULL) {
        int result = JOptionPane.showConfirmDialog(this, java.text.MessageFormat.format(
                            tr("confirmPortalDelete"), portal.getName()),
                        tr("makePortal"), JOptionPane.YES_NO_OPTION,
                        JOptionPane.QUESTION_MESSAGE);
        if (result==JOptionPane.YES_OPTION) {
            portal.dispose();
            _portalListModel.dataChange();
        }
    }
    PortalIcon icon = _parent.getPortalIconMap().get(name);
    if (icon!=NULL) {
        deletePortalIcon(icon);
    }
}

/*private*/ void deletePortalIcon(PortalIcon icon) {
    _parent.removePortal(icon.getName());
    _parent.getCircuitIcons(_homeBlock).remove(icon);
    icon.remove();
    _parent._editor.repaint();
}

protected void closingEvent() {
//        checkPortalIcons();
    _parent.closePortalFrame(_homeBlock);
    _loc = getLocation(_loc);
    _dim = getSize(_dim);
    dispose();
}

protected OBlock getHomeBlock() {
    return _homeBlock;
}

/********************** DnD *****************************/

protected QWidget* makeDndIconPanel() {
    QWidget* iconPanel = new QWidget();

    String fileName = "resources/icons/throttles/RoundRedCircle20.png";
    NamedIcon icon = new NamedIcon(fileName, fileName);
    QWidget* panel = new QWidget();
    panel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black),
                                                     tr("portal")));
    try {
        JLabel label = new IconDragJLabel(new DataFlavor(Editor.POSITIONABLE_FLAVOR));
        label.setIcon(icon);
        label.setName(tr("portal"));
        panel->layout()->addWidget(label);
    } catch (java.lang.ClassNotFoundException cnfe) {
        cnfe.printStackTrace();
    }
    iconPanel->layout()->addWidget(panel);
    return iconPanel;
}

/*public*/ class IconDragJLabel extends DragJLabel {

    /*public*/ IconDragJLabel(DataFlavor flavor) {
        super(flavor);
    }
    /*public*/ Object getTransferData(DataFlavor flavor) throws UnsupportedFlavorException,IOException {
        if (!isDataFlavorSupported(flavor)) {
            return NULL;
        }
        String name = _portalName.getText();
        if (name==NULL || name.trim().length()==0) {
            JOptionPane.showMessageDialog(this, tr("needPortalName"),
                            tr("makePortal"), JOptionPane.INFORMATION_MESSAGE);
            return NULL;
        } else {
            Portal p = _parent.getPortalByName(name);	// check all portals for name
            if (p!=NULL && !(_homeBlock.equals(p.getFromBlock()) || _homeBlock.equals(p.getToBlock())) ) {
                JOptionPane.showMessageDialog(this, java.text.MessageFormat.format(
                        tr("portalExists"), name, p.getFromBlockName(), p.getToBlockName()),
                        tr("makePortal"), JOptionPane.INFORMATION_MESSAGE);
                return NULL;
            }
            PortalIcon pi = _parent.getPortalIconMap().get(name);
            if (name.equals(_currentPortalName) || pi != NULL) {
                JOptionPane.showMessageDialog(this, java.text.MessageFormat.format(
                                tr("portalIconExists"), name),
                                tr("makePortal"), JOptionPane.INFORMATION_MESSAGE);
                _parent._editor.highlight(pi);
                return NULL;
            } else {
                Portal portal = _homeBlock.getPortalByName(name);
                if (portal==NULL) {
                    portal = new Portal(_homeBlock, name, NULL);
                    _portalListModel.dataChange();
                }
                pi = new PortalIcon(_parent._editor, portal);
                pi.setLevel(Editor.MARKERS);
                pi.setStatus(PortalIcon.BLOCK);
                _parent.addPortalIcon(pi);
            }
            _currentPortalName = name;
            return pi;
        }
    }
}
#endif
