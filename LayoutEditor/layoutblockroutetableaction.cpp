#include "layoutblockroutetableaction.h"
#include "jmrijframe.h"
#include "layoutblockroutetable.h"
#include "layoutblock.h"

//LayoutBlockRouteTableAction::LayoutBlockRouteTableAction(QObject *parent) :
//    QObject(parent)
//{
//}
/**
     * Swing action to create and register a Block Routing Table.
     * <P>
     * @author	Kevin Dickerson   Copyright (C) 2011
     * @version	$Revision: 17977 $
     */

// /*public*/ class LayoutBlockRouteTableAction extends AbstractAction {

    /**
     * Create an action with a specific title.
     * <P>
     * Note that the argument is the Action title, not the title of the
     * resulting frame.  Perhaps this should be changed?
     * @param s
     */

/*public*/ LayoutBlockRouteTableAction::LayoutBlockRouteTableAction(QString s, LayoutBlock* lBlock, QObject *parent) :
    AbstractAction(s, parent)
{
 //super(s);
 this->s = s;
 this->lBlock = lBlock;
}

//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor.LayoutEditorBundle");

void LayoutBlockRouteTableAction::createModel()
{
 m = new LayoutBlockRouteTable(false, lBlock);
}

/*public*/ void LayoutBlockRouteTableAction::actionPerformed(JActionEvent * /*e*/)
{
 // create the JTable model, with changes for specific NamedBean
 createModel();

 // create the frame
 f = new JmriJFrameX("LayoutBlockRoute");
 //f->add(m);
 f->setCentralWidget(m);
 setTitle();
 //f.pack();
 f->setVisible(true);
 }


///*public*/ void LayoutBlockRouteTableAction::actionPerformed(ActionEvent* /*e*/) {
//    actionPerformed();
//}

void LayoutBlockRouteTableAction::setTitle() {
if (lBlock!=NULL)
    f->setTitle(tr("Routing Table for Block") + " " + lBlock->getDisplayName());
else
    f->setTitle(tr("Block Routing Table"));
}

QString LayoutBlockRouteTableAction::helpTarget() {
return "package.jmri.jmrit.display.layoutEditor";
}
