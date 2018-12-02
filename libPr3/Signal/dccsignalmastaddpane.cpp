#include "dccsignalmastaddpane.h"
#include "loggerfactory.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QGroupBox>
#include <QComboBox>
#include "jtextfield.h"
#include "commandstation.h"
#include "instancemanager.h"
#include "dccsignalmast.h"
#include "joptionpane.h"
#include "connectionnamefromsystemname.h"
#include "signalmastmanager.h"
#include <QCheckBox>
#include "nmrapacket.h"
#include <QSignalMapper>

/**
 * A pane for configuring MatrixSignalMast objects
 * <P>
 * @see jmri.jmrit.beantable.signalmast.SignalMastAddPane
 * @author Bob Jacobsen Copyright (C) 2018
 * @since 4.11.2
 */
///*public*/ class DccSignalMastAddPane extends SignalMastAddPane {

/*public*/ DccSignalMastAddPane::DccSignalMastAddPane(QWidget* parent) : SignalMastAddPane(parent) {
 dccMastPanel = new QGroupBox();
 dccMastPanelLayout = new QVBoxLayout();
 systemPrefixBoxLabel = new QLabel(/*"MakeLabel",*/ tr("System"));
 systemPrefixBox = new QComboBox();
 dccAspectAddressLabel = new QLabel(/*("MakeLabel",*/ tr("DCC Accessory Address"));
    //setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
 dccAspectAddressField = new JTextField(5);
 QCheckBox* allowUnLit = new QCheckBox();
 unLitAspectField = new JTextField(5);
 dccAspect = QMap<QString, DCCAspectPanel*>(/*NOTIONAL_ASPECT_COUNT*/);

 QVBoxLayout* thisLayout = new QVBoxLayout(this);
 // lit/unlit controls
 QWidget* p = new QWidget();
 //p.setLayout(new BoxLayout(p, BoxLayout.X_AXIS));
 QHBoxLayout* pLayout = new QHBoxLayout(p);
 pLayout->addWidget(new QLabel(tr("This Mast can be unlit") + ": "));
 pLayout->addWidget(allowUnLit);
 //p.setAlignmentX(Component.LEFT_ALIGNMENT);
 thisLayout->addWidget(p,0, Qt::AlignLeft);

 dccMastScroll = new QScrollArea(/*dccMastPanel*/);
//    dccMastScroll.setBorder(BorderFactory.createEmptyBorder());
 dccMastScroll->setWidget(dccMastPanel);
 dccMastScroll->setWidgetResizable(true);
 thisLayout->addWidget(dccMastScroll);

}

/** {@inheritDoc} */
//@Override
/*@Nonnull*/ /*public*/ QString DccSignalMastAddPane::getPaneName() {
    return tr("DCC Signal Mast Decoder");
}


/**
 * Check if a command station will work for this subtype
 */
/*protected*/ bool DccSignalMastAddPane::usableCommandStation(CommandStation* cs) {
    return true;
}

