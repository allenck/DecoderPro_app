#ifndef SYSTEMNAMEVALIDATOR_H
#define SYSTEMNAMEVALIDATOR_H

#include "jinputvalidator.h"
#include "abstractborder.h"

class JInputValidatorPreferences;
class Validation;
class Manager;
class SystemNameValidator : public JInputValidator
{
 Q_OBJECT
public:
 explicit SystemNameValidator(QObject *parent = nullptr);
 /*public*/ SystemNameValidator(/*@Nonnull*/ JComponent* component, /*@Nonnull*/ Manager* manager, bool required = false);
 /*public*/ bool isRequired();
 /*public*/ void setRequired(bool required);
 /*public*/ void setManager(/*@Nonnull*/ Manager* manager);
 /*public*/ Validation* getValidation();

signals:

public slots:

private:
 /*private*/ Manager* manager;
 /*private*/ bool required = false;
  QValidator::State validate(QString& input, int &pos) const override;

 protected:
  /*protected*/ Validation* getValidation(JComponent* component, JInputValidatorPreferences *preferences)override;

};

#endif // SYSTEMNAMEVALIDATOR_H
