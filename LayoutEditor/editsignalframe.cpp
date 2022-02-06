#include "editsignalframe.h"
#include "loggerfactory.h"
#include <qlabel.h>
#include "oblock.h"
#include "portallist.h"
#include "listselectionlistener.h"
#include "box.h"
#include <QPushButton>
#include "circuitbuilder.h"
#include "controlpaneleditor.h"
#include "jtextfield.h"
#include "joptionpane.h"
#include "openpicklistbutton.h"
#include "portal.h"
#include "lengthpanel.h"
#include "instancemanager.h"
#include "signalmastmanager.h"
#include "signalheadmanager.h"
#include "signalhead.h"
#include "signalmast.h"
#include "portalicon.h"
#include "signalheadicon.h"
#include "signalmasticon.h"

/**
 *
 * @author Pete Cressman Copyright: Copyright (c) 2019
 *
 */
///*public*/ class EditSignalFrame extends EditFrame implements ListSelectionListener {


    /*public*/ EditSignalFrame::EditSignalFrame(QString title, CircuitBuilder* parent, OBlock* block) : EditFrame(title, parent, block){
        //super(title, parent, block);
 initContents();
        checkCircuitIcons("BlockSignal");
        pack();
    }

    //@Override
    /*protected*/ JPanel* EditSignalFrame::makeContentPanel() {
        JPanel* signalPanel = new JPanel();
        signalPanel->setLayout(new QVBoxLayout());//signalPanel, BoxLayout.Y_AXIS));

        JPanel* panel = new JPanel();
        panel->layout()->addWidget(new QLabel(tr("Portals into and out of circuit \"%1\"").arg(_homeBlock->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME))));
        signalPanel->layout()->addWidget(panel);

        _portalList = new PortalList(_homeBlock, this);
        _portalList->addListSelectionListener((ListSelectionListener*)this);
        signalPanel->layout()->addWidget(/*new JScrollPane*/(_portalList));
        signalPanel->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE));

        QPushButton* clearButton = new QPushButton(tr("Clear Selection"));
//        clearButton.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent a) {
        connect(clearButton, &QPushButton::clicked, [=]{
                _portalList->clearSelection();
                _parent->_editor->highlight(nullptr);
                _mastName->setText("");
//            }
        });
        panel = new JPanel();
        panel->layout()->addWidget(clearButton);
        signalPanel->layout()->addWidget(panel);
        signalPanel->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE));

        panel = new JPanel();
        _mastName = new JTextField();
        panel->layout()->addWidget(CircuitBuilder::makeTextBoxPanel(false, _mastName, "mastName", true, nullptr));
        _mastName->resize(QSize(300, _mastName->sizeHint().height()));
        _mastName->setToolTip(tr("Enter a name to configure a signal mast to protect block \"%1\".").arg(_homeBlock->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME)));
        signalPanel->layout()->addWidget(panel);

        panel = new JPanel();
        QPushButton* addButton = new QPushButton(tr("Configure Signal"));
