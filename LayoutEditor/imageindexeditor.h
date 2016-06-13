#ifndef IMAGEINDEXEDITOR_H
#define IMAGEINDEXEDITOR_H
#include "jmrijframe.h"
#include "liblayouteditor_global.h"

class CatalogTreeItem;
class CatalogPanel;
class ShutDownTask;
class CatalogTreeNode;
class Editor;
class LIBLAYOUTEDITORSHARED_EXPORT ImageIndexEditor : public JmriJFrame
{
    Q_OBJECT
public:
    //explicit ImageIndexEditor(QWidget *parent = 0);
    /*public*/ static ImageIndexEditor* instance(Editor* editor);
    /*public*/ static /*final*/ /*synchronized*/ void indexChanged(bool changed);
    /*public*/ static bool isIndexChanged();
    /*public*/ static bool checkImageIndex();
    /*public*/ static /*final*/ QString IconDataFlavorMime;// = DataFlavor.javaJVMLocalObjectMimeType +

signals:

public slots:
    /*public*/ static void storeImageIndex();

private:
    CatalogPanel*    _catalog;
    CatalogPanel*    _index;
    static ImageIndexEditor* _instance;
    static bool  _indexChanged;// = false;
    static ShutDownTask* 	_shutDownTask;
    /*private*/ ImageIndexEditor(QString name = "", QWidget *parent = 0);
//    /*private*/ int countSubNodes(CatalogTreeNode* node) ;
    /*private*/ int countSubNodes(CatalogTreeItem* node);
//    /*private*/ int countIcons(CatalogTreeNode* node);
    /*private*/ int countIcons(CatalogTreeItem* node);
    /*private*/ void init(Editor* editor);
    /*private*/ QWidget* makeCatalogPanel();
    /*private*/ QWidget*  makeIndexPanel();
    Logger* log;
private slots:
    void addNode();
    void renameNode();
    void deleteNode();
    void openItem_triggered();
};

#endif // IMAGEINDEXEDITOR_H
