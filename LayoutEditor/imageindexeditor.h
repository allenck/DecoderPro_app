#ifndef IMAGEINDEXEDITOR_H
#define IMAGEINDEXEDITOR_H
#include "jmrijframe.h"
#include "liblayouteditor_global.h"
#include "abstractinstanceinitializer.h"

class CatalogTreeNode;
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
    /*public*/ QString getClassName();
  //@ServiceProvider(service = InstanceInitializer.class)
  /*public*/ /*static*/ class Initializer : public AbstractInstanceInitializer {

      //@Override
      //@Nonnull
      /*public*/ /*<T>*/ QObject* getDefault(QString type) const override{
          if (type == ("ImageIndexEditor")) {
           ImageIndexEditor* instance = new ImageIndexEditor(tr("Create/Edit Image Index"));
           instance->init(nullptr);
           return instance;          }
          return AbstractInstanceInitializer::getDefault(type);
      }

      //@Override
      //@Nonnull
      /*public*/ QSet</*Class<?>*/QString>* getInitalizes()override {
          QSet</*Class<?>*/QString>* set = AbstractInstanceInitializer::getInitalizes();
          set->insert("ImageIndexEditor");
          return set;
      }

  };
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
    /*private*/ int countSubNodes(CatalogTreeNode* node) ;
    /*private*/ int countIcons(CatalogTreeNode* node);
    /*private*/ void init(Editor* editor);
    /*private*/ QWidget* makeCatalogPanel();
    /*private*/ QWidget*  makeIndexPanel();
    Logger* log;
private slots:
    void addNode();
    void renameNode();
    void deleteNode();
    void openItem_triggered();
    friend class InstanceManager;
};
class IIEWindowListener : public WindowListener
{
 Q_OBJECT
 ImageIndexEditor* iie;
public:
 IIEWindowListener(ImageIndexEditor* iie);

public slots:
 /*public*/ void windowClosing(QCloseEvent*);

};
#endif // IMAGEINDEXEDITOR_H
