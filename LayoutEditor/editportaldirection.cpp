#include "editportaldirection.h"
#include "portalicon.h"
#include "oblock.h"
#include <QBoxLayout>
#include "flowlayout.h"
#include <QPushButton>
#include "circuitbuilder.h"
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>
#include "controlpaneleditor.h"
#include "portal.h"
#include <QPoint>
#include "borderfactory.h"
#include "portallist.h"
#include "box.h"
#include "joptionpane.h"

//EditPortalDirection::EditPortalDirection(QWidget *parent) :
//  JmriJFrame(parent)
//{
//}

/**
 * <P>
 * @author Pete Cressman Copyright: Copyright (c) 2013
 *
 */
///*public*/ class EditPortalDirection extends jmri.util.JmriJFrame implements ActionListener, ListSelectionListener {

/**
 *
 */
///*private:*/ static final long serialVersionUID = 4492310660948299211L;

/*static*/ int EditPortalDirection::STRUT_SIZE = 10;
/*static*/ bool EditPortalDirection::_firstInstance = true;
/*static*/ QPoint EditPortalDirection::_loc = QPoint();
/*static*/ QSize EditPortalDirection::_dim = QSize();

/*public*/ EditPortalDirection::EditPortalDirection(QString title, CircuitBuilder* parent, OBlock* block) :
  EditFrame(title, parent, block)
{
 initContents();

    _homeBlock = block;
    _parent = parent;
#if 0
    //setTitle(java.text.MessageFormat.format(title, _homeBlock.getDisplayName()));
    setTitle(title.replace("%1", block->getDisplayName()));

//    addWindowListener(new java.awt.event.WindowAdapter() {
//        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//            closingEvent();
//        }
//    });
    addHelpMenu("package.jmri.jmrit.display.CircuitBuilder", true);

    QWidget* contentPane = new QWidget();
    //contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));
    QVBoxLayout* contentPaneLayout = new QVBoxLayout(contentPane);

    contentPaneLayout->addStrut(STRUT_SIZE);
    contentPaneLayout->addWidget(makePortalPanel());
    contentPaneLayout->addStrut(STRUT_SIZE);

    QWidget* border = new QWidget();
    //border.setLayout(new java.awt.BorderLayout(10, 10));
    QVBoxLayout* borderLayout = new QVBoxLayout(border);
    borderLayout->addWidget(contentPane);
    setCentralWidget(border);
    if (_firstInstance)
    {
     //setLocationRelativeTo(_parent->_editor);
//     setLocation(parent->_editor->pos().x(), parent->_editor->pos.y());
//            setSize(500,500);
        _firstInstance = false;
    } else {
        setLocation(_loc.x(), _loc.y());
        resize(_dim);
    }
#endif
    adjustSize();
    setVisible(true);
}



/*private:*/ QWidget*  EditPortalDirection::makeArrowPanel()
{
 JPanel* panel = new JPanel();
 //panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
 QVBoxLayout* panelLayout = new QVBoxLayout(panel);
 panel->setBorder(BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black),
         tr("Entry Icon")));
// QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
// panel->setStyleSheet(gbStyleSheet);
 panel->layout()->addWidget(Box::createHorizontalStrut(200));

 QButtonGroup* group = new QButtonGroup();
 _toButton = new QRadioButton(/*_parent->_editor->getPortalIcon*/(PortalIcon::TO_ARROW));
 //_toButton.setActionCommand(PortalIcon::TO_ARROW);
  //_toButton.addActionListener(this);
 connect(_toButton, &QRadioButton::clicked, [=]{
  actionPerformed(PortalIcon::TO_ARROW);
 });
  group->addButton(_toButton);
 panelLayout->addWidget(_toButton);

 _fromButton = new QRadioButton(/*_parent->_editor->getPortalIcon*/(PortalIcon::FROM_ARROW));
 //_fromButton.setActionCommand(PortalIcon::FROM_ARROW);
 //_fromButton.addActionListener(this);
 connect(_fromButton, &QRadioButton::clicked, [=]{
  actionPerformed(PortalIcon::FROM_ARROW);
 });
 group->addButton(_fromButton);
 panelLayout->addWidget(_fromButton);

 _noButton = new QRadioButton(tr("No Icon")/*, _parent->_editor->getPortalIcon(PortalIcon::HIDDEN)*/);
