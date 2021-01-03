#include "reportericon.h"
#include "instancemanager.h"
#include "abstractreporter.h"
#include "defaultidtag.h"
#include "editor.h"
#include "rosterentry.h"

//ReporterIcon::ReporterIcon(QObject *parent) :
//    PositionableLabel(parent)
//{
//}
/**
 * An icon to display info from a Reporter, e.g. transponder or RFID reader.<P>
 *
 * @author Bob Jacobsen  Copyright (c) 2004
 * @version $Revision: 22320 $
 */

///*public*/ class ReporterIcon extends PositionableLabel implements java.beans.PropertyChangeListener {

/*public*/ ReporterIcon::ReporterIcon(Editor* editor) : PositionableLabel("???", editor)
{
    // super ctor call to make sure this is a QString label
    //super("???", editor);
    log = new Logger("ReporterIcon");
    setText("<no report>");
    reporter = NULL;
    setPopupUtility(new ReporterPopupUtil((Positionable*)this, this));
}
/*public*/ ReporterIcon::~ReporterIcon() {}
/*public*/ Positionable* ReporterIcon::deepClone() {
    ReporterIcon* pos = new ReporterIcon(_editor);
    return finishClone((Positionable*)pos);
}

/*public*/ Positionable* ReporterIcon::finishClone(Positionable* p) {
    ReporterIcon* pos = (ReporterIcon*)p;
    pos->setReporter(reporter->getSystemName());
    return PositionableLabel::finishClone((Positionable*)pos);
}

/**
 * Attached a named Reporter to this display item
 * @param pName Used as a system/user name to lookup the Reporter object
 */
/*public*/ void ReporterIcon::setReporter(QString pName)
{
 if (((ReporterManager*)InstanceManager::getDefault("ReporterManager"))!=NULL)
 {
  reporter = ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->provideReporter(pName);
  if (reporter != NULL)
  {
   setReporter(reporter);
   AbstractReporter* aR = (AbstractReporter*)reporter;
   connect(aR->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(on_propertyChange(PropertyChangeEvent*)));
  }
  else
  {
   log->error("Reporter '"+pName+"' not available, icon won't see changes");
  }
 }
 else
 {
  log->error("No ReporterManager for this protocol, icon won't see changes");
 }
}

/*public*/ void ReporterIcon::setReporter(Reporter* r)
{
 if (reporter != NULL)
 {
  //reporter->removePropertyChangeListener(this);
 }
 reporter = r;
 if (reporter != NULL)
 {
  displayState();
  reporter->addPropertyChangeListener((PropertyChangeListener*)this);
  //AbstractReporter* ar = (AbstractReporter*)r;
//  connect(ar, SIGNAL(propertyChange(AbstractReporter*,QString,QObject*,QObject*)), this, SLOT(on_propertyChange(AbstractReporter*,QString,QObject*,QObject*)));
//  connect(ar->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(on_propertyChange(PropertyChangeEvent*)));
 }
}

/*public*/ Reporter* ReporterIcon::getReporter() { return reporter; }

// update icon as state changes
/*public*/ void ReporterIcon::propertyChange(PropertyChangeEvent* e) {
    if (log->isDebugEnabled()) log->debug("property change: "
                                        +e->getPropertyName()
                                        +" is now "+e->getNewValue().toString());
    displayState();
}
//void ReporterIcon::on_propertyChange(AbstractReporter*,QString sType, QObject * oOld, QObject * oNew)
void ReporterIcon::on_propertyChange(PropertyChangeEvent*e)
{
 QString sType = e->getPropertyName();
 QObject* oOld = VPtr<QObject>::asPtr(e->getOldValue());
 QObject* oNew = VPtr<QObject>::asPtr(e->getNewValue());

 if(sType == "lastReport" && oOld != NULL)
  log->debug(tr("PropertyChange %1 %2").arg(sType).arg(oOld->metaObject()->className()));
 if(sType == "currentReport")
 {
  log->debug(tr("PropertyChange %1 %2").arg(sType).arg(oNew->metaObject()->className()));
  if(qobject_cast<DefaultIdTag*>(oNew)!=NULL)
  {
   DefaultIdTag* tag = (DefaultIdTag*)oNew;
   if(tag->rosterId() != 0)
    setText(QString("%1").arg(tag->rosterId()));
   else
    setText(tag->getTagID());
   _editor->addToTarget((Positionable*)this);
  }
 }
}

/*public*/ QString ReporterIcon::getNameString()
{
 QString name;
 if (reporter == NULL) name = tr("<Not connected>");
 else if (reporter->getUserName()!=NULL)
  name = reporter->getUserName()+" ("+reporter->getSystemName()+")";
 else
  name = reporter->getSystemName();
 return name;
}


/**
 * Drive the current state of the display from the state of the
 * Reporter.
 */
void ReporterIcon::displayState()
{
    if (((AbstractReporter*)reporter)->getCurrentReport()!=QVariant())
 {
  if (((AbstractReporter*)reporter)->getCurrentReport().toString()==(""))
   setText(tr("Blank"));
  else
   setText(reporter->getCurrentReport().toString());
 }
 else
 {
  setText(tr("<no report>"));
 }
 updateSize();
 return;
}
#if 1 // TODO:
/*protected*/ void ReporterIcon::edit()
{
 makeIconEditorFrame(this, "Reporter", true, NULL);
 _iconEditor->setPickList(PickListModel::reporterPickModelInstance());
//    ActionListener addIconAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            editReporter();
//        }
//    };
 AddReporterIconActionListener* addIconAction = new AddReporterIconActionListener(this);
 _iconEditor->complete(addIconAction, false, true, true);
 _iconEditor->setSelection(reporter);

}
void ReporterIcon::editReporter() {
    setReporter((Reporter*)_iconEditor->getTableSelection());
    setSize(getPreferredSize().width(), getPreferredSize().height());
    _iconEditorFrame->dispose();
    _iconEditorFrame = NULL;
    _iconEditor = NULL;
//    invalidate();
}

/*public*/ void ReporterIcon::dispose() {
//    reporter->removePropertyChangeListener(this);
    reporter = NULL;

    PositionableLabel::dispose();
}
#endif
