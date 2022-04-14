#include "moduleeditormalesocket.h"
#include "module.h"
#include "debugable.h"
/**
 * MaleSocket for a Module.
 * This class is used by the ModuleEditor class
 *
 * @author Daniel Bergqvist 2020
 */
//class ModuleEditorMaleSocket extends AbstractMaleSocket {

//    Module _module;

    /*public*/  ModuleEditorMaleSocket::ModuleEditorMaleSocket(BaseManager/*<? extends NamedBean>*/* manager, Module* module, QObject* parent) : AbstractMaleSocket(manager, module, parent){
        //super(manager, module);
    }

    //@Override
    /*protected*/ void ModuleEditorMaleSocket::registerListenersForThisClass() {
        // Do nothing
    }

    //@Override
    /*protected*/ void ModuleEditorMaleSocket::unregisterListenersForThisClass() {
        // Do nothing
    }

    //@Override
    /*protected*/ void ModuleEditorMaleSocket::disposeMe() {
        ((Module*)getObject())->Base::dispose();
    }

    //@Override
    /*public*/  void ModuleEditorMaleSocket::setEnabled(bool enable) {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  void ModuleEditorMaleSocket::setEnabledFlag(bool enable) {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  bool ModuleEditorMaleSocket::isEnabled() {
        return true;
    }

    //@Override
    /*public*/  void ModuleEditorMaleSocket::setDebugConfig(Debugable::DebugConfig* config) {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  Debugable::DebugConfig* ModuleEditorMaleSocket::getDebugConfig() {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  Debugable::DebugConfig* ModuleEditorMaleSocket::createDebugConfig() {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  QString ModuleEditorMaleSocket::getComment() {
        return ((Module*)getObject())->Base::getComment();
    }

    //@Override
    /*public*/  void ModuleEditorMaleSocket::setComment(QString comment) {
        ((Module*)getObject())->Base::setComment(comment);
    }
