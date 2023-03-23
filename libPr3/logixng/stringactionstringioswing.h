#ifndef STRINGACTIONSTRINGIOSWING_H
#define STRINGACTIONSTRINGIOSWING_H

#include "abstractstringactionswing.h"

class BeanSelectPanel;
class StringActionStringIOSwing : public AbstractStringActionSwing
{
public:
    Q_INVOKABLE explicit StringActionStringIOSwing(QObject *parent = nullptr);
    ~StringActionStringIOSwing() {}
    StringActionStringIOSwing(const StringActionStringIOSwing&) : AbstractStringActionSwing() {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object) override;
    /*public*/ QString toString() override;
    /*public*/ void dispose() override;

    QObject* sself() override{return this;}

   private:
    /*private*/ BeanSelectPanel/*<StringIO>*/* _stringIOBeanPanel;

protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;

};
Q_DECLARE_METATYPE(StringActionStringIOSwing)
#endif // STRINGACTIONSTRINGIOSWING_H
