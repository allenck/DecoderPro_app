#include "idtagtableaction.h"
#include "idtagmanager.h"
#include "idtag.h"
#include "instancemanager.h"
#include <QPushButton>
#include "userpreferencesmanager.h"
#include "jtextfield.h"
#include <QCheckBox>
#include "reporter.h"
#include "joptionpane.h"
#include "abstracttabletabaction.h"
#include <QBoxLayout>
#include "addnewdevicepanel.h"
#include "rfid/proxyidtagmanager.h"
#include "idtagtabledatamodel.h"
#include "loggerfactory.h"

//IdTagTableAction::IdTagTableAction()
//{

//}
/**
 * Swing action to create and register a IdTagTable GUI.
 *
 * @author  Bob Jacobsen Copyright (C) 2003
 * @author  Matthew Harris Copyright (C) 2011
 * @since 2.11.4
 */
///*public*/ class IdTagTableAction extends AbstractTableAction {

/**
* Create an action with a specific title.
* <P>
* Note that the argument is the Action title, not the title of the
* resulting frame. Perhaps this should be changed?
*
* @param actionName title of the action
*/
//@SuppressWarnings("OverridableMethodCallInConstructor")
/*public*/ IdTagTableAction::IdTagTableAction(QString actionName, QObject* parent) :
    AbstractTableAction(actionName, parent)
{
 //super(actionName);

 // disable ourself if there is no primary IdTag manager available
 if (((DefaultIdTagManager*)InstanceManager::getDefault("IdTagManager")) == NULL) {
     setEnabled(false);
 }

 init();
}

/*public*/ IdTagTableAction::IdTagTableAction(QObject* parent) : AbstractTableAction(tr("IdTag Table"), parent)
{
//this(tr("TitleIdTagTable"));
 init();
}

/*final*/ void IdTagTableAction::init(){
    tagManager->addPropertyChangeListener(this);
}

/**
 * {@inheritDoc}
 */
//@Override
/*final*/ void IdTagTableAction::setManager(/*@Nonnull*/ Manager/*<IdTag>*/* t) {
    tagManager->removePropertyChangeListener(this);
    if (qobject_cast<IdTagManager*>(t->mself())) {
        tagManager = (IdTagManager*) t->mself();
        if (m != nullptr) {
            m->setManager(tagManager);
        }
    }
    // if t is not an instance of IdTagManager, tagManager may not change.
    tagManager->addPropertyChangeListener(this);
}

/**
* Create the JTable DataModel, along with the changes for the specific case
* of IdTag objects
*/
//@Override
/*protected*/ void IdTagTableAction::createModel()
{
 m = new IdTagTableDataModel(tagManager);
}
//@Override
/*protected*/ void IdTagTableAction::setTitle() {
    f->setTitle(tr("IdTag Table"));
}

//@Override
/*protected*/ QString IdTagTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.IdTagTable";
}


//@Override
/*protected*/ void IdTagTableAction::addPressed(JActionEvent *) {
    if (addFrame == nullptr) {
        addFrame = new JmriJFrameX(tr("Add Id Tag"), false, true);
        addFrame->addHelpMenu("package.jmri.jmrit.beantable.IdTagAddEdit", true);
        QVBoxLayout* thisLayout;
        addFrame->getContentPane()->setLayout(thisLayout = new QVBoxLayout()); //, BoxLayout.Y_AXIS));

//        ActionListener okListener = (ActionEvent ev) -> {
//            okPressed(ev);
//        };
        IdTagOkListener* okListener = new IdTagOkListener(this);

//        ActionListener cancelListener = (ActionEvent ev) -> {
//            cancelPressed(ev);
//        };
        CancelListener* cancelListener = new CancelListener(this);

        thisLayout->addWidget(new AddNewDevicePanel(sysName, userName, "OK", okListener, cancelListener));
    }
    addFrame->adjustSize();
    addFrame->setVisible(true);
}

void IdTagTableAction::cancelPressed(ActionEvent* /*e*/) {
    addFrame->setVisible(false);
    addFrame->dispose();
    addFrame = NULL;
}

void IdTagTableAction::okPressed(ActionEvent* /*e*/) {
    QString user = userName->text();
    if (user==("")) {
        user = "";
    }
//        String tag = tagID.getText();
//        if (tag.equals("")) tag=NULL;
    QString sName = sysName->text();
    try {
        tagManager->newIdTag(sName, user);
    } catch (IllegalArgumentException* ex) {
        // user input no good
        handleCreateException(sName, ex);
    }
    //addFrame->close();
}

//private boolean noWarn = false;
IdTagOkListener::IdTagOkListener(IdTagTableAction *act)
{
    this->act = act;
}
void IdTagOkListener::actionPerformed(JActionEvent *)
{
  act->okPressed();
}
CancelListener::CancelListener(IdTagTableAction *act)
{ this->act = act; }
void CancelListener::actionPerformed(JActionEvent */*e*/)
{
    act->cancelPressed();
}

