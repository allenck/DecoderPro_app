#include "functionshelpdialog.h"
#include "functionmanager.h"
#include "gridbaglayout.h"
#include "instancemanager.h"
#include "jpanel.h"
#include "vptr.h"
#include "jeditorpane.h"
#include "jbutton.h"

/**
 * Show a dialog that shows information about the functions for formula
 *
 * @author Daniel Bergqvist 2020
 */
///*public*/  class FunctionsHelpDialog implements jmri.InstanceManagerAutoDefault {

    /*private*/ /*static*/ /*final*/ int FunctionsHelpDialog::panelWidth = 500;
    /*private*/ /*static*/ /*final*/ int FunctionsHelpDialog::panelHeight = 500;

    /*private*/ /*static*/ /*final*/ QMap<QString, Module_x*> FunctionsHelpDialog::_modules =  QMap<QString, Module_x*>();



    /*public*/  FunctionsHelpDialog::FunctionsHelpDialog(QObject* parent) {
        FunctionManager* fm = (FunctionManager*)InstanceManager::getDefault("FunctionManager");
        //for (Map.Entry<String, Function> entry : fm->getFunctions().entrySet())
        QMapIterator<QString, Function*> entry(fm->getFunctions());
        while(entry.hasNext())
        {
         entry.next();
//            System.out.format("Existing functions: %s, %s%n", entry->getValue()->getModule(), entry->getValue()->getName());

            Module_x* m = _modules.value(entry.value()->getModule());
#if 1
            if (m == nullptr) {
                m = new Module_x(entry.value()->getModule(), entry.value()->getConstantDescriptions());
                _modules.insert(m->_name, m);
            }
            m->_functions.append(entry.value());
#endif
        }
    }

    /*public*/  void FunctionsHelpDialog::showDialog() {
        #if 1
        if (_selectItemTypeDialog != nullptr) {
            _selectItemTypeDialog->show();
            return;
        }

        _documentationEditorPane->setEditable(false);
        _documentationEditorPane->setContentType("text/html");

        _moduleComboBox->clear();
        QList<Module_x*> list = QList<Module_x*>(_modules.values());
//        Collections.sort(list);
        for (Module_x* module : list) {
            _moduleComboBox->addItem(module->_name, VPtr<Module_x>::asQVariant(module));
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_moduleComboBox);
        //_moduleComboBox.addActionListener((ActionEvent e) -> {
        connect(_moduleComboBox, &JComboBox::focusGained, [=]{
            initFunctionsComboBox();
        });

        //_functionComboBox.addActionListener((ActionEvent e) -> {
        connect(_functionComboBox, &JComboBox::currentTextChanged, [=] {
            if (_functionComboBox->getSelectedIndex() > -1) {
                SortableFunction* f = VPtr<SortableFunction>::asPtr(_functionComboBox
                        ->getItemAt(_functionComboBox->getSelectedIndex()));
                _documentationEditorPane->setText(f->_functionDescr);
                _documentationEditorPane->setCaretPosition(0);
            } else {
                _documentationEditorPane->setText("");
            }
        });

        if (_moduleComboBox->getItemCount() > 0) {
            _moduleComboBox->setSelectedIndex(0);
        }

        _selectItemTypeDialog  = new JDialog(
                (JDialog*)nullptr,
                tr("Help for functions"),
                true);


        QWidget* contentPanel = _selectItemTypeDialog->getContentPane();
        contentPanel->setLayout(new QVBoxLayout());//contentPanel, BoxLayout.Y_AXIS));

        JPanel* p;
        p = new JPanel();
//        p->setLayout(new FlowLayout());
        GridBagLayout* pLayout;
        p->setLayout(pLayout=new GridBagLayout());
        GridBagConstraints c = GridBagConstraints();
        c.gridwidth = 1;
        c.gridheight = 1;
        c.gridx = 0;
        c.gridy = 0;
        c.anchor = GridBagConstraints::EAST;
        pLayout->addWidget(_moduleLabel, c);
        c.gridy = 1;
        pLayout->addWidget(_functionLabel, c);
        c.gridx = 1;
        c.gridy = 0;
        c.anchor = GridBagConstraints::WEST;
        c.weightx = 1.0;
        c.fill = GridBagConstraints::HORIZONTAL;  // text field will expand
        pLayout->addWidget(_moduleComboBox, c);
        c.gridy = 1;
        c.fill = GridBagConstraints::BOTH;  // text field will expand
        pLayout->addWidget(_functionComboBox, c);

        c.gridx = 0;
        c.gridy = 2;
        c.gridwidth = 2;

//        JScrollPane documentationScroller = new JScrollPane(_documentationEditorPane);
//        documentationScroller->setPreferredSize(new Dimension(panelWidth, panelHeight));
//        documentationScroller->setAlignmentX(LEFT_ALIGNMENT);
//        documentationScroller->setAlignmentY(TOP_ALIGNMENT);
//        pLayout->addWidget(documentationScroller, c);
        _documentationEditorPane->resize(panelWidth,panelHeight);
        _documentationEditorPane->setEnabled(true);
        pLayout->addWidget(_documentationEditorPane,c);

//        _categoryComboBox->setToolTipText(jmri.jmrit.logixng.tools.swing.Bundle->getMessage("CategoryNamesHint"));    // NOI18N
//        _swingConfiguratorComboBox->setToolTipText(jmri.jmrit.logixng.tools.swing.Bundle->getMessage("TypeNamesHint"));   // NOI18N
        contentPanel->layout()->addWidget(p);
        // set up message
        JPanel* panel3 = new JPanel();
        panel3->setLayout(new QVBoxLayout());//panel3, BoxLayout.Y_AXIS));

        contentPanel->layout()->addWidget(panel3);

        // set up create and cancel buttons
        JPanel* panel5 = new JPanel();
        panel5->setLayout(new FlowLayout());
        // Cancel
        JButton* cancel = new JButton(tr("Cancel"));    // NOI18N
        panel5->layout()->addWidget(cancel);
        connect(cancel, &JButton::clicked, [=] {
            cancelAddPressed(nullptr);
        });
//        cancel->setToolTipText(Bundle->getMessage("CancelLogixButtonHint"));      // NOI18N
        cancel->setToolTip("Press to return to Logix Table without any changes");      // NOI18N

//        _selectItemTypeDialog.addWindowListener(new event.WindowAdapter() {
//            //@Override
//            /*public*/  void windowClosing(event.WindowEvent e) {
//                cancelAddPressed(null);
//            }
//        });
/*
        _create = new JButton(Bundle->getMessage("ButtonCreate"));  // NOI18N
        panel5.add(_create);
        _create.addActionListener((ActionEvent e) -> {
            cancelAddPressed(null);

            SwingConfiguratorInterface swingConfiguratorInterface =
                    _swingConfiguratorComboBox->getItemAt(_swingConfiguratorComboBox->getSelectedIndex());
//            System.err.format("swingConfiguratorInterface: %s%n", swingConfiguratorInterface->getClass()->getName());
            createAddFrame(femaleSocket, path, swingConfiguratorInterface);
        });
*/
        contentPanel->layout()->addWidget(panel5);

        _selectItemTypeDialog->setMinimumSize(QSize(panelWidth, panelHeight));

//        addLogixNGFrame->setLocationRelativeTo(component);
        _selectItemTypeDialog->setLocationRelativeTo(nullptr);
        _selectItemTypeDialog->pack();
        _selectItemTypeDialog->setVisible(true);
#endif
    }
    #if 1
    /*final*/ /*protected*/ void FunctionsHelpDialog::cancelAddPressed(JActionEvent* e) {
        _selectItemTypeDialog->setVisible(false);
        _selectItemTypeDialog->dispose();
        _selectItemTypeDialog = nullptr;
    }

    /*private*/ void FunctionsHelpDialog::initFunctionsComboBox() {
        _functionComboBox->clear();

        if (_moduleComboBox->getSelectedIndex() > -1) {
            Module_x* module = VPtr<Module_x>::asPtr(_moduleComboBox->getItemAt(_moduleComboBox->getSelectedIndex()));
            QList<SortableFunction*> list = QList<SortableFunction*>();
            if (module->_constantDescriptions != nullptr) {
                list.append(new SortableFunction(tr("::: Constants"), module->_constantDescriptions));
            }
            for (Function* f : module->_functions) {
                list.append(new SortableFunction(f->getName(), f->getDescription()));
            }
//            Collections.sort(list);
            for (SortableFunction* function : list) {
                _functionComboBox->addItem(function->toString(), VPtr<SortableFunction>::asQVariant(function));
            }
//            JComboBoxUtil->setupComboBoxMaxRows(_functionComboBox);
        }
    }