/** {@inheritDoc} */
//@Override
/*public*/ void DccSignalMastAddPane::setAspectNames(/*@Nonnull*/ SignalAppearanceMap* map, /*@Nonnull*/ SignalSystem* sigSystem)
{
    log->trace("setAspectNames(...) start");

    dccAspect.clear();

    QStringListIterator aspects = map->getAspects();
    sigsys = map->getSignalSystem();

    while (aspects.hasNext()) {
        QString aspect = aspects.next();
        DCCAspectPanel* aPanel = new DCCAspectPanel(aspect);
        dccAspect.insert(aspect, aPanel);
        log->trace(tr(" in loop, dccAspect: %1 ").arg(map->getProperty(aspect, "dccAspect")));
        aPanel->setAspectId( sigSystem->getProperty(aspect, "dccAspect").toString());
    }

    systemPrefixBox->clear();
    QObjectList connList = InstanceManager::getList("CommandStation");
    if (!connList.isEmpty()) {
        for (int x = 0; x < connList.size(); x++) {
            CommandStation* station = (CommandStation*)connList.at(x);
            if (usableCommandStation(station)) {
                systemPrefixBox->addItem(station->getUserName());
            }
        }
    } else {
        systemPrefixBox->addItem("None");
    }

    //dccMastPanel.removeAll();
    QObjectList ol = dccMastPanel->children();
    foreach (QObject* obj, ol) {
     if(qobject_cast<QWidget*>(obj))
      dccMastPanelLayout->removeWidget(qobject_cast<QWidget*>(obj));
     obj->deleteLater();
    }
    delete dccMastPanelLayout;
    dccMastPanel->setLayout(dccMastPanelLayout = new QVBoxLayout());

    dccMastPanelLayout->addWidget(systemPrefixBoxLabel);
    dccMastPanelLayout->addWidget(systemPrefixBox);

    dccMastPanelLayout->addWidget(dccAspectAddressLabel);
    dccAspectAddressField->setText("");
    dccMastPanelLayout->addWidget(dccAspectAddressField);

    for (QString aspect : dccAspect.keys()) {
        log->trace(tr("   aspect: %1").arg(aspect));
        dccMastPanelLayout->addWidget(dccAspect.value(aspect)->getPanel());
    }

    dccMastPanelLayout->addWidget(new QLabel(tr("Copy Aspect IDs from Mast") + ":"));
    dccMastPanelLayout->addWidget(copyFromMastSelection());

//??    dccMastPanel.setLayout(new jmri.util.javaworld.GridLayout2(0, 2)); // 0 means enough
    dccMastPanel->update();
    dccMastScroll->update();

    log->trace("setAspectNames(...) end");
}


/** {@inheritDoc} */
//@Override
/*public*/ bool DccSignalMastAddPane::canHandleMast(/*@Nonnull*/ SignalMast* mast) {
    // because that mast can be subtyped by something
    // completely different, we text for exact here.
    //return mast.getClass().getCanonicalName().equals(DccSignalMast.class.getCanonicalName());
 return QString(mast->metaObject()->className()) == QString("DccSignalMast");
}

/** {@inheritDoc} */
//@Override
/*public*/ void DccSignalMastAddPane::setMast(SignalMast* mast) {
//    log->debug(tr("setMast(%1) start").arg(mast->normalizeUserName()));
    if (mast == nullptr) {
        currentMast = nullptr;
        log->debug("setMast() end early with null");
        return;
    }

    //if (! (mast instanceof DccSignalMast) )
    if(qobject_cast<DccSignalMast*>(mast)!= nullptr)
    {
        log->error(tr("mast was wrong type: %1 %2").arg(mast->getSystemName()).arg( mast->metaObject()->className()));
        log->debug(tr("setMast(%1) end early: wrong type").arg(mast->getDisplayName()));
        return;
    }

    currentMast = (DccSignalMast*) mast;
    SignalAppearanceMap* appMap = mast->getAppearanceMap();

    if (appMap != nullptr) {
        QStringListIterator aspects = appMap->getAspects();
        while (aspects.hasNext()) {
            QString key = aspects.next();
            DCCAspectPanel* dccPanel = dccAspect.value(key);
            dccPanel->setAspectDisabled(currentMast->isAspectDisabled(key));
            if (!currentMast->isAspectDisabled(key)) {
                dccPanel->setAspectId(currentMast->getOutputForAppearance(key));
            }

        }
    }
    QObjectList connList = InstanceManager::getList("CommandStation");
    if (!connList.isEmpty()) {
        for (int x = 0; x < connList.size(); x++) {
            CommandStation* station = (CommandStation*)connList.at(x);
            if (usableCommandStation(station)) {
                systemPrefixBox->addItem(station->getUserName());
            }
        }
    } else {
        systemPrefixBox->addItem("None");
    }
    dccAspectAddressField->setText("" + currentMast->getDccSignalMastAddress());
    systemPrefixBox->setCurrentText(currentMast->getCommandStation()->getUserName());

    systemPrefixBoxLabel->setEnabled(false);
    systemPrefixBox->setEnabled(false);
    dccAspectAddressLabel->setEnabled(false);
    dccAspectAddressField->setEnabled(false);
    if (currentMast->allowUnLit()) {
        unLitAspectField->setText("" + currentMast->getUnlitId());
    }

    log->debug(tr("setMast(%1) end").arg(mast->getDisplayName()));
}

