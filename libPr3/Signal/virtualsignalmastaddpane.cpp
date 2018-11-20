#include "virtualsignalmastaddpane.h"
#include "loggerfactory.h"
#include <QBoxLayout>
#include <QCheckBox>
#include "virtualsignalmast.h"
#include <QScrollArea>
#include <QGroupBox>
#include "signalmastmanager.h"
#include "instancemanager.h"
#include "virtualsignalmast.h"
#include <QLabel>

/**
 * A pane for configuring VirtualSignalMast objects
 * <P>
 * @see jmri.jmrit.beantable.signalmast.SignalMastAddPane
 * @author Bob Jacobsen Copyright (C) 2018
 * @since 4.11.2
 */
// /*public*/ class VirtualSignalMastAddPane extends SignalMastAddPane {

/*public*/ VirtualSignalMastAddPane::VirtualSignalMastAddPane(QWidget *parent)
{
 allowUnLit = new QCheckBox();
 disabledAspects = QMap<QString, QCheckBox*>(/*NOTIONAL_ASPECT_COUNT*/);
 disabledAspectsPanel = new JPanel();
 disabledAspectsPanel->setLayout(new QVBoxLayout());

 currentMast = nullptr;
 paddedNumber = new DecimalFormat("0000");


    //setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
 QVBoxLayout* thisLayout = new QVBoxLayout(this);
    // lit/unlit controls
    QWidget* p = new QWidget();
    //p.setLayout(new BoxLayout(p, BoxLayout.X_AXIS));
    QHBoxLayout* pLayout = new QHBoxLayout(p);
    pLayout->addWidget(new QLabel(tr("This Mast can be unlit") + ": "));
    pLayout->addWidget(allowUnLit);
   // p.setAlignmentX(Component.LEFT_ALIGNMENT);
    thisLayout->addWidget(p);

    // disabled aspects controls
//    TitledBorder disableborder = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));
    QGroupBox* disableborder = new QGroupBox();
    disableborder->setLayout(new QVBoxLayout());
    disableborder->setTitle(tr("Disable specific Aspects"));
    QScrollArea* disabledAspectsScroll = new QScrollArea(/*disabledAspectsPanel*/);
    disableborder->layout()->addWidget(disabledAspectsScroll);
    disabledAspectsScroll->setWidgetResizable(true);
    disabledAspectsScroll->setWidget(disabledAspectsPanel);
    //disabledAspectsScroll.setBorder(disableborder);
    thisLayout->addWidget(disabledAspectsScroll);
}

/** {@inheritDoc} */
//Override
/*@Nonnull*/ /*public*/ QString VirtualSignalMastAddPane::getPaneName() {
    return tr("Virtual Mast");
}



/** {@inheritDoc} */
//@Override
/*public*/ void VirtualSignalMastAddPane::setAspectNames(/*@Nonnull*/
        SignalAppearanceMap* map, SignalSystem* sigSystem) {
    QStringListIterator aspects (map->getAspects());
    // update immediately
    disabledAspects = QMap<QString, QCheckBox*>(/*NOTIONAL_ASPECT_COUNT*/);
    //disabledAspectsPanel.removeAll();
    QObjectList ol = disabledAspectsPanel->layout()->children();
    foreach (QObject* obj, ol) {
     if(qobject_cast<QWidget*>(obj) != nullptr)
      disabledAspectsPanel->layout()->removeWidget(qobject_cast<QWidget*>(obj));
      qobject_cast<QWidget*>(obj)->deleteLater();
    }
    while (aspects.hasNext()) {
        QString aspect = aspects.next();
        QCheckBox* disabled = new QCheckBox(aspect);
        disabledAspects.insert(aspect, disabled);
    }
    for (QString aspect : disabledAspects.keys()) {
        disabledAspectsPanel->layout()->addWidget(disabledAspects.value(aspect));
    }

// ??    disabledAspectsPanel.setLayout(new jmri.util.javaworld.GridLayout2(0, 1)); // 0 means enough

    disabledAspectsPanel->update();
}

/** {@inheritDoc} */
//@Override
/*public*/ bool VirtualSignalMastAddPane::canHandleMast(/*@Nonnull*/ SignalMast* mast) {
   // return mast instanceof jmri.implementation.VirtualSignalMast;
 return qobject_cast<VirtualSignalMast*>(mast) != nullptr;
}

/** {@inheritDoc} */
//@Override
/*public*/ void VirtualSignalMastAddPane::setMast(SignalMast* mast) {
    log->trace(tr("setMast %1 start").arg((mast == nullptr)?"null":mast->getDisplayName()));
    if (mast == nullptr) {
        currentMast = nullptr;
        return;
    }

    if (! (qobject_cast<VirtualSignalMast*>(mast) != nullptr) ) {
        log->error(tr("mast was wrong type: %1 %1").arg(mast->getSystemName()).arg(mast->metaObject()->className()));
        return;
    }

    currentMast = (VirtualSignalMast*) mast;
    QStringList* disabled = currentMast->getDisabledAspects();
    if (disabled != nullptr) {
        for (QString aspect : *disabled) {
            if (disabledAspects.contains(aspect)) {
                disabledAspects.value(aspect)->setChecked(true);
            }
        }
    }

    allowUnLit->setChecked(currentMast->allowUnLit());

    log->trace(tr("setMast %1 end").arg(mast->getDisplayName()));
}


/** {@inheritDoc} */
//@Override
/*public*/ bool VirtualSignalMastAddPane::createMast(/*@Nonnull*/
        QString sigsysname, /*@Nonnull*/
                QString mastname, /*@Nonnull*/
                        QString username)
{
    log->trace(tr("createMast %1 %1 %1 start with currentMast: %1").arg(sigsysname).arg( mastname).arg(username).arg(currentMast->getDisplayName()));
    if (currentMast == nullptr) {
        // create a mast
        QString name = "IF$vsm:"
                + sigsysname
                + ":" + mastname.mid(11, mastname.length() - 4);
        name += "($" + (paddedNumber->format(VirtualSignalMast::getLastRef() + 1)) + ")";
        currentMast = new VirtualSignalMast(name);
        if (username != ("")) {
            currentMast->setUserName(username);
        }
        currentMast->setMastType(mastname.mid(11, mastname.length() - 4));
        static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->Register(currentMast);
    }

    // load a new or existing mast
    for (QString aspect : disabledAspects.keys()) {
        if (disabledAspects.value(aspect)->isChecked()) {
            currentMast->setAspectDisabled(aspect);
        } else {
            currentMast->setAspectEnabled(aspect);
        }
    }
    currentMast->setAllowUnLit(allowUnLit->isChecked());
    log->trace(tr("createMast %1 %2 %3 end").arg(sigsysname).arg(mastname).arg(username));
    return true;
}

//@ServiceProvider(service = SignalMastAddPane.SignalMastAddPaneProvider.class)
// /*static*/ /*public*/ class SignalMastAddPaneProvider extends SignalMastAddPane.SignalMastAddPaneProvider {
    /** {@inheritDoc} */
    //@Override
    /*@Nonnull*/ /*public*/ QString VirtualSignalMastAddPaneProvider::getPaneName() {
        return tr("Virtual Mast");
    }
    /** {@inheritDoc} */
    //@Override
    /*@Nonnull*/ /*public*/ SignalMastAddPane* VirtualSignalMastAddPaneProvider::getNewPane() {
        return new VirtualSignalMastAddPane();
    }
//};

/*private*/ /*final*/ /*static*/ Logger* VirtualSignalMastAddPane::log = LoggerFactory::getLogger("VirtualSignalMastAddPane");

