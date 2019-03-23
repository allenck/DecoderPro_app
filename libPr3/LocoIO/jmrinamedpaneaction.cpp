#include "jmrinamedpaneaction.h"
#include "windowinterface.h"
#include "jmripanel.h"
#include <QMetaType>
#include "locostatspanel.h"
#include "instancemanager.h"
#include "slotmonpane.h"
#include "ds64panel.h"
#include "clockmonpane.h"
#include "locoidpanel.h"
#include "locomonpane.h"
#include "querycvdialog.h"
#include "loconetmsgdialog.h"
#include "cmdstnconfigpane.h"
#include "messagepanel.h"
#include "pr3selectpane.h"
#include "loaderpane.h"
#include "../loconet/soundloaderpane.h"
#include "../loconet/editorpane.h"
#include "class.h"

JmriNamedPaneAction::JmriNamedPaneAction(QObject *parent) :
  JmriAbstractAction("<none>", parent)
{
 common();
}
/**
 * Action to create and load a JmriPanel from just its name.
 *
 * @author	Bob Jacobsen Copyright (C) 2010
 * @version	$Revision: 28746 $
 */
///*public*/ class JmriNamedPaneAction extends JmriAbstractAction {

//    /**
//     *
//     */
//    private static final long serialVersionUID = -16587323774213371L;

/**
 * Enhanced constructor for placing the pane in various GUIs
 */
/*public*/ JmriNamedPaneAction::JmriNamedPaneAction(QString s, WindowInterface* wi, QString paneClass)
 : JmriAbstractAction(s, wi)
{
 //super(s, wi);
 this->paneClass = paneClass;
 this->wi = wi;
 common();
}

/*public*/ JmriNamedPaneAction::JmriNamedPaneAction(QString s, QIcon i, WindowInterface* wi, QString paneClass)
 : JmriAbstractAction(s, i, wi)
{
 //super(s, i, wi);
 this->paneClass = paneClass;
 this->wi = wi;
 common();
}
void JmriNamedPaneAction::common()
{
 log = new Logger("JmriNamedPaneAction");
 context = nullptr;
 cache = nullptr;
 hint = WindowInterface::DEFAULT;
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/**
 * Original constructor for compatibility with older menus. Assumes SDI GUI.
 */
/*public*/ JmriNamedPaneAction::JmriNamedPaneAction(QString s, QString p, QObject* parent) : JmriAbstractAction(s, parent)
{
    //this(s, new jmri.util.swing.sdi.JmriJFrameInterface(), p);
 this->paneClass = p;
 common();
}


/*public*/ JmriPanel* JmriNamedPaneAction::makePanel()
{
 try
 {
  JmriPanel* p = (JmriPanel*) Class::forName(paneClass)->newInstance();
// QString className = paneClass;
// if(className.contains("."))
//  className = paneClass.mid(paneClass.lastIndexOf(".")+1);
// int typeId = QMetaType::type(className.toLocal8Bit());
// if(typeId != 0)
// {
//#if QT_VERSION < 0x050000
//  JmriPanel* p = (JmriPanel*) QMetaType::construct(typeId);
//#else
//  JmriPanel* p = (JmriPanel*) QMetaType::create(typeId);
//#endif
  p->setWindowInterface(wi);
  p->resize(100,80);
  p->initComponents();
  if(context == nullptr)
   context = (LocoNetSystemConnectionMemo*) InstanceManager::getDefault("LocoNetSystemConnectionMemo");
  p->initContext(context);
  p->setVisible(true);
  //p->pack();
  p->adjustSize();
  return p;
 }
 catch(ClassNotFoundException ex)
 {
  log->warn("could not load pane class: " + paneClass);
  //ex.printStackTrace();
  return nullptr;
 }
 catch(IllegalAccessException ex)
 {
  log->warn("could not load pane class: " + paneClass);
  //ex.printStackTrace();
  return nullptr;
 }
 catch(InstantiationException ex)
 {
  log->warn("could not load pane class: " + paneClass);
  //ex.printStackTrace();
  return nullptr;
 }
}
#if 0
//@Override
/*public*/ void JmriNamedPaneAction::actionPerformed(ActionEvent* /*e*/)
{
 // we have to make a new panel if we don't have one yet
 // we don't make a new panel if the window interface is
 //      single instance (not multiple instance),
 // of if the existing panel is single instance (not multiple instance)
 if (cache == NULL
         || (wi->multipleInstances() && cache->isMultipleInstances()))
 {
  //try {
  cache = makePanel();
  //} catch (Exception ex) {
//  if(cache == NULL)
//      log->error("Exception creating panel: " + ex);
//      return;
//  }
  if (cache == NULL)
  {
   log->error("Unable to make panel " + paneClass);
   return;
  }
 }
 QSize sz = cache->size();
 wi->setMinimumSize(sz);
 wi->show(cache, this, hint);  // no real context, this is new content
 wi->resize(sz);
}
#endif
