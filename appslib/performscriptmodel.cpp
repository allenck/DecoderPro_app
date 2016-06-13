#include "performscriptmodel.h"

//PerformScriptModel::PerformScriptModel(QObject *parent) :
//  QObject(parent)
//{
//}
/**
 * A PerformScriptModel object runs a script when the program is started.
 * <P>
 * @author	Bob Jacobsen Copyright 2003
 * @version $Revision: 28746 $
 * @see PerformScriptPanel
 */
///*public*/ class PerformScriptModel {

/*public*/ PerformScriptModel::PerformScriptModel(QObject *parent) :
  QObject(parent)
{
 fileName = "";
}


/*public*/ QString  PerformScriptModel::getFileName() {
    return fileName;
}

/*public*/ void  PerformScriptModel::setFileName(QString n) {
    fileName = n;
}

/*static*/ /*public*/ void  PerformScriptModel::rememberObject(PerformScriptModel* m) {
    l.append(m);
}

/*static*/ /*public*/ QList<PerformScriptModel*>  PerformScriptModel::rememberedObjects() {
    return l;
}
/*static*/ QList<PerformScriptModel*>  PerformScriptModel::l =  QList<PerformScriptModel*>();
