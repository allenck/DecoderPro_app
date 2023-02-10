#ifndef DEFAULTMODULEMANAGER_H
#define DEFAULTMODULEMANAGER_H

#include <abstractmanager.h>
#include "femalesocketmanager.h"
#include "modulemanager.h"
#include "defaultmodule.h"

class DefaultModuleManager : public AbstractManager, public ModuleManager
{
  Q_OBJECT
  Q_INTERFACES(ModuleManager)
 public:
  explicit DefaultModuleManager(QObject *parent = nullptr);
  /*public*/  int getXMLOrder() const override;
  /*public*/  QChar typeLetter()const override;
  /*public*/  NameValidity validSystemNameFormat(QString systemName)override;
  /*public*/  Module* createModule(QString systemName, QString userName,
          FemaleSocketManager::SocketType* socketType)
          /*throws IllegalArgumentException*/override;
  /*public*/  NamedBean *createModule(QString userName, FemaleSocketManager::SocketType* socketType)override;
  /*public*/  Module* getModule(QString name) override;
  /*public*/  DefaultModule *getByUserName(QString name)override;
  /*public*/  Module* getBySystemName(QString name) override;
  /*public*/  QString getBeanTypeHandled(bool plural) const override;
  /*public*/  bool resolveAllTrees(QList<QString> *errors)override;
  /*public*/  void setupAllModules()override;
  /*public*/  void deleteModule(Module* x) override;
  /*public*/  void printTree(
          Base::PrintTreeSettings* settings,
          PrintWriter* writer,
          QString indent,
          /*MutableInt*/int* lineNumber) override;
  /*public*/  void printTree(
          Base::PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString indent,
          /*MutableInt*/int* lineNumber)override;
  static /*public*/  DefaultModuleManager* instance();
  /*public*/  /*Class<Module>*/QString getNamedBeanClass() const override;
  /*public*/  void fireVetoableChange(QString p, QVariant old) /*throws PropertyVetoException*/;
  /*public*/  /*final*/ void deleteBean(/*@Nonnull*/ /*Module**/NamedBean* module, /*@Nonnull*/ QString property) /*throws PropertyVetoException*/override;

  QObject* self() override {return (QObject*)this;}
  QObject* vself() override {return (QObject*)this;}
  QObject* pself() override {return (QObject*)this;}

 private:
  static /*volatile*/ DefaultModuleManager* _instance;// = nullptr;
  static Logger* log;
};

#endif // DEFAULTMODULEMANAGER_H
