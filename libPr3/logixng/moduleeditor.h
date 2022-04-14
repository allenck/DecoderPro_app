#ifndef MODULEEDITOR_H
#define MODULEEDITOR_H

#include "treeeditor.h"
#include "abstractlogixngeditor.h"
#include "beantableframe.h"
#include "beantabledatamodel.h"
#include "moduleeditormalesocket.h"
#include "femalesocketlistener.h"
class Module;
class ModuleEditor : public TreeEditor, public AbstractLogixNGEditor
{
  Q_OBJECT
  Q_INTERFACES(AbstractLogixNGEditor)
 public:
  ModuleEditor(BeanTableFrame/*<Module>*/* f,
                            BeanTableDataModel/*<Module>*/* m, QString sName, QWidget *parent = nullptr);
  /*public*/  void windowClosed(QCloseEvent* e);
  /*public*/  void addEditorEventListener(EditorEventListener* listener) override;
  /*public*/  void removeEditorEventListener(EditorEventListener* listener)override;
  /*public*/  void bringToFront()override;

 private:
  BeanTableDataModel/*<Module>*/* beanTableDataModel;
  /**
   * Maintain a list of listeners -- normally only one.
   */
  /*private*/ /*final*/ QList<EditorEventListener*> listenerList = QList<EditorEventListener*>();
  /*private*/ static FemaleSocket* setupRootSocket(Base* parent, QString sName);

  /**
   * This contains a list of commands to be processed by the listener
   * recipient.
   */
  /*final*/ QMap<QString, QString> moduleData = QMap<QString, QString>();

  void fireModuleEvent();
  /*private*/ /*static*/ class RootSocket : public AbstractFemaleSocket {

   public:
      /*public*/  RootSocket(Base* parent, FemaleSocketListener* listener, QString name) : AbstractFemaleSocket(parent, listener, name) {
          //super(parent, listener, name);
      }

      //@Override
      /*public*/  bool canDisconnect() {
          return false;
      }

      //@Override
      /*public*/  void disposeMe() {
          throw new UnsupportedOperationException("Not supported");
      }

      //@Override
      /*public*/  bool isCompatible(MaleSocket* socket) {
          return qobject_cast<ModuleEditorMaleSocket*>(socket->bself());
      }

      //@Override
      /*public*/  QHash<Category*, QList</*Class<? extends Base>*/QString>> getConnectableClasses() {
//            Map<Category, List<Class<? extends Base>>> map = new HashMap<>();
//            List<Class<? extends Base>> list = new ArrayList<>();
//            map.put(Category.OTHER, list);
//            list.add(Module.class);
//            return map;
          throw new UnsupportedOperationException("Not supported");
      }

      //@Override
      /*public*/  QString getShortDescription(QLocale locale) {
          return tr(/*locale,*/ "-");
      }

      //@Override
      /*public*/  QString getLongDescription(QLocale locale) {
          return tr(/*locale,*/ "- %1").arg(getName());
      }
    QObject* bself() override {return (QObject*)this;}
    QString getClassName() {return "RootSocket";}
  };
 protected:
  /*protected*/ /*final*/ Module* _module = nullptr;
  /*protected*/ void executeEvaluate(SwingConfiguratorInterface* swi, MaleSocket* maleSocket);

};

class FemaleSocketListener13 : public FemaleSocketListener
{
 public:
  //@Override
  /*public*/  void connected(FemaleSocket* socket) override{
      // Do nothing
  }

  //@Override
  /*public*/  void disconnected(FemaleSocket* socket) override{
      // Do nothing
  }

};

#endif // MODULEEDITOR_H