/*static*/ bool DccSignalMastAddPane::validateAspectId(/*@Nonnull*/ QString strAspect) {
    int aspect;
    //try {
     bool bok;
        aspect = (strAspect.trimmed().toInt(&bok));
    if(!bok)
    {
        JOptionPane::showMessageDialog(nullptr, tr("Aspect ID must be a number"));
        return false;
    }
    if (aspect < 0 || aspect > 31) {
        JOptionPane::showMessageDialog(nullptr, tr("Signal Mast Aspect should be in the range of 0 to 31"));
        log->error(tr("invalid aspect %1").arg(aspect));
        return false;
    }
    return true;
}

/**
 * Return the first part of the system name
 * for the specific mast type
 */
/*protected*/ /*@Nonnull*/ QString DccSignalMastAddPane::getNamePrefix() {
    return "F$dsm:";
}

/**
 * Create a mast of the specific subtype
 */
/*protected*/ DccSignalMast* DccSignalMastAddPane::constructMast(/*@Nonnull*/ QString name) {
    return new DccSignalMast(name);
}

/** {@inheritDoc} */
//@Override
/*public*/ bool DccSignalMastAddPane::createMast(/*@Nonnull*/
        QString sigsysname, /*@Nonnull*/
                QString mastname, /*@Nonnull*/
                        QString username) {
    log->debug(tr("createMast(%1,%2 start)").arg(sigsysname).arg(mastname));

    // are we already editing?  If no, create a new one.
    if (currentMast == nullptr) {
        log->trace("Creating new mast");
        if (!validateDCCAddress()) {
            log->trace("validateDCCAddress failed, return from createMast");
            return false;
        }
        QString systemNameText = ConnectionNameFromSystemName::getPrefixFromName(systemPrefixBox->currentText());
        // if we return a null string then we will set it to use internal, thus picking up the default command station at a later date.
        if (systemNameText == "" || systemNameText.isEmpty()) {
            systemNameText = "I";
        }
        systemNameText = systemNameText + getNamePrefix();

        QString name = systemNameText
                + sigsysname
                + ":" + mastname.mid(11, mastname.length() - 4);
        name += "(" + dccAspectAddressField->text() + ")";
        currentMast = constructMast(name);
        static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->Register(currentMast);
    }

    for (QString aspect : dccAspect.keys()) {
        dccMastPanelLayout->addWidget(dccAspect.value(aspect)->getPanel()); // update mast from aspect subpanel panel
        currentMast->setOutputForAppearance(aspect, dccAspect.value(aspect)->getAspectId());
        if (dccAspect.value(aspect)->isAspectDisabled()) {
            currentMast->setAspectDisabled(aspect);
        } else {
            currentMast->setAspectEnabled(aspect);
        }
    }
    if (username != ("")) {
        currentMast->setUserName(username);
    }

    currentMast->setAllowUnLit(allowUnLit->isChecked());
    if (allowUnLit->isChecked()) {
        currentMast->setUnlitId((unLitAspectField->text()).toInt());
    }

    log->debug(tr("createMast(%1,%2 end)").arg(sigsysname).arg(mastname));
    return true;
}

