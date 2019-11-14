#include "signalheadsignalmastaddpane.h"
#include "loggerfactory.h"
#include <QBoxLayout>
#include <QLabel>
#include <QGroupBox>>
#include "jmribeancombobox.h"
#include <QCheckBox>
#include <QScrollArea>
#include <QMap>
#include "defaultsignalappearancemap.h"
#include "joptionpane.h"
#include "signalheadmanager.h"
#include "instancemanager.h"
#include "signalheadsignalmast.h"
#include "stringutil.h"
#include "signalmastmanager.h"

/**
 * A pane for configuring SignalHeadSignalMast objects
 * <P>
 * @see jmri.jmrit.beantable.signalmast.SignalMastAddPane
 * @author Bob Jacobsen Copyright (C) 2018
 * @since 4.11.2
 */
///*public*/ class SignalHeadSignalMastAddPane extends SignalMastAddPane {

/*public*/ SignalHeadSignalMastAddPane::SignalHeadSignalMastAddPane(QWidget *parent) : SignalMastAddPane(parent)
{
 signalHeadPanel = new QGroupBox();
 signalHeadPanel->setLayout(new QVBoxLayout());
 headList = QList<JmriBeanComboBox*>(/*5*/);
 includeUsed = new QCheckBox(tr("Include previously used Signal Heads"));
 allowUnLit = new QCheckBox();
 disabledAspects = QMap<QString, QCheckBox*>(/*NOTIONAL_ASPECT_COUNT*/);
 disabledAspectsPanel = new QWidget();
 disabledAspectsPanel->setLayout(new QVBoxLayout());
 currentMast = nullptr;
 alreadyUsed = QList<NamedBean*>();

    //setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
 QVBoxLayout* thisLayout = new QVBoxLayout(this);
 // lit/unlit controls
 QWidget* p = new QWidget();
 //p.setLayout(new BoxLayout(p, BoxLayout.X_AXIS));
 QHBoxLayout*pLayout = new QHBoxLayout(p);
 pLayout->addWidget(new QLabel(tr("This Mast can be unlit") + ": "));
 pLayout->addWidget(allowUnLit);
 //p.setAlignmentX(Component.LEFT_ALIGNMENT);
 thisLayout->addWidget(p, 0, Qt::AlignLeft);

//        TitledBorder border = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));
//        border.setTitle(tr("MenuItemSignalTable")); // Signal Heads
 signalHeadPanel->setTitle(tr("Signal Heads"));
 thisLayout->addWidget(signalHeadPanel);

//        includeUsed.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                refreshHeadComboBox();
//            }
//        });
 connect(includeUsed, SIGNAL(toggled(bool)), this, SLOT(refreshHeadComboBox()));

    // disabled aspects controls
//        TitledBorder disableborder = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));
//        disableborder.setTitle(tr("DisableAspectsLabel"));
    QGroupBox* disableBorder = new QGroupBox();
    disableBorder->setLayout(new QVBoxLayout());
    disableBorder->setTitle(tr("Disable specific Aspects"));
    QScrollArea* disabledAspectsScroll = new QScrollArea(/*disabledAspectsPanel*/);
    //disabledAspectsScroll.setBorder(disableborder);
    disabledAspectsScroll->setWidget(disabledAspectsPanel);
    disabledAspectsScroll->setWidgetResizable(true);
    disableBorder->layout()->addWidget(disabledAspectsScroll);
    thisLayout->addWidget(disableBorder);
}

/** {@inheritDoc} */
//@Override
/*@Nonnull*/ /*public*/ QString SignalHeadSignalMastAddPane::getPaneName() {
    return tr("Signal Head Controlled Mast");
}

