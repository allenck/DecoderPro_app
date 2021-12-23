#include "turnoutsignalmastaddpane.h"
#include "loggerfactory.h"
#include <QBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QScrollArea>
#include "beanselectcreatepanel.h"
#include "turnout.h"
#include "instancemanager.h"
#include <QComboBox>
#include <QGroupBox>
#include "turnoutsignalmast.h"
#include "signalmastmanager.h"

/**
 * A pane for configuring TurnoutSignalMast objects
 * <P>
 * @see jmri.jmrit.beantable.signalmast.SignalMastAddPane
 * @author Bob Jacobsen Copyright (C) 2017, 2018
 * @since 4.11.2
 */
///*public*/ class TurnoutSignalMastAddPane extends SignalMastAddPane {

/*public*/ TurnoutSignalMastAddPane::TurnoutSignalMastAddPane(QWidget *parent)
 : SignalMastAddPane(parent)
{
 turnoutMastPanel = new QWidget();
 turnoutMastPanel->setLayout(new QVBoxLayout());
 resetPreviousState = new QCheckBox(tr("Reset previous Aspect"));
 allowUnLit = new QCheckBox();
 turnoutAspect = QMap<QString, TurnoutAspectPanel*>(/*NOTIONAL_ASPECT_COUNT*/); // only used once, see updateTurnoutAspectPanel()
 disabledAspectsPanel = new QWidget();
 currentMast = nullptr;

 stateThrown = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText();
 stateClosed = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText();
 turnoutStates = QStringList() << stateClosed << stateThrown;
 turnoutStateValues = QList<int>() << Turnout::CLOSED <<  Turnout::THROWN;

 turnoutUnLitBox = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
 turnoutUnLitState = new QComboBox(/*turnoutStates*/);
 turnoutUnLitState->addItems(turnoutStates);
 paddedNumber = new DecimalFormat("0000");

 //setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
 QVBoxLayout* thisLayout = new QVBoxLayout(this);
 // lit/unlit controls
 QWidget* p = new QWidget();
 //p.setLayout(new BoxLayout(p, BoxLayout.X_AXIS));
 QHBoxLayout* pLayout = new QHBoxLayout(p);
 pLayout->addWidget(new QLabel(tr("This Mast can be unlit") + ": "));
 pLayout->addWidget(allowUnLit);
 //p.setAlignmentX(Component.LEFT_ALIGNMENT);
 thisLayout->addWidget(p, 0, Qt::AlignLeft);

 turnoutMastScroll = new QScrollArea(/*turnoutMastPanel*/);
 turnoutMastScroll->setWidget(turnoutMastPanel);
 turnoutMastScroll->setWidgetResizable(true);
 //turnoutMastScroll.setBorder(BorderFactory.createEmptyBorder());
 thisLayout->addWidget(turnoutMastScroll);

}

/** {@inheritDoc} */
//@Override
/*@Nonnull*/ /*public*/ QString TurnoutSignalMastAddPane::getPaneName() {
    return tr("Turnout Controlled Mast");
}

/** {@inheritDoc} */
//@Override
/*public*/ void TurnoutSignalMastAddPane::setAspectNames(/*@Nonnull*/
        SignalAppearanceMap* map, SignalSystem* /*sigSystem*/)
{
    QStringListIterator aspects = map->getAspects();
    log->debug("setAspectNames(...)");

    //turnoutMastPanel.removeAll();
    QObjectList ol = turnoutMastPanel->children();
    foreach(QObject* obj, ol)
    {
     if(qobject_cast<QWidget*>(obj))
     {
      turnoutMastPanel->layout()->removeWidget(qobject_cast<QWidget*>(obj));
      if(!qobject_cast<QCheckBox*>(obj))
       obj->deleteLater();
     }
    }

    turnoutAspect.clear();
    while (aspects.hasNext())
    {
     QString aspect = aspects.next();
     TurnoutAspectPanel* aPanel = new TurnoutAspectPanel(aspect, this);
     turnoutAspect.insert(aspect, aPanel);
    }

    delete turnoutMastPanel->layout();
    turnoutMastPanel->setLayout(new QVBoxLayout());
    for (QString aspect : turnoutAspect.keys())
    {
     log->trace(tr("   aspect: %1").arg(aspect));
     turnoutMastPanel->layout()->addWidget(turnoutAspect.value(aspect)->getPanel());
    }

    turnoutMastPanel->layout()->addWidget(resetPreviousState);
    resetPreviousState->setToolTip(tr("Select to reset the previous Aspect command to Dark before setting the new Aspect."));

//??    turnoutMastPanel.setLayout(new jmri.util.javaworld.GridLayout2(0, 2)); // 0 means enough

    turnoutMastPanel->update();
    turnoutMastScroll->update();
}