//        addButton.addActionListener((ActionEvent a) -> {
        connect(addButton, &QPushButton::clicked, [=]{
            Portal* portal = VPtr<Portal>::asPtr(_portalList->getSelectedValue());
            QString msg = "";
            if (portal != nullptr) {
                NamedBean* signal = getSignal();
                if (signal != nullptr) {
                    if (replaceQuestion(signal, portal)) {
                        addMast(portal, signal);
                    }
                } else {
                    QString name = _mastName->text().trimmed();
                    if ( name.length()==0) {
                        msg = tr("Enter the name of a signal mast into the Signal Name field."/*, Bundle.getMessage("mastName")*/);
                    } else {
                        msg = tr("Signal named \"%1\" not found.").arg(name);
                    }
                }
            } else {
                msg = tr("Select a portal to set a signal for the protection of %1.").arg(_homeBlock->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME));
            }
            if (msg != "") {
                JOptionPane::showMessageDialog(this, msg,
                        tr("ConfigureSignal"), JOptionPane::INFORMATION_MESSAGE);
            }
        });
        addButton->setToolTip(tr("Configures the signal mast to protect %1 at the selected portal->").arg(_homeBlock->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME)));
        panel->layout()->addWidget(addButton);

        QPushButton* removeButton = new QPushButton(tr("Remove Signal"));
        //removeButton.addActionListener((ActionEvent a) -> {
        connect(removeButton, &QPushButton::clicked, [=]{
            removeMast();
        });
        removeButton->setToolTip(tr("Removes the signal protection at the selected portal of %1. (Does not delete the signal)").arg(_homeBlock->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME)));
        panel->layout()->addWidget(removeButton);
        signalPanel->layout()->addWidget(panel);
        signalPanel->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE));

        QStringList blurbLines = {tr("Drag the name of a Signal to the %1 field.").arg(tr("Signal Name"))};


        _pickMast = new OpenPickListButton/*<SignalMast>*/ (blurbLines, PickListModel::signalMastPickModelInstance(), this);
        _pickHead = new OpenPickListButton/*<SignalHead>*/ (blurbLines, PickListModel::signalHeadPickModelInstance(), this);
        panel = new JPanel();
        panel->layout()->addWidget(_pickMast->getButtonPanel());
        panel->layout()->addWidget(_pickHead->getButtonPanel());
        signalPanel->layout()->addWidget(panel);
        signalPanel->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE));

        _lengthPanel = new LengthPanel(_homeBlock, "entranceSpace");
        _lengthPanel->changeUnits();
        signalPanel->layout()->addWidget(_lengthPanel);
        signalPanel->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE));

        panel = new JPanel();
        panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));
        JLabel* l = new JLabel(tr("Select a portal to set a signal for the protection of %1.").arg(_homeBlock->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME)));
        l->setAlignmentX(Qt::AlignLeft);
        panel->layout()->addWidget(l);
        l = new JLabel(tr("Enter the name of a signal mast into the Signal Name field."));
        l->setAlignmentX(Qt::AlignLeft);
        panel->layout()->addWidget(l);
        l = new JLabel(tr("THEN press the %1 button.").arg(tr("Configure Signal")));
        l->setAlignmentX(Qt::AlignLeft);
        panel->layout()->addWidget(l);
        l = new JLabel(tr("Now reposition the signal icon displayed over the portal->"));
        l->setAlignmentX(Qt::AlignLeft);
        panel->layout()->addWidget(l);
        JPanel* p = new JPanel(new FlowLayout());
        p->layout()->addWidget(panel);
        signalPanel->layout()->addWidget(p);

        signalPanel->layout()->addWidget(Box::createVerticalStrut(STRUT_SIZE));
        signalPanel->layout()->addWidget(makeDoneButtonPanel());
        return signalPanel;
    }

    /*protected*/ void EditSignalFrame::setSelected(PositionableIcon* icon) {
        if (!canEdit()) {
            return;
        }
        NamedBean* mast = nullptr;
        Portal* portal = nullptr;
        if (qobject_cast<PortalIcon*>(icon->self())) {
            portal = ((PortalIcon*)icon)->getPortal();
        } else if (qobject_cast<SignalMastIcon*>(icon->self())) {
            mast = ((SignalMastIcon*)icon)->getSignalMast();
        } else if (qobject_cast< SignalHeadIcon*>(icon->self())) {
            mast = ((SignalHeadIcon*)icon)->getSignalHead();
        } else {
            return;
        }
        if (log->isDebugEnabled()) {
            log->debug(tr("setSelected portal= \"%1\" mast =%1").arg((portal!=nullptr?portal->getName():"null")).arg((mast!=nullptr?mast->getDisplayName():"null")));
        }
        _portalIcon = nullptr;
        if (portal != nullptr) {
            setPortalSelected(portal, icon);
            mast = portal->getSignalProtectingBlock(_homeBlock);
            if (mast !=nullptr) {
                setMastNameAndIcon(mast);
            }
        } else if (mast !=nullptr) {
            portal =_parent->getSignalPortal(mast);
            if (portal != nullptr) {
                OBlock* protectedBlock = portal->getProtectedBlock(mast);
                if (_homeBlock->equals(protectedBlock)) {
                    setPortalSelected(portal, icon);
                }
            }
            setMastNameAndIcon(mast);
        }
    }

    /*private*/ void EditSignalFrame::setMastNameAndIcon(NamedBean* mast) {
        _mastName->setText(mast->getDisplayName(NamedBean::DisplayOptions::DISPLAYNAME));
       QList<PositionableIcon*>* sigArray = _parent->getSignalIconMap(mast);
        if (sigArray->isEmpty()) {
            _parent->_editor->highlight(nullptr);
        } else {
            PositionableIcon* icon = sigArray->at(0);
            _parent->_editor->highlight(icon);
        }
    }

    /*private*/ void EditSignalFrame::setPortalSelected(Portal* portal, PositionableIcon* icon) {
        QList<Portal*> list = _homeBlock->getPortals();
        for (int i = 0; i < list.size(); i++) {
            if (portal == (list.at(i))) {
                _portalList->setSelectedIndex(i);
                _parent->_editor->highlight(icon);
                break;
            }
        }   // selection within currently configured _homeBlock
    }

    /**
     * *********************** end setup *************************
     */
    /*
     * Listener on list of Portals
     * @see javax.swing.event.ListSelectionListener#valueChanged(javax.swing.event.ListSelectionEvent)
     */
    //@Override
    /*public*/ void EditSignalFrame::valueChanged(ListSelectionEvent* e) {
        Portal* portal = VPtr<Portal>::asPtr(_portalList->getSelectedValue());
        if (log->isDebugEnabled()) {
            log->debug(tr("valueChanged: portal = %1, _currentPortal = %2").arg((portal==nullptr?"null":portal->getName())).arg(
                    (_currentPortal==nullptr?"null":_currentPortal->getName())));
        }
        NamedBean* mast = nullptr;
        if (portal != nullptr) {
            if (portal !=(_currentPortal)) {
                QString msg = checkMastForSave();
                if (msg.length() > 0) {
                    QString sb;// = new StringBuffer(msg);
                    sb.append("\n");
                    sb.append(tr("Make and save changes?"));
                    int answer = JOptionPane::showConfirmDialog(this, sb, tr("ConfigureSignal"),
                            JOptionPane::YES_NO_OPTION, JOptionPane::QUESTION_MESSAGE);
                    if (answer == JOptionPane::YES_OPTION) {
                        addMast(_currentPortal, getSignal());
                    }
                }
            }
            mast = portal->getSignalProtectingBlock(_homeBlock);
        }
        if (_portalIcon == nullptr) {
            _parent->_editor->highlight(nullptr);
        }
        _currentPortal = portal;
        if (portal != nullptr) {
            _lengthPanel->setLength(portal->getEntranceSpaceForBlock(_homeBlock));
           QList<PortalIcon*>* piArray = _parent->getPortalIconMap(portal);
           if (!piArray->isEmpty()) {
               _portalIcon = piArray->at(0);
           }
        }

        if (mast != nullptr) {
            setMastNameAndIcon(mast);
        } else {
            _mastName->setText("");
            if (portal != nullptr) {
                _parent->_editor->highlight(_portalIcon);
            }
            _lengthPanel->setLength(0);
        }
    }

    // Called from ButtonAddMast
    /*private*/ bool EditSignalFrame::replaceQuestion(/*@Nonnull*/ NamedBean* mast, /*@Nonnull*/ Portal* homePortal) {
        QString sb;// = new StringBuffer();
        Portal* portal = _parent->getSignalPortal(mast);
        OBlock* blk = nullptr;
        if (portal != nullptr) {
            blk = portal->getProtectedBlock(mast);
            if (blk != nullptr && !blk->equals(_homeBlock)) {
                sb.append(tr("Signal mast %1 protects block %2 at portal \"%3\".").arg(
                        mast->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME)).arg(
                        blk->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME)).arg(
                        portal->getName()));
                sb.append("\n");
            }
        }
        NamedBean* homeMast = homePortal->getSignalProtectingBlock(_homeBlock);
        QString mastName = mast->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME);
        QString homeName = _homeBlock->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME);
        if (homeMast != nullptr) {
            if (homeMast->equals(mast->self())) {
                // no changes needed except for length.  So do it now and skip the rest of AddMast()
                homePortal->setEntranceSpaceForBlock(_homeBlock, _lengthPanel->getLength());
                return false;
            } else {
                QString homeMastName = homeMast->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME);
                sb.append(tr("Signal mast %1 protects block %2 at portal \"%3\".").arg(homeMastName).arg(homeName).arg(homePortal->getName()));
                sb.append("\n");
                sb.append(tr("Do you want to replace signal %1 with signal %2 at portal \"%3\"?").arg(homeMast->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME)).arg(
                                mastName).arg(homePortal->getName()));
            }
        } else if (sb.length() > 0) {
            sb.append(tr("No signal protects \"%3\" at portal \"%1\". Set signal \"%2\" to protect it?").arg(homePortal->getName()).arg(mastName).arg(homeName));
            sb.append("\n");
            sb.append(tr("Do you want mast %1 to protect block %2at portal \"%3\"?").arg(mastName).arg(homeName).arg(homePortal->getName()));
        }
        if (sb.length() > 0) {
            int answer = JOptionPane::showConfirmDialog(this,  sb,
                    tr("ConfigureSignal"), JOptionPane::YES_NO_OPTION, JOptionPane::QUESTION_MESSAGE);
            if (answer != JOptionPane::YES_OPTION) {
                return false;   // Skip the rest
            }
        }
        if (homeMast != nullptr) {
            homePortal->setProtectSignal(nullptr, 0, blk);
        }
        _parent->putSignalPortal(mast, nullptr);
        return true;
    }

    /*private*/ NamedBean* EditSignalFrame::getSignal() {
        QString name = _mastName->text();
        if (name.trimmed().length() == 0) {
            return nullptr;
        }
        NamedBean* signal = (NamedBean*)((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(name);
        if (signal == nullptr) {
            signal = (NamedBean*)((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(name);
        }
        return signal;
    }
    // Called from:
    // ConfigureButton -    addMast(portal, mast); portal from portal list, mast from name field
    /*private*/ void EditSignalFrame::addMast(/*@Nonnull*/ Portal* portal, /*@Nonnull*/ NamedBean *newMast) {
        if (log->isDebugEnabled()) {
            log->debug(tr("addMast \"%1\" icon =%2").arg(newMast->getDisplayName()));
        }
        if (static_cast<SignalMast*>(newMast)) {
            SignalMast* mast = (SignalMast*)newMast;
            if (mast->getAspect() == "") {
                mast->setAspect(mast->getValidAspects().at(0));
            }
        }
        if (log->isDebugEnabled()) {
            if (static_cast<SignalHead*>(newMast)){
                log->debug(tr("addMast SignalHead state= %1, appearance= %2").arg(((SignalHead*)newMast)->getState()).arg(((SignalHead*)newMast)->getAppearanceName()));
            } else {
                log->debug(tr("addMast SignalMast state= %1, aspect= %2").arg(((SignalHead*)newMast)->getState()).arg(((SignalMast*)newMast)->getAspect()));
            }
        }
        portal->setProtectSignal(newMast, _lengthPanel->getLength(), _homeBlock);
        _parent->putSignalPortal(newMast, portal);
        setMastIcon(newMast, portal);
    }

    /*private*/ void EditSignalFrame::setMastIcon(NamedBean* newMast,  Portal* portal) {
        QList<PositionableIcon*>* mastIcons = _parent->getSignalIconMap(newMast);
        PositionableIcon* icon = nullptr;
        bool newIcon = true;
        if (!mastIcons->isEmpty()) {
            icon = mastIcons->at(0);
            newIcon = false;
        } else if (static_cast<SignalMast*>(newMast)) {
            icon = new SignalMastIcon(_parent->_editor);
            ((SignalMastIcon*)icon)->setSignalMast(newMast->getDisplayName());
        } else if (static_cast<SignalHead*>(newMast)) {
            icon = new SignalHeadIcon(_parent->_editor);
            ((SignalHeadIcon*)icon)->setSignalHead(newMast->getDisplayName());
        }
        if (icon == nullptr) {
            return;
        }
        if (newIcon) {
            _parent->_editor->putItem(icon);
        }
        QList<PortalIcon*>* portalIcons = _parent->getPortalIconMap(portal);
        if (!portalIcons->isEmpty()) {
            _portalIcon = portalIcons->at(0);
            icon->setDisplayLevel(_portalIcon->getDisplayLevel());
            icon->setLocation(_portalIcon->getLocation());
        }
        _parent->_editor->highlight(icon);
        icon->updateSize();
        if (!mastIcons->contains(icon)) {
            mastIcons->append(icon);
        }
        _parent->getCircuitIcons(_homeBlock)->append(icon);
    }

    /*private*/ void EditSignalFrame::removeMast() {
        Portal* portal = VPtr<Portal>::asPtr(_portalList->getSelectedValue());
        NamedBean* oldMast = nullptr;
        if (portal != nullptr) {
            oldMast = portal->getSignalProtectingBlock(_homeBlock);
        } else {
            _mastName->setText("null");
            return;
        }
        if (oldMast != nullptr) {
            _mastName->setText("");    // do before portal triggers propertyChange
            portal->setProtectSignal(nullptr, 0, _homeBlock);
            _parent->putSignalPortal(oldMast, nullptr);
        } else {
            JOptionPane::showMessageDialog(this,
                    tr("There is no signal configured to protect %1 at portal \"%2\".").arg(_homeBlock->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME)).arg(
                            portal->getName()),
                    tr("ConfigureSignal"), JOptionPane::INFORMATION_MESSAGE);
        }
        _mastName->setText("");
    }

    /**
     * Check for questions about configuring this signal
     * @return message of any concerns. But ALWAYS non-null.
     */
    /*private*/ QString EditSignalFrame::checkMastForSave() {
        if (_currentPortal == nullptr) {
            return "";
        }
        QString sb;// = new StringBuffer();
        NamedBean* selectedMast = getSignal();
        NamedBean* currentMast = _currentPortal->getSignalProtectingBlock(_homeBlock);

        if (selectedMast == nullptr) {
            if (currentMast != nullptr) {
                QString curMastName = currentMast->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME);
                QString curPortalName = _currentPortal->getName();
                sb.append(tr("Signal mast %1 protects block %2 at portal \"%3\".").arg(curMastName).arg(
                        _homeBlock->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME)).arg(curPortalName));
                sb.append("\n");
                QString name = _mastName->text();
                if (name.trimmed().length() > 0) {
                    sb.append(tr("Signal named \"%1\" not found.").arg(name));
                    sb.append("\n");
                }
                sb.append(tr("Do you want to remove signal %1 at portal \"%2\".").arg(curMastName).arg(curPortalName));
            }
        } else {
            QString selMastName = selectedMast->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME);
            QString curPortalName = _currentPortal->getName();
            QString homeName = _homeBlock->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME);
            if (!selectedMast->equals(currentMast->self())) {
                if (currentMast != nullptr) {
                    Portal* selectedPortal = _parent->getSignalPortal(selectedMast);
                    if (selectedPortal != nullptr) {
                        OBlock* blk = selectedPortal->getProtectedBlock(selectedMast);
                        if (blk != nullptr) {
                            sb.append(tr("Signal mast %1 protects block %2 at portal \"%3\".").arg(selMastName).arg(
                                    blk->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME)).arg(selectedPortal->getName()));
                            sb.append("\n");
                        }
                    }
                    QString curMastName = currentMast->getDisplayName(NamedBean::DisplayOptions::QUOTED_DISPLAYNAME);
                    sb.append(tr("Signal mast %1 protects block %2 at portal \"%3\".").arg(curMastName).arg(homeName).arg(curPortalName));
                    sb.append("\n");
                    sb.append(tr("Do you want to replace signal %1 with signal %2 at portal \"%3\"?").arg(curMastName).arg(selMastName).arg(curPortalName));
                    sb.append("\n");
                    if (_lengthPanel->isChanged(_currentPortal->getEntranceSpaceForBlock(_homeBlock))) {
                        sb.append(tr("Entrance adjustment for signal \"%1\" at portal \"%2\" is changed.").arg(selMastName).arg(_currentPortal->getName()));
                    }
                } else {
                    sb.append(tr("No signal protects \"%3\" at portal \"%1\". Set signal \"%2\" to protect it?").arg(curPortalName).arg(selMastName).arg(homeName));
                    sb.append("\n");
                    sb.append(tr("Do you want mast %1 to protect block %2at portal \"%3\"?").arg(selMastName).arg(
                            homeName).arg(_currentPortal->getName()));
                }
            }
        }
        return sb;
    }

    //@Override
    /*protected*/ void EditSignalFrame::closingEvent(bool close) {
        QString sb;// = new StringBuffer();
        QString msg = _parent->checkForPortals(_homeBlock, "ItemTypeSignalMast");
        if (msg.length() > 0) {
            sb.append(msg);
            sb.append("\n");
        }
        msg = checkMastForSave();
        if  (msg.length() > 0) {
            sb.append(msg);
            sb.append("\n");
        }
        EditFrame::closingEvent(close, sb);
        if (_pickMast != nullptr) {
            _pickMast->closePickList();
        }
        if (_pickHead != nullptr) {
            _pickHead->closePickList();
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* EditSignalFrame::log = LoggerFactory::getLogger("EditSignalFrame");

