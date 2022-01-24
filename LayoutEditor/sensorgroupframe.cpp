#include "sensorgroupframe.h"
#include <QBoxLayout>
#include "jtable.h"
#include "tablecolumn.h"
#include "tablecolumnmodel.h"
#include "flowlayout.h"
#include "jtextfield.h"
#include <QLabel>
#include <QPushButton>
#include "../libPr3/routemanager.h"
#include "instancemanager.h"
#include "defaultlistmodel.h"
#include "logix.h"
#include "conditional.h"
#include "conditionalmanager.h"
#include <QListView>
#include "sensortablemodel.h"
#include "listselectionmodel.h"
#include <QMessageBox>
#include "sensorgroupconditional.h"
#include "conditionalvariable.h"
#include "defaultconditionalaction.h"

SensorGroupFrame::SensorGroupFrame(QWidget *parent) :
    JmriJFrame(parent)
{
 log = new Logger("SensorGroupFrame");
}
/**
 * User interface for creating and editing sensor groups.
 * <P>
 * Sensor groups are implemented by (groups) of Routes, not by
 * any other object.
 *
 * @author			Bob Jacobsen   Copyright (C) 2007
 * @author			Pete Cressman   Copyright (C) 2009
 * @version			$Revision: 17977 $
 */
///*public*/ class SensorGroupFrame extends jmri.util.JmriJFrame {

///*public*/ SensorGroupFrame() {
//    super();
//}

/*private*/ /*final*/ /*static*/ QString SensorGroupFrame::namePrefix  = "SENSOR GROUP:";  // should be upper case
/*private*/ /*final*/ /*static*/ QString SensorGroupFrame::nameDivider = ":";
/*public*/ /*final*/ /*static*/ QString SensorGroupFrame::logixSysName = "SYS";
/*public*/ /*final*/ /*static*/ QString SensorGroupFrame::logixUserName = "System Logix";
/*public*/ /*final*/ /*static*/ QString SensorGroupFrame::ConditionalSystemPrefix = SensorGroupFrame::logixSysName+"_SGC_";
/*private*/ /*final*/ /*static*/ QString SensorGroupFrame::ConditionalUserPrefix = "Sensor Group ";

