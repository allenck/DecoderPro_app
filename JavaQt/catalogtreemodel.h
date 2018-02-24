#ifndef CATALOGTREEMODEL_H
#define CATALOGTREEMODEL_H

#include "defaulttreemodel.h"
#include <QStringList>
#include <QDir>
#include "logger.h"
#include "defaultmutabletreenode.h"

class CatalogTreeModel : public DefaultTreeModel
{
    Q_OBJECT
public:
 /*public*/ CatalogTreeModel(QObject* parent = 0);
 //QT_DEPRECATED static /*public*/ CatalogTreeModel* instance();
 static /*final*/ QString resourceRoot;// = "resources";
 static /*final*/ QString fileRoot;// = FileUtil::getUserFilesPath() + "resources";


signals:
public slots:
private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("CatalogTreeModel");
 void insertResourceNodes(QString pName, QString pPath, DefaultMutableTreeNode* pParent);
 DefaultMutableTreeNode* dRoot;
 void insertFileNodes(QString name, QString path, DefaultMutableTreeNode* parent);

};

#endif // CATALOGTREEMODEL_H
