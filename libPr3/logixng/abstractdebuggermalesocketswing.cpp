#include "abstractdebuggermalesocketswing.h"
#include "instancemanager.h"
#include "exceptions.h"

/**
 * Abstract class for SwingConfiguratorInterface
 */
// /*public*/  abstract class AbstractDebuggerMaleSocketSwing extends AbstractSwingConfigurator {


    /** {@inheritDoc} */
    //@Override
    /*public*/  BaseManager/*<? extends NamedBean>*/* AbstractDebuggerMaleSocketSwing::getManager() {
        throw new UnsupportedOperationException("Not supported");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  /*final*/ JPanel* AbstractDebuggerMaleSocketSwing::getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ {
        createPanel(nullptr, buttonPanel);
        return panel;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  /*final*/ JPanel* AbstractDebuggerMaleSocketSwing::getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ {
        createPanel(object, buttonPanel);
        return panel;
    }

    /*protected*/ /*final*/ void AbstractDebuggerMaleSocketSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        if ((object != nullptr) && (! (qobject_cast<MaleSocket*>(object->bself()))) ){
            throw new IllegalArgumentException(QString("object is not a MaleSocket: ") + object->bself()->metaObject()->className());
        }
        panel = new JPanel();
/*
        MaleSocket maleSocket = (MaleSocket)object;
        int row = 0;
        panel.setLayout(new java.awt.GridBagLayout());
        java.awt.GridBagConstraints c = new java.awt.GridBagConstraints();
        c.gridwidth = 1;
        c.gridheight = 1;
        c.gridx = 0;
        c.anchor = java.awt.GridBagConstraints.EAST;
        JPanel* subPanel = createSubPanel(object, buttonPanel);
        if (subPanel != null) {
            c.gridy = row++;
            panel.add(subPanel, c);
        }
        createTablePanel(maleSocket, buttonPanel);
        c.gridy = row;
        panel.add(tablePanel, c);
*/
    }
/*
    private void createTablePanel(MaleSocket maleSocket, @Nonnull JPanel* buttonPanel) {
        tablePanel = new JPanel();
        table = new JTable();
        tableModel = new LocalVariableTableModel(maleSocket);
        table.setModel(tableModel);
        table.setDefaultRenderer(InitialValueType.class,
                new LocalVariableTableModel.TypeCellRenderer());
        table.setDefaultEditor(InitialValueType.class,
                new LocalVariableTableModel.TypeCellEditor());
        table.setDefaultRenderer(LocalVariableTableModel.Menu.class,
                new LocalVariableTableModel.MenuCellRenderer());
        table.setDefaultEditor(LocalVariableTableModel.Menu.class,
                new LocalVariableTableModel.MenuCellEditor(table, tableModel));
        tableModel.setColumnForMenu(table);
        JScrollPane scrollpane = new JScrollPane(table);
        scrollpane.setPreferredSize(new Dimension(400, 200));
        tablePanel.add(scrollpane, BorderLayout.CENTER);
        JButton add = new JButton(Bundle.getMessage("TableAddVariable"));
        buttonPanel.add(add);
        add.addActionListener((ActionEvent e) -> {
            tableModel.add();
        });
    }
*/
    /** {@inheritDoc} */
    //@Override
    /*public*/  /*final*/ bool AbstractDebuggerMaleSocketSwing::validate(/*@Nonnull*/ QList<QString> *errorMessages) {
        return true;
    }

    /**
     * The sub class may override this method to add more detail to the panel.
     * @param object the object for which to return a configuration panel
     * @param buttonPanel panel with the buttons
     * @return a panel that configures this object
     */
    /*protected*/ JPanel* AbstractDebuggerMaleSocketSwing::createSubPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        return nullptr;
    }

    /**
     * If the sub class overrides createSubPanel(), it may use this method to
     * validate the sub panel.
     * <P>
     * The parameter errorMessage is used to give the error message in case of
     * an error. If there are errors, the error messages is added to the list
     * errorMessage.
     *
     * @param errorMessages the error messages in case of an error
     * @return true if data in the form is valid, false otherwise
     */
    /*public*/  bool AbstractDebuggerMaleSocketSwing::validateSubPanel(/*@Nonnull*/ QList<QString> errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* AbstractDebuggerMaleSocketSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        throw new UnsupportedOperationException("Not supported");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  /*final*/ void AbstractDebuggerMaleSocketSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<MaleSocket*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object is not a MaleSocket: ") + object->bself()->metaObject()->className());
        }
/*
        MaleSocket maleSocket = (MaleSocket)object;
        maleSocket.clearLocalVariables();
        for (VariableData variableData : tableModel.getVariables()) {
            maleSocket.addLocalVariable(variableData);
        }
*/
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractDebuggerMaleSocketSwing::getExampleSystemName() {
        throw new UnsupportedOperationException("Not supported");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractDebuggerMaleSocketSwing::getAutoSystemName() {
        throw new UnsupportedOperationException("Not supported");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractDebuggerMaleSocketSwing::toString() {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  /*final*/ void AbstractDebuggerMaleSocketSwing::dispose() {
    }
