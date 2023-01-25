#include "actionlistenonbeansswing.h"
#include "actionlistenonbeans.h"
#include "listenonbeanstablemodel.h"
#include "jtable.h"
#include "tablecolumnmodel.h"
#include "tablecolumn.h"
#include "defaultdigitalactionmanager.h"

ActionListenOnBeansSwing::ActionListenOnBeansSwing(QObject *parent) : AbstractDigitalActionSwing(parent)
{
 setObjectName("ActionListenOnBeansSwing");
}
/**
 * Configures an ActionListenOnBeans object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class ActionListenOnBeansSwing extends AbstractDigitalActionSwing {


    //@Override
    /*protected*/ void ActionListenOnBeansSwing::createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        if ((object != nullptr) && (! (qobject_cast<ActionListenOnBeans*>(object->bself())))) {
            throw new IllegalArgumentException(QString("object is not a Module: ") + object->bself()->metaObject()->className());
        }
        ActionListenOnBeans* listenOnBeans = nullptr;
        if(object)
         listenOnBeans = (ActionListenOnBeans*)object->bself();

        panel = new JPanel();

        panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));

        JPanel* tablePanel = new JPanel(new FlowLayout());
        _listenOnBeansTable = new JTable();

        if (listenOnBeans != nullptr) {
            QList<ActionListenOnBeans::NamedBeanReference*>* namedBeanReference
                    = new QList<ActionListenOnBeans::NamedBeanReference*>(listenOnBeans->getReferences());
#if 0 // TODO:
            namedBeanReference.sort((o1, o2) -> {
                int result = o1.getType().toString().compareTo(o2.getType().toString());
                if (result == 0) result = o1.getName().compareTo(o2.getName());
                return result;
            });
#endif
            _listenOnBeansTableModel = new ListenOnBeansTableModel(namedBeanReference);
        } else {
            _listenOnBeansTableModel = new ListenOnBeansTableModel(nullptr);
        }

        _listenOnBeansTable->setModel(_listenOnBeansTableModel);
//        _listenOnBeansTable.setDefaultRenderer(NamedBeanType.class,
//                new ListenOnBeansTableModel.CellRenderer());
//        _listenOnBeansTable.setDefaultEditor(NamedBeanType.class,
//                new ListenOnBeansTableModel.NamedBeanTypeCellEditor());
//        _listenOnBeansTable.setDefaultEditor(String.class,
//                _listenOnBeansTableModel.getNamedBeanCellEditor());
        _listenOnBeansTableModel->setColumnsForComboBoxes(_listenOnBeansTable);
        _listenOnBeansTable->setDefaultRenderer("JButton", new ButtonRenderer());
        _listenOnBeansTable->setDefaultEditor("JButton", new ButtonEditor(new JButton()));

        JButton* testButton = new JButton("XXXXXX");  // NOI18N
//        _listenOnBeansTable.setRowHeight(testButton.getPreferredSize().height);
        TableColumn* deleteColumn = _listenOnBeansTable->getColumnModel()
                ->getColumn(ListenOnBeansTableModel::COLUMN_DUMMY);
        deleteColumn->setMinWidth(testButton->sizeHint().width());
        deleteColumn->setMaxWidth(testButton->sizeHint().width());
        deleteColumn->setResizable(false);

        // The dummy column is used to be able to force update of the
        // other columns when the panel is closed.
        TableColumn* dummyColumn = _listenOnBeansTable->getColumnModel()
                ->getColumn(ListenOnBeansTableModel::COLUMN_DUMMY);
        dummyColumn->setMinWidth(0);
        dummyColumn->setPreferredWidth(0);
        dummyColumn->setMaxWidth(0);

//        JScrollPane scrollpane = new JScrollPane(_listenOnBeansTable);
//        scrollpane.setPreferredSize(new Dimension(400, 200));
        tablePanel->layout()->addWidget(/*scrollpane*/_listenOnBeansTable);//, BorderLayout.CENTER);
        panel->layout()->addWidget(tablePanel);

        // Add parameter
        JButton* add = new JButton(tr("Add reference"));
        buttonPanel->layout()->addWidget(add);
        connect(add, &JButton::clicked, [=] {
            _listenOnBeansTableModel->add();
        });
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ActionListenOnBeansSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* ActionListenOnBeansSwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
        ActionListenOnBeans* action = new ActionListenOnBeans(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionListenOnBeansSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ActionListenOnBeans*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object is not a Module: ") + object->bself()->metaObject()->className());
        }
        ActionListenOnBeans* listenOnBeans = (ActionListenOnBeans*)object->bself();

        // Do this to force update of the table
//        _listenOnBeansTable.editCellAt(0, 2);

        listenOnBeans->clearReferences();

        for (ActionListenOnBeans::NamedBeanReference* reference : *_listenOnBeansTableModel->getReferences()) {
            listenOnBeans->addReference(reference);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ActionListenOnBeansSwing::toString() {
        return tr("Listen on beans");
    }

    //@Override
    /*public*/  void ActionListenOnBeansSwing::dispose() {
    }
