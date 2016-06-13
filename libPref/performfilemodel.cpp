#include "performfilemodel.h"

//PerformFileModel::PerformFileModel(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * A PerformFileModel object loads an xml file
 * when the program is started.
 * <P>
 * @author	Bob Jacobsen   Copyright 2003
 * @version     $Revision: 17977 $
 * @see PerformFilePanel
 */
// /*public*/ class PerformFileModel {

/*public*/ PerformFileModel::PerformFileModel(QObject *parent) :
    QObject(parent)
{
    fileName="";
}

/*public*/ QString PerformFileModel::getFileName() {
    return fileName;
}

/*public*/ void PerformFileModel::setFileName(QString n) {
    fileName = n;
}

/*static*/ /*public*/ void PerformFileModel::rememberObject(PerformFileModel* m) {
    l.append(m);
}
/*static*/ /*public*/ QList<PerformFileModel*> PerformFileModel::rememberedObjects() {
    return l;
}
/*static*/ QList<PerformFileModel*> PerformFileModel::l =  QList<PerformFileModel*>();
