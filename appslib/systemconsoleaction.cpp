#include "systemconsoleaction.h"
#include "systemconsole.h"
#include "windowinterface.h"
#include "jmrijframe.h"

//SystemConsoleAction::SystemConsoleAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Swing action to display the JMRI System Console
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author Matthew Harris copyright (c) 2010
 * @version $Revision: 28746 $
 */
///*public*/  class SystemConsoleAction extends jmri.util.swing.JmriAbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -5843920804488337948L;

/*public*/  SystemConsoleAction::SystemConsoleAction(QString s, WindowInterface* wi)
 : QAction(s, (QObject*)wi)
{
    //super(s, wi);
 common();
}

/*public*/  SystemConsoleAction::SystemConsoleAction(QString s, QIcon i, WindowInterface* wi)
 : QAction(i, s, (QObject*)wi){
    //super(s, i, wi);
    common();
}

/*public*/  SystemConsoleAction::SystemConsoleAction(QObject *parent) :
  QAction(tr("JMRI System console"), parent){
    //super(tr("TitleConsole"));
 common();
}
void SystemConsoleAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

//@Override
/*public*/  void SystemConsoleAction::actionPerformed(ActionEvent* /*e*/) {
    // Show system console
    SystemConsole::getConsole()->setVisible(true);
}

//// never invoked, because we overrode actionPerformed above
////@Override
///*public*/  JmriPanel makePanel() {
//    throw new IllegalArgumentException("Should not be invoked"); // NOI18N
//}