/** {@inheritDoc} */
//@Override
/*public*/ bool TurnoutSignalMastAddPane::canHandleMast(/*@Nonnull*/ SignalMast* mast) {
    //return mast instanceof TurnoutSignalMast;
     return qobject_cast<TurnoutSignalMast*>(mast) != nullptr;
}

/** {@inheritDoc} */
//@Override
/*public*/ void TurnoutSignalMastAddPane::setMast(SignalMast* mast) {
    log->trace(tr("setMast(%1) start").arg(mast == nullptr?"null":mast->getDisplayName()));
    if (mast == nullptr) {
        currentMast = nullptr;
        return;
    }

    if (! (qobject_cast<TurnoutSignalMast*>(mast)!= nullptr) ) {
        log->error(tr("mast was wrong type: %1 %2").arg(mast->getSystemName()).arg( mast->className()));
        return;
    }

    currentMast = (TurnoutSignalMast*) mast;
    SignalAppearanceMap* appMap = mast->getAppearanceMap();

    if (appMap != nullptr) {
        QStringListIterator aspects = appMap->getAspects();
        while (aspects.hasNext()) {
            QString key = aspects.next();
            //Objects.requireNonNull(key, "only non-null keys are expected");
            TurnoutAspectPanel* turnPanel = turnoutAspect.value(key);
            //Objects.requireNonNull(turnPanel, "a panel should exist for each aspect");
            turnPanel->setSelectedTurnout(currentMast->getTurnoutName(key));
            turnPanel->setTurnoutState(currentMast->getTurnoutState(key));
            turnPanel->setAspectDisabled(currentMast->isAspectDisabled(key));
        }
    }
    if (currentMast->resetPreviousStates()) {
        resetPreviousState->setChecked(true);
    }
    if (currentMast->allowUnLit()) {
        turnoutUnLitBox->setDefaultNamedBean(currentMast->getUnLitTurnout());
        if (currentMast->getUnLitTurnoutState() == Turnout::CLOSED) {
            turnoutUnLitState->setCurrentText(stateClosed);
        } else {
            turnoutUnLitState->setCurrentText(stateThrown);
        }

    }

    allowUnLit->setChecked(currentMast->allowUnLit());

    log->trace(tr("setMast(%1) end").arg(mast->getDisplayName()));
}

/** {@inheritDoc} */
//@Override
/*public*/ bool TurnoutSignalMastAddPane::createMast(/*@Nonnull*/ QString sigsysname, /*@Nonnull */QString mastname, /*@Nonnull*/ QString username) {
    log->debug(tr("createMast(%1,%2)").arg(sigsysname).arg(mastname));
    QString name;
    if (currentMast == nullptr) {
        name = "IF$tsm:"
                + sigsysname
                + ":" + mastname.mid(11, mastname.length() - 15);
        name += "($" + (paddedNumber->format(TurnoutSignalMast::getLastRef() + 1)) + ")";
        currentMast = new TurnoutSignalMast(name);

        static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->Register(currentMast);
    }
    name = currentMast->getSystemName();

    // load a new or existing mast
    for (QString aspect : turnoutAspect.keys()) {
        turnoutAspect.value(aspect)->setReference(name + ":" + aspect);
        turnoutMastPanel->layout()->addWidget(turnoutAspect.value(aspect)->getPanel());
        if (turnoutAspect.value(aspect)->isAspectDisabled()) {
            currentMast->setAspectDisabled(aspect);
        } else {
            currentMast->setAspectEnabled(aspect);
            currentMast->setTurnout(aspect, turnoutAspect.value(aspect)->getTurnoutName(), turnoutAspect.value(aspect)->getTurnoutState());
        }
    }
    currentMast->resetPreviousStates(resetPreviousState->isChecked());
    if (username != ("")) {
        currentMast->setUserName(username);
    }
    currentMast->setAllowUnLit(allowUnLit->isChecked());
    if (allowUnLit->isChecked()) {
        currentMast->setUnLitTurnout(turnoutUnLitBox->getDisplayName(), turnoutStateValues[turnoutUnLitState->currentIndex()]);
    }
    return true;
}


//@ServiceProvider(service = SignalMastAddPane.SignalMastAddPaneProvider.class)
//static /*public*/ class SignalMastAddPaneProvider extends SignalMastAddPane.SignalMastAddPaneProvider {
    /** {@inheritDoc} */
    //@Override
    /*@Nonnull*/ /*public*/ QString TurnoutSignalMastAddPaneProvider::getPaneName() {
        return tr("Turnout Controlled Mast");
    }
    /** {@inheritDoc} */
    //@Override
    /*@Nonnull*/ /*public*/ SignalMastAddPane* TurnoutSignalMastAddPaneProvider::getNewPane() {
        return new TurnoutSignalMastAddPane();
    }
