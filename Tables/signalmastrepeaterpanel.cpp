#include "signalmastrepeaterpanel.h"
#include "defaultsignalmastmanager.h"
#include "instancemanager.h"
#include "propertychangeevent.h"
#include <QBoxLayout>
#include "jtable.h"
#include "signalmastrepeaterpanel.h"
#include "signalmastrepeater.h"
#include "jtextfield.h"
#include "tablecolumn.h"
#include "tablecolumnmodel.h"

//SignalMastRepeaterPanel::SignalMastRepeaterPanel()
//{

//}
/**
 * Frame for Signal Mast Add / Edit Panel
 *
 * @author	Kevin Dickerson Copyright (C) 2011
 * @version $Revision: 20084 $
 */
///*public*/ class SignalMastRepeaterPanel extends jmri.util.swing.JmriPanel implements PropertyChangeListener {

/**
 *
 */
//private static final long serialVersionUID = -9220621583127217095L;



/*public*/ SignalMastRepeaterPanel::SignalMastRepeaterPanel(QWidget* parent) : JmriPanel(parent)
{
    //super();
    dsmm = static_cast<DefaultSignalMastManager*>(InstanceManager::getDefault("SignalMastManager"));
    //dsmm.addPropertyChangeListener(this);
    connect(dsmm->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

    //setLayout(new BorderLayout());
    QVBoxLayout* thisLayout = new QVBoxLayout(this);

    QWidget* header = new QWidget();
    QVBoxLayout* headerLayout = new QVBoxLayout(header);
    //header.setLayout(new BoxLayout(header, BoxLayout.Y_AXIS));

    QWidget* sourcePanel = new QWidget();

    headerLayout->addWidget(sourcePanel);
    thisLayout->addWidget(header, /*BorderLayout.NORTH*/0, Qt::AlignTop);

    _RepeaterModel = new SignalMastRepeaterModel(this);
#if 0
    JTable* _RepeaterTable = JTableUtil::sortableDataModel(_RepeaterModel);

    try {
        jmri.util.com.sun.TableSorter tmodel = ((jmri.util.com.sun.TableSorter) _RepeaterTable.getModel());
        tmodel.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
        tmodel.setSortingStatus(SignalMastRepeaterModel.DIR_COLUMN, jmri.util.com.sun.TableSorter.ASCENDING);
    } catch (ClassCastException e3) {
    }  // if not a sortable table model

    _RepeaterTable.setRowSelectionAllowed(false);
    _RepeaterTable.setPreferredScrollableViewportSize(new java.awt.Dimension(526, 120));
    _RepeaterModel.configureTable(_RepeaterTable);
    _SignalAppearanceScrollPane = new JScrollPane(_RepeaterTable);
    _RepeaterModel.fireTableDataChanged();
    add(_SignalAppearanceScrollPane, BorderLayout.CENTER);

    JPanel footer = new JPanel();
    updateDetails();

    _MasterBox = new JmriBeanComboBox(dsmm);
    _MasterBox.addActionListener(new ActionListener() {
        /*public*/ void actionPerformed(ActionEvent e) {
            setSlaveBoxLists();
        }
    });

    _SlaveBox = new JmriBeanComboBox(dsmm);
    _SlaveBox.setEnabled(false);
    footer.add(new JLabel(tre("Master") + " : "));
    footer.add(_MasterBox);
    footer.add(new JLabel(tre("Slave") + " : "));
    footer.add(_SlaveBox);
    _addRepeater = new JButton(tre("ButtonAdd"));
    _addRepeater.setEnabled(false);
    _addRepeater.addActionListener(new ActionListener() {
        /*public*/ void actionPerformed(ActionEvent e) {
            SignalMastRepeater rp = new SignalMastRepeater((SignalMast) _MasterBox.getSelectedBean(), (SignalMast) _SlaveBox.getSelectedBean());
            try {
                dsmm.addRepeater(rp);
            } catch (jmri.JmriException ex) {
                log.error(ex.toString());
                /**/
                JOptionPane.showMessageDialog(NULL, java.text.MessageFormat.format(tre("MessageAddFailed"),
                        new Object[]{_MasterBox.getSelectedDisplayName(), _SlaveBox.getSelectedDisplayName()}),
                        tre("TitleAddFailed"), JOptionPane.ERROR_MESSAGE);
            }
        }
    });
    footer.add(_addRepeater);

    TitledBorder border = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));
    border.setTitle(tre("AddRepeater"));
    footer.setBorder(border);

    add(footer, BorderLayout.SOUTH);
