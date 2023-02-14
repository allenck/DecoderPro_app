#ifndef DEFAULTLOGIXNGMANAGER_H
#define DEFAULTLOGIXNGMANAGER_H
#include "abstractmanager.h"
#include <QClipboard>
#include "logixng_manager.h"
#include "defaultclipboard.h"
#include "runnable.h"

class LogixNG;
class LogixNGPreferences;
class Logger;
class DefaultLogixNGManager : public AbstractManager, public LogixNG_Manager
{
  Q_OBJECT
  Q_INTERFACES(LogixNG_Manager)
 public:
  DefaultLogixNGManager(QObject* parent =nullptr);
  ~DefaultLogixNGManager() {}
  DefaultLogixNGManager(const DefaultLogixNGManager&) : AbstractManager() {}
  /*public*/ int getXMLOrder() const override;
  /*public*/ QChar typeLetter() const override;
  /*public*/ Manager::NameValidity validSystemNameFormat(QString systemName)  override;
  /*public*/ LogixNG* createLogixNG(QString systemName, QString userName) /*throw (IllegalArgumentException)*/ override;
  /*public*/ LogixNG* createLogixNG(QString userName) /*throw (IllegalArgumentException)*/ override;
  /*public*/ LogixNG* getLogixNG(QString name) override;
  /*public*/ NamedBean* getByUserName(QString name) override;
  /*public*/ NamedBean* getBySystemName(QString name)  override;
  /*public*/ QString getBeanTypeHandled(bool plural=false) const override;
  /*public*/ void setupAllLogixNGs() override;
  /*public*/ void activateAllLogixNGs()override;
  /*public*/ void activateAllLogixNGs(bool runDelayed, bool runOnSeparateThread)override;
  /*public*/ void deActivateAllLogixNGs() override;
  /*public*/ bool isActive()override;
  /*public*/ void deleteLogixNG(LogixNG* x)override;
  /*public*/ void setLoadDisabled(bool s)override;
  /*public*/ void printTree(
          Base::PrintTreeSettings* settings,
          PrintWriter* writer,
          QString indent,
          /*MutableInt*/int* lineNumber)override;
  /*public*/ void printTree(Base::PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString indent,
          /*MutableInt*/int *lineNumber)override;
  static /*public*/ DefaultLogixNGManager* instance();
  /*public*/ QString getNamedBeanClass()const override;
  /*public*/ DefaultClipboard* getClipboard()override;
  /*public*/ void registerManager(Manager/*<? extends MaleSocket>*/* manager)override;
  /*public*/ Manager/*<? extends MaleSocket>*/* getManager(QString className)override;
  /*public*/ void fireVetoableChange(QString p, QVariant old) /*throw (PropertyVetoException)*/ ;
  /*public*/ /*final*/ void deleteBean(/*@Nonnull*/  /*LogixNG*/NamedBean* logixNG, /*@Nonnull*/  QString property) /*throw (PropertyVetoException)*/override;
  //Register(NamedBean *s) const override();

  QObject* self() override {return (QObject*)this;}
  QObject* vself() override {return (QObject*)this;}
  QObject* pself() override {return (QObject*)this;}
  QObject* mself() override {return (QObject*)this;}
  QSet<NamedBean*> getNamedBeanSet() override {return AbstractManager::getNamedBeanSet();}

  /*public*/ QString getSubSystemNamePrefix() const override {return  AbstractManager::getSystemPrefix()+ typeLetter();}
 private:
  static Logger* log;
  /*private*/ /*final*/ QMap<QString, Manager/*<? extends MaleSocket>*/*> _managers = QMap<QString, Manager*>();
  /*private*/ /*final*/ DefaultClipboard* _clipboard= new DefaultClipboard();
  /*private*/ bool _isActive = false;
  static /*volatile*/ DefaultLogixNGManager* _instance;// = null;
  /*private*/ void checkItemsHaveParents();
  /*private*/ void messageDialog(QString titleKey, QList<QString> *messages, QString helpKey);
  /*private*/ void checkItemsHaveParents(QSet</*? extends*/ MaleSocket*> set, QList<MaleSocket*> beansWithoutParentList);

  friend class DLMRunnable;
};
Q_DECLARE_METATYPE(DefaultLogixNGManager)

class DLMRunnable : public Runnable
{
  Q_OBJECT
  DefaultLogixNGManager* dlm;
 public:
  DLMRunnable(DefaultLogixNGManager* dlm) {this->dlm = dlm;}
 public slots:
  void run() override ;
};

#endif // DEFAULTLOGIXNGMANAGER_H
