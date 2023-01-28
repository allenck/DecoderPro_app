#ifndef DIGITALCALLMODULESWING_H
#define DIGITALCALLMODULESWING_H

#include "../abstractdigitalactionswing.h"
#include "../module.h"
class JComboBox;
class CallModuleParameterTableModel;
namespace Actions
{
 class DigitalCallModuleSwing : public AbstractDigitalActionSwing
 {
   Q_OBJECT
  public:
   Q_INVOKABLE DigitalCallModuleSwing(QObject* parent = nullptr);
   ~DigitalCallModuleSwing() {}
   DigitalCallModuleSwing(const DigitalCallModuleSwing&) {}
   /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
   /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName,/* @CheckForNull*/ QString userName)override;
   /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
   /*public*/  QString toString()override;
   /*public*/  void dispose()override;


    QObject* sself() override {return this;}
  private:
   /*private*/ JComboBox/*<ModuleItem>*/* _moduleComboBox;
   /*private*/ CallModuleParameterTableModel* _moduleParametersTableModel;
    /*private*/ /*static*/ class ModuleItem {

        /*private*/ /*final*/ Module* _module;
     public:
        /*public*/  ModuleItem(Module* m) {
            _module = m;
        }

        //@Override
        /*public*/  QString toString() {
            if (_module == nullptr) return "";
            else return _module->getDisplayName();
        }
      friend class DigitalCallModuleSwing;
    };

  protected:
   /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;

 };
}
Q_DECLARE_METATYPE(Actions::DigitalCallModuleSwing)
#endif // DIGITALCALLMODULESWING_H
