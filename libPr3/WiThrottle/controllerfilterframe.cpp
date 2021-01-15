#include "controllerfilterframe.h"
#include "loggerfactory.h"
#include <QTabWidget>
#include "instancemanager.h"
#include "turnoutmanager.h"
#include "routemanager.h"
#include <QLabel>
#include "jtable.h"
#include <QBoxLayout>
#include "box.h"
#include <QPushButton>
#include "storexmluseraction.h"
#include "tablemodelevent.h"
#include "abstracttablemodel.h"
#include "tablecolumnmodel.h"
#include "tablecolumn.h"
#include "defaultroute.h"
/**
 * @author Brett Hoffman Copyright (C) 2010
 */
// /*public*/ class ControllerFilterFrame extends JmriJFrame implements TableModelListener {

//    static /*final*/ ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.withrottle.WiThrottleBundle");
    //static /*final*/ ResourceBundle rbx = ResourceBundle.getBundle("jmri.jmrit.beantable.LogixTableBundle");
/*private*/ /*static*/ QStringList ControllerFilterFrame::COLUMN_NAMES = QStringList() << tr("System Name") <<
        tr("User Name") <<
        tr("Include");

/*public*/ ControllerFilterFrame::ControllerFilterFrame(QWidget* parent) : JmriJFrame(tr("Filter Controls"), parent){
    //super(tr("TitleControlsFilter"), true, true);
}

////@Override
/*public*/ void ControllerFilterFrame::initComponents() throw (Exception)
{
    QTabWidget* tabbedPane = new QTabWidget();
    if (InstanceManager::getNullableDefault("TurnoutManager") != NULL) {

        //tabbedPane.addTab(tr("Turnout"), NULL, addTurnoutPanel(), tr("ToolTipTurnoutTab"));
     QWidget* turnoutPanel;
     tabbedPane->addTab(turnoutPanel = addTurnoutPanel(), tr("Turnout"));
      turnoutPanel->setToolTip(tr("Limit the turnouts controllable by WiFi devices."));
    }

    if (InstanceManager::getNullableDefault("RouteManager") != NULL) {

        //tabbedPane.addTab(tr("Route"), NULL, addRoutePanel(), tr("ToolTipRouteTab"));
     QWidget* routePanel = addRoutePanel();
     routePanel->setToolTip(tr("Limit the routes controllable by WiFi devices."));
     tabbedPane->addTab(routePanel, tr("Route"));
    }

    //add(tabbedPane);
    setCentralWidget(tabbedPane);

    adjustSize();

    addHelpMenu("package.jmri.jmrit.withrottle.UserInterface", true);
}

/*public*/ void ControllerFilterFrame::dispose()
{
 JmriJFrame::dispose();
}

/*private*/ QWidget* ControllerFilterFrame::addTurnoutPanel() {
    QWidget* tPanel = new QWidget(); //new BorderLayout());
    QVBoxLayout* tPanelLayout = new QVBoxLayout(tPanel);
    QLabel* label = new QLabel(tr("Select Turnouts to be controlled by WiFi devices.")); //, SwingConstants.CENTER);
    label->setAlignment(Qt::AlignCenter);
    tPanelLayout->addWidget(label, 0, Qt::AlignTop); //BorderLayout.NORTH);
    tPanelLayout->addWidget(addCancelSavePanel(), 0, Qt::AlignLeft); //BorderLayout.WEST);
#if 1
    /*final*/ TurnoutFilterModel* filterModel = new TurnoutFilterModel();
    JTable* table = new JTable(filterModel);
    buildTable(table);

    //JScrollPane scrollPane = new JScrollPane(table);
    tPanelLayout->addWidget(table, 0, Qt::AlignCenter);//scrollPane, BorderLayout.CENTER);

    tPanelLayout->addWidget(getIncludeButtonsPanel(filterModel), 0, Qt::AlignBottom); //BorderLayout.SOUTH);
#endif
    return tPanel;
}

/*private*/ QWidget* ControllerFilterFrame::addRoutePanel()
{
 QWidget* tPanel = new QWidget(); //new BorderLayout());
 QVBoxLayout* tPanelLayout = new QVBoxLayout(tPanel);
    QLabel* label = new QLabel(tr("Select Routes to be controlled by WiFi devices.")); //, SwingConstants.CENTER);
    label->setAlignment(Qt::AlignCenter);
    tPanelLayout->addWidget(label, 0, Qt::AlignTop); //BorderLayout.NORTH);
    tPanelLayout->addWidget(addCancelSavePanel(), 0, Qt::AlignLeft); //BorderLayout.WEST);
#if 1
    /*final*/ RouteFilterModel* filterModel = new RouteFilterModel();
    JTable* table = new JTable(filterModel);
    buildTable(table);

    //JScrollPane scrollPane = new JScrollPane(table);
    tPanelLayout->addWidget(/*scrollPane*/table, 0, Qt::AlignCenter); //BorderLayout.CENTER);

    tPanelLayout->addWidget(getIncludeButtonsPanel(filterModel), 0, Qt::AlignBottom); // BorderLayout.SOUTH);
#endif
    return tPanel;
}

