#include "defaultmoduleswing.h"
#include "instancemanager.h"
#include "jtable.h"
#include "logixng/femalesocket.h"
#include "logixng/module.h"
#include "module.h"
#include "malesocket.h"
#include "swingtools.h"
#include "moduleparameterstablemodel.h"

DefaultModuleSwing::DefaultModuleSwing(QObject *parent) : AbstractSwingConfigurator(parent)
{

}

/**
 * Configures an DefaultModule object with a Swing JPanel.
 */
// /*public*/ class DefaultModuleSwing extends AbstractSwingConfigurator {

//    static final java.util.ResourceBundle rbx =
//            java.util.ResourceBundle.getBundle("jmri.jmrit.logixng.tools.swing.LogixNGSwingBundle");  // NOI18N


/** {@inheritDoc} */
//@Override
/*public*/ QString DefaultModuleSwing::getExecuteEvaluateMenuText() {
    return tr("Execute");
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultModuleSwing::executeEvaluate(/*@Nonnull*/ Base* object) {

    if (! (qobject_cast<MaleSocket*>(object->bself()))) {
        throw new IllegalArgumentException("object is not a MaleSocket");
    }
    if (! (qobject_cast<Module*>(((MaleSocket*)object->bself())->getObject()->bself()))) {
        throw new IllegalArgumentException("((MaleSocket)object).getObject() is not a Module");
    }
    Module* module = (Module*)((MaleSocket*)object->bself())->getObject()->bself();

    FemaleSocket* femaleSocket = module->getRootSocket();
    if (!femaleSocket->isConnected()) {
        // Nothing to do since nothing is connected to the female socket
//            jmri.util.ThreadingUtil.runOnGUIEventually(() -> {
//                JOptionPane.showMessageDialog(null,
//                        Bundle.getMessage("ExecuteEvaluate_ActionCompleted"),
//                        Bundle.getMessage("ExecuteEvaluate_Title"),
//                        JOptionPane.PLAIN_MESSAGE);
//            });
        ThreadingUtil::runOnGUIEventually(new DMS_ThreadingUtil());
        return;

    }


    Base* obj = femaleSocket->getConnectedSocket();
    if (obj == nullptr) throw new NullPointerException("object is null");
    while (qobject_cast<MaleSocket*>(obj->bself())) {
        obj = ((MaleSocket*)obj->bself())->getObject();
    }
    SwingConfiguratorInterface* swi =
            SwingTools::getSwingConfiguratorForClass(obj->bself()->metaObject()->className());

    swi->executeEvaluate(femaleSocket->getConnectedSocket());
}

/** {@inheritDoc} */
//@Override
/*public*/ BaseManager/*<? extends NamedBean>*/* DefaultModuleSwing::getManager() {
    return nullptr;
}

/** {@inheritDoc} */
//@Override
/*public*/ JPanel* DefaultModuleSwing::getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ {
    // This method is used to create a new item.
    throw new UnsupportedOperationException("Not supported");
}

/** {@inheritDoc} */
//@Override
/*public*/ JPanel* DefaultModuleSwing::getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException */{
    createPanel(object, buttonPanel);
    return panel;
}

/** {@inheritDoc} */
//@Override
/*public*/ QString DefaultModuleSwing::getExampleSystemName() {
    throw new UnsupportedOperationException("Not supported");
}

/** {@inheritDoc} */
//@Override
/*public*/ QString DefaultModuleSwing::getAutoSystemName() {
    throw new UnsupportedOperationException("Not supported");
}

/*protected*/ void DefaultModuleSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
       // This method is never used to create a module so we expect to have a module
       if (! (qobject_cast< Module*>(object->bself()))) {
           throw new IllegalArgumentException(tr("object is not a Module: ") + object->bself()->metaObject()->className());
       }
       Module* module = (Module*)object->bself();

       panel = new JPanel();

       panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));

       JPanel* tablePanel = new JPanel(new FlowLayout);
       JTable* table = new JTable();
       _moduleParametersTableModel = new ModuleParametersTableModel(module);
       table->setModel(_moduleParametersTableModel);
//       table.setDefaultRenderer(SymbolTable::InitialValueType.class,
//               new ModuleParametersTableModel.TypeCellRenderer());
//       table.setDefaultEditor(SymbolTable.InitialValueType.class,
//               new ModuleParametersTableModel.TypeCellEditor());
//       table.setDefaultRenderer(ModuleParametersTableModel.Menu.class,
//               new ModuleParametersTableModel.MenuCellRenderer());
//       table.setDefaultEditor(ModuleParametersTableModel.Menu.class,
//               new ModuleParametersTableModel.MenuCellEditor(table, _moduleParametersTableModel));
       _moduleParametersTableModel->setColumnForMenu(table);
       //JScrollPane scrollpane = new JScrollPane(table);
       //scrollpane.setPreferredSize(new Dimension(400, 200));
       table->resize(QSize(400, 200));
       tablePanel->layout()->addWidget(/*scrollpane, BorderLayout.CENTER*/table);
       panel->layout()->addWidget(tablePanel);

       // Add parameter
       JButton* add = new JButton(tr("Add parameter"));
       buttonPanel->layout()->addWidget(add);
       connect(add, &JButton::clicked, [=] {
           _moduleParametersTableModel->add();
       });
   }
/** {@inheritDoc} */
    //@Override
    /*public*/ bool DefaultModuleSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        bool hasErrors = false;
        for (DefaultSymbolTable::DefaultParameter* p : _moduleParametersTableModel->getParameters()) {
            if (p->getName().isEmpty()) {
                errorMessages->append(tr("The name of the parameter is empty").arg(p->getName()));
                hasErrors = true;
            } else if (! SymbolTable::validateName(p->getName())) {
                errorMessages->append(tr("The name of parameter \"%1\" is not valid").arg(p->getName()));
                hasErrors = true;
            }
            if (!p->isInput() && !p->isOutput()) {
                errorMessages->append(tr("The parameter \"%1\" is neither in or out").arg(p->getName()));
                hasErrors = true;
            }
        }

        return !hasErrors;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ MaleSocket* DefaultModuleSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        throw new UnsupportedOperationException("Not supported");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultModuleSwing::updateObject(/*@Nonnull*/ Base* object) {
        // This method is never used to create a module so we expect to have a module
        if (! (qobject_cast<Module*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object is not a Module: ") + object->bself()->metaObject()->className());
        }
        Module* module = (Module*)object->bself();

        module->getParameters().clear();
        for (Module::Parameter* p : _moduleParametersTableModel->getParameters()) {
            module->addParameter(p);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString DefaultModuleSwing::toString() {
        return tr("DefaultModule");
    }

    //@Override
    /*public*/ void DefaultModuleSwing::dispose() {
    }
