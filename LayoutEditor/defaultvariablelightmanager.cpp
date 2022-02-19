#include "defaultvariablelightmanager.h"
#include "vptr.h"

/**
 * Default implementation of a VariableLightManager.
 *
 * @author Bob Jacobsen       Copyright (C) 2004
 * @author Daniel Bergqvist   Copyright (C) 2020
 */
// /*public*/ class DefaultVariableLightManager extends AbstractManager<VariableLight>
//        implements VariableLightManager {

    /**
     * Create a new VariableLightManager instance.
     *
     * @param memo the system connection
     */
    /*public*/ DefaultVariableLightManager::DefaultVariableLightManager(SystemConnectionMemo* memo, QObject* parent)
     : AbstractManager(memo, parent){
        //super(memo);
    }

    /**
     * Initializes a new VariableLightManager instance.
     * @return itself
     */
    /*public*/ DefaultVariableLightManager* DefaultVariableLightManager::init() {
        LightManager* lm = (LightManager*)InstanceManager::getDefault("LightManager");
       ((AbstractManager*)lm->self())->PropertyChangeSupport::addPropertyChangeListener("beans", this);
        for (NamedBean* nb : ((AbstractManager*)lm->self())->getNamedBeanSet()) {
         Light* l = (Light*)nb;
            if (qobject_cast<VariableLight*>(l->self())) {
                Register((NamedBean*) l->self());
            }
        }
        return this;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultVariableLightManager::dispose() {
        dispose();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ int DefaultVariableLightManager::getXMLOrder() const{
        return Manager::LIGHTS;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QChar DefaultVariableLightManager::typeLetter() const{
        return 'L';
    }

    /** {@inheritDoc} */
    //@Override
    //@Nonnull
    /*public*/ QString DefaultVariableLightManager::getBeanTypeHandled(bool plural) const{
        return tr(plural ? "VariableLights" : "VariableLight");
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ /*Class<VariableLight>*/QString DefaultVariableLightManager::getNamedBeanClass() const {
        return "VariableLight";
    }

    /** {@inheritDoc} */
    //@Override
    //@OverridingMethodsMustInvokeSuper
    /*public*/ void DefaultVariableLightManager::Register(/*@Nonnull*/ NamedBean* /*s*/){
        throw new UnsupportedOperationException("Not supported. Use LightManager.register() instead");
    }

    /** {@inheritDoc} */
    //@Override
    //@OverridingMethodsMustInvokeSuper
    /*public*/ void DefaultVariableLightManager::deregister(/*@Nonnull*/ NamedBean */*s*/)  {
        throw new UnsupportedOperationException("Not supported. Use LightManager.deregister() instead");
    }

    /** {@inheritDoc} */
    //@Override
    //@OverridingMethodsMustInvokeSuper
    /*public*/ void DefaultVariableLightManager::deleteBean(/*@Nonnull*/ NamedBean* n, /*@Nonnull*/ QString /*property*/) {
        throw new UnsupportedOperationException("Not supported. Use LightManager.deleteBean() instead");
    }

    //@Override
    /*public*/ void DefaultVariableLightManager::propertyChange(PropertyChangeEvent* e) {
        propertyChange(e);

        if ("beans" == (e->getPropertyName())) {

            // A NamedBean is added
            if (e->getNewValue() != QVariant()
                    && (qobject_cast<VariableLight*>(VPtr<VariableLight>::asPtr(e->getNewValue())->self()))) {
                Register((NamedBean*)VPtr<VariableLight>::asPtr(e->getNewValue())->self());
            }

            // A NamedBean is removed
            if (e->getOldValue() != QVariant()
                    && (qobject_cast<VariableLight*>(VPtr<VariableLight>::asPtr(e->getOldValue())->self()))) {
                deregister((NamedBean*) VPtr<VariableLight>::asPtr(e->getOldValue())->self());
            }
        }
    }

//    /*public*/ NamedBean* DefaultVariableLightManager::getByUserName(/*@Nonnull*/ QString s)
//    {
//     return AbstractManager::getByUserName(s);
//    }

//    /*public*/ NamedBean* DefaultVariableLightManager::getBySystemName(/*@Nonnull*/ QString s)
//    {
//     return AbstractManager::getBySystemName(s);
//    }

//    /*public*/ SystemConnectionMemo* DefaultVariableLightManager::getMemo()
//    {
//     return  memo;
//    }