/*private*/ void ControllerFilterFrame::buildTable(JTable* table) {
#if 1
    ((TableModel*)table->getModel())->addTableModelListener((TableModelListener*)this);

    table->setRowSelectionAllowed(false);
    //table->setPreferredScrollableViewportSize(new java.awt.Dimension(580, 240));

    //table.getTableHeader().setBackground(Color.lightGray);
    table->setShowGrid(false);
    table->setShowHorizontalLines(true);
    table->setGridColor(QColor(Qt::gray));
    table->setRowHeight(30);

    TableColumnModel* columnModel = table->getColumnModel();

    TableColumn* include = columnModel->getColumn(AbstractFilterModel::INCLUDECOL);
    include->setResizable(false);
    include->setMinWidth(60);
    include->setMaxWidth(70);

    TableColumn* sName = columnModel->getColumn(AbstractFilterModel::SNAMECOL);
    sName->setResizable(true);
    sName->setMinWidth(80);
    sName->setPreferredWidth(80);
    sName->setMaxWidth(340);

    TableColumn* uName = columnModel->getColumn(AbstractFilterModel::UNAMECOL);
    uName->setResizable(true);
    uName->setMinWidth(180);
    uName->setPreferredWidth(300);
    uName->setMaxWidth(440);
#endif
}
#if 1
/*private*/ QWidget* ControllerFilterFrame::getIncludeButtonsPanel(/*final*/ AbstractFilterModel* fm) {
 this->fm =fm;
    QWidget* pane = new QWidget();
    pane->setLayout(new QHBoxLayout());//pane, BoxLayout.X_AXIS));
    pane->layout()->addWidget(Box::createHorizontalGlue());

    QPushButton* selectAllButton = new QPushButton(tr("Select All"));
//    selectAllButton.addActionListener(new ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            fm.setIncludeColToValue(true);
//        }
//    });
    connect(selectAllButton, SIGNAL(clicked(bool)), this, SLOT(on_selectAllButton()));
    pane->layout()->addWidget(selectAllButton);

    QPushButton* deselectAllButton = new QPushButton(tr("Deselect All"));
//    deselectAllButton.addActionListener(new ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            fm.setIncludeColToValue(false);
//        }
//    });
    connect(deselectAllButton, SIGNAL(clicked(bool)), this, SLOT(on_deselectAllButton()));

    pane->layout()->addWidget(deselectAllButton);

    QPushButton* selectUserNamedButton = new QPushButton(tr("Select By UserName"));
//    selectUserNamedButton.addActionListener(new ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            fm.SetIncludeToUserNamed();
//        }
//    });
    connect(selectUserNamedButton, SIGNAL(clicked(bool)), this, SLOT(on_selectUserNamedButton()));

    pane->layout()->addWidget(selectUserNamedButton);

    return pane;
}

void ControllerFilterFrame::on_selectAllButton()
{
 fm->setIncludeColToValue(true);
}

void ControllerFilterFrame::on_deselectAllButton()
{
 fm->setIncludeColToValue(false);
}
void ControllerFilterFrame::on_selectUserNamedButton()
{
 fm->SetIncludeToUserNamed();
}
#endif
/*private*/ QWidget* ControllerFilterFrame::addCancelSavePanel() {
    QWidget* p = new QWidget();
    QVBoxLayout* pLayout;
    p->setLayout(pLayout = new QVBoxLayout()); //p, BoxLayout.Y_AXIS));
    p->layout()->addWidget(Box::createVerticalGlue());

    QPushButton* cancelButton = new QPushButton(tr("Cancel"));
    //cancelButton->setAlignment(Qt::AlignHCenter);
    cancelButton->setToolTip(tr("Close window without saving changes."));
//    cancelButton.addActionListener(new ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            dispose();
//        }
//    });
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(dispose()));
    pLayout->addWidget(cancelButton, 0, Qt::AlignHCenter);

    QPushButton* saveButton = new QPushButton(tr("Save"));
    //saveButton->setAlignment(Qt::AlignHCenter);
    saveButton->setToolTip(tr("Save changes to panel file."));
