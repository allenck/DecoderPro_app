#include "dualdecodertoolaction.h"
#include "instancemanager.h"
#include "dualdecoderselectframe.h"

//DualDecoderToolAction::DualDecoderToolAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Swing action to create and register a DualDecoderTool
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @version $Revision: 29735 $
 */
// /*public*/ class DualDecoderToolAction extends JmriAbstractAction {

/*public*/ DualDecoderToolAction::DualDecoderToolAction(QString s, WindowInterface* wi)
 : JmriAbstractAction(s, (QObject*)wi)
{
 //super(s, wi);
 common();
}

/*public*/ DualDecoderToolAction::DualDecoderToolAction(QString s, QIcon i, WindowInterface* wi)
 : JmriAbstractAction(s, i, wi)
{
 //super(s, i, wi);
 common();
}

/*public*/ DualDecoderToolAction::DualDecoderToolAction(QString s,QObject *parent) :
    JmriAbstractAction(s, parent)
{
 // super(s);
 common();
}
void DualDecoderToolAction::common()
{
 // disable ourself if programming is not possible
 bool enabled = false;
 if ((InstanceManager::getList("GlobalProgrammerManager") != NULL)
     && (InstanceManager::getList("GlobalProgrammerManager")->size() > 0))
 {
     enabled = true;
 }
 if ((InstanceManager::getList("AddressedProgrammerManager") != NULL)
     && (InstanceManager::getList("AddressedProgrammerManager")->size() > 0))
 {
     enabled = true;
 }

 setEnabled(enabled);
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ DualDecoderToolAction::DualDecoderToolAction(QObject* parent)
 : JmriAbstractAction(tr("Multi-Decoder Control"), parent)
{
 //this(tr("MenuItemMultiDecoderControl"));
 common();
}

/*public*/ void DualDecoderToolAction::actionPerformed(ActionEvent* /*e*/)
{
 (new DualDecoderSelectFrame())->setVisible(true);
}
