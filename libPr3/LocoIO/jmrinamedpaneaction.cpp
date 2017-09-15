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
#if 0
 qRegisterMetaType<LocoStatsPanel>("LocoStatsPanel");
 qRegisterMetaType<SlotMonPane>("SlotMonPane");
 qRegisterMetaType<DS64Panel>("DS64Panel");
 qRegisterMetaType<ClockMonPane>("ClockMonPane");
 qRegisterMetaType<LocoIdPanel>("LocoIdPanel");
 qRegisterMetaType<LocoMonPane>("LocoMonPane");
 qRegisterMetaType<QueryCvDialog>("QueryCvDialog");
 qRegisterMetaType<LocoNetMsgDialog>("LocoNetMsgDialog");
 qRegisterMetaType<CmdStnConfigPane>("CmdStnConfigPane");
 qRegisterMetaType<MessagePanel>("MessagePanel");
 qRegisterMetaType<Pr3SelectPane>("Pr3SelectPane");
 qRegisterMetaType<LoaderPane>("LoaderPane");
 qRegisterMetaType<SoundLoaderPane>("SoundLoaderPane");
 qRegisterMetaType<EditorPane>("EditorPane");
#endif
 log = new Logger("JmriNamedPaneAction");
 context = NULL;
 cache = NULL;
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

//        JmriPanel* p = (JmriPanel) Class.forName(paneClass).newInstance();
 QString className = paneClass;
 if(className.contains("."))
  className = paneClass.mid(paneClass.lastIndexOf(".")+1);
 int typeId = QMetaType::type(className.toLocal8Bit());
 if(typeId != 0)
 {
#if QT_VERSION < 0x050000
  JmriPanel* p = (JmriPanel*) QMetaType::construct(typeId);
#else
  JmriPanel* p = (JmriPanel*) QMetaType::create(typeId);
#endif
  p->setWindowInterface(wi);
  p->resize(100,80);
  p->initComponents();
  if(context == NULL)
   context = (LocoNetSystemConnectionMemo*) InstanceManager::getDefault("SystemConnectionMemo");
  p->initContext(context);
  p->setVisible(true);
  //p->pack();
  p->adjustSize();
  return p;
 }
 else
 {
  log->warn("could not load pane class: " + paneClass);
  //ex.printStackTrace();
  return NULL;
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