//    saveButton.addActionListener(new ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            storeValues();
//            dispose();
//        }
//    });
    connect(saveButton, SIGNAL(clicked()), this, SLOT(on_save()));
    pLayout->addWidget(saveButton,0, Qt::AlignHCenter);

    return p;
}
void ControllerFilterFrame::on_save()
{
 storeValues();
 dispose();
}

////@Override
/*protected*/ void ControllerFilterFrame::storeValues() {
    (new StoreXmlUserAction())->actionPerformed();
}

//@Override
/*public*/ void ControllerFilterFrame::tableChanged(TableModelEvent* /*e*/) {
    if (log->isDebugEnabled()) {
        log->debug("Set mod flag true for: " + getTitle());
    }
    this->setModifiedFlag(true);
}
#if 1
// /*public*/ abstract class AbstractFilterModel extends AbstractTableModel implements PropertyChangeListener {

//    List<String> sysNameList = NULL;
//    boolean isDirty;

//    //@Override
//    /*public*/ Class<?> getColumnClass(int c) {
//        if (c == INCLUDECOL) {
//            return Boolean.class;
//        } else {
//            return String.class;
//        }
//    }

    //@Override
    /*public*/ void AbstractFilterModel::propertyChange(PropertyChangeEvent* e) {
        if (e->getPropertyName() == ("length")) {
            fireTableDataChanged();
        }
    }

    /*public*/ void AbstractFilterModel::dispose() {
        InstanceManager::turnoutManagerInstance()->removePropertyChangeListener(QPointer<PropertyChangeListener>((PropertyChangeListener*)this));
        ((RouteManager*)InstanceManager::getDefault("RouteManager"))->removePropertyChangeListener(QPointer<PropertyChangeListener>((PropertyChangeListener*)this));
    }

    //@Override
    /*public*/ QVariant AbstractFilterModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
        if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
        {
         switch(section)
         {
         case SNAMECOL:
          return "System Name";
         case UNAMECOL:
          return "User Name";
         case INCLUDECOL:
          return "Include";
         default:
          break;
         }
        }
        return QVariant();
    }

    //@Override
    /*public*/ int AbstractFilterModel::columnCount(const QModelIndex &parent) const
    {
        return 3;
    }

    //@Override
    /*public*/ int AbstractFilterModel::rowCount(const QModelIndex &parent) const
    {
        return sysNameList.size();
    }

    //@Override
    /*public*/ Qt::ItemFlags AbstractFilterModel::flags(const QModelIndex &index) const
    {
      if(index.column() == INCLUDECOL)
        return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
      else
       return  Qt::ItemIsEnabled;
    }

    //abstract void setIncludeColToValue(boolean value);

    //abstract void SetIncludeToUserNamed();

//    /*public*/ /*static*/ /*final*/ int SNAMECOL = 0;
//    /*public*/ static /*final*/ int UNAMECOL = 1;
//    /*public*/ static /*final*/ int INCLUDECOL = 2;
//};
#endif
#if 1
//class TurnoutFilterModel extends AbstractFilterModel {

//    TurnoutManager mgr = InstanceManager.turnoutManagerInstance();

    TurnoutFilterModel::TurnoutFilterModel()
    {
     mgr = InstanceManager::turnoutManagerInstance();
     sysNameList = mgr->getSystemNameList();
     mgr->addPropertyChangeListener(QPointer<PropertyChangeListener>((PropertyChangeListener*)this));
    }

    //@Override
    /*public*/ QVariant TurnoutFilterModel::data(const QModelIndex &index, int role) const
    {
     // some error checking
     if (index.row() >= sysNameList.size()) {
         log->debug("row is greater than turnout list size");
         return QVariant();
     }

     Turnout* t = (Turnout*)mgr->getBySystemName(sysNameList.at(index.row()));
     if(role == Qt::CheckStateRole)
     {
        switch (index.column())
        {
         case INCLUDECOL:
         {
          if(t!= nullptr)
          {
            QVariant o =t->getProperty("WifiControllable");
            if ((!o.isNull()) && (o.toString().toLower() == "false")) {
                return Qt::CheckState::Unchecked;
            }
          }
          return Qt::CheckState::Checked;
         }
        default:
         break;
        }
     }
     if(role == Qt::DisplayRole)
     {
      switch (index.column())
      {
         case SNAMECOL:
             return sysNameList.at(index.row());
         case UNAMECOL:
             return t != nullptr ? t->getUserName() : "";
         default:
             break;
        }
     }
     return QVariant();
    }

    //@Override
    /*public*/ bool TurnoutFilterModel::setData(const QModelIndex &index, const QVariant &type, int role)
    {
     if(role == Qt::EditRole)
     {
        switch (index.column())
        {
            case INCLUDECOL:
                mgr->getBySystemName(sysNameList.at(index.row()))->setProperty("WifiControllable", type);
                if (!isDirty) {
                    this->fireTableChanged(new TableModelEvent(this));
                    isDirty = true;
                }
         return true;

        }
     }
     return false;
    }

    //@Override
    /*public*/ void TurnoutFilterModel::setIncludeColToValue(bool value) {
        for (QString sysName : sysNameList) {
            mgr->getBySystemName(sysName)->setProperty("WifiControllable", value);
        }
        fireTableDataChanged();
    }

    //@OverrideTurnoutFilterModel::
    /*public*/ void TurnoutFilterModel::SetIncludeToUserNamed() {
        for (QString sysName : sysNameList) {
            NamedBean *bean = mgr->getBySystemName(sysName);
            QString uname = bean->getUserName();
            if ((uname != "") && (uname.length() > 0)) {
                bean->setProperty("WifiControllable", true);
            } else {
                bean->setProperty("WifiControllable", false);
            }
        }
        fireTableDataChanged();
    }
