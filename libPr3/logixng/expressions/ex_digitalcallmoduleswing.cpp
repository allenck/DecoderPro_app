#include "ex_digitalcallmoduleswing.h"
#include "../abstractbase.h"
#include "ex_digitalcallmodule.h"
#include "jlabel.h"
#include "jcombobox.h"
#include "instancemanager.h"
#include "../defaultmodulemanager.h"
#include "../callmoduleparametertablemodel.h"
#include "jtable.h"
#include "../defaultdigitalexpressionmanager.h"

/**
 * Configures an ModuleDigitalExpression object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class DigitalCallModuleSwing extends AbstractDigitalExpressionSwing {
namespace Expressions
{

    //@Override
    /*protected*/ void DigitalCallModuleSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        if ((object != nullptr) && (! (qobject_cast<DigitalCallModule*>(object->bself())))) {
            throw new IllegalArgumentException(QString("object is not a Module: ") + object->bself()->metaObject()->className());
        }
        DigitalCallModule* callModule = (DigitalCallModule*)object->bself();

        panel = new JPanel();

        panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));

        JPanel* beanPanel = new JPanel(new FlowLayout);
        beanPanel->layout()->addWidget(new JLabel("Module:"));
        _moduleComboBox = new JComboBox();
        _moduleComboBox->addItem( "", VPtr<ModuleItem>::asQVariant(new ModuleItem(nullptr)));
        for (NamedBean* nb : ((DefaultModuleManager*)InstanceManager::getDefault("ModuleManager"))->getNamedBeanSet())
        {
         Module* m = (Module*)nb->self();
//            System.out.format("Root socket type: %s%n", m.getRootSocketType().getName());
            if ("DefaultFemaleDigitalExpressionSocket" == (m->getRootSocketType()->getName())) {
                ModuleItem* mi = new ModuleItem(m);
                _moduleComboBox->addItem(mi->toString(), VPtr<ModuleItem>::asQVariant(mi));
                if ((callModule != nullptr)
                        && (callModule->getModule() != nullptr)
                        && (callModule->getModule()->getBean() == m)) {
                    _moduleComboBox->setSelectedItem(mi->toString());
                }
            }
        }
//        JComboBoxUtil.setupComboBoxMaxRows(_moduleComboBox);
        beanPanel->layout()->addWidget(_moduleComboBox);
        panel->layout()->addWidget(beanPanel);

        Module* module = nullptr;
        QList<Module::ParameterData*>* parameterData;
        if (callModule != nullptr) {
            if (callModule->getModule() != nullptr) {
                module = callModule->getModule()->getBean();
            }
            parameterData = callModule->getParameterData();
        } else {
            parameterData = new QList<Module::ParameterData*>();
        }
        JPanel* tablePanel = new JPanel(new QVBoxLayout);
        JTable* table = new JTable();
        _moduleParametersTableModel = new CallModuleParameterTableModel(module, parameterData);
        table->setModel(_moduleParametersTableModel);
#if 0
        table.setDefaultRenderer(InitialValueType.class,
                new CallModuleParameterTableModel.TypeCellRenderer());
        table.setDefaultEditor(InitialValueType.class,
                new CallModuleParameterTableModel.InitialValueCellEditor());
        table.setDefaultRenderer(ReturnValueType.class,
                new CallModuleParameterTableModel.TypeCellRenderer());
        table.setDefaultEditor(ReturnValueType.class,
                new CallModuleParameterTableModel.ReturnValueCellEditor());
#endif
        _moduleParametersTableModel->setColumnsForComboBoxes(table);
//        JScrollPane scrollpane = new JScrollPane(table);
//        scrollpane.setPreferredSize(new Dimension(400, 200));
        ((QVBoxLayout*)tablePanel->layout())->addWidget(/*scrollpane*/ table,1, Qt::AlignHCenter );//BorderLayout.CENTER);
        panel->layout()->addWidget(tablePanel);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool  DigitalCallModuleSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket*  DigitalCallModuleSwing::createNewObject(/*@Nonnull*/ QString systemName,/* @CheckForNull*/ QString userName) {
        DigitalCallModule* action = new DigitalCallModule(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void  DigitalCallModuleSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<DigitalCallModule*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object is not a Module: ") + object->bself()->metaObject()->className());
        }
        DigitalCallModule* callModule = (DigitalCallModule*)object->bself();

        ModuleItem* mi = VPtr<ModuleItem>::asPtr(_moduleComboBox->getItemAt(_moduleComboBox->getSelectedIndex()));
        if (mi->_module != nullptr) {
            callModule->setModule(mi->_module);
            callModule->getParameterData()->clear();
            //callModule->getParameterData()->unite(_moduleParametersTableModel->getParameters());
            for (Module::ParameterData* pd : *_moduleParametersTableModel->getParameters()) {
                callModule->getParameterData()->append(pd);
            }
        }
        else {
            callModule->removeModule();
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString  DigitalCallModuleSwing::toString() {
        return tr("DigitalCallModule");
    }

    //@Override
    /*public*/  void  DigitalCallModuleSwing::dispose() {
    }


}