#endif
}
#if 0
void setSlaveBoxLists() {
    SignalMast masterMast = (SignalMast) _MasterBox.getSelectedBean();
    if (masterMast == NULL) {
        _SlaveBox.setEnabled(false);
        _addRepeater.setEnabled(false);
        return;
    }
    java.util.Iterator<String> iter
            = dsmm.getSystemNameList().iterator();

    // don't return an element if there are not sensors to include
    if (!iter.hasNext()) {
        return;
    }
    ArrayList<NamedBean> excludeList = new ArrayList<NamedBean>();
    while (iter.hasNext()) {
        String mname = iter.next();
        if (mname != NULL) {
            SignalMast s = dsmm.getBySystemName(mname);
            if (s.getAppearanceMap() != masterMast.getAppearanceMap()) {
                excludeList.add(s);
            } else if (s == masterMast) {
                excludeList.add(s);
            }
        }
    }
    _SlaveBox.excludeItems(excludeList);
    if (excludeList.size() == dsmm.getSystemNameList().size()) {
        _SlaveBox.setEnabled(false);
        _addRepeater.setEnabled(false);
    } else {
        _SlaveBox.setEnabled(true);
        _addRepeater.setEnabled(true);
    }
}

JmriJFrame signalMastLogicFrame = NULL;
JLabel sourceLabel = new JLabel();

/*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {

}

#endif

/*private*/ void SignalMastRepeaterPanel::updateDetails() {
    _signalMastRepeaterList = new QList<SignalMastRepeater*>();
    foreach (SignalMastRepeater* r, *dsmm->getRepeaterList()) {
     _signalMastRepeaterList->append(r);
    }
    _RepeaterModel->fireTableDataChanged();//updateSignalMastLogic(old, sml);
}

///*public*/ class SignalMastRepeaterModel extends AbstractTableModel implements PropertyChangeListener {

//    /**
//     *
//     */
//    private static final long serialVersionUID = -452987462897570268L;

    SignalMastRepeaterModel::SignalMastRepeaterModel(SignalMastRepeaterPanel* panel) :AbstractTableModel()
    {
        //super();
        this->panel = panel;
        log = new Logger("SignalMastRepeaterModel");
        //dsmm.addPropertyChangeListener(this);
        connect(panel->dsmm->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }

    //@Override
//    /*public*/ Class<?> getColumnClass(int c) {
//        if (c == DIR_COLUMN) {
//            return JButton.class;
//        }
//        if (c == ENABLE_COLUMN) {
//            return Boolean.class;
//        }
//        if (c == DEL_COLUMN) {
//            return JButton.class;
//        }
//        return String.class;
//    }

/*public*/ void SignalMastRepeaterModel::configureTable(JTable* table) {
    // allow reordering of the columns
    //table.getTableHeader().setReorderingAllowed(true);

    // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
    //table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);

    // resize columns as requested

    for (int i = 0; i < table->model()->columnCount(); i++) {
        int width = getPreferredWidth(i);
        table->getColumnModel()->getColumn(i)->setPreferredWidth(width);
    }
    table->resizeColumnsToContents();

    configEditColumn(table);

}

/*public*/ int SignalMastRepeaterModel::getPreferredWidth(int col) {
    switch (col) {
        case ENABLE_COLUMN:
        case DIR_COLUMN:
            return  JTextField(5).sizeHint().width();
        case SLAVE_COLUMN:
            return  JTextField(15).sizeHint().width();
        case MASTER_COLUMN:
            return  JTextField(15).sizeHint().width();
        case DEL_COLUMN: // not actually used due to the configureTable, setColumnToHoldButton, configureButton
            return  JTextField(22).sizeHint().width();
        default:
            log->warn("Unexpected column in getPreferredWidth: " + QString::number(col));
            return  JTextField(8).sizeHint().width();
    }
}

//@Override
/*public*/ QVariant SignalMastRepeaterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
         int col =section;

    if (col == MASTER_COLUMN) {
        return tr("Master");
    }
    if (col == DIR_COLUMN) {
        return tr("Dir");
    }
    if (col == SLAVE_COLUMN) {
        return tr("Slave");
    }
    if (col == ENABLE_COLUMN) {
        return tr("Enabled");
    }
    if (col == DEL_COLUMN) {
        return tr("Delete");
    }
     }
    return QVariant();
}

/*public*/ void SignalMastRepeaterModel::dispose() {

}

/*public*/ void SignalMastRepeaterModel::propertyChange(PropertyChangeEvent* e) {
    if (e->getPropertyName()==("repeaterlength")) {
        panel->updateDetails();
    }
}