#if 1
/*public*/ void SensorGroupFrame::initComponents() {
    addHelpMenu("package.jmri.jmrit.sensorgroup.SensorGroupFrame", true);

    setTitle("Define Sensor Group");
//    getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
    QWidget* centralWidget = new QWidget();
    QVBoxLayout* thisLayout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // add the sensor table
    QWidget* p2xs = new QWidget();
    QVBoxLayout* p2xsLayout = new QVBoxLayout(p2xs);
    //QWidget* p21s = new QWidget();
    //p21s.setLayout(new BoxLayout(p21s, BoxLayout.Y_AXIS));
    QVBoxLayout* p21sLayout = new QVBoxLayout();
    p21sLayout->addWidget(new QLabel("Please select"));
    p21sLayout->addWidget(new QLabel("Sensors to "));
    p21sLayout->addWidget(new QLabel("be included "));
    p21sLayout->addWidget(new QLabel("in this group."));
    p2xsLayout->addLayout(p21sLayout);
    _sensorModel = new SensorTableModel();
    JTable* sensorTable = new JTable(_sensorModel);
    /*
    JTable sensorTable = jmri.util.JTableUtil.sortableDataModel(sensorModel);
    try {
        jmri.util.com.sun.TableSorter tmodel = ((jmri.util.com.sun.TableSorter)sensorTable.getModel());
        tmodel.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
        tmodel.setSortingStatus(SensorTableModel.SNAME_COLUMN, jmri.util.com.sun.TableSorter.ASCENDING);
    } catch (ClassCastException e3) {}  // if not a sortable table model
    */
//    sensorTable.setRowSelectionAllowed(false);
//    sensorTable.setPreferredScrollableViewportSize(new java.awt.Dimension(450,200));
    TableColumnModel* sensorColumnModel = sensorTable->getColumnModel();
    for(int col = 0; col < _sensorModel->columnCount(QModelIndex()); col ++)
     sensorColumnModel->addColumn(new TableColumn);
    TableColumn* includeColumnS = sensorColumnModel->
                                        getColumn(SensorTableModel::INCLUDE_COLUMN);
    includeColumnS->setResizable(false);
    includeColumnS->setMinWidth(50);
    includeColumnS->setMaxWidth(60);
    TableColumn* sNameColumnS = sensorColumnModel->
                                        getColumn(SensorTableModel::SNAME_COLUMN);
    sNameColumnS->setResizable(true);
    sNameColumnS->setMinWidth(75);
    sNameColumnS->setPreferredWidth(95);
    TableColumn* uNameColumnS = sensorColumnModel->
                                        getColumn(SensorTableModel::UNAME_COLUMN);
    uNameColumnS->setResizable(true);
    uNameColumnS->setMinWidth(210);
    uNameColumnS->setPreferredWidth(260);

//    rowHeight = sensorTable->getRowHeight();
    //_sensorScrollPane = new JScrollPane(sensorTable);
    p2xsLayout->addWidget(sensorTable/*_sensorScrollPane,BorderLayout.CENTER*/,0, Qt::AlignVCenter);
    thisLayout->addWidget(p2xs);
    p2xs->setVisible(true);

    // add name field
    QWidget* p3 = new QWidget();
    FlowLayout* p3Layout = new FlowLayout(p3);
    p3Layout->addWidget(new QLabel(tr("Group Name:")));
    _nameField = new JTextField(20);
    p3Layout->addWidget(_nameField);
    thisLayout->addWidget(p3);

    // button
    //QWidget p4 = new QWidget();
    FlowLayout* p4Layout = new FlowLayout();
    QPushButton* viewButton = new QPushButton(" View ");
//    viewButton.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                viewPressed();
//            }
//        });
    connect(viewButton, SIGNAL(clicked()), this, SLOT(viewPressed()));
    p4Layout->addWidget(viewButton);
    QPushButton* addButton = new QPushButton(tr("Make Group"));
//    addButton.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                addPressed();
//            }
//        });
    connect(addButton, SIGNAL(clicked()), this, SLOT(addPressed()));
    p4Layout->addWidget(addButton);
    QPushButton* undoButton = new QPushButton(tr("Undo Group"));
//    undoButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            undoGroupPressed();
//        }
//    });
    connect(undoButton, SIGNAL(clicked()), this, SLOT(undoGroupPressed()));
    thisLayout->addLayout(p4Layout);

    QWidget* p5 = new QWidget();
    QVBoxLayout* p5Layout = new QVBoxLayout(p5);

    DefaultListModel* groupModel = new DefaultListModel();
    // Look for Sensor group in Route table
    RouteManager* rm = (RouteManager*)InstanceManager::getDefault("RouteManager");
    QStringList routeList = rm->getSystemNameList();
    int i = 0;
    while (i < routeList.size()) {
        QString name = routeList.at(i);
        if (name.startsWith(namePrefix)) {
            name = name.mid(namePrefix.length());
            QString group = name.mid(0, name.indexOf(nameDivider));
            QString prefix = namePrefix+group+nameDivider;
            do {
                i++;
                if (i >= routeList.size()) {
                    break;
                }
                name = routeList.at(i);
            } while (name.startsWith(prefix));
            groupModel->addElement(group);
        }
        i++;
    }
    // Look for Sensor group in Logix
    Logix* logix = getSystemLogix();
    for (i = 0; i<logix->getNumConditionals(); i++) {
        QString name = logix->getConditionalByNumberOrder(i);
        Conditional* c = ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->getBySystemName(name);
        if (c != NULL) {
            groupModel->addElement(c->getUserName().mid(ConditionalUserPrefix.length()));
        }
    }
    _sensorGroupList = new QListView(/*groupModel*/);
    _sensorGroupList->setModel(groupModel);
//    _sensorGroupList->setPrototypeCellValue(ConditionalUserPrefix+"XXXXXXXXXX");
    //_sensorGroupList->setSelectionMode(ListSelectionModel::SINGLE_SELECTION);
    _sensorGroupList->setSelectionMode(QAbstractItemView::SingleSelection);
//    _sensorGroupList->setVisibleRowCount(5);
//    JScrollPane scrollPane = new JScrollPane(_sensorGroupList);
    p5Layout->addWidget(/*scrollPane*/_sensorGroupList);
    p5Layout->addStrut(10);
    QPushButton* doneButton = new QPushButton(" Done ");
//    doneButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            donePressed(e);
//        }
//    });
    connect(doneButton, SIGNAL(clicked()), this, SLOT(donePressed()));
    p5Layout->addWidget(doneButton);
    thisLayout->addWidget(p5);

    // pack to cause display
    adjustSize();
}
#endif
#if 1
void SensorGroupFrame::addPressed() {
    deleteGroup(false);
    QString group = _nameField->text();
    if (group == NULL || group.length()==0) {
//        javax.swing.JOptionPane.showMessageDialog(this,
//                        "Please enter a name for this group.", "Error",
//                        javax.swing.JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(this, tr("Error"), tr( "Please enter a name for this group."));
        return;
    }
    Logix* logix = getSystemLogix();
    logix->deActivateLogix();
    QString cSystemName = ConditionalSystemPrefix+group.toUpper();
    QString cUserName = ConditionalUserPrefix+group;
    // add new Conditional
    QList <ConditionalVariable*> variableList =  QList<ConditionalVariable*>();
    QList <ConditionalAction*> actionList =  QList<ConditionalAction*>();
    int count = 0;
    for (int i = 0; i<_sensorModel->rowCount(QModelIndex()); i++) {
      if (_sensorModel->data(_sensorModel->index(i,BeanTableModel::INCLUDE_COLUMN),Qt::DisplayRole).toBool())
      {
       QString sensor = _sensorModel->data(_sensorModel->index(i,BeanTableModel::SNAME_COLUMN),Qt::DisplayRole).toString();
            variableList.append(new ConditionalVariable(false, Conditional::OPERATOR_OR,
                                                     Conditional::TYPE_SENSOR_ACTIVE, sensor, true));
            actionList.append(new DefaultConditionalAction(Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE,
                                                 Conditional::ACTION_SET_SENSOR, sensor,
                                                 Sensor::INACTIVE, ""));
            count++;
        }
    }
    if (count < 2) {
//        javax.swing.JOptionPane.showMessageDialog(this,
//                          "A Sensor Group needs to have at least 2 sensors to be useful.",
//                          "Error", javax.swing.JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(this, tr("Error"), tr("A Sensor Group needs to have at least 2 sensors to be useful."));
    }
    Conditional* c = (Conditional*)new SensorGroupConditional(cSystemName, cUserName);
    ((ConditionalManager*)InstanceManager::getDefault("ConditionaManager"))->Register(c);
    c->setStateVariables(&variableList);
    c->setLogicType(Conditional::ALL_OR, "");
    c->setAction(&actionList);
    logix->addConditional(cSystemName, 0);
    logix->setEnabled(true);
    logix->activateLogix();
    ((DefaultListModel*)_sensorGroupList->model())->addElement(
                            cUserName.mid(ConditionalUserPrefix.length()));
    clear();
}

