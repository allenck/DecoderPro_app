#include "tableforeachswing.h"
#include "tableforeach.h"
#include "tableroworcolumn.h"
#include "defaultnamedtablemanager.h"
#include "instancemanager.h"
#include "parserexception.h"
#include "defaultdigitalactionmanager.h"
#include "namedbeanhandlemanager.h"

/**
 * Configures an TableForEach object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class TableForEachSwing extends AbstractDigitalActionSwing {



    //@Override
    /*protected*/ void TableForEachSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        if ((object != nullptr) && !(qobject_cast<TableForEach*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an TableForEach but is a: ")+object->bself()->metaObject()->className());
        }

        TableForEach* action = nullptr;
        if(object)
         action = (TableForEach*)object->bself();

        panel = new JPanel();
        panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));

        _panelRowOrColumnLabel = new JLabel(tr("Row"));

        _tableRowOrColumnComboBox = new JComboBox();
        for (TableRowOrColumn::TYPE item : TableRowOrColumn::values()) {
            _tableRowOrColumnComboBox->addItem(item);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_tableRowOrColumnComboBox);
//        _tableRowOrColumnComboBox.addActionListener((evt) -> {
        connect(_tableRowOrColumnComboBox, &JComboBox::currentIndexChanged, [=]{
            setupRowOrColumnNameComboBox(action != nullptr ? action->getRowOrColumnName() : nullptr);

            if (_tableRowOrColumnComboBox->getItemAt(_tableRowOrColumnComboBox->getSelectedIndex()) == TableRowOrColumn::Row) {
                _panelRowOrColumnLabel->setText(tr("Row"));
            } else {
                _panelRowOrColumnLabel->setText(tr("Column"));
            }
        });

        JPanel* tableRowOrColumnPanel = new JPanel(new FlowLayout());
        tableRowOrColumnPanel->layout()->addWidget(new JLabel(tr("Row or column")));
        tableRowOrColumnPanel->layout()->addWidget(_tableRowOrColumnComboBox);
        panel->layout()->addWidget(tableRowOrColumnPanel);

        JPanel* tabbedPanesPanel = new JPanel();
        tabbedPanesPanel->setLayout(new QHBoxLayout());//tabbedPanesPanel, BoxLayout.X_AXIS));

        _tabbedTablePane = new JTabbedPane();
        _panelTable = new JPanel(new FlowLayout);
        _panelReference = new JPanel(new FlowLayout);
        _panelLocalVariable = new JPanel(new FlowLayout);
        _panelFormula = new JPanel(new FlowLayout);

        _tabbedTablePane->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelTable);
        _tabbedTablePane->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelReference);
        _tabbedTablePane->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelLocalVariable);
        _tabbedTablePane->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelFormula);

        //_tabbedTablePane->addChangeListener((evt) -> {
        connect(_tabbedTablePane, &JTabbedPane::currentChanged, [=]{
            bool isPanelTable = (_tabbedTablePane->getSelectedComponent() == _panelTable);
            _rowOrColumnNameComboBox->setVisible(isPanelTable);
            _rowOrColumnNameTextField->setVisible(!isPanelTable);
        });

        tableBeanPanel = new BeanSelectPanel((DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager"), nullptr);
        _panelTable->layout()->addWidget(tableBeanPanel);

        //tableBeanPanel->getBeanCombo().addActionListener((evt) -> {
         connect(tableBeanPanel->getBeanCombo(), &JComboBox::currentIndexChanged, [=]{
            setupRowOrColumnNameComboBox(action != nullptr ? action->getRowOrColumnName() : nullptr);
        });

        _referenceTextField = new JTextField();
        _referenceTextField->setColumns(20);
        _panelReference->layout()->addWidget(_referenceTextField);

        _localVariableTextField = new JTextField();
        _localVariableTextField->setColumns(20);
        _panelLocalVariable->layout()->addWidget(_localVariableTextField);

        _formulaTextField = new JTextField();
        _formulaTextField->setColumns(20);
        _panelFormula->layout()->addWidget(_formulaTextField);

        tabbedPanesPanel->layout()->addWidget(new JLabel(tr("Table")));

        tabbedPanesPanel->layout()->addWidget(_tabbedTablePane);

        _tabbedRowOrColumnPane = new JTabbedPane();
        _panelRowOrColumnName = new JPanel(new FlowLayout);
        _panelRowOrColumnReference = new JPanel(new FlowLayout);
        _panelRowOrColumnLocalVariable = new JPanel(new FlowLayout());
        _panelRowOrColumnFormula = new JPanel(new FlowLayout());

        _tabbedRowOrColumnPane->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelRowOrColumnName);
        _tabbedRowOrColumnPane->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelRowOrColumnReference);
        _tabbedRowOrColumnPane->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelRowOrColumnLocalVariable);
        _tabbedRowOrColumnPane->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelRowOrColumnFormula);

        _rowOrColumnNameComboBox = new JComboBox();
        _panelRowOrColumnName->layout()->addWidget(_rowOrColumnNameComboBox);
        _rowOrColumnNameTextField = new JTextField(20);
        _rowOrColumnNameTextField->setVisible(false);
        _panelRowOrColumnName->layout()->addWidget(_rowOrColumnNameTextField);