#if 0 // defined in header!
//@ServiceProvider(service = SignalMastAddPane.SignalMastAddPaneProvider.class)
static /*public*/ class SignalMastAddPaneProvider extends SignalMastAddPane.SignalMastAddPaneProvider {
    /** {@inheritDoc} */
    //@Override
    @Nonnull /*public*/ String getPaneName() {
        return Bundle.getMessage("DCCMast");
    }
    /** {@inheritDoc} */
    //@Override
    @Nonnull /*public*/ SignalMastAddPane getNewPane() {
        return new DccSignalMastAddPane();
    }
};
#endif
/*private*/ bool DccSignalMastAddPane::validateDCCAddress() {
    if (dccAspectAddressField->text() == ("")) {
        JOptionPane::showMessageDialog(nullptr, tr("A DCC Address must be entered"));
        return false;
    }
    int address;
    bool bok;
        address = (dccAspectAddressField->text().trimmed().toInt(&bok));
    if(!bok) {
        JOptionPane::showMessageDialog(nullptr, tr("DCC Address must be a number"));
        return false;
    }

    if (address < NmraPacket::accIdLowLimit || address > NmraPacket::accIdAltHighLimit) {
        JOptionPane::showMessageDialog(nullptr, tr("Signal Mast address should be in the range of 1 to 2044"));
        log->error(tr("invalid address %1").arg(address));
        return false;
    }
    if (DccSignalMast::isDCCAddressUsed(address) != nullptr) {
        QString msg = tr("Address \"%1\" is already assigned to Signal Mast \"%2\"").arg(dccAspectAddressField->text()).arg(DccSignalMast::isDCCAddressUsed(address));
        JOptionPane::showMessageDialog(nullptr, msg);
        return false;
    }
    return true;
}

/*@Nonnull*/ QComboBox* DccSignalMastAddPane::copyFromMastSelection() {
    QComboBox* mastSelect = new QComboBox();
    QSignalMapper* mapper = new QSignalMapper(this);
    QList<QString> names = static_cast<SignalMastManager*>( InstanceManager::getDefault("SignalMastManager"))->getSystemNameList();
    for (QString name : names)
    {
     if( qobject_cast<DccSignalMast*>(static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getNamedBean(name)) != nullptr)
     {
            mastSelect->addItem(static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getNamedBean(name)->getDisplayName());
        }
    }
    if (mastSelect->count() == 0) {
        mastSelect->setEnabled(false);
    } else {
        mastSelect->insertItem(0, "");
        mastSelect->setCurrentIndex(0);
//        mastSelect.addActionListener(new ActionListener() {
//            @SuppressWarnings("unchecked") // e.getSource() cast from mastSelect source
//            //@Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                JComboBox<String> eb = (JComboBox<String>) e.getSource();
//                String sourceMast = (String) eb.getSelectedItem();
//                if (sourceMast != null && !sourceMast.equals("")) {
//                    copyFromAnotherDCCMastAspect(sourceMast);
//                }
//            }
//        });
        mapper->setMapping(mastSelect, mastSelect);
        connect(mastSelect, SIGNAL(currentIndexChanged(int)), mapper, SLOT(map()));
        connect(mapper, SIGNAL(mapped(QObject*)), this, SLOT(onMastSelect(QObject*)));
    }
    return mastSelect;
}

/*public*/ void DccSignalMastAddPane::onMastSelect(QObject *o) {
    QComboBox* eb =  (QComboBox*)o;
    QString sourceMast =  eb->currentText();
    if (sourceMast != nullptr && sourceMast!=("")) {
        copyFromAnotherDCCMastAspect(sourceMast);
    }
}


/**
 * Copy aspects by name from another DccSignalMast
 */
void DccSignalMastAddPane::copyFromAnotherDCCMastAspect(/*@Nonnull*/ QString strMast) {
    DccSignalMast* mast = (DccSignalMast* )static_cast<SignalMastManager*>( InstanceManager::getDefault("SignalMastManager"))->getNamedBean(strMast);
    if (mast == nullptr) {
        log->error(tr("can't copy from another mast because %1 doesn't exist").arg(strMast));
        return;
    }
   QVector<QString> validAspects = mast->getValidAspects();
    for (QString aspect : dccAspect.keys()) {
        if (validAspects.contains(aspect) || mast->isAspectDisabled(aspect)) { // valid doesn't include disabled
            // present, copy
            dccAspect.value(aspect)->setAspectId(mast->getOutputForAppearance(aspect));
            dccAspect.value(aspect)->setAspectDisabled(mast->isAspectDisabled(aspect));
        } else {
            // not present, log
            log->info(tr("Can't get aspect \"%1\" from head \"%2\", leaving unchanged").arg(aspect).arg(mast->getDisplayName()));
        }
    }
}

