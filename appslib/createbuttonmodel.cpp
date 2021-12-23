#include "createbuttonmodel.h"
#include <QPushButton>
#include "apps.h"
#include "apps3.h"
#include <QBoxLayout>
#include "abstractaction.h"

CreateButtonModel::CreateButtonModel(QObject *parent) :
    AbstractActionModel(parent)
{
 setObjectName("CreateButtonModel");
}
/**
 * Creates a button
 * when the program is started.
 * <P>
 * The list of actions available is defined in the
 * {@link AbstractActionModel} superclass.
 * <P>
 * This is a separate class, even though it
 * has no additional behavior, so that persistance
 * systems realize the type of data being stored.
 * @author	Bob Jacobsen   Copyright 2003
 * @version     $Revision: 17977 $
 * @see CreateButtonPanel
 */
///*public*/ class CreateButtonModel extends AbstractActionModel {

///*public*/ CreateButtonModel() {
//    super();
//}

//@Override
/*protected*/ void CreateButtonModel::performAction(Action* action) /*throw (JmriException)*/
{
 this->action = action;
 b = new QPushButton(action->text());
 connect(b, SIGNAL(clicked()), action, SLOT(actionPerformed()));
 b->setToolTip(this->toString());
 if (Apps::buttonSpace() != NULL) {
     Apps::buttonSpace()->layout()->addWidget(b);
 } else if (Apps3::buttonSpace() != NULL) {
     Apps3::buttonSpace()->layout()->addWidget(b);
 }
 AbstractAction* act = (AbstractAction*)action;
 connect(act, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

}

void CreateButtonModel::propertyChange(PropertyChangeEvent* evt)
{
 if(evt->getPropertyName() == "Name")
 {
  b->setText(evt->getNewValue().toString());
  b->update();
 }
}