// _noButton.setVerticalTextPosition(AbstractButton.CENTER);
// _noButton.setHorizontalTextPosition(AbstractButton.CENTER);
 //_noButton.setActionCommand(PortalIcon::HIDDEN);
 //_noButton.addActionListener(this);
 connect(_noButton, &QRadioButton::clicked, [=]{
  actionPerformed(PortalIcon::PortalIcon::HIDDEN);
 });
 group->addButton(_noButton);
 panelLayout->addWidget(_noButton);

 return panel;
}

//@Override
/*protected*/ JPanel* EditPortalDirection::makeContentPanel() {
    JPanel* portalPanel = new JPanel();
    portalPanel->setLayout(new QVBoxLayout());//portalPanel, BoxLayout.Y_AXIS));

    JPanel* panel = new JPanel(new FlowLayout);
    panel->layout()->addWidget(new JLabel(tr("Portal %1").arg(_homeBlock->getDisplayName())));
    portalPanel->layout()->addWidget(panel);

    _portalList = new PortalList(_homeBlock, this);
    _portalList->addListSelectionListener((ListSelectionListener*)this);
    portalPanel->layout()->addWidget(/*new JScrollPane*/(_portalList));

    portalPanel->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE));

    panel = new JPanel();
    panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));

    JLabel* l = new JLabel(tr("Set the icons that indicate entry into block \"%1\".").arg(_homeBlock->getDisplayName()));
    l->setAlignmentX(/*JComponent::LEFT_ALIGNMENT*/Qt::AlignLeft);
    panel->layout()->addWidget(l);
    panel->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE / 2));
    l = new JLabel(tr("The icon shows the direction of movement"));
    l->setAlignmentX(/*JComponent.LEFT_ALIGNMENT*/Qt::AlignLeft);
    panel->layout()->addWidget( l);
    l = new JLabel(tr("when a Warrant is allocated and set."));
    l->setAlignmentX(/*JComponent.LEFT_ALIGNMENT*/Qt::AlignLeft);
    panel->layout()->addWidget( l);
    panel->layout()->addWidget( Box::createVerticalStrut(STRUT_SIZE));
    l = new JLabel(tr("Select a Portal to show its entry direction into the block."));
    l->setAlignmentX(/*JComponent.LEFT_ALIGNMENT*/Qt::AlignLeft);
    panel->layout()->addWidget( l);
    l = new JLabel(tr("Select the desired icon below to change the direction icon."));
    l->setAlignmentX(/*JComponent.LEFT_ALIGNMENT*/Qt::AlignLeft);
    panel->layout()->addWidget( l);
    portalPanel->layout()->addWidget( panel);

    portalPanel->layout()->addWidget( Box::createVerticalStrut(STRUT_SIZE));
    panel = new JPanel(new FlowLayout());
    panel->layout()->addWidget( makeArrowPanel());
    portalPanel->layout()->addWidget( panel);

    portalPanel->layout()->addWidget( Box::createVerticalStrut(STRUT_SIZE));

    portalPanel->layout()->addWidget( makeDoneButtonPanel());
    return portalPanel;
}

//@Override
/*protected*/ void EditPortalDirection::clearListSelection() {
    _portalList->clearSelection();
    _parent->_editor->highlight(nullptr);
}

/**
 * *********************** end setup *************************
 */