/**
 * JPanel to define properties of an Aspect for a DCC Signal Mast.
 * <p>
 * Invoked from the AddSignalMastPanel class when a DCC Signal Mast is
 * selected.
 */
//static class DCCAspectPanel {

//    String aspect = "";
//    JCheckBox disabledCheck = new JCheckBox(Bundle.getMessage("DisableAspect"));
//    JLabel aspectLabel = new JLabel(Bundle.getMessage("DCCMastSetAspectId") + ":");
//    JTextField aspectId = new JTextField(5);

    DCCAspectPanel::DCCAspectPanel(QString aspect)
    {
     disabledCheck = new QCheckBox(tr("Disable Aspect"));
     aspectLabel = new QLabel(tr("Aspect ID") + ":");
     aspectId = new JTextField(5);

        this->aspect = aspect;
    }

    void DCCAspectPanel::setAspectDisabled(bool boo) {
        disabledCheck->setChecked(boo);
        if (boo) {
            aspectLabel->setEnabled(false);
            aspectId->setEnabled(false);
        } else {
            aspectLabel->setEnabled(true);
            aspectId->setEnabled(true);
        }
    }

    bool DCCAspectPanel::isAspectDisabled() {
        return disabledCheck->isChecked();
    }

    int DCCAspectPanel::getAspectId() {
        bool bok;
            QString value = aspectId->text();
            return (value).toInt(&bok);

        if(!bok) {
            Logger::error("failed to convert DCC number");
        }
        return -1;
    }

    void DCCAspectPanel::setAspectId(int i) {
        aspectId->setText("" + i);
    }

    void DCCAspectPanel::setAspectId(QString s) {
        aspectId->setText(s);
    }

    //JPanel panel;

    QWidget* DCCAspectPanel::getPanel() {
        if (panel == nullptr) {
            panel = new QGroupBox();
            //panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
            QVBoxLayout* panelLayout = new QVBoxLayout(panel);
            QWidget* dccDetails = new QWidget();
            QHBoxLayout* dccDetailsLayout = new QHBoxLayout(dccDetails);
            dccDetailsLayout->addWidget(aspectLabel);
            dccDetailsLayout->addWidget(aspectId);
            panelLayout->addWidget(dccDetails);
            panelLayout->addWidget(disabledCheck);
//            TitledBorder border = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));
//            border.setTitle(aspect);
//            panel.setBorder(border);
            panel->setTitle(aspect);
#if 0
            aspectId.addFocusListener(new FocusListener() {
                //@Override
                /*public*/ void focusLost(FocusEvent e) {
                    if (aspectId.getText().equals("")) {
                        return;
                    }
                    if (!validateAspectId(aspectId.getText())) {
                        aspectId.requestFocusInWindow();
                    }
                }

                //@Override
                /*public*/ void focusGained(FocusEvent e) {
                }

            });
#endif
//            disabledCheck.addActionListener(new ActionListener() {
//                //@Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    setAspectDisabled(disabledCheck.isSelected());
//                }
//            });
         connect(disabledCheck, SIGNAL(toggled(bool)), this, SLOT(onDisabledCheck()));
        }
        return panel;
    }
//}

    void DCCAspectPanel::onDisabledCheck()
    {
     setAspectDisabled(disabledCheck->isChecked());
    }


/*private*/ /*final*/ /*static*/ Logger* DccSignalMastAddPane::log = LoggerFactory::getLogger("DccSignalMastAddPane");