void SensorGroupFrame:: viewPressed()
{
 for (int i = 0; i<_sensorModel->rowCount(QModelIndex()); i++)
 {
  _sensorModel->setData(_sensorModel->index( i, BeanTableModel::INCLUDE_COLUMN),Qt::EditRole,false);
    }
    // look for name in List panel
    QString group = _sensorGroupList->currentIndex().data().toString();
    if (group == NULL) { // not there, look in text field
        group = _nameField->text().toUpper().trimmed();
    }
    _nameField->setText(group);
    // Look for Sensor group in Route table
    RouteManager* rm = (RouteManager*)InstanceManager::getDefault("RouteManager");
    QStringList l = rm->getSystemNameList();
    QString prefix = (namePrefix+group+nameDivider).toUpper();
    bool isRoute = false;
    int setRow = 0;
    for (int i = 0; i<l.size(); i++) {
        QString name = l.at(i);
        if (name.startsWith(prefix)) {
            isRoute = true;
            QString sensor = name.mid(prefix.length());
            // find and check that sensor
            for (int j=_sensorModel->rowCount(QModelIndex())-1; j>=0; j--) {
             if (_sensorModel->data(_sensorModel->index(j,BeanTableModel::SNAME_COLUMN),Qt::DisplayRole).toString() ==(sensor))
                {
                 _sensorModel->setData(_sensorModel->index( j, BeanTableModel::INCLUDE_COLUMN),Qt::EditRole,true);
                    setRow = j;
                }
            }
        }
    }
    // look for  Sensor group in SYSTEM Logix
    if (!isRoute)
    {
     Logix* logix = getSystemLogix();
     QString cSystemName = (ConditionalSystemPrefix+group).toUpper();
     QString cUserName = ConditionalUserPrefix+group;
     for (int i = 0; i<logix->getNumConditionals(); i++)
     {
      QString name = logix->getConditionalByNumberOrder(i);
      if (cSystemName==(name) || cUserName==(name))
      {
       Conditional* c = ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->getBySystemName(name);
       if (c == NULL) {
           log->error("Conditional \""+name+"\" expected but NOT found in Logix "+logix->getSystemName());
       }
       else
       {
        QList <ConditionalVariable*>* variableList = c->getCopyOfStateVariables();
        for (int k=0; k<variableList->size(); k++)
        {
         QString sensor = variableList->at(k)->getName();
         for (int j=_sensorModel->rowCount(QModelIndex())-1; j>=0; j--)
         {
          if (_sensorModel->data(_sensorModel->index(j,BeanTableModel::SNAME_COLUMN),Qt::DisplayRole).toString() ==(sensor)) {
              _sensorModel->setData(_sensorModel->index(j, BeanTableModel::INCLUDE_COLUMN),Qt::EditRole,true);
              setRow = j;
          }
         }
        }
       }
      }
     }
    }
    _sensorModel->fireTableDataChanged();
    setRow -= 9;
    if (setRow < 0) {
        setRow = 0;
    }
//    _sensorScrollPane.getVerticalScrollBar().setValue(setRow*rowHeight);
}
#endif
Logix* SensorGroupFrame::getSystemLogix() {
    Logix* logix = (Logix*)((LogixManager*)InstanceManager::getDefault("LogixManager"))->getBySystemName(logixSysName);
    if (logix == NULL) {
        logix = ((LogixManager*)InstanceManager::getDefault("LogixManager"))->createNewLogix(logixSysName, logixUserName);
    }
    return logix;
}

