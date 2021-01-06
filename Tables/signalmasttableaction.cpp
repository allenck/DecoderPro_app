#include "signalmasttableaction.h"
#include "jtable.h"
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include "signalmastrepeaterjframe.h"
#include "signalmasttabledatamodel.h"
#include "addsignalmastjframe.h"
#include "mysortfilterproxymodel.h"

SignalMastTableAction::SignalMastTableAction(QObject*parent)
    : AbstractTableAction(tr("Signal Mast Table"), parent)
{

}
/**
 * Swing action to create and register a SignalMastTable GUI.
 *
 * @author	Bob Jacobsen Copyright (C) 2003, 2009, 2010
 */
///*public*/ class SignalMastTableAction extends AbstractTableAction {

/**
 * Create an action with a specific title.
 * <P>
 * Note that the argument is the Action title, not the title of the
 * resulting frame. Perhaps this should be changed?
 *
 * @param actionName title of the action
 */
/*public*/ SignalMastTableAction::SignalMastTableAction(QString actionName, QObject* parent)
    : AbstractTableAction(actionName, parent)
{
   //super(actionName);
 addFrame = NULL;

}

///*public*/ SignalMastTableAction() {
//    this(tr("TitleSignalMastTable"));
//}

/**
 * Create the JTable DataModel, along with the changes for the specific case
 * of Sensors
 */
/*protected*/ void SignalMastTableAction::createModel() {
    m = new SignalMastTableDataModel();
}

/*protected*/ void SignalMastTableAction::setTitle() {
    f->setTitle(tr("Signal Mast Table"));
}

/*protected*/ QString SignalMastTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.SignalMastTable";
}

/*public*/ void SignalMastTableAction::actionPerformed(JActionEvent * /*e*/) {
    // create the JTable model, with changes for specific NamedBean
    createModel();
    MySortFilterProxyModel* sorter = new MySortFilterProxyModel(m);
    JTable* dataTable = m->makeJTable(sorter);
    //sorter.setTableHeader(dataTable.getTableHeader());
    m->setColumnToHoldButton(dataTable, SignalMastTableDataModel::EDITMASTCOL);
    m->setColumnToHoldButton(dataTable, SignalMastTableDataModel::EDITLOGICCOL);

    // create the frame
    f = new SMTBeanTableFrame(m, helpTarget(), dataTable, this);
    setTitle();
    addToFrame(f);
    f->adjustSize();
    f->setVisible(true);
}
SMTBeanTableFrame::SMTBeanTableFrame(BeanTableDataModel *m, QString helpTarget, JTable * dataTable, SignalMastTableAction* act)
    : BeanTableFrame(m, helpTarget, dataTable)
{
  this->act = act;
}

/**
 * Include an "add" button
 */
void SMTBeanTableFrame::extras() {
    QPushButton* addButton = new QPushButton(tr("Add"));
    addToBottomBox(addButton, this->metaObject()->className());
//    addButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            addPressed(e);
//        }
    connect(addButton, SIGNAL(clicked()), act, SLOT(addPressed()));
}

/*protected*/ void SignalMastTableAction::addPressed(JActionEvent* /*e*/) {
    if (addFrame == NULL) {
        addFrame = new AddSignalMastJFrame();
    } else {
        addFrame->refresh();
    }
    addFrame->setVisible(true);
}

/*public*/ void SignalMastTableAction::setMenuBar(BeanTableFrame* f) {
    QMenuBar* menuBar = f->menuBar();
    QMenu* pathMenu = new QMenu(tr("Tools"));
    menuBar->addMenu(pathMenu);
    QAction* item = new QAction(tr("Repeaters"),this);
    pathMenu->addAction(item);
//    item.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            jmri.jmrit.beantable.signalmast.SignalMastRepeaterJFrame frame = new jmri.jmrit.beantable.signalmast.SignalMastRepeaterJFrame();
//            frame.setVisible(true);
//        }
//    });
    connect(item, SIGNAL(triggered(bool)), this, SLOT(On_repeatersTriggered()));
}

void SignalMastTableAction::On_repeatersTriggered()
{
 SignalMastRepeaterJFrame* frame = new SignalMastRepeaterJFrame();
                frame->setVisible(true);

}
#if 0

/*public*/ static class MyComboBoxRenderer extends JComboBox<QString> implements TableCellRenderer {

    /*public*/ MyComboBoxRenderer(Vector<QString> items) {
        super(items);
    }

    /*public*/ Component getTableCellRendererComponent(JTable table, Object value,
            boolean isSelected, boolean hasFocus, int row, int column) {
        if (isSelected) {
            setForeground(table.getSelectionForeground());
            super.setBackground(table.getSelectionBackground());
        } else {
            setForeground(table.getForeground());
            setBackground(table.getBackground());
        }

        // Select the current value
        setSelectedItem(value);
        return this;
    }
}

/*public*/ static class MyComboBoxEditor extends DefaultCellEditor {

    /*public*/ MyComboBoxEditor(Vector<QString> items) {
        super(new JComboBox<QString>(items));
    }
}
#endif
/*protected*/ QString SignalMastTableAction::getClassName() {
    return "jmri.jmrit.beantable.SignalMastTableAction";
}

/*public*/ QString SignalMastTableAction::getClassDescription() {
    return tr("Signal Group Table");
}
