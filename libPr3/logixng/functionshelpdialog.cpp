#include "functionshelpdialog.h"
#include "functionmanager.h"
#include "instancemanager.h"
/**
 * Show a dialog that shows information about the functions for formula
 *
 * @author Daniel Bergqvist 2020
 */
///*public*/  class FunctionsHelpDialog implements jmri.InstanceManagerAutoDefault {

    /*private*/ /*static*/ /*final*/ int FunctionsHelpDialog::panelWidth = 500;
    /*private*/ /*static*/ /*final*/ int panelHeight = 500;

    /*private*/ /*static*/ /*final*/ QMap<QString, Module*> FunctionsHelpDialog::_modules = QMap<QString, Module*>();



    /*public*/  FunctionsHelpDialog::FunctionsHelpDialog(QObject* parent) {
        FunctionManager* fm = (FunctionManager*)InstanceManager::getDefault("FunctionManager");
        //for (Map.Entry<String, Function> entry : fm.getFunctions().entrySet())
        QMapIterator<QString, Function*> entry(fm->getFunctions());
        while(entry.hasNext())
        {
         entry.next();
//            System.out.format("Existing functions: %s, %s%n", entry.getValue().getModule(), entry.getValue().getName());
            Module* m = _modules.value(entry.value()->getModule());
#if 0
            if (m == nullptr) {
                m = new Module(entry.value()->getModule(), entry.value()->getConstantDescriptions());
                _modules.insert(m->_name, m);
            }
            m->_functions.append(entry.value());
#endif
        }
    }

    /*public*/  void showDialog() {
        #if 0
        if (_selectItemTypeDialog != null) {
            _selectItemTypeDialog.requestFocus();
            return;
        }

        _documentationEditorPane.setEditable(false);
        _documentationEditorPane.setContentType("text/html");

        _moduleComboBox.removeAllItems();
        List<Module> list = new ArrayList<>(_modules.values());
        Collections.sort(list);
        for (Module module : list) {
            _moduleComboBox.addItem(module);
        }
        JComboBoxUtil.setupComboBoxMaxRows(_moduleComboBox);
        _moduleComboBox.addActionListener((ActionEvent e) -> {
            initFunctionsComboBox();
        });

        _functionComboBox.addActionListener((ActionEvent e) -> {
            if (_functionComboBox.getSelectedIndex() > -1) {
                SortableFunction f = _functionComboBox
                        .getItemAt(_functionComboBox.getSelectedIndex());
                _documentationEditorPane.setText(f._functionDescr);
                _documentationEditorPane.setCaretPosition(0);
            } else {
                _documentationEditorPane.setText("");
            }
        });

        if (_moduleComboBox.getItemCount() > 0) {
            _moduleComboBox.setSelectedIndex(0);
        }

        _selectItemTypeDialog  = new JDialog(
                (JDialog)null,
                Bundle.getMessage("FunctionsHelpDialogTitle"),
                true);


        Container contentPanel = _selectItemTypeDialog.getContentPane();
        contentPanel.setLayout(new BoxLayout(contentPanel, BoxLayout.Y_AXIS));

        JPanel p;
        p = new JPanel();
//        p.setLayout(new FlowLayout());
        p.setLayout(new java.awt.GridBagLayout());
        java.awt.GridBagConstraints c = new java.awt.GridBagConstraints();
        c.gridwidth = 1;
        c.gridheight = 1;
        c.gridx = 0;
        c.gridy = 0;
        c.anchor = java.awt.GridBagConstraints.EAST;
        p.add(_moduleLabel, c);
        c.gridy = 1;
        p.add(_functionLabel, c);
        c.gridx = 1;
        c.gridy = 0;
        c.anchor = java.awt.GridBagConstraints.WEST;
        c.weightx = 1.0;
        c.fill = java.awt.GridBagConstraints.HORIZONTAL;  // text field will expand
        p.add(_moduleComboBox, c);
        c.gridy = 1;
        c.fill = java.awt.GridBagConstraints.BOTH;  // text field will expand
        p.add(_functionComboBox, c);

        c.gridx = 0;
        c.gridy = 2;
        c.gridwidth = 2;

        JScrollPane documentationScroller = new JScrollPane(_documentationEditorPane);
        documentationScroller.setPreferredSize(new Dimension(panelWidth, panelHeight));
        documentationScroller.setAlignmentX(LEFT_ALIGNMENT);
        documentationScroller.setAlignmentY(TOP_ALIGNMENT);
        p.add(documentationScroller, c);

//        _categoryComboBox.setToolTipText(jmri.jmrit.logixng.tools.swing.Bundle.getMessage("CategoryNamesHint"));    // NOI18N
//        _swingConfiguratorComboBox.setToolTipText(jmri.jmrit.logixng.tools.swing.Bundle.getMessage("TypeNamesHint"));   // NOI18N
        contentPanel.add(p);
        // set up message
        JPanel panel3 = new JPanel();
        panel3.setLayout(new BoxLayout(panel3, BoxLayout.Y_AXIS));

        contentPanel.add(panel3);

        // set up create and cancel buttons
        JPanel panel5 = new JPanel();
        panel5.setLayout(new FlowLayout());
        // Cancel
        JButton cancel = new JButton(Bundle.getMessage("ButtonCancel"));    // NOI18N
        panel5.add(cancel);
        cancel.addActionListener((ActionEvent e) -> {
            cancelAddPressed(null);
        });
//        cancel.setToolTipText(Bundle.getMessage("CancelLogixButtonHint"));      // NOI18N
        cancel.setToolTipText("CancelLogixButtonHint");      // NOI18N

        _selectItemTypeDialog.addWindowListener(new java.awt.event.WindowAdapter() {
            //@Override
            /*public*/  void windowClosing(java.awt.event.WindowEvent e) {
                cancelAddPressed(null);
            }
        });
/*
        _create = new JButton(Bundle.getMessage("ButtonCreate"));  // NOI18N
        panel5.add(_create);
        _create.addActionListener((ActionEvent e) -> {
            cancelAddPressed(null);

            SwingConfiguratorInterface swingConfiguratorInterface =
                    _swingConfiguratorComboBox.getItemAt(_swingConfiguratorComboBox.getSelectedIndex());
//            System.err.format("swingConfiguratorInterface: %s%n", swingConfiguratorInterface.getClass().getName());
            createAddFrame(femaleSocket, path, swingConfiguratorInterface);
        });
*/
        contentPanel.add(panel5);

        _selectItemTypeDialog.setMinimumSize(new Dimension(panelWidth, panelHeight));

//        addLogixNGFrame.setLocationRelativeTo(component);
        _selectItemTypeDialog.setLocationRelativeTo(null);
        _selectItemTypeDialog.pack();
        _selectItemTypeDialog.setVisible(true);
#endif
    }
    #if 0
    /*final*/ protected void cancelAddPressed(ActionEvent e) {
        _selectItemTypeDialog.setVisible(false);
        _selectItemTypeDialog.dispose();
        _selectItemTypeDialog = null;
    }

    /*private*/ void initFunctionsComboBox() {
        _functionComboBox.removeAllItems();

        if (_moduleComboBox.getSelectedIndex() > -1) {
            Module module = _moduleComboBox.getItemAt(_moduleComboBox.getSelectedIndex());
            List<SortableFunction> list = new ArrayList<>();
            if (module._constantDescriptions != null) {
                list.add(new SortableFunction(Bundle.getMessage("FunctionsHelpDialog_Constants"), module._constantDescriptions));
            }
            for (Function f : module._functions) {
                list.add(new SortableFunction(f.getName(), f.getDescription()));
            }
            Collections.sort(list);
            for (SortableFunction function : list) {
                _functionComboBox.addItem(function);
            }
            JComboBoxUtil.setupComboBoxMaxRows(_functionComboBox);
        }
    }




    /*private*/ static class Module implements Comparable<Module> {

        /*private*/ /*final*/ String _name;
        /*private*/ /*final*/ String _constantDescriptions;
        /*private*/ /*final*/ List<Function> _functions = new ArrayList<>();

        /*private*/ Module(String name, String constantDescriptions) {
            _name = name;
            _constantDescriptions = constantDescriptions;
        }

        //@Override
        /*public*/  boolean equals(Object o) {
            return (o instanceof Module) && _name.equals(((Module)o)._name);
        }

        //@Override
        /*public*/  int hashCode() {
            int hash = 7;
            hash = 47 * hash + Objects.hashCode(this._name);
            return hash;
        }

        //@Override
        /*public*/  int compareTo(Module o) {
            return _name.compareTo(o._name);
        }

        //@Override
        /*public*/  String toString() {
            return _name;
        }
    }

    /*private*/ static class SortableFunction implements Comparable<SortableFunction> {

        /*private*/ /*final*/ String _name;
        /*private*/ /*final*/ String _functionDescr;

        /*private*/ SortableFunction(String name, String functionDescr) {
            _name = name;
            _functionDescr = functionDescr;
        }

        //@Override
        /*public*/  boolean equals(Object o) {
            return (o instanceof SortableFunction) && _name.equals(((SortableFunction)o)._name);
        }

        //@Override
        /*public*/  int hashCode() {
            int hash = 7;
            hash = 47 * hash + Objects.hashCode(this._name);
            return hash;
        }

        //@Override
        /*public*/  int compareTo(SortableFunction o) {
            return _name.compareTo(o._name);
        }

        //@Override
        /*public*/  String toString() {
            return _name;
        }
    }
    #endif
