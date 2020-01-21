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
  JmriJFrame((QWidget*)parent)
{
    _homeBlock = block;
    _parent = parent;
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
    adjustSize();
    setVisible(true);
}

/*private:*/ QWidget* EditPortalDirection::makeDoneButtonPanel()
{
 QWidget* buttonPanel = new QWidget();
 //buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.Y_AXIS));
 QVBoxLayout* buttonPanelLayout = new QVBoxLayout(buttonPanel);
 QWidget* panel = new QWidget();
 //panel.setLayout(new FlowLayout());
 FlowLayout* panelLayout = new FlowLayout(panel);

 QPushButton* doneButton = new QPushButton(tr("Done"));
//    doneButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            closingEvent();
//        }
//    });
 connect(doneButton, SIGNAL(clicked()), this, SLOT(closingEvent()));
 panelLayout->addWidget(doneButton);
 buttonPanelLayout->addWidget(panel);
 {
  panel = new QWidget();
  //panel.setLayout(new FlowLayout());
  FlowLayout* panelLayout = new FlowLayout(panel);
  panelLayout->addWidget(buttonPanel);
 }
 return panel;
}

/*private:*/ QWidget*  EditPortalDirection::makeArrowPanel()
{
 QGroupBox* panel = new QGroupBox("Entry Icon");
 //panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
 QVBoxLayout* panelLayout = new QVBoxLayout(panel);
 //panel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(java.awt.Color.black),
//         Bundle.getMessage("ArrowIconsTitle")));
 QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
 panel->setStyleSheet(gbStyleSheet);
 panelLayout->addStrut(200);

 QSignalMapper* group = new QSignalMapper();
 _toButton = new QRadioButton(/*_parent->_editor->getPortalIcon*/(PortalIcon::TO_ARROW));
 //_toButton.setActionCommand(PortalIcon::TO_ARROW);
 group->setMapping(_toButton,PortalIcon::TO_ARROW);
 connect(_toButton, SIGNAL(clicked()), group, SLOT(map()));
 //_toButton.addActionListener(this);
 panelLayout->addWidget(_toButton);

 _fromButton = new QRadioButton(/*_parent->_editor->getPortalIcon*/(PortalIcon::FROM_ARROW));
 //_fromButton.setActionCommand(PortalIcon::FROM_ARROW);
 group->setMapping(_fromButton, PortalIcon::FROM_ARROW);
 //_fromButton.addActionListener(this);
 connect(_fromButton, SIGNAL(clicked()), this, SLOT(map()));
 //group.add(_fromButton);
 panelLayout->addWidget(_fromButton);

 _noButton = new QRadioButton(tr("No Icon")/*, _parent->_editor->getPortalIcon(PortalIcon::HIDDEN)*/);
// _noButton.setVerticalTextPosition(AbstractButton.CENTER);
// _noButton.setHorizontalTextPosition(AbstractButton.CENTER);
 //_noButton.setActionCommand(PortalIcon::HIDDEN);
 //_noButton.addActionListener(this);
 group->setMapping(_noButton, PortalIcon::HIDDEN);
 connect(_noButton, SIGNAL(clicked()), group, SLOT(map()));
 panelLayout->addWidget(_noButton);
 connect(group, SIGNAL(mapped(QString)), this, SLOT(actionPerformed(QString)));

 return panel;
}

/*private:*/ QWidget* EditPortalDirection::makePortalPanel()
{
    QWidget* portalPanel = new QWidget();
    //portalPanel.setLayout(new BoxLayout(portalPanel, BoxLayout.Y_AXIS));
    QVBoxLayout* portalPanelLayout = new QVBoxLayout(portalPanel);
#if 0
    _portalList = new PortalList(_homeBlock);
    _portalList.addListSelectionListener(this);
    portalPanelLayout->addWidget(new JScrollPane(_portalList));

    portalPanelLayout->addStrut(STRUT_SIZE));

    QWidget* panel = new QWidget();
    panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
    JLabel l = new JLabel(Bundle.getMessage("PortalDirection1", _homeBlock.getDisplayName()));
    l.setAlignmentX(JComponent.LEFT_ALIGNMENT);
    panelLayout->addWidget(l);
    panelLayout->addWidget(STRUT_SIZE / 2));
    l = new JLabel(Bundle.getMessage("PortalDirection2"));
    l.setAlignmentX(JComponent.LEFT_ALIGNMENT);
    panelLayout->addWidget(l);
    l = new JLabel(Bundle.getMessage("PortalDirection3"));
    l.setAlignmentX(JComponent.LEFT_ALIGNMENT);
    panelLayout->addWidget(l);
    panelLayout->addWidget(STRUT_SIZE));
    l = new JLabel(Bundle.getMessage("PortalDirection4"));
    l.setAlignmentX(JComponent.LEFT_ALIGNMENT);
    panelLayout->addWidget(l);
    l = new JLabel(Bundle.getMessage("PortalDirection5"));
    l.setAlignmentX(JComponent.LEFT_ALIGNMENT);
    panelLayout->addWidget(l);
    portalPanelLayout->addWidget(panel);

    portalPanelLayout->addWidget(STRUT_SIZE));
    panel = new QWidget();
//        panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
    panelLayout->addWidget(makeArrowPanel());
    portalPanelLayout->addWidget(panel);
#endif
    portalPanelLayout->addStrut(STRUT_SIZE);

    portalPanelLayout->addWidget(makeDoneButtonPanel());
    return portalPanel;
}

/**
 * *********************** end setup *************************
 */
/*public*/ void EditPortalDirection::valueChanged(ListSelectionEvent* e)
{
#if 0
    Portal* portal = _portalList.getSelectedValue();
    if (portal != NULL) {
        PortalIcon* icon = _parent.getPortalIconMap().get(portal.getName());
        setPortalIcon(icon, false);
    }
#endif
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
//        	_icon->setIcon(PortalIcon::TO_ARROW,_parent->_editor->getPortalIcon(PortalIcon::HIDDEN));
//        	_icon->setArrowOrientatuon(true);
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

/*protected*/ void EditPortalDirection::closingEvent()
{
 _parent->closePortalDirection(_homeBlock);
// _loc = pos(_loc.x(), _loc.y());
// _dim = size(_dim.x(), _dim.y());
 dispose();
}

/*protected*/ OBlock* EditPortalDirection::getHomeBlock() {
    return _homeBlock;
}

/*public*/ QString EditPortalDirection::getClassName()
{
 return "jmri.jmrit.display.controlPanelEditor.EditPortalDirection";
}
