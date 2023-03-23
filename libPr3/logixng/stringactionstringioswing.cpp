#include "stringactionstringioswing.h"
#include "beanselectpanel.h"
#include "logixng/stringactionstringio.h"
#include "instancemanager.h"
#include "logixng/stringio.h"
#include "abstractstringiomanager.h"
#include "jlabel.h"
#include "defaultstringactionmanager.h"


StringActionStringIOSwing::StringActionStringIOSwing(QObject *parent)
    : AbstractStringActionSwing(parent)
{

}
/**
 * Configures an StringActionStringIO object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ class StringActionStringIOSwing extends AbstractStringActionSwing {



    //@Override
    /*protected*/ void StringActionStringIOSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        StringActionStringIO* action = (StringActionStringIO*)object->bself();

        panel = new JPanel(new FlowLayout);
        _stringIOBeanPanel = new BeanSelectPanel((AbstractStringIOManager*)InstanceManager::getDefault("StringIOManager"), nullptr);

        if (action != nullptr) {
            if (action->getStringIO() != nullptr) {
                _stringIOBeanPanel->setDefaultNamedBean(action->getStringIO()->getBean());
            }
        }

        panel->layout()->addWidget(new JLabel(tr("StringIO")));
        panel->layout()->addWidget(_stringIOBeanPanel);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool StringActionStringIOSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ MaleSocket* StringActionStringIOSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        StringActionStringIO* action = new StringActionStringIO(systemName, userName);
        if (!_stringIOBeanPanel->isEmpty()) {
            StringIO* memory = (StringIO*)_stringIOBeanPanel->getNamedBean()->self();
            if (memory != nullptr) {
                NamedBeanHandle<StringIO*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(memory->getDisplayName(), memory);
                action->setStringIO(handle);
            }
        }
        return ((DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void StringActionStringIOSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<StringActionStringIO*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object must be an StringActionStringIO but is a: ")+object->bself()->metaObject()->className());
        }
        StringActionStringIO* action = (StringActionStringIO*)object->bself();
        StringIO* memory = (StringIO*)(AbstractNamedBean*)_stringIOBeanPanel->getNamedBean()->self();
        if (memory != nullptr) {
            NamedBeanHandle<StringIO*>* handle
                    = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                    ->getNamedBeanHandle(memory->getDisplayName(), memory);
            action->setStringIO(handle);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString StringActionStringIOSwing::toString() {
        return tr("StringActionStringIO");
    }

    //@Override
    /*public*/ void StringActionStringIOSwing::dispose() {
        if (_stringIOBeanPanel != nullptr) {
            _stringIOBeanPanel->dispose();
        }
    }