//    /*private*/ static class Module implements Comparable<Module> {

//        /*private*/ /*final*/ String _name;
//        /*private*/ /*final*/ String _constantDescriptions;
//        /*private*/ /*final*/ List<Function> _functions = new ArrayList<>();

//        /*private*/ Module(String name, String constantDescriptions) {
//            _name = name;
//            _constantDescriptions = constantDescriptions;
//        }

//        //@Override
//        /*public*/  boolean equals(Object o) {
//            return (o instanceof Module) && _name.equals(((Module)o)._name);
//        }

//        //@Override
//        /*public*/  int hashCode() {
//            int hash = 7;
//            hash = 47 * hash + Objects.hashCode(this._name);
//            return hash;
//        }

//        //@Override
//        /*public*/  int compareTo(Module o) {
//            return _name.compareTo(o._name);
//        }

//        //@Override
//        /*public*/  String toString() {
//            return _name;
//        }
//    }

//    /*private*/ static class SortableFunction implements Comparable<SortableFunction> {

//        /*private*/ /*final*/ String _name;
//        /*private*/ /*final*/ String _functionDescr;

//        /*private*/ SortableFunction(String name, String functionDescr) {
//            _name = name;
//            _functionDescr = functionDescr;
//        }

//        //@Override
//        /*public*/  boolean equals(Object o) {
//            return (o instanceof SortableFunction) && _name.equals(((SortableFunction)o)._name);
//        }

//        //@Override
//        /*public*/  int hashCode() {
//            int hash = 7;
//            hash = 47 * hash + Objects.hashCode(this._name);
//            return hash;
//        }

//        //@Override
//        /*public*/  int compareTo(SortableFunction o) {
//            return _name.compareTo(o._name);
//        }

//        //@Override
//        /*public*/  String toString() {
//            return _name;
//        }
//    }
    #endif
