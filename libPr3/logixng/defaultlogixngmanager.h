#ifndef DEFAULTLOGIXNGMANAGER_H
#define DEFAULTLOGIXNGMANAGER_H
#include "abstractmanager.h"
#include <QClipboard>
#include "logixng_manager.h"
#include "defaultclipboard.h"

class LogixNG;
class LogixNGPreferences;
class Logger;
class DefaultLogixNGManager : public AbstractManager, public LogixNG_Manager
{
  Q_OBJECT
  Q_INTERFACES(LogixNG_Manager)
 public:
  DefaultLogixNGManager(QObject* parent =nullptr);
  /*public*/ int getXMLOrder() const override;
  /*public*/ QChar typeLetter()  override;
  /*public*/ LogixNG* createLogixNG(QString systemName, QString userName) throw (IllegalArgumentException) override;
  /*public*/ LogixNG* createLogixNG(QString userName) throw (IllegalArgumentException) override;
  /*public*/ LogixNG* getLogixNG(QString name) override;
  /*public*/ LogixNG* getByUserName(QString name) override;
  /*public*/ LogixNG* getBySystemName(QString name)  override;
  /*public*/ QString getBeanTypeHandled(bool plural) const override;
  /*public*/ void setupAllLogixNGs() override;
  /*public*/ void activateAllLogixNGs()override;
  /*public*/ void activateAllLogixNGs(bool runDelayed, bool runOnSeparateThread)override;
  /*public*/ void deActivateAllLogixNGs() override;
  /*public*/ bool isActive()override;
  /*public*/ void deleteLogixNG(LogixNG* x)override;
  /*public*/ void setLoadDisabled(bool s)override;
  /*public*/ void printTree(
          PrintTreeSettings* settings,
          PrintWriter* writer,
          QString indent,
          /*MutableInt*/int lineNumber) override;
  /*public*/ void printTree(
          PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString indent,
          /*MutableInt*/int lineNumber)override;
  static /*public*/ DefaultLogixNGManager* instance();
  /*public*/ QString getNamedBeanClass()const override;
  /*public*/ Clipboard* getClipboard()override;
  /*public*/ void registerManager(Manager/*<? extends MaleSocket>*/* manager)override;
  /*public*/ Manager/*<? extends MaleSocket>*/* getManager(QString className)override;
  /*public*/ void fireVetoableChange(QString p, QVariant old) throw (PropertyVetoException);
  /*public*/ /*final*/ void deleteBean(/*@Nonnull*/  /*LogixNG*/NamedBean* logixNG, /*@Nonnull*/  QString property) throw (PropertyVetoException)override;
  //Register(NamedBean *s) const override();

 private:
  static Logger* log;
  /*private*/ /*final*/ QMap<QString, Manager/*<? extends MaleSocket>*/*> _managers = QMap<QString, Manager*>();
  /*private*/ /*final*/ Clipboard* _clipboard = new DefaultClipboard();
  /*private*/ bool _isActive = false;
  static /*volatile*/ DefaultLogixNGManager* _instance;// = null;
  /*private*/ void checkItemsHaveParents();
  /*private*/ void messageDialog(QString titleKey, QList<QString> messages, QString helpKey);
  /*private*/ void checkItemsHaveParents(QSet</*? extends*/ MaleSocket*> set, QList<MaleSocket*> beansWithoutParentList);

};

#endif // DEFAULTLOGIXNGMANAGER_H