/** {@inheritDoc} */
//@Override
/*public*/ void SignalHeadSignalMastAddPane::setAspectNames(/*@Nonnull*/
        SignalAppearanceMap* newMap, SignalSystem* sigSystem)
{
 log->debug("setAspectNames(...)");

 map = (DefaultSignalAppearanceMap*)newMap;

 int count = map->getAspectSettings(map->getAspects().next())->length();
 log->trace(tr(" head count is %1").arg(count));

 QStringListIterator aspects = map->getAspects();

 headList = QList<JmriBeanComboBox*>(/*count*/);

 //signalHeadPanel.removeAll();
 QObjectList ol;
 if(signalHeadPanel->layout()!= nullptr)
 {
  ol = signalHeadPanel->layout()->children();
  foreach(QObject* obj, ol)
  {
   if(qobject_cast<QWidget*>(obj))
    signalHeadPanel->layout()->removeWidget(qobject_cast<QWidget*>(obj));
  }
  delete signalHeadPanel->layout();
  signalHeadPanel->setLayout(new QVBoxLayout());
  signalHeadPanel->setTitle(tr("Signal Heads"));
 }
 for (int i = 0; i < count; i++)
 {
  JmriBeanComboBox* head = new JmriBeanComboBox(static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager")));
  head->excludeItems(alreadyUsed);
  headList.append(head);
  signalHeadPanel->layout()->addWidget(head);
 }
 signalHeadPanel->layout()->addWidget(includeUsed);

// ??    signalHeadPanel.setLayout(new jmri.util.javaworld.GridLayout2(0, 1)); // 0 means enough
 signalHeadPanel->update();

 disabledAspects = QMap<QString, QCheckBox*>(/*10*/);
 //disabledAspectsPanel.removeAll();
 ol = disabledAspectsPanel->layout()->children();
 foreach(QObject* obj, ol)
 {
  if(qobject_cast<QWidget*>(obj))
   disabledAspectsPanel->layout()->removeWidget(qobject_cast<QWidget*>(obj));
 }
 delete disabledAspectsPanel->layout();
 disabledAspectsPanel->setLayout(new QVBoxLayout());
 while (aspects.hasNext())
 {
  QString aspect = aspects.next();
  QCheckBox* disabled = new QCheckBox(aspect);
  disabledAspects.insert(aspect, disabled);
 }

 for (QString aspect : disabledAspects.keys())
 {
  disabledAspectsPanel->layout()->addWidget(disabledAspects.value(aspect));
 }

// ??   disabledAspectsPanel.setLayout(new jmri.util.javaworld.GridLayout2(0, 1)); // 0 means enough
 disabledAspectsPanel->update();

}

/** {@inheritDoc} */
//@Override
/*public*/ bool SignalHeadSignalMastAddPane::canHandleMast(/*@Nonnull*/ SignalMast* mast) {
    //return mast instanceof SignalHeadSignalMast;
 return qobject_cast<SignalHeadSignalMast*>(mast) != nullptr;
}

/** {@inheritDoc} */
//@Override
/*public*/ void SignalHeadSignalMastAddPane::setMast(SignalMast* mast) {
    log->debug(tr("setMast(%1)").arg((mast==nullptr)?"null":mast->getDisplayName()));
    if (mast == nullptr) {
        currentMast = nullptr;
        return;
    }

    if (! (qobject_cast<SignalHeadSignalMast*>(mast) != nullptr) ) {
        log->error(tr("mast was wrong type: %1 %2").arg(mast->getSystemName()).arg( mast->className()));
        return;
    }

    currentMast = (SignalHeadSignalMast*) mast;

    // can't actually edit the heads in this kind of mast
    int count = map->getAspectSettings(map->getAspects().next())->length();
    log->trace(tr(" head count is %1").arg(count));
    //signalHeadPanel.removeAll();
    QObjectList ol = signalHeadPanel->layout()->children();
    foreach(QObject* obj, ol)
    {
     if(qobject_cast<QWidget*>(obj))
      signalHeadPanel->layout()->removeWidget(qobject_cast<QWidget*>(obj));
    }
    delete signalHeadPanel->layout();
    //signalHeadPanel->setLayout(new QVBoxLayout());
    signalHeadPanel->setLayout(new QGridLayout(/*count + 1, 1*/));
    for (int i = 0; i < count; i++) {
        JmriBeanComboBox* head = new JmriBeanComboBox(static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager")));
        head->excludeItems(alreadyUsed);
        headList.append(head);

        head->setEnabled(false);
        head->setCurrentText(currentMast->getHeadsUsed()->value(i)->getBean()->getDisplayName()); // must match JmriBeanComboBox above
        signalHeadPanel->layout()->addWidget(head);
    }
    signalHeadPanel->layout()->addWidget(includeUsed);
    signalHeadPanel->update();


    QStringList* disabled = currentMast->getDisabledAspects();
    if (!disabled->isEmpty()) {
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
/*public*/ bool SignalHeadSignalMastAddPane::createMast(/*@Nonnull*/ QString sigsysname, /*@Nonnull*/ QString mastname, /*@Nonnull*/ QString username) {
    log->debug(tr("createMast(%1,%1)").arg(sigsysname).arg(mastname));
    QString name;
    if (currentMast == nullptr) {
            QString build;// = new StringBuilder();
            build.append("IF$shsm:").append(sigsysname).append(":").append(mastname.mid(11, mastname.length() - 4));
            for (JmriBeanComboBox* head : headList) {
                if (head != nullptr && head->currentText() != "") {
                    build.append("(").append(StringUtil::parenQuote(head->currentText())).append(")");
                }
            }
            name = build;
            log->debug(tr("add signal: %1").arg(name));

            // see if it exists (remember, we're not handling a current mast)
            SignalMast* m = static_cast<SignalMastManager*>( InstanceManager::getDefault("SignalMastManager"))->getSignalMast(name);
            if (m != nullptr) {
                JOptionPane::showMessageDialog(nullptr, tr("The creation of this Signal Mast will cause a duplication of Signal Mast \"%1\"\nTherefore the Signal Mast has not been created").arg(m->getDisplayName()), tr("Duplicate Signal Mast"), JOptionPane::INFORMATION_MESSAGE);
                return false;
            }
            try {
                // now create it
                currentMast = (SignalHeadSignalMast*)static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->provideSignalMast(name);
            } catch (IllegalArgumentException ex) {
                // user input no good
                handleCreateException(name);
                return false; // without creating
            }
    }

    // heads are attached via the system name

    for (QString aspect : disabledAspects.keys()) {
        if (disabledAspects.value(aspect)->isChecked()) {
            currentMast->setAspectDisabled(aspect);
        } else {
            currentMast->setAspectEnabled(aspect);
        }
    }

    if (username !=("")) {
        currentMast->setUserName(username);
    }

    currentMast->setAllowUnLit(allowUnLit->isChecked());

    return true;
}

/*protected*/ void SignalHeadSignalMastAddPane::refreshHeadComboBox() {
    log->trace("refreshHeadComboBox");
    if (includeUsed->isChecked()) {
        alreadyUsed = QList<NamedBean*>();
    } else {
        QList<SignalHead*> alreadyUsedHeads = *SignalHeadSignalMast::getSignalHeadsUsed();
        alreadyUsed = QList<NamedBean*> ();
        log->trace(tr("   found %1").arg(alreadyUsedHeads.size()));
        for (SignalHead* head : alreadyUsedHeads) {
            alreadyUsed.append(head);
        }
    }

    for (JmriBeanComboBox* head : headList) {
        head->excludeItems(alreadyUsed);
    }
}

void SignalHeadSignalMastAddPane::handleCreateException(QString sysName) {
    JOptionPane::showMessageDialog(nullptr,
            tr("Could not create Signal Mast \"%1\" to add it.").arg(sysName) + "\n" + tr("ErrorAddFailedCheck"),
            tr("ErrorTitle"),
            JOptionPane::ERROR_MESSAGE);
}
#if 0
@ServiceProvider(service = SignalMastAddPane.SignalMastAddPaneProvider.class)
static /*public*/ class SignalMastAddPaneProvider extends SignalMastAddPane.SignalMastAddPaneProvider {
    /** {@inheritDoc} */
    @Override
    @Nonnull /*public*/ String getPaneName() {
        return tr("HeadCtlMast");
    }
    /** {@inheritDoc} */
    @Override
    @Nonnull /*public*/ SignalMastAddPane getNewPane() {
        return new SignalHeadSignalMastAddPane();
    }
}
#endif
/*private*/ /*final*/ /*static*/ Logger* SignalHeadSignalMastAddPane::log = LoggerFactory::getLogger("SignalHeadSignalMastAddPane");