/*public*/ void EditPortalDirection::valueChanged(ListSelectionEvent* e)
{
 Portal* portal = VPtr<Portal>::asPtr(_portalList->getSelectedValue());
 if (portal != nullptr) {
     QList<PortalIcon*>* piArray = _parent->getPortalIconMap(portal);
     if (piArray->isEmpty()) {
         JOptionPane::showMessageDialog(this, tr("Portal %1 needs an icon to indicate direction of warrants.").arg(portal->getName()),
                 tr("Track Circuit Incomplete"), JOptionPane::INFORMATION_MESSAGE);
         clearListSelection();
     } else {
         for (PortalIcon* icon : *piArray) {
             setPortalIcon(icon, false);
         }
     }
 }
}

/*public*/ void EditPortalDirection::actionPerformed(QString actionCmd) {
    if (_icon == NULL) {
        return;
    }
    if (PortalIcon::TO_ARROW== actionCmd) {
        _icon->setIcon(PortalIcon::TO_ARROW, _parent->_editor->getPortalIcon(PortalIcon::TO_ARROW));
        _icon->setIcon(PortalIcon::FROM_ARROW, _parent->_editor->getPortalIcon(PortalIcon::FROM_ARROW));
        _icon->setArrowOrientatuon(true);
        _icon->setHideArrows(false);
    }
    else if (PortalIcon::FROM_ARROW== actionCmd) {
        _icon->setIcon(PortalIcon::TO_ARROW, _parent->_editor->getPortalIcon(PortalIcon::FROM_ARROW));
        _icon->setIcon(PortalIcon::FROM_ARROW, _parent->_editor->getPortalIcon(PortalIcon::TO_ARROW));
        _icon->setArrowOrientatuon(false);
        _icon->setHideArrows(false);
    }
    else if (PortalIcon::HIDDEN== actionCmd)
    {
         _icon->setIcon(PortalIcon::TO_ARROW,_parent->_editor->getPortalIcon(PortalIcon::HIDDEN));
         _icon->setArrowOrientatuon(true);
        _icon->setHideArrows(true);
        _icon->setStatus(PortalIcon::HIDDEN);
        return;
    }
    _icon->setStatus(PortalIcon::TO_ARROW);
}

/*protected*/ void EditPortalDirection::setPortalIcon(PortalIcon* icon, bool setValue) {
    _parent->_editor->highlight(icon);
    if (_icon != NULL) {
        _icon->setStatus(PortalIcon::VISIBLE);
    }
    _icon = icon;
    if (_icon != NULL) {
        if (_icon->getArrowHide()) {
            _icon->setStatus(PortalIcon::HIDDEN);
        } else {
            OBlock* toBlock = _icon->getPortal()->getToBlock();
            if (_homeBlock==(toBlock)) {
                _icon->setStatus(PortalIcon::TO_ARROW);
            } else {
                _icon->setStatus(PortalIcon::FROM_ARROW);
            }
        }
//        _toButton->setIcon(_icon->getIcon(PortalIcon::TO_ARROW));
//        _fromButton.setIcon(_icon->getIcon(PortalIcon::FROM_ARROW));
        if (setValue) {
//            _portalList.setSelectedValue(_icon->getPortal(), true);
        }
    }
}

/*protected*/ void EditPortalDirection::closingEvent(bool close)
{
 QString sb;// = new StringBuffer();
  QString msg = _parent->checkForPortals(_homeBlock, "BlockPaths");
  if (msg.length() > 0) {
      sb.append(msg);
      sb.append("\n");
      close = true;
  }
  msg = _parent->checkForPortalIcons(_homeBlock, "DirectionArrow");
  if (msg.length() > 0) {
      sb.append(msg);
      sb.append("\n");
      close = true;
  }
  EditFrame::closingEvent(close, sb);
}

/*protected*/ OBlock* EditPortalDirection::getHomeBlock() {
    return _homeBlock;
}

/*public*/ QString EditPortalDirection::getClassName()
{
 return "jmri.jmrit.display.controlPanelEditor.EditPortalDirection";
}
