#include "oblocktableaction.h"
#include "tableframes.h"

//OBlockTableAction::OBlockTableAction(QObject *parent) :
//  AbstractAction(parent)
//{
//}
/**
 * GUI to define OBlocks, OPaths and Portals
 * <P>
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
 * @author	Pete Cressman (C) 2009, 2010
 * @version $Revision: 28746 $
 */
///*public*/ class OBlockTableAction extends AbstractAction {

/**
 *
 */
///*private*/ static final long serialVersionUID = 6331453045183182013L;

/*public*/ OBlockTableAction::OBlockTableAction(QObject *parent) :
AbstractAction(tr("OBlock Table"),parent) {
    //this("OBlock Table");
 common();
}

/*public*/ OBlockTableAction::OBlockTableAction(QString actionName, QObject *parent) :
AbstractAction(actionName, parent){
    //super(actionName);
 common();
}

void OBlockTableAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void OBlockTableAction::actionPerformed(ActionEvent* e)
{
 TableFrames* f = new TableFrames();
 f->initComponents();
}
//}
