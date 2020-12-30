#include "jmriabstractaction.h"
#include "jmrijframeinterface.h"
#include "action.h"
#include "exceptions.h"
#include "jmripanel.h"

JmriAbstractAction::JmriAbstractAction(QObject *parent) :
  AbstractAction(parent)
{
 common();
}
/**
 * Abstract base for actions that will work with multiple JMRI GUIs.
 *
 * An opaque Object can be passed as a context, but nullptr is also possible.
 *
 * <b>NOTE</b> Either {@link jmri.util.swing.JmriAbstractAction#actionPerformed(java.awt.event.ActionEvent)
 * }
 * or {@link jmri.util.swing.JmriAbstractAction#makePanel() } must be overridden
 * by extending classes.
 *
 * @author	Bob Jacobsen Copyright (C) 2010
 * @version	$Revision: 28746 $
 */
///*abstract*/ /*public*/  class JmriAbstractAction extends javax.swing.AbstractAction {

/**
 *
 */
//static Logger log = LoggerFactory.getLogger(JmriAbstractAction.class.getName());

/**
 * Enhanced constructor for placing the pane in various GUIs
 */
/*public*/  JmriAbstractAction::JmriAbstractAction(QString s, WindowInterface* wi)
 :  AbstractAction(s,  wi)
{
 //super(s);
 common();
 this->wi = wi;
 if (wi == nullptr)
 {
  Logger::error(tr("Cannot create '%1' action with NULL WindowInterface"/*, new Exception()*/).arg(s));
 }
}

/*public*/  JmriAbstractAction::JmriAbstractAction(QString s, QIcon i, WindowInterface* wi)
:  AbstractAction(s, i, wi)
{
 //super(s, i);
 common();
 this->wi = wi;
}

/**
 * @since 2.9.4
 */
/*public*/  void JmriAbstractAction::setContext(QObject* context)
{
 this->context = context;
}

/**
 * Original constructor for compatibility with older menus. Assumes SDI GUI.
 */
/*public*/  JmriAbstractAction::JmriAbstractAction(QString s,QObject *parent)
 : AbstractAction(s, parent)
{
 //super(s);
 common();
 this->wi = new JmriJFrameInterface();
}

void JmriAbstractAction::common()
{
 //hint = WindowInterface::DEFAULT;
 context = nullptr;
 cache = nullptr;
 //connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/  void JmriAbstractAction::setWindowInterface(WindowInterface* wi) {
    this->wi = wi;
}

/*public*/  void JmriAbstractAction::setName(QString name) {
    putValue(Action::NAME, name);
}

//@Override
/*public*/  QString toString() {
    //return (String) getValue(javax.swing.Action.NAME);
 return Action::NAME;
}

///*public*/  JmriAbstractAction* JmriAbstractAction::setHint(WindowInterface::Hint hint) {
//    this->hint = hint;
//    return this;
//}

//@Override
/*public*/  void JmriAbstractAction::actionPerformed(JActionEvent * /*e*/)
{
 // we have to make a new panel if we don't have one yet
 // we don't make a new panel if the window interface is
 //      single instance (not multiple instance),
 // of if the existing panel is single instance (not multiple instance)
 if (cache == nullptr
         || (wi->multipleInstances() && cache->isMultipleInstances()))
 {
  try
  {
   cache = makePanel();
  } catch (Exception ex)
  {
Logger::error("Exception creating panel: " + ex.getMessage());
   return;
  }
  if (cache == nullptr)
  {
   Logger::error("Unable to make panel");
   return;
  }
 }

 if(static_cast<JmriJFrameInterface*>(wi) != nullptr)
  ((JmriJFrameInterface*)wi)->show(cache, this, WindowInterface::DEFAULT);  // no real context, this is new content

 wi->show(cache, this, WindowInterface::DEFAULT);  // no real context, this is new content
}

/*public*/  void JmriAbstractAction::dispose()
{
 if (cache != nullptr)
 {
  cache->dispose();
  cache = nullptr;
 }
}

//A crude method to set a parameter in a given window when loading from the xml file
/*public*/  void JmriAbstractAction::setParameter(QString /*parameter*/, QString /*value*/) {
}

// A method to allow named parameters to be passed in
// Note that if value is a String, setParameter(String, String) needs to be
// implemented (for reasons I do not understand jmri.util.swing.GuiUtilBase
// will not call this method with a String parameter for value)
/*public*/  void JmriAbstractAction::setParameter(QString /*parameter*/, QObject* /*value*/) {
}

/*public*/  JmriPanel* JmriAbstractAction::makePanel() {
    Logger::error("makePanel must be overridden"/*, new Exception()*/);
    return nullptr;
}
