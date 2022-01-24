#include "jinputvalidator.h"
#include "jtextarea.h"
#include "jcomponent.h"
#include "validatorborder.h"

/*public*/ JInputValidator::JInputValidator(/*@Nonnull*/ JComponent *component) {
 common(component, true, true, nullptr);
}

void JInputValidator::common(JComponent* component, bool /*onInput*/, bool isVerifying, /*@Nonnull*/ JInputValidatorPreferences *preferences)
{
 this->component = component;
 originalBorder = this->component->getBorder();
 originalToolTipText = ((QWidget*)this->component->jself())->toolTip();
// if (onInput && qobject_cast<JTextArea*>(this->component->jself())) {
//     addChangeListener((/*JTextComponent*/JTextArea*) this->component, e -> verify(this->component));
// }
 this->preferences = preferences;
 this->isVerifying = isVerifying;
 validation = getNoneValidation();
 oldValidation = getNoneValidation();
}

/*public*/ JInputValidator::JInputValidator(/*@Nonnull*/ JComponent* jc, bool bln, bool bln1) {
 common(jc, bln, bln1, new JInputValidatorPreferences());
}

/*public*/ JInputValidator::JInputValidator(/*@Nonnull*/ JComponent* jc, bool bln, bool bln1, /*@Nonnull*/ JInputValidatorPreferences* jivp) {
 common(jc, bln, bln1, jivp);
}

/*protected*/ /*final*/ QString JInputValidator::trimHtmlTags(/*@Nullable */QString input) {
 QString output = !input.isNull() ? input.trimmed() : "";
         if (output.startsWith("<html>")) {
             output = output.mid(6);
         }
         if (output.endsWith("</html>")) {
             output = output.mid(0, output.length() - 7);
         }
         return output.trimmed();}

/*public*/ QString JInputValidator::getToolTipText() {
 return originalToolTipText;
}
/**
 * Get the current validation. This property can be listened to using the
 * property name {@code validation}.
 *
 * @return the current validation
 */
//@Nonnull
/*public*/ /*final*/ Validation* JInputValidator::getValidation() {
    return validation;
}

/**
 * Get the validation object for the current state of the input component.
 *
 * @param input       the component to get the state of
 * @param preferences preferences to use for creating the validation
 * @return the validation for the current state
 */
// /*protected*/ /*abstract*/ Validation getValidation(JComponent input, JInputValidatorPreferences preferences);


/*public*/ /*final*/ Validation* JInputValidator::getNoneValidation() {
 return new Validation(Validation::Type::NONE, getToolTipText(), preferences);    }

/*public*/ void JInputValidator::addPropertyChangeListener(PropertyChangeListener* listener) {
    pcs->SwingPropertyChangeSupport::addPropertyChangeListener(listener);
}

/*public*/ void JInputValidator::addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
    pcs->SwingPropertyChangeSupport::addPropertyChangeListener(propertyName, listener);
}

/*public*/ void JInputValidator::removePropertyChangeListener(PropertyChangeListener* listener) {
    pcs->removePropertyChangeListener(listener);
}

/*public*/ void JInputValidator::removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
    pcs->removePropertyChangeListener(propertyName, listener);
}

/*public*/ QVector<PropertyChangeListener*> JInputValidator::getPropertyChangeListeners() {
    return pcs->getPropertyChangeListeners();
}

/*public*/ QVector<PropertyChangeListener*> JInputValidator::getPropertyChangeListeners(QString propertyName) {
    return pcs->getPropertyChangeListeners(propertyName);
}

/*protected*/ SwingPropertyChangeSupport* JInputValidator::getSwingPropertyChangeSupport() {
return pcs;
}

/*public*/ bool JInputValidator::verify(JComponent *input) {
 oldValidation = validation;
 validation = getValidation(input, preferences);
 if (validation != (oldValidation) && !inVerifyMethod) {
     inVerifyMethod = true;
     if (validation->getType() == Validation::Type::NONE) {
         input->setBorder(originalBorder);
         ((QWidget*)input->jself())->setToolTip(originalToolTipText);
     } else {
         input->setBorder(new ValidatorBorder(validation, originalBorder));
         ((QWidget*)input->jself())->setToolTip(validation->getMessage());
     }
     //input->validate(); //??
     ((QWidget*)input->jself())->update();
     pcs->firePropertyChange("validation", oldValidation, validation);
     inVerifyMethod = false;
 }
 return isVerifying
         ? validation->getType() == Validation::Type::WARNING || validation->getType() == Validation::Type::DANGER
         : isVerifying;
}

/*protected*/ JComponent* JInputValidator::getComponent() {
 return  component;
}