//}


/**
 * JPanel to define properties of an Aspect for a Turnout Signal Mast.
 * <p>
 * Invoked from the AddSignalMastPanel class when a Turnout Signal Mast is
 * selected.
 */
//class TurnoutAspectPanel {


TurnoutAspectPanel::TurnoutAspectPanel(QString aspect, TurnoutSignalMastAddPane* pane) {
 this->pane = pane;
 setObjectName("TurnoutAspectPanel" + aspect);
 common();
    this->aspect = aspect;
}

TurnoutAspectPanel::TurnoutAspectPanel(QString turnoutName, int /*state*/, TurnoutSignalMastAddPane* pane) {
 this->pane = pane;
 setObjectName("TurnoutAspectPanel" + turnoutName);
 common();
 if (turnoutName.isEmpty()) {
     return;
 }
 beanBox->setDefaultNamedBean(InstanceManager::turnoutManagerInstance()->getTurnout(turnoutName));
}
void TurnoutAspectPanel::common()
{

 beanBox = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
 disabledCheck = new QCheckBox(tr("Disable Aspect"));
 turnoutStateLabel = new QLabel(tr("Set State"));
 turnoutState = new QComboBox(/*turnoutStates*/);
 turnoutState->addItems(pane->turnoutStates);

 aspect = "";
}
/**
 * Store the mast name as comment in the turnout.
 *
 * @param reference Text to use as comment
 */
void TurnoutAspectPanel::setReference(QString reference) {
    beanBox->setReference(reference);
}

int TurnoutAspectPanel::getTurnoutState() {
    return pane->turnoutStateValues[turnoutState->currentIndex()];
}

void TurnoutAspectPanel::setSelectedTurnout(QString name) {
    if (name.isEmpty()) {
        return;
    }
    beanBox->setDefaultNamedBean(InstanceManager::turnoutManagerInstance()->getTurnout(name));
}

void TurnoutAspectPanel::setTurnoutState(int state) {
    if (state == Turnout::CLOSED) {
        turnoutState->setCurrentText(pane->stateClosed);
    } else {
        turnoutState->setCurrentText(pane->stateThrown);
    }
}

void TurnoutAspectPanel::setAspectDisabled(bool boo) {
    disabledCheck->setChecked(boo);
    if (boo) {
        beanBox->setEnabled(false);
        turnoutStateLabel->setEnabled(false);
        turnoutState->setEnabled(false);
    } else {
        beanBox->setEnabled(true);
        turnoutStateLabel->setEnabled(true);
        turnoutState->setEnabled(true);
    }
}

bool TurnoutAspectPanel::isAspectDisabled() {
    return disabledCheck->isChecked();
}

QString TurnoutAspectPanel::getTurnoutName() {
    return beanBox->getDisplayName();
}

NamedBean* TurnoutAspectPanel::getTurnout() {
    try {
        return beanBox->getNamedBean();
    } catch (JmriException* ex) {
        pane->log->warn("skipping creation of turnout");
        return nullptr;
    }
}

//JPanel panel;

QGroupBox* TurnoutAspectPanel::getPanel()
{
 if (panel == nullptr)
 {
  panel = new QGroupBox();
  //panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
  QVBoxLayout* panelLayout = new QVBoxLayout(panel);
  panel->resize(300,200);
  QWidget* turnDetails = new QWidget();
  QHBoxLayout* turnDetailsLayout = new QHBoxLayout(turnDetails);
  turnDetailsLayout->addWidget(beanBox);
  turnDetailsLayout->addWidget(turnoutStateLabel);
  turnDetailsLayout->addWidget(turnoutState);
  panelLayout->addWidget(turnDetails);
  panelLayout->addWidget(disabledCheck);
//            TitledBorder border = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));
//            border.setTitle(aspect);
//            panel.setBorder(border);
  panel->setTitle(aspect);

//            disabledCheck.addActionListener((ActionEvent e) -> {
//                setAspectDisabled(disabledCheck.isSelected());
//            });
  connect(disabledCheck, SIGNAL(toggled(bool)), this, SLOT(setAspectDisabled(bool)));
 }
 return panel;
}

/*private*/ /*final*/ /*static*/ Logger* TurnoutSignalMastAddPane::log = LoggerFactory::getLogger("TurnoutSignalMastAddPane");

