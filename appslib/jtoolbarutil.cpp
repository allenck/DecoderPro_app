#include "jtoolbarutil.h"
#include "windowinterface.h"
#include "action.h"
#include <QToolBar>
#include <QVariant>
#include "rosterentry.h"
#include <QToolButton>
#include "fileutil.h"
#include "file.h"

JToolBarUtil::JToolBarUtil(QObject *parent) :
  GuiUtilBase(parent)
{
}
/**
 * Common utility methods for working with JToolBars.
 * <P>
 * Chief among these is the loadToolBar method, for creating a JToolBar from an
 * XML definition
 * <p>
 * Only parses top level of XML file, since ToolBars have only level.
 *
 * @author Bob Jacobsen Copyright 2003, 2010
 * @version $Revision: 28746 $
 * @since 2.9.4
 */
///*public*/  class JToolBarUtil extends GuiUtilBase {

/*static*/ /*public*/  QToolBar* JToolBarUtil::loadToolBar(QString name)
{
 return loadToolBar(name, NULL, NULL);  // tool bar without window or context
}

/*static*/ /*public*/  QToolBar* JToolBarUtil::loadToolBar(QString name, WindowInterface* wi, QObject *context)
{
// File file(name);
// if(!file.isAbsolute())
//  name = FileUtil::getUserFilesPath() + name;

 QDomElement root = rootFromName(name);

 QToolBar* retval = new QToolBar(root.firstChildElement("name").text());

 QDomNodeList nodes = root.elementsByTagName("node");
 for(int i = 0; i < nodes.size(); i++)
 {
  Action* act = actionFromNode(nodes.at(i).toElement(), wi, context);
  if (act == NULL) {
      continue;
  }
  if (act->getValue(Action::SMALL_ICON) != QVariant())
  {
   // icon present, add explicitly
   //QPushButton* b = new QPushButton(VPtr<QIcon>::asPtr(act->getValue(Action::SMALL_ICON), ""));
   Action* b = new Action("", *VPtr<QIcon>::asPtr(act->getValue(Action::SMALL_ICON)), wi);
//      b->setAction(act);
   retval->addAction(b);
  }
  else
  {
   retval->addAction(act);
  }
 }
 return retval;

}