//};

//class RouteFilterModel extends AbstractFilterModel {

//    RouteManager mgr = InstanceManager.getDefault(jmri.RouteManager.class);

    RouteFilterModel::RouteFilterModel()
    {
     mgr = (RouteManager*)InstanceManager::getDefault("RouteManager");
     sysNameList = mgr->getSystemNameList();
     mgr->addPropertyChangeListener(QPointer<PropertyChangeListener>((PropertyChangeListener*)this));
    }

    //@Override
    /*public*/ QVariant RouteFilterModel::data(const QModelIndex &index, int role) const
    {
     // some error checking
     if (index.row() >= sysNameList.size()) {
//            log->debug("row is greater than turnout list size");
         return QVariant();
     }
     Route* rt = (Route*)mgr->getBySystemName(sysNameList.at(index.row()));

     if(role == Qt::CheckStateRole)
     {
      switch (index.column())
      {
        case INCLUDECOL:
        {
         if (rt == nullptr) {
             return QVariant();
         }
         QVariant o = ((DefaultRoute*)rt)->getProperty("WifiControllable");
         if ((!o.isNull()) && (o.toString().toLower()=="false")) {
             return Qt::CheckState::Unchecked;
         }
         return Qt::CheckState::Checked;
        }
        default:
         break;
     }
    }
    if(role == Qt::DisplayRole)
    {
      switch (index.column())
      {

         case SNAMECOL:
             return sysNameList.at(index.row());
         case UNAMECOL:
             if (rt!=nullptr) {
                 return QVariant();
             }
             return ((DefaultRoute*)rt)->getUserName();
         default:
             break;
      }
     return QVariant();
    }
}
    //@Override
    /*public*/ bool RouteFilterModel::setData(const QModelIndex &index, const QVariant &type, int role)
    {
     if(role == Qt::EditRole)
     {
        switch (index.column()) {
            case INCLUDECOL:
                Route* rt = (Route*)mgr->getBySystemName(sysNameList.at(index.row()));
                if (rt != NULL) {
                    ((DefaultRoute*)rt)->setProperty("WifiControllable", type);
                    if (!isDirty) {
                        this->fireTableChanged(new TableModelEvent(this));
                        isDirty = true;
                    }
                }
                break;
        }
     }
     return AbstractFilterModel::setData(index,type, role);
    }

    //@Override
    /*public*/ void RouteFilterModel::setIncludeColToValue(bool value) {
        for (QString sysName : sysNameList) {
            Route* rt = (Route*)mgr->getBySystemName(sysName);
            if (rt != nullptr) {
                ((DefaultRoute*)rt)->setProperty("WifiControllable", value);
            }
        }
        fireTableDataChanged();
    }

    //@Override
    /*public*/ void RouteFilterModel::SetIncludeToUserNamed() {
        for (QString sysName : sysNameList) {
            NamedBean* bean = (NamedBean*)mgr->getBySystemName(sysName);
            if (bean != nullptr) {
                QString uname = bean->getUserName();
                if ((uname != NULL) && (uname.length() > 0)) {
                    bean->setProperty("WifiControllable", true);
                } else {
//                    bean.setProperty("WifiControllable", false);
                }
            } else {
//                log->error("Failed to get bean from getBySystemName {}", sysName);
            }
        }
        fireTableDataChanged();
    }
//};
#endif
/*public*/ QString ControllerFilterFrame::getClassName(){
 return "jmri.jmrit.withrottle.ControllerFilterFrame";
}
/*private*/ /*final*/ /*static*/ Logger* TurnoutFilterModel::log = LoggerFactory::getLogger("TurnoutFilterModel");

/*private*/ /*final*/ /*static*/ Logger* ControllerFilterFrame::log = LoggerFactory::getLogger("ControllerFilterFrame");