/*protected*/ void SignalMastRepeaterModel::configEditColumn(JTable* table) {
    // have the delete column hold a button
    /*AbstractTableAction.tre("EditDelete")*/
#
//    JButton b = new JButton("< >");
//    b.putClientProperty("JComponent.sizeVariant", "small");
//    b.putClientProperty("JButton.buttonType", "square");

    setColumnToHoldButton(table, DIR_COLUMN);
    setColumnToHoldButton(table, DEL_COLUMN);
}
#if 0
/*protected*/ void setColumnToHoldButton(JTable table, int column, JButton sample) {
    //TableColumnModel tcm = table.getColumnModel();
    // install a button renderer & editor
    ButtonRenderer buttonRenderer = new ButtonRenderer();
    table.setDefaultRenderer(JButton.class, buttonRenderer);
    TableCellEditor buttonEditor = new ButtonEditor(new JButton());
    table.setDefaultEditor(JButton.class, buttonEditor);
    // ensure the table rows, columns have enough room for buttons
    table.setRowHeight(sample.getPreferredSize().height);
    table.getColumnModel().getColumn(column)
            .setPreferredWidth((sample.sizeHint()->width()) + 4);
}
#endif
/*public*/ int SignalMastRepeaterModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

//@Override
/*public*/ Qt::ItemFlags SignalMastRepeaterModel::flags(const QModelIndex &index) const
{
 int c = index.column();
    if (c == DEL_COLUMN) {
        return Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }
    if (c == ENABLE_COLUMN) {
        return Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }
    if (c == DIR_COLUMN) {
        return Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }

    return Qt::ItemIsEnabled;
}

/*protected*/ void SignalMastRepeaterModel::deleteRepeater(int r) {
    panel->dsmm->removeRepeater(panel->_signalMastRepeaterList->at(r));
}


/*public*/ void SignalMastRepeaterModel::setSetToState(QString x) {
}

/*public*/ int SignalMastRepeaterModel::rowCount(const QModelIndex &parent) const
{
    if (panel->_signalMastRepeaterList == NULL) {
        return 0;
    }
    return panel->_signalMastRepeaterList->size();
}

/*public*/ QVariant SignalMastRepeaterModel::data(const QModelIndex &index, int role) const
{
  int r = index.row();
  int c = index.column();
  if(role == Qt::DisplayRole)
  {
    if (r >= panel->_signalMastRepeaterList->size()) {
        log->debug("row is greater than turnout list size");
        return QVariant();
    }
    switch (c) {
        case MASTER_COLUMN:
            return panel->_signalMastRepeaterList->at(r)->getMasterMastName();
        case DIR_COLUMN:  // slot number
            switch (panel->_signalMastRepeaterList->at(r)->getDirection()) {
                case SignalMastRepeater::BOTHWAY:
                    return "< >";
                case SignalMastRepeater::MASTERTOSLAVE:
                    return " > ";
                case SignalMastRepeater::SLAVETOMASTER:
                    return " < ";
                default:
                    return "< >";
            }
        case SLAVE_COLUMN:
            return panel->_signalMastRepeaterList->at(r)->getSlaveMastName();
        case ENABLE_COLUMN:
            return panel->_signalMastRepeaterList->at(r)->getEnabled();
        case DEL_COLUMN:
            return tr("Delete");
        default:
            break;;
    }

  }
  return QVariant();
}

//@Override
/*public*/ bool SignalMastRepeaterModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
     int c = index.column();
     int r = index.column();
    if (c == DIR_COLUMN) {
        switch (panel->_signalMastRepeaterList->at(r)->getDirection()) {
            case SignalMastRepeater::BOTHWAY:
                panel->_signalMastRepeaterList->at(r)->setDirection(SignalMastRepeater::MASTERTOSLAVE);
                break;
            case SignalMastRepeater::MASTERTOSLAVE:
                panel->_signalMastRepeaterList->at(r)->setDirection(SignalMastRepeater::SLAVETOMASTER);
                break;
            case SignalMastRepeater::SLAVETOMASTER:
                panel->_signalMastRepeaterList->at(r)->setDirection(SignalMastRepeater::BOTHWAY);
                break;
            default:
                panel->_signalMastRepeaterList->at(r)->setDirection(SignalMastRepeater::BOTHWAY);
                break;
        }
        panel->_RepeaterModel->fireTableDataChanged();
    } else if (c == DEL_COLUMN) {
        deleteRepeater(r);
    } else if (c == ENABLE_COLUMN) {
        bool b = value.toBool();
        panel->_signalMastRepeaterList->at(r)->setEnabled(b);
    }\
    return true;
 }
 return false;
}


