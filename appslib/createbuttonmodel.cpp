#include "createbuttonmodel.h"


CreateButtonModel::CreateButtonModel(QObject *parent) :
    AbstractActionModel(parent)
{
 setObjectName("CreateButtonModel");
 //l = QList<CreateButtonModel*>();
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

/*static*/ /*public*/ void CreateButtonModel::rememberObject(CreateButtonModel* m) {
    l.append(m);
}
/*static*/ /*public*/ QList<CreateButtonModel*> CreateButtonModel::rememberedObjects() {
    return l;
}
/*static*/ QList<CreateButtonModel*> CreateButtonModel::l = QList<CreateButtonModel*>();
