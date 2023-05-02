#ifndef JINPUTVALIDATOR_H
#define JINPUTVALIDATOR_H

#include "inputverifier.h"
#include "validation.h"
#include "swingpropertychangesupport.h"
#include "jinputvalidatorpreferences.h"
#include "border.h"
#include "jcomponent.h"

class JInputValidator : public InputVerifier
{
    Q_OBJECT
 public:
  JInputValidator(JComponent* component);
  /*public*/ JInputValidator(/*@Nonnull*/ JComponent* jc, bool bln, bool bln1);
  /*public*/ JInputValidator(/*@Nonnull*/ JComponent* jc, bool bln, bool bln1, /*@Nonnull*/ JInputValidatorPreferences *jivp);
  /*public*/ QString getToolTipText();
  /*public*/ /*final*/ Validation* getNoneValidation();
  /*public*/ bool verify(JComponent* jc)override;
  /*public*/ void addPropertyChangeListener(PropertyChangeListener* listener);
  /*public*/ void addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener);
  /*public*/ void removePropertyChangeListener(PropertyChangeListener* listener);
  /*public*/ void removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener);
  /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListeners();
  /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListeners(QString propertyName);
  /*public*/ /*final*/ Validation* getValidation();

 private:
  void common(JComponent* component, bool onInput, bool isVerifying, /*@Nonnull*/ JInputValidatorPreferences* preferences);
  /*private*/ /*final*/ Border* originalBorder = nullptr;
  /*private*/ QString originalToolTipText = "";
  /*private*/ /*final*/ SwingPropertyChangeSupport* pcs = new SwingPropertyChangeSupport(this, nullptr);
  /*private*/ Validation* validation = nullptr;
  /*private*/ Validation* oldValidation = nullptr;
  /*private*/ /*final*/ JInputValidatorPreferences* preferences = nullptr;
  /*private*/ /*final*/ JComponent* component = nullptr;
  /*private*/ bool inVerifyMethod;
  /*private*/ bool isVerifying;

 protected:
  /*protected*/ /*final*/ QString trimHtmlTags(/*@Nullable */QString string);
  /*protected*/ SwingPropertyChangeSupport* getSwingPropertyChangeSupport();
  /*protected*/ JComponent* getComponent();
  virtual /*protected*/ /*abstract*/ Validation* getValidation(JComponent* input, JInputValidatorPreferences* preferences) =0;

};

#endif // JINPUTVALIDATOR_H
