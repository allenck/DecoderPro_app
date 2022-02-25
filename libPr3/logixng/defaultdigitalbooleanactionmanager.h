#ifndef DEFAULTDIGITALBOOLEANACTIONMANAGER_H
#define DEFAULTDIGITALBOOLEANACTIONMANAGER_H

#include "abstractbasemanager.h"
#include "category.h"
#include "digitalbooleanactionmanager.h"

class DefaultDigitalBooleanActionManager : public AbstractBaseManager, public DigitalBooleanActionManager
{
  Q_OBJECT
  Q_INTERFACES(DigitalBooleanActionManager)
 public:
  explicit DefaultDigitalBooleanActionManager(QObject *parent = nullptr);
  /*public*/  /*Class<? extends MaleSocket>*/QString getMaleSocketClass() override;
  /*public*/  MaleSocket* getLastRegisteredMaleSocket()override;
  /*public*/  MaleDigitalBooleanActionSocket* registerBean(/*MaleDigitalBooleanActionSocket*/NamedBean* maleSocket) override;
  /*public*/  MaleDigitalBooleanActionSocket* registerAction(/*@Nonnull*/ DigitalBooleanActionBean* action)
          /*throws IllegalArgumentException*/override;
  /*public*/  int getXMLOrder()  const override;
  /*public*/  QChar typeLetter() const override;
  /*public*/  FemaleDigitalBooleanActionSocket* createFemaleSocket(
          Base* parent, FemaleSocketListener* listener, QString socketName)override;
  /*public*/  QHash<Category *, QList<QString> > getActionClasses()override;
  /*public*/  QString getBeanTypeHandled(bool plural) const override;
  /*public*/  void deleteDigitalBooleanAction(MaleDigitalBooleanActionSocket* x)override;
  static /*public*/  DefaultDigitalBooleanActionManager* instance();
  /*public*/  /*Class<MaleDigitalBooleanActionSocket>*/QString getNamedBeanClass() const override;
 private:
  static Logger* log;
  /*private*/ /*final*/ QHash<Category*, QList</*Class<? extends Base>*/QString>> actionClassList = QHash<Category*, QList</*Class<? extends Base>*/QString>>();
  /*private*/ MaleSocket* _lastRegisteredBean;
  static /*volatile*/ DefaultDigitalBooleanActionManager* _instance;// = nullptr;

  QObject* vself() override {return (QObject*)this;}
  QObject* pself() override {return (QObject*)this;}

 protected:
  /*protected*/ MaleDigitalBooleanActionSocket* castBean(MaleSocket* maleSocket)override;
  /*protected*/ MaleDigitalBooleanActionSocket* createMaleActionSocket(DigitalBooleanActionBean* action);

};

#endif // DEFAULTDIGITALBOOLEANACTIONMANAGER_H