void IdTagTableAction::handleCreateException(QString sysName, IllegalArgumentException* ex) {
    JOptionPane::showMessageDialog(addFrame,
            tr("Error: Could not create ID tag \%1\" to add it.rIdTagAddFailed").arg(sysName) + "\n" + tr("Check that number/name is OK and not in use.")
            + "\n" + ex->getLocalizedMessage() ,
            tr("Error"),
            JOptionPane::ERROR_MESSAGE);
}

//@Override
/*public*/ QString IdTagTableAction::getClassDescription() {
    return tr("IdTag Table");
}

//@Override
/*public*/ void IdTagTableAction::addToFrame(BeanTableFrame* f) {
    f->addToBottomBox(isStateStored, this->metaObject()->className());
    isStateStored->setChecked(tagManager->isStateStored());
//    isStateStored->addActionListener((ActionEvent e) -> {
    connect(isStateStored, &QCheckBox::clicked, [=]{
        ((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->setStateStored(isStateStored->isChecked());
    });
//    StateStoredActionListener* stateStoredActionListener = new StateStoredActionListener(this);
//    //connect(isStateStored, SIGNAL(toggled(bool)), stateStoredActionListener->self(), SLOT(actionPerformed()));
//    connect(isStateStored, &QCheckBox::clicked, [=]{stateStoredActionListener->actionPerformed();});
    f->addToBottomBox(isFastClockUsed, this->metaObject()->className());
    isFastClockUsed->setChecked(tagManager->isFastClockUsed());
//    isFastClockUsed.addActionListener((ActionEvent e) -> {
    connect(isFastClockUsed, &QCheckBox::clicked, [=]{
        ((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->setFastClockUsed(isFastClockUsed->isChecked());
    });
//    FastClockUsedActionListener* fastClockUsedActionListener = new FastClockUsedActionListener(this);
//    //connect(isFastClockUsed, SIGNAL(toggled(bool)), fastClockUsedActionListener->self(), SLOT(actionPerformed()));
//    connect(isFastClockUsed, &QCheckBox::clicked, [=]{fastClockUsedActionListener->actionPerformed();});
    log->debug("Added CheckBox in addToFrame method");
}
//StateStoredActionListener::StateStoredActionListener(IdTagTableAction* act)
//{
//  this->act = act;
//}
//void StateStoredActionListener::actionPerformed(JActionEvent *)
//{
// ((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->setStateStored(act->isStateStored->isChecked());

//}
//FastClockUsedActionListener::FastClockUsedActionListener(IdTagTableAction *act)
//{
//    this->act = act;
//}
//void FastClockUsedActionListener::actionPerformed(JActionEvent *)
//{
//    ((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->setFastClockUsed(act->isFastClockUsed->isChecked());
//}

//@Override
/*public*/ void IdTagTableAction::addToPanel(AbstractTableTabAction* f) {
    QString connectionName = tagManager->getMemo()->getUserName();
    if (qobject_cast<ProxyIdTagManager*>(tagManager->mself())) {
        connectionName = "All";
    }
//    else if (connectionName == nullptr && (tagManager instanceof DefaultRailComManager)) {
//        connectionName = "RailCom"; // NOI18N (proper name).
//    }
    f->addToBottomBox(isStateStored, this->metaObject()->className());
    isStateStored->setChecked(((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->isStateStored());
//    isStateStored.addActionListener((ActionEvent e) -> {
    connect(isStateStored, &QCheckBox::clicked, [=]{
        ((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->setStateStored(isStateStored->isChecked());
    });
//    StateStoredActionListener* stateStoredActionListener = new StateStoredActionListener(this);
//    connect(isStateStored, SIGNAL(toggled(bool)), stateStoredActionListener->self(), SLOT(actionPerformed()));
    f->addToBottomBox(isFastClockUsed, this->metaObject()->className());
    isFastClockUsed->setChecked(((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->isFastClockUsed());
//    isFastClockUsed.addActionListener((ActionEvent e) -> {
    connect(isFastClockUsed, &QCheckBox::clicked, [=]{
        ((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->setFastClockUsed(isFastClockUsed->isChecked());
    });
//    FastClockUsedActionListener* fastClockUsedActionListener = new FastClockUsedActionListener(this);
//    connect(isFastClockUsed, SIGNAL(toggled(bool)), fastClockUsedActionListener->self(), SLOT(actionPerformed()));
    log->debug("Added CheckBox in addToPanel method");
}

//@Override
/*protected*/ QString IdTagTableAction::getClassName() {
    return "jmri.jmrit.beantable.IdTagTableAction";
}

/*private*/ /*static*/ /*final*/ Logger* IdTagTableAction::log = LoggerFactory::getLogger("IdTagTableAction");
