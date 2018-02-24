#include "picksinglepanel.h"
#include <QBoxLayout>
#include <QLabel>
#include "instancemanager.h"
#include "namedbeanhandlemanager.h"
#include "listselectionmodel.h"
#include "addnewdevicepanel.h"

/**
 * Container with a single PickList table
 * <p>
 * See also PickTabbedPanel for multiple panes with multiple tables
 *
 * @author Bob Jacobsen  Copyright (c) 2017
 * @author Pete Cressman Copyright (c) 2010
 */
// /*public*/ class PickSinglePanel<T extends NamedBean> extends JPanel {

//template<class T>
/*public*/ PickSinglePanel::PickSinglePanel(PickListModel* model, QWidget *parent) {
    _model = model;
    _table = _model->makePickTable();
    _table->setSelectionMode(QAbstractItemView::SingleSelection);//ListSelectionModel::SINGLE_SELECTION);
//    _table.setCellSelectionEnabled(true);
#if 0
    _table.getSelectionModel().addListSelectionListener(new ListSelectionListener() {
        /*public*/ void valueChanged(ListSelectionEvent e) {
            int row = getTable().getSelectedRow();
            int col = getTable().getSelectedColumn(); // might be -1 if just inserted
            if (col != 1) return;
            if (row >= 0) {
                String username = (String) _model.getTable().getValueAt(row, 1);
                if (username != null) return;
            }
            // have to set selection to col 0
            _model.getTable().setColumnSelectionInterval(0,0);
        }
    });
#endif
    QWidget* p = new QWidget();
    QVBoxLayout* pLayout = new QVBoxLayout(p);
    //p.setLayout(new BorderLayout(5, 5));
    pLayout->addWidget(new QLabel(_model->getName()), 0, Qt::AlignTop);//SwingConstants.CENTER), BorderLayout.NORTH);
    //pLayout.add(_scroll = new JScrollPane(_table), BorderLayout.CENTER);
    pLayout->addWidget(_table, 0, Qt::AlignCenter);
    ROW_HEIGHT = _table->getRowHeight();

    //setLayout(new BorderLayout(5, 5));
    QVBoxLayout* thisLayout = new QVBoxLayout(this);
    thisLayout->addWidget(p, 0, Qt::AlignCenter);//BorderLayout.CENTER);
    thisLayout->addWidget(makeAddToTablePanel(), 0, Qt::AlignBottom);// BorderLayout.SOUTH);
}

//template<class T>
/*public*/ NamedBeanHandle<NamedBean*>* PickSinglePanel::getSelectedBeanHandle() {
    int row = getTable()->getSelectedRow();
    int col = getTable()->getSelectedColumn(); // might be -1 if just inserted
    //System::out.println(" r c "+row+" "+col);

    // are we sure this is always col 0 for sysname and col 1 for user name?
    QString sysname = _model->/*getTable()->*/data(_model->index(row, 0), Qt::DisplayRole).toString();
    QString username =  _model/*.getTable()*/->data(_model->index(row, 1), Qt::DisplayRole).toString();

    QString beanName = sysname;
    if (col == 1 && username != NULL) beanName = username;
    NamedBean* bean = _model->addBean(sysname, username);
    return ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                    ->getNamedBeanHandle(beanName, bean);
}

/*public*/ JTable* PickSinglePanel::getTable() { return _table; }

/*private*/ QWidget* PickSinglePanel::makeAddToTablePanel() {
    _sysNametext = new JTextField();
    _userNametext = new JTextField();
#if 0
    ActionListener cancelListener = new ActionListener() {
        @Override
        /*public*/ void actionPerformed(ActionEvent a) {
            //do nothing as Cancel button is hidden on Pick Lists
        }
    };

    ActionListener okListener = new ActionListener() {
        @Override
        /*public*/ void actionPerformed(ActionEvent a) {
            addToTable();
        }
    };
#endif
    PSPCancelListener* cancelListener = new PSPCancelListener(this);
    PSPOkListener* okListener = new PSPOkListener(this);
    _addPanel = new AddNewDevicePanel(
            _sysNametext, _userNametext, "addToTable", okListener, cancelListener); // No I18N
    // hide Cancel button as not handled bij Picker Panel

    _cantAddPanel = new QWidget();
    QVBoxLayout* _cantAddPanelLayout = new QVBoxLayout();
    _cantAddPanel->setLayout(_cantAddPanelLayout=new QVBoxLayout());//BorderLayout(5, 5));
    _cantAddPanelLayout->addWidget(new QLabel(tr("Cannot add new items to this pick panel.")), 0, Qt::AlignCenter);//SwingConstants.CENTER), BorderLayout.NORTH);
    _cantAddPanelLayout->addWidget(new QLabel(tr("Open the Table to add this type of item.")), 0, Qt::AlignBottom);// SwingConstants.CENTER), BorderLayout.SOUTH);
    QWidget* p = new QWidget();
    QVBoxLayout* pLayout= new QVBoxLayout(p);
    pLayout->addWidget(_addPanel);
    pLayout->addWidget(_cantAddPanel);
    int width = qMax(100, this->sizeHint().width());
    _sysNametext->resize(QSize(width, _sysNametext->sizeHint().height()));
    return p;
}

PSPCancelListener::PSPCancelListener(PickSinglePanel *panel) {this->panel = panel;}
void PSPCancelListener::actionPerformed(){}

PSPOkListener::PSPOkListener(PickSinglePanel *panel) {this->panel = panel;}
void PSPOkListener::actionPerformed(){ panel->addToTable();}

//template<class T>
void PickSinglePanel::addToTable() {
    QString sysname = _model->getManager()->normalizeSystemName(_sysNametext->text());

    if (sysname != NULL && sysname.length() > 1) {
        QString uname = NamedBean::normalizeUserName(_userNametext->text());
        if (uname != NULL && uname.trimmed().length() == 0) {
            uname = "";
        }
        NamedBean* bean = _model->addBean(sysname, uname);
        if (bean != NULL) {
            int setRow = _model->getIndexOf(bean);
            _model->getTable()->setRowSelectionInterval(setRow, setRow);
//            _scroll.getVerticalScrollBar().setValue(setRow * ROW_HEIGHT);
            _sysNametext->setText("");
        }
    }
}
