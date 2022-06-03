#include "moduleeditor.h"
#include "runtimeexception.h"
#include "treepane.h"
#include "defaultmodule.h"
#include "logixng_thread.h"
#include "defaultmodulemanager.h"

/**
 * Editor of Module
 *
 * @author Daniel Bergqvist 2020
 */
///*public*/  class ModuleEditor extends TreeEditor implements AbstractLogixNGEditor<Module> {


//    private final ModuleManager _moduleManager =
//            InstanceManager.getDefault(ModuleManager.class);



    /**
     * Create a new ConditionalNG List View editor.
     *
     * @param f the bean table frame
     * @param m the bean table model
     * @param sName name of the LogixNG being edited
     */
    /*public*/  ModuleEditor::ModuleEditor(BeanTableFrame/*<Module>*/* f,
            BeanTableDataModel/*<Module>*/* m, QString sName, QWidget* parent) :

        TreeEditor((AbstractFemaleSocket*)setupRootSocket(nullptr, sName)->bself(),
                EnableClipboard::EnableClipboard,
                EnableRootRemoveCutCopy::DisableRootRemoveCutCopy,
                EnableRootPopup::EnableRootPopup,
                EnableExecuteEvaluate::EnableExecuteEvaluate,
        parent){
        setObjectName("ModuleEditor");
        this->beanTableDataModel = m;

        if (!_treePane->_femaleRootSocket->isConnected()) {
            // This should never happen
            throw new RuntimeException("Module is not connected");
        }
        if (!(qobject_cast<Module*>(_treePane->_femaleRootSocket->getConnectedSocket()->getObject()->bself()))) {
            // This should never happen
            throw new RuntimeException("Connected socket is not a Module");
        }
        _module = (Module*) _treePane->_femaleRootSocket->getConnectedSocket()->getObject()->bself();

        if (_module->NamedBean::getUserName() == "") {
            this->setTitle(
                    tr("Edit Module %1").arg(_module->NamedBean::getSystemName()));
        } else {
            this->setTitle(
                    tr("Edit Module %1 - %2").arg(
                            _module->NamedBean::getSystemName(),
                            _module->NamedBean::getUserName()));
        }
    }

    //@Override
    /*protected*/ void ModuleEditor::executeEvaluate(SwingConfiguratorInterface* swi, MaleSocket* maleSocket) {
        Base* b = maleSocket;
        Module* module;
        if (qobject_cast<Module*>(maleSocket->getObject()->bself())) {
            module = (Module*)maleSocket->getObject()->bself();
        } else {
            while ((b != nullptr) && !(qobject_cast<Module*>(b->bself()))) b = b->getParent();
            if (b == nullptr) throw new RuntimeException("Module is not found");
            module = (Module*)b->bself();
        }
#if 0
        LogixNG_Thread::getThread(LogixNG_Thread::DEFAULT_LOGIXNG_THREAD).runOnLogixNGEventually(() -> {

            // We need to create a temporary ConditionalNG to be able to
            // execute/evaluate a module or a part of a module
            module.setCurrentConditionalNG(new DefaultConditionalNG("IQC1", null));

            swi.executeEvaluate(maleSocket);
        });
#endif
    }

    /*private*/ /*static*/ FemaleSocket* ModuleEditor::setupRootSocket(Base* parent, QString sName) {
        AbstractFemaleSocket* socket = new RootSocket(parent, new ModuleEditor_FemaleSocketListener1()
//                                              {
//            //@Override
//            /*public*/  void connected(FemaleSocket socket) {
//                // Do nothing
//            }

//            //@Override
//            /*public*/  void disconnected(FemaleSocket socket) {
//                // Do nothing
//            }
//        }
                                              , "Root");

        //Module* module = ((DefaultModuleManager*)InstanceManager::getDefault("ModuleManager"))->getBySystemName(sName)->self();
        NamedBean* module = ((DefaultModuleManager*)InstanceManager::getDefault("ModuleManager"))->getBySystemName(sName);
        try {
            socket->_connect(new ModuleEditorMaleSocket(nullptr, (DefaultModule*)module->self()));
        } catch (SocketAlreadyConnectedException* e) {
            // This should never happen
            throw new RuntimeException("Socket already connected", e);
        }
        return socket;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ModuleEditor::windowClosed(QCloseEvent* e) {
        moduleData.clear();
        moduleData.insert("Finish", _module->NamedBean::getSystemName());  // NOI18N
        fireModuleEvent();
    }

    /**
     * Notify the listeners to check for new data.
     */
    void ModuleEditor::fireModuleEvent() {
        for (EditorEventListener* l : listenerList) {
            l->editorEventOccurred(moduleData);
        }
    }

    //@Override
    /*public*/  void ModuleEditor::addEditorEventListener(EditorEventListener* listener) {
        listenerList.append(listener);
    }

    //@Override
    /*public*/  void ModuleEditor::removeEditorEventListener(EditorEventListener* listener) {
        listenerList.removeOne(listener);
    }

    //@Override
    /*public*/  void ModuleEditor::bringToFront() {
        this->setVisible(true);
    }