void SensorGroupFrame::clear()
{
    //_sensorGroupList->getSelectionModel().clearSelection();
 _sensorGroupList->clearSelection();
    _nameField->setText("");
    for (int i = 0; i<_sensorModel->rowCount(QModelIndex()); i++)
    {
     //_sensorModel->setValueAt(Boolean.FALSE, i, BeanTableModel::INCLUDE_COLUMN);
     _sensorModel->setData(_sensorModel->index(i,BeanTableModel::INCLUDE_COLUMN), false,Qt::EditRole);
    }
    _sensorModel->fireTableDataChanged();
}


void SensorGroupFrame::donePressed(JActionEvent* /*e*/) {
    _sensorModel->dispose();
    dispose();
}
#if 1
void SensorGroupFrame::deleteGroup(bool showMsg) {
    QString group = _nameField->text();
    QString prefix = (namePrefix+group+nameDivider).toUpper();

    // remove the old routes
    RouteManager* rm = (RouteManager*)InstanceManager::getDefault("RouteManager");
    QStringList l = rm->getSystemNameList();

    for (int i = 0; i<l.size(); i++) {
        QString name = l.at(i);
        if (name.startsWith(prefix)) {
            // OK, kill this one
            Route* r = (Route*)rm->getBySystemName(l.at(i));
            r->deActivateRoute();
            rm->deleteRoute(r);
        }
    }
    QString cSystemName = (ConditionalSystemPrefix+group).toUpper();
    QString cUserName = ConditionalUserPrefix+group;
    Logix* logix = getSystemLogix();
    for (int i = 0; i<logix->getNumConditionals(); i++) {
        QString name = logix->getConditionalByNumberOrder(i);
        if (cSystemName==(name) || cUserName==(name)) {
            Conditional* c = ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->getBySystemName(name);
            if (c == NULL) {
                log->error("Conditional \""+name+"\" expected but NOT found in Logix "+logix->getSystemName());
            } else {
                logix->deleteConditional(cSystemName);
                break;
            }
        }
    }
    DefaultListModel* model = (DefaultListModel*)_sensorGroupList->model();
    int index = model->indexOf(group);
#if 1
    if (index > -1) {
        model->remove(index);
    }

    index = _sensorGroupList->currentIndex().row();
    if (index > -1)  {
     QString sysName = ConditionalSystemPrefix+model->elementAt(index).toString();
        QStringList* msgs = logix->deleteConditional(sysName);
        if (msgs != NULL) {
            if (showMsg) {
             //                javax.swing.JOptionPane.showMessageDialog(this,"Conditional "+msgs[0]+" ("+
             //                                  msgs[1]+") is a Conditional Variable in the Conditional,\n"+
             //                                  msgs[2]+" ("+msgs[3]+"), of Logix, "+msgs[4]+" ("+msgs[5]+
             //                                  ").\nPlease remove that variable first.",
             //                                  "Error", javax.swing.JOptionPane.ERROR_MESSAGE);
             QMessageBox::critical(this, tr("Error"), msgs->at(0)+" ("+msgs->at(1)+") is a Conditional Variable in the Conditional,\n"+ msgs->at(2)+" ("+msgs->at(3)+"), of Logix, "+msgs->at(4)+" ("+msgs->at(5)+ ").\nPlease remove that variable first.");
            }
        } else {
            model->remove(index);
        }
    }
#endif
}
#endif
void SensorGroupFrame::undoGroupPressed() {
    deleteGroup(true);
    clear();
}

/*public*/ QString SensorGroupFrame::getClassName()
{
 return "jmri.jmrit.sensorgroup.SensorGroupFrame";
}
