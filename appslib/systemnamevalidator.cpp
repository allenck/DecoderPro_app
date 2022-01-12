#include "systemnamevalidator.h"
#include "manager.h"
#include "validation.h"
#include "jinputvalidatorpreferences.h"
#include "jtextfield.h"
#include "abstractproxymanager.h"
#include "namedbean.h"
#include "vptr.h"

SystemNameValidator::SystemNameValidator(QObject *parent) : JInputValidator(nullptr)
{

}
/**
 * A {@link com.alexandriasoftware.swing.JInputValidator} that validates a
 * {@link jmri.NamedBean} system name.
 * <p>
 * Until the component gets focus, no validation icon is shown. Once the
 * component has focus the following icons are shown:
 * <ul>
 * <li>If the component is blank and required was false when the validator was
 * created, no validation is shown.</li>
 * <li>If the component is blank and required was true when the validator was
 * created, a warning icon is shown.</li>
 * <li>If the component has an invalid system name, an error icon is shown.</li>
 * <li>If the component has a potentially valid system name, a waring icon is
 * shown.</li>
 * <li>If the component has a valid system name, a success icon is shown.</li>
 * </ul>
 *
 * @author Randall Wood Copyright 2019
 */
// /*public*/ class SystemNameValidator extends JInputValidator {


    /**
     * Create a SystemNameValidator. Same as calling
     * {@link #SystemNameValidator(javax.swing.JComponent, jmri.Manager, boolean)}
     * with {@code required == false}.
     *
     * @param component the component to validate has a valid system name
     * @param manager   the manager that will be used for validation
     */
//    /*public*/ SystemNameValidator(/*@Nonnull*/ /*JComponent*/QWidget* component, /*@Nonnull*/ Manager* manager) {
//        this(component, manager, false);
//    }

    /**
     * Create a SystemNameValidator.
     *
     * @param component the component to validate has a valid system name
     * @param manager   the manager that will be used for validation
     * @param required  true if input must be valid and
     *                  {@link javax.swing.InputVerifier#verify(javax.swing.JComponent)}
     *                  must return true to allow focus change; false otherwise
     */
    /*public*/ SystemNameValidator::SystemNameValidator(/*@Nonnull*/ /*JComponent*/JComponent *component,
                                                        /*@Nonnull*/ Manager* manager, bool required) : JInputValidator(component)
    {
        //super(component, true, required);
        setManager(manager);
        this->required = required;
    }

    /*public*/ Validation* SystemNameValidator::getValidation()
    {
     return JInputValidator::getValidation();
    }
#if 1
    //@Override
    /*protected*/ Validation* SystemNameValidator::getValidation(/*JComponent*/JComponent *component, JInputValidatorPreferences* preferences) {
        //if (component instanceof JTextComponent)
        if(qobject_cast<JTextField*>(component->jself()))
        {
         //JTextComponent jtc = (JTextComponent) component;
         JTextField* jtc = (JTextField*)component->jself();
         QString text = jtc->text();
            if (!text .isNull() && !text.isEmpty()) {
                try {
                    if (qobject_cast<AbstractProxyManager*>(manager->self())) {
                        AbstractProxyManager/*<?>*/* proxyManager = (AbstractProxyManager/*<?>*/*) manager->self();
                        proxyManager->validateSystemNameFormat(text, QLocale());
                    } else {
                        manager->makeSystemName(text, false);
                    }
                } catch (NamedBean::BadSystemNameException* ex) {
                    if (manager->validSystemNameFormat(text) == Manager::NameValidity::VALID_AS_PREFIX_ONLY) {
                        return new Validation(Validation::Type::WARNING, tr("<html>\"%1\" is an incomplete system name for a %2.<br><br>%3</html>").arg(text, manager->getBeanTypeHandled(),
                                trimHtmlTags(getToolTipText())), preferences);
                    }
                    return new Validation(Validation::Type::DANGER, tr("<html>{0}<br><br>{1}</html>").arg(ex->getMessage(), trimHtmlTags(getToolTipText())), preferences);
                }
                return new Validation(Validation::Type::SUCCESS, getToolTipText(), preferences);
            }
        }
        if (required) {
            return new Validation(Validation::Type::WARNING, tr("<html>A system name is required.<br><br>%1</html>").arg(trimHtmlTags(getToolTipText())), preferences);
        }
        return getNoneValidation();
    }
#endif
    /*public*/ bool SystemNameValidator::isRequired() {
        return required;
    }

    /*public*/ void SystemNameValidator::setRequired(bool required) {
        this->required = required;
    }

    /**
     * Set the Manager used to validate system names.
     * <p>
     * If the manager changes, fires the a property change for the property
     * {@code manager} and calls {@link #verify(javax.swing.JComponent)} to
     * verify any text against the new manager.
     *
     * @param manager the new manager
     */
    /*public*/ void SystemNameValidator::setManager(/*@Nonnull*/ Manager* manager) {
//        Objects.requireNonNull(manager, "Cannot validate against a null manager");
        Manager* old = this->manager;
        if (old == nullptr || old != (manager)) {
            this->manager = manager;
#if 1
            getSwingPropertyChangeSupport()->firePropertyChange("manager",VPtr<Manager>::asQVariant( old), VPtr<Manager>::asQVariant(this->manager));
            verify(getComponent());
#endif
        }
    }

    QValidator::State SystemNameValidator::validate(QString& text, int& pos) const
    {
     try {
         if (static_cast<AbstractProxyManager*>(manager)) {
             AbstractProxyManager/*<?>*/* proxyManager = (AbstractProxyManager/*<?>*/*) manager->self();
             proxyManager->validateSystemNameFormat(text, QLocale());
         } else {
             manager->makeSystemName(text, false);
         }
     } catch (NamedBean::BadSystemNameException ex) {
         if (text.length()<2 || manager->validSystemNameFormat(text) == Manager::NameValidity::VALID_AS_PREFIX_ONLY) {
//             return new Validation(Validation::Type::WARNING, tr("<html>\"%1\" is an incomplete system name for a %2.<br><br>%3</html>").arg(text, manager->getBeanTypeHandled(),
//                     trimHtmlTags(getToolTipText())), preferences);
          return QValidator::Intermediate;
         }
         //return new Validation(Validation::Type::DANGER, tr("<html>{0}<br><br>{1}</html>").arg(ex->getMessage(), trimHtmlTags(getToolTipText())), preferences);
         return QValidator::Invalid;
     }
     //return new Validation(Validation::Type::SUCCESS, getToolTipText(), preferences);
     return QValidator::Acceptable;
    }
