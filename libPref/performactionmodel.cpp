#include "performactionmodel.h"

PerformActionModel::PerformActionModel(QObject *parent) :
    AbstractActionModel(parent)
{
 setObjectName("PerformActionModel");
 l = QList<PerformActionModel*>();
}
/**
 * Invokes a Swing Action
 * when the program is started.
 * <P>
 * The list of actions available is defined in the
 * {@link AbstractActionModel} superclass.
 * <P>
 * This is a separate class, even though it
 * has no additional behavior, so that persistance
 * systems realize the type of data being stored.
 *
 * @author	Bob Jacobsen   Copyright 2003
 * @version     $Revision: 17977 $
 * @see PerformActionPanel
 */
// /*public*/ class PerformActionModel : public  AbstractActionModel {

///*public*/ PerformActionModel() {
//    super();
//}
/*static*/ /*public*/ void PerformActionModel::rememberObject(PerformActionModel* m) {
    l.append(m);
}
/*static*/ /*public*/ QList<PerformActionModel*> PerformActionModel::rememberedObjects() {
    return l;
}
/*static*/ QList<PerformActionModel*> PerformActionModel::l =  QList<PerformActionModel*>();