//        JComboBoxUtil->setupComboBoxMaxRows(_rowOrColumnNameComboBox);

        _referenceRowOrColumnTextField = new JTextField();
        _referenceRowOrColumnTextField->setColumns(20);
        _panelRowOrColumnReference->layout()->addWidget(_referenceRowOrColumnTextField);

        _localRowOrColumnVariableTextField = new JTextField();
        _localRowOrColumnVariableTextField->setColumns(20);
        _panelRowOrColumnLocalVariable->layout()->addWidget(_localRowOrColumnVariableTextField);

        _formulaRowOrColumnTextField = new JTextField();
        _formulaRowOrColumnTextField->setColumns(20);
        _panelRowOrColumnFormula->layout()->addWidget(_formulaRowOrColumnTextField);

        tabbedPanesPanel->layout()->addWidget(_panelRowOrColumnLabel);

        tabbedPanesPanel->layout()->addWidget(_tabbedRowOrColumnPane);

        panel->layout()->addWidget(tabbedPanesPanel);

        JPanel* localVariablePanel = new JPanel(new FlowLayout());
        localVariablePanel->layout()->addWidget(new JLabel(tr("Local variable")));
        _localVariable = new JTextField(20);
        localVariablePanel->layout()->addWidget(_localVariable);
        panel->layout()->addWidget(localVariablePanel);

        if (action != nullptr) {
            _tableRowOrColumnComboBox->setSelectedItem(action->getRowOrColumn());

            switch (action->getAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedTablePane->setSelectedComponent(_panelTable); break;
                case NamedBeanAddressing::Reference: _tabbedTablePane->setSelectedComponent(_panelReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedTablePane->setSelectedComponent(_panelLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedTablePane->setSelectedComponent(_panelFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }

            if (action->getTable() != nullptr) {
                tableBeanPanel->setDefaultNamedBean(action->getTable()->getBean());
            }

            _referenceTextField->setText(action->getTableReference());
            _localVariableTextField->setText(action->getTableLocalVariable());
            _formulaTextField->setText(action->getTableFormula());

            switch (action->getRowOrColumnAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedRowOrColumnPane->setSelectedComponent(_panelRowOrColumnName); break;
                case NamedBeanAddressing::Reference: _tabbedRowOrColumnPane->setSelectedComponent(_panelRowOrColumnReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedRowOrColumnPane->setSelectedComponent(_panelRowOrColumnLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedRowOrColumnPane->setSelectedComponent(_panelRowOrColumnFormula); break;
                default: throw new IllegalArgumentException("invalid _rowOrColumnAddressing state: " + NamedBeanAddressing::toString(action->getRowOrColumnAddressing()));
            }

            _rowOrColumnNameTextField->setText(action->getRowOrColumnName());
            _referenceRowOrColumnTextField->setText(action->getRowOrColumnReference());
            _localRowOrColumnVariableTextField->setText(action->getRowOrColumnLocalVariable());
            _formulaRowOrColumnTextField->setText(action->getRowOrColumnFormula());

            _localVariable->setText(action->getLocalVariableName());
        }
    }

    /*private*/ void TableForEachSwing::setupRowOrColumnNameComboBox(QString rowOrColumnName) {
        _rowOrColumnNameComboBox->clear();
        NamedTable* table;
        NamedBean* nb = tableBeanPanel->getNamedBean();
        if (nb != nullptr) {
         table = (NamedTable*)nb->self();
            if (_tableRowOrColumnComboBox->getItemAt(_tableRowOrColumnComboBox->getSelectedIndex()) == TableRowOrColumn::Column) {
                for (int column=0; column <= table->numColumns(); column++) {
                    // If the header is null or empty, treat the row as a comment
                    QVariant header = table->getCell(0, column);
                    if ((header != QVariant()) && (!header.toString().isEmpty())) {
                        _rowOrColumnNameComboBox->addItem(header.toString());
                    }
                }
            } else {
                for (int row=0; row <= table->numRows(); row++) {
                    // If the header is null or empty, treat the row as a comment
                    QVariant header = table->getCell(row, 0);
                    if ((header != QVariant()) && (!header.toString().isEmpty())) {
                        _rowOrColumnNameComboBox->addItem(header.toString());
                    }
                }
            }
            _rowOrColumnNameComboBox->setSelectedItem(rowOrColumnName);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool TableForEachSwing::validate(/*@Nonnull*/ QList<QString> *errorMessages) {
        // Create a temporary action to test formula
        TableForEach* action = new TableForEach("IQDA1", "");

        try {
            if (_tabbedTablePane->getSelectedComponent() == _panelTable) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedTablePane->getSelectedComponent() == _panelReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedTablePane->getSelectedComponent() == _panelLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedTablePane->getSelectedComponent() == _panelFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
                action->setTableFormula(_formulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPane has unknown selection");
            }

            if (_tabbedRowOrColumnPane->getSelectedComponent() == _panelRowOrColumnName) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedRowOrColumnPane->getSelectedComponent() == _panelRowOrColumnReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedRowOrColumnPane->getSelectedComponent() == _panelRowOrColumnLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedRowOrColumnPane->getSelectedComponent() == _panelRowOrColumnFormula) {
                action->setRowOrColumnFormula(_formulaRowOrColumnTextField->text());
                action->setAddressing(NamedBeanAddressing::Formula);
            } else {
                throw new IllegalArgumentException("_tabbedRowOrColumnPane has unknown selection");
            }
        } catch (ParserException* e) {
            errorMessages->append("Cannot parse formula: " + e->getMessage());
            return false;
        }
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* TableForEachSwing::createNewObject(/*@Nonnull */QString systemName,  QString userName) {
        TableForEach* action = new TableForEach(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void TableForEachSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (!(qobject_cast<TableForEach*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an TableForEach but is a: ")+object->bself()->metaObject()->className());
        }


        TableForEach* action = (TableForEach*)object->bself();
        action->setRowOrColumn((TableRowOrColumn::TYPE)_tableRowOrColumnComboBox->getItemAt(_tableRowOrColumnComboBox->getSelectedIndex()).toInt());

        try {
            if (_tabbedTablePane->getSelectedComponent() == _panelTable) {
                action->setAddressing(NamedBeanAddressing::Direct);
                NamedTable* table;
                NamedBean* nb = tableBeanPanel->getNamedBean();
                if (nb != nullptr) {
                 table = (NamedTable*)nb->self();
                    NamedBeanHandle<NamedTable*>* handle
                            = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                    ->getNamedBeanHandle(table->getDisplayName(), table);
                    action->setTable(handle);
                } else {
                    action->removeTable();
                }
            } else if (_tabbedTablePane->getSelectedComponent() == _panelReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
                action->setTableReference(_referenceTextField->text());
            } else if (_tabbedTablePane->getSelectedComponent() == _panelLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
                action->setTableLocalVariable(_localVariableTextField->text());
            } else if (_tabbedTablePane->getSelectedComponent() == _panelFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
                action->setTableFormula(_formulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneTurnoutState has unknown selection");
            }

            if (_tabbedRowOrColumnPane->getSelectedComponent() == _panelRowOrColumnName) {
                action->setRowOrColumnAddressing(NamedBeanAddressing::Direct);
                if (_tabbedTablePane->getSelectedComponent() == _panelTable) {
                    if (_rowOrColumnNameComboBox->getSelectedIndex() != -1) {
                        action->setRowOrColumnName(_rowOrColumnNameComboBox->getItemAt(_rowOrColumnNameComboBox->getSelectedIndex()).toString());
                    } else {
                        action->setRowOrColumnName("");
                    }
                } else {
                    action->setRowOrColumnName(_rowOrColumnNameTextField->text());
                }
            } else if (_tabbedRowOrColumnPane->getSelectedComponent() == _panelRowOrColumnReference) {
                action->setRowOrColumnAddressing(NamedBeanAddressing::Reference);
                action->setRowOrColumnReference(_referenceRowOrColumnTextField->text());
            } else if (_tabbedRowOrColumnPane->getSelectedComponent() == _panelRowOrColumnLocalVariable) {
                action->setRowOrColumnAddressing(NamedBeanAddressing::LocalVariable);
                action->setRowOrColumnLocalVariable(_localRowOrColumnVariableTextField->text());
            } else if (_tabbedRowOrColumnPane->getSelectedComponent() == _panelRowOrColumnFormula) {
                action->setRowOrColumnAddressing(NamedBeanAddressing::Formula);
                action->setRowOrColumnFormula(_formulaRowOrColumnTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneTurnoutState has unknown selection");
            }

            action->setLocalVariableName(_localVariable->text());
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: " + e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString TableForEachSwing::toString() {
        return tr("TableForEach");
    }

    //@Override
    /*public*/  void TableForEachSwing::dispose() {
    }

