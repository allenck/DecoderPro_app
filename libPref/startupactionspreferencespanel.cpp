#include "startupactionspreferencespanel.h"
#include "indexedpropertychangeevent.h"
#include "propertychangeevent.h"
#include "instancemanager.h"
#include "startupactionsmanager.h"
#include "startupmodelfactory.h"
#include <QAction>
#include <QSignalMapper>
#include <QBoxLayout>
#include "flowlayout.h"
#include "profilemanager.h"
#include "listselectionmodel.h"
#include "vptr.h"
#include <QHeaderView>

/**
 * Preferences panel to configure optional actions taken at startup.
 *
 * @author Randall Wood (C) 2016
 */
///*public*/ class StartupActionsPreferencesPanel extends JPanel implements PreferencesPanel {

/**
 * Creates new form StartupActionsPreferencesPanel
 */
/*public*/ StartupActionsPreferencesPanel::StartupActionsPreferencesPanel(QWidget* parent)  : PreferencesPanel(parent)
{
 initComponents();
    //this->actionsTbl.getSelectionModel().addListSelectionListener((ListSelectionEvent e) ->
//    {
//        int row = this->actionsTbl.getSelectedRow();
//        this->upBtn.setEnabled(row != 0 && row != -1);
//        this->downBtn.setEnabled(row != this->actionsTbl.getRowCount() - 1 && row != -1);
//        this->removeBtn.setEnabled(row != -1);
//    });
 connect(this->actionsTbl, SIGNAL(clicked(QModelIndex)), this, SLOT(on_listSelected(/*ListSelectionEvent*)*/QModelIndex)));
 QList<QAction*> items = QList<QAction*>();
//    InstanceManager::getDefault("StartupActionsManager").getFactories().values().stream().forEach((factory) ->
 QSignalMapper* mapper = new QSignalMapper();
 QMap</*Class<? extends StartupModel>*/QString, StartupModelFactory*>*  factories = ((StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager"))->getFactories();
 foreach(StartupModelFactory* factory, factories->values())
 {
  QAction* item = new QAction(factory->getActionText(),this);
  mapper->setMapping(item, factory);
//        item.addActionListener((ActionEvent e) -> {
//            StartupModel model = factory.newModel();
//            factory.editModel(model, this->getTopLevelAncestor());
//            if (model.isValid()) {
//                InstanceManager.getDefault(StartupActionsManager.class).addAction(model);
//            }
//        });
  items.append(item);
  connect(item, SIGNAL(triggered(bool)), mapper, SLOT(map()));
 }//);
  connect(mapper, SIGNAL(mapped(QObject*)), this, SLOT(on_getAction(QObject*)));
//    items.sort((JMenuItem o1, JMenuItem o2) -> o1.getText().compareTo(o2.getText()));
//    items.stream().forEach((item) ->
 foreach(QAction* item, items)
 {
  this->actionsMenu->addAction(item);
 }//);
}

void StartupActionsPreferencesPanel::on_listSelected(QModelIndex index)
{
 int row = index.row();//this->actionsTbl->getSelectedRow();
 this->upBtn->setEnabled(row != 0 && row != -1);
 this->downBtn->setEnabled(row != this->actionsTbl->model()->rowCount() - 1 && row != -1);
 this->removeBtn->setEnabled(row != -1);

}
void StartupActionsPreferencesPanel::on_getAction(QObject* factory)
{
 StartupModel* model = ((StartupModelFactory*)factory)->newModel();
 ((StartupModelFactory*)factory)->editModel(model, this->getTopLevelAncestor());
 if (model->isValid()) {
     ((StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager"))->addAction(model);
 }
}
/**
 * This method is called from within the constructor to performAction the form.
 * WARNING: Do NOT modify this code. The content of this method is always
 * regenerated by the Form Editor.
 */
//@SuppressWarnings("unchecked")
// <editor-fold defaultstate="collapsed" desc="Generated Code">
/*private*/ void StartupActionsPreferencesPanel::initComponents() {

    actionsMenu = new QMenu();
    //jScrollPane1 = new JScrollPane();
    actionsTbl = new JTable();
#if 0 // TODO:
    {
        //Implement table cell tool tips.
        /*public*/ String getToolTipText(MouseEvent e) {
            try {
                return getValueAt(rowAtPoint(e.getPoint()), -1).toString();
            } catch (RuntimeException e1) {
                //catch null pointer exception if mouse is over an empty line
            }
            return null;
        }
    };
#endif
    addBtn = new QPushButton();
    removeBtn = new QPushButton();
    startupLbl = new QLabel();
    upBtn = new QPushButton();
    downBtn = new QPushButton();
    moveLbl = new QLabel();
    recommendationsLbl = new QLabel();

//    actionsTbl.setDefaultRenderer(StartupModel.class, new StartupModelCellRenderer());
//    actionsTbl.setDefaultEditor(StartupModel.class, new StartupModelCellEditor());
    actionsTbl->setModel(new SATableModel((StartupActionsManager*) InstanceManager::getDefault("StartupActionsManager")));
    actionsTbl->setSelectionMode(QAbstractItemView::SingleSelection);
//    actionsTbl.getTableHeader().setReorderingAllowed(false);
    //jScrollPane1.setViewportView(actionsTbl);
    actionsTbl->setColumnWidth(0, 200);
    actionsTbl->horizontalHeader()->setStretchLastSection(true);
//    actionsTbl.getColumnModel().getSelectionModel().setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

//    ResourceBundle bundle = ResourceBundle.getBundle("apps/startup/Bundle"); // NOI18N
    addBtn->setText(tr("Add ▾")); // NOI18N
//    addBtn.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent evt) {
//            addBtnActionPerformed(evt);
//        }
//    });
    connect(addBtn, SIGNAL(clicked(bool)), this, SLOT(addBtnActionPerformed()));

    removeBtn->setText(tr("Remove")); // NOI18N
    removeBtn->setEnabled(false);
//    removeBtn.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent evt) {
//            removeBtnActionPerformed(evt);
//        }
//    });
    connect(removeBtn, SIGNAL(clicked(bool)), this, SLOT(removeBtnActionPerformed()));

    startupLbl->setText(tr("<html>Add items to be executed or opened when the application starts.<br>Items will be executed or opened in the order listed.</html>")); // NOI18N

    upBtn->setText(tr("Up")); // NOI18N
    upBtn->setEnabled(false);
//    upBtn.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent evt) {
//            upBtnActionPerformed(evt);
//        }
//    });
    connect(upBtn, SIGNAL(clicked(bool)), this, SLOT(upBtnActionPerformed()));

    downBtn->setText(tr("Down")); // NOI18N
    downBtn->setEnabled(false);
//    downBtn.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent evt) {
//            downBtnActionPerformed(evt);
//        }
//    });
    connect(downBtn, SIGNAL(clicked(bool)), this, SLOT(downBtnActionPerformed()));

    moveLbl->setText(tr("Move")); // NOI18N

    recommendationsLbl->setText(tr("<html>Scripts should be run last in most cases.</html>")); // NOI18N
#if 0
    GroupLayout layout = new GroupLayout(this);
    this->setLayout(layout);
    layout.setHorizontalGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(layout.createSequentialGroup()
            .addContainerGap()
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                .addComponent(recommendationsLbl)
                .addComponent(jScrollPane1, GroupLayout.DEFAULT_SIZE, 487, Short.MAX_VALUE)
                .addGroup(layout.createSequentialGroup()
                    .addComponent(addBtn)
                    .addGap(18, 18, 18)
                    .addComponent(moveLbl)
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                    .addComponent(upBtn)
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                    .addComponent(downBtn)
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(removeBtn))
                .addComponent(startupLbl))
            .addContainerGap())
    );


    layout.setVerticalGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(layout.createSequentialGroup()
            .addContainerGap()
            .addComponent(startupLbl, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(jScrollPane1, GroupLayout.DEFAULT_SIZE, 200, Short.MAX_VALUE)
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(recommendationsLbl, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(addBtn)
                .addComponent(removeBtn)
                .addComponent(upBtn)
                .addComponent(downBtn)
                .addComponent(moveLbl))
            .addContainerGap())
    );
#endif
    QVBoxLayout* panelLayout = new QVBoxLayout(this);
    panelLayout->addWidget(startupLbl);
    panelLayout->addWidget(actionsTbl);
    panelLayout->addWidget(recommendationsLbl);
    QWidget* buttons = new QWidget();
    FlowLayout* buttonLayout = new FlowLayout(buttons);
    buttonLayout->addWidget(addBtn);
    buttonLayout->addWidget(removeBtn);
    buttonLayout->addWidget(upBtn);
    buttonLayout->addWidget(downBtn);
    buttonLayout->addWidget(moveLbl);
    panelLayout->addWidget(buttons);

}// </editor-fold>

/*private*/ void StartupActionsPreferencesPanel::addBtnActionPerformed(ActionEvent* /*evt*/) {
    //Component c = (Component) evt.getSource();
//    this->actionsMenu->show(c, 0 - 1, c.getHeight());
 this->actionsMenu->exec(QCursor::pos());
}

/*private*/ void StartupActionsPreferencesPanel::removeBtnActionPerformed(ActionEvent* /*evt*/) {
    int row = this->actionsTbl->getSelectedRow();
    if (row != -1) {
        StartupModel* model = ((StartupActionsManager*) InstanceManager::getDefault("StartupActionsManager"))->getActions(row);
        ((StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager"))->removeAction(model);
    }
}

/*private*/ void StartupActionsPreferencesPanel::upBtnActionPerformed(ActionEvent* /*evt*/) {
    int row = this->actionsTbl->getSelectedRow();
    if (row != 0) {
        ((StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager"))->moveAction(row, row - 1);
        this->actionsTbl->setRowSelectionInterval(row - 1, row - 1);
    }
}

/*private*/ void StartupActionsPreferencesPanel::downBtnActionPerformed(ActionEvent* /*evt*/) {
    int row = this->actionsTbl->getSelectedRow();
    if (row != this->actionsTbl->model()->rowCount() - 1) {
        ((StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager"))->moveAction(row, row + 1);
        this->actionsTbl->setRowSelectionInterval(row + 1, row + 1);
    }
}

//@Override
/*public*/ QString StartupActionsPreferencesPanel::getPreferencesItem() {
    return "STARTUP"; // NOI18N
}

//@Override
/*public*/ QString StartupActionsPreferencesPanel::getPreferencesItemText() {
    return tr("StartUp"); // NOI18N
}

//@Override
/*public*/ QString StartupActionsPreferencesPanel::getTabbedPreferencesTitle() {
    return "";
}

//@Override
/*public*/ QString StartupActionsPreferencesPanel::getLabelKey() {
    return "";
}

//@Override
/*public*/ QWidget* StartupActionsPreferencesPanel::getPreferencesComponent() {
    return this;
}

//@Override
/*public*/ bool StartupActionsPreferencesPanel::isPersistant() {
    return true;
}

//@Override
/*public*/ QString StartupActionsPreferencesPanel::getPreferencesTooltip() {
    return "";
}

//@Override
/*public*/ void StartupActionsPreferencesPanel::savePreferences() {
    ((StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager"))->savePreferences(ProfileManager::getDefault()->getActiveProfile());
}

//@Override
/*public*/ bool StartupActionsPreferencesPanel::isDirty() {
    return ((StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager"))->isDirty();
}

//@Override
/*public*/ bool StartupActionsPreferencesPanel::isRestartRequired() {
    return ((StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager"))->isRestartRequired();
}

//@Override
/*public*/ bool StartupActionsPreferencesPanel::isPreferencesValid() {
    // To really test would require that the models know their valid state
    // they don't, and it can change externally, so we don't really check.
    return true;
}



//private static class TableModel extends AbstractTableModel implements PropertyChangeListener {

//    private final StartupActionsManager manager;

//@SuppressWarnings("LeakingThisInConstructor")
/*public*/ SATableModel::SATableModel(StartupActionsManager* manager) {
    this->manager = manager;
    //this->manager.addPropertyChangeListener(this);
 connect(manager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

//@Override
/*public*/ int SATableModel::rowCount(const QModelIndex &/*parent*/) const
{

    return this->manager->getActions()->length();
}

//@Override
/*public*/ int SATableModel::columnCount(const QModelIndex &/*parent*/) const
{
 return 2;
}

//@Override
/*public*/ QVariant SATableModel::data(const QModelIndex &index, int role) const
{
 int rowIndex = index.row();
 StartupModel* model = this->manager->getActions(rowIndex);
 if(role == Qt::ToolTipRole)
 {
  return model->toString();
 }
 if(role == Qt::DisplayRole)
 {
  switch (index.column())
  {
//        case -1: // tooltip
//            return model->/*toString()*/metaObject()->className();
   case 0:
       return model->metaObject()->className();
   case 1:
  {
   QString className = QString(model->metaObject()->className());
   StartupModelFactory* factory = this->manager->getFactories(className);
   QString descr = factory->getDescription();
   return descr;
  }
   default:
       return QVariant();
  }
 }
 return QVariant();
}

//@Override
/*public*/ QVariant SATableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
 {
    switch (section) {
        case 0:
            return tr("Name"); // NOI18N
        case 1:
            return tr("Type"); // NOI18N
        default:
            return "";
    }
 }
 return QVariant();
}

////@Override
///*public*/ Class<?> getColumnClass(int columnIndex) {
//    switch (columnIndex) {
//        case 0:
//            return StartupModel.class;
//        case 1:
//            return String.class;
//        default:
//            return null;
//    }
//}

//@Override
/*public*/ Qt::ItemFlags SATableModel::flags(const QModelIndex &index) const
{
    if(index.column() == 0)
     return Qt::ItemIsEditable | Qt::ItemIsEnabled;
    return Qt::ItemIsEnabled;
}

//@Override
/*public*/ void SATableModel::propertyChange(PropertyChangeEvent* evt)
{
 int index = -1;
 if (qobject_cast<IndexedPropertyChangeEvent*>(evt) != NULL) {
     index = ((IndexedPropertyChangeEvent*) evt)->getIndex();
 }
 if (index != -1 && evt->getOldValue().toInt())
 {
  this->fireTableRowsUpdated(evt->getOldValue().toInt(), index);
 }
 else
 {
  this->fireTableDataChanged();
  StartupModel* model = VPtr<StartupModel>::asPtr(evt->getNewValue());
 }
}
//}
