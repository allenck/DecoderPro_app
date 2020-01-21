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
/*public*/ void ControllerFilterFrame::initComponents() throw (Exception) {
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
#if 0
    /*final*/ TurnoutFilterModel filterModel = new TurnoutFilterModel();
    JTable table = new JTable(filterModel);
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
#if 0
    /*final*/ RouteFilterModel filterModel = new RouteFilterModel();
    JTable* table = new JTable(filterModel);
    buildTable(table);

    //JScrollPane scrollPane = new JScrollPane(table);
    tPanelLayout->addWidget(/*scrollPane*/table, 0, Qt::AlignCenter); //BorderLayout.CENTER);

    tPanelLayout->addWidget(getIncludeButtonsPanel(filterModel), 0, Qt::AlignBottom); // BorderLayout.SOUTH);
#endif
    return tPanel;
}

/*private*/ void ControllerFilterFrame::buildTable(JTable* table) {
#if 0
    table.getModel().addTableModelListener(this);

    table.setRowSelectionAllowed(false);
    table.setPreferredScrollableViewportSize(new java.awt.Dimension(580, 240));

    //table.getTableHeader().setBackground(Color.lightGray);
    table.setShowGrid(false);
    table.setShowHorizontalLines(true);
    table.setGridColor(Color.gray);
    table.setRowHeight(30);

    TableColumnModel columnModel = table.getColumnModel();

    TableColumn include = columnModel.getColumn(AbstractFilterModel.INCLUDECOL);
    include.setResizable(false);
    include.setMinWidth(60);
    include.setMaxWidth(70);

    TableColumn sName = columnModel.getColumn(AbstractFilterModel.SNAMECOL);
    sName.setResizable(true);
    sName.setMinWidth(80);
    sName.setPreferredWidth(80);
    sName.setMaxWidth(340);

    TableColumn uName = columnModel.getColumn(AbstractFilterModel.UNAMECOL);
    uName.setResizable(true);
    uName.setMinWidth(180);
    uName.setPreferredWidth(300);
    uName.setMaxWidth(440);
#endif
}
#if 0
/*private*/ QWidget* getIncludeButtonsPanel(/*final*/ AbstractFilterModel fm) {
    QWidget* pane = new QWidget();
    pane.setLayout(new BoxLayout(pane, BoxLayout.X_AXIS));
    pane.add(Box.createHorizontalGlue());

    JButton selectAllButton = new JButton(tr("ButtonSelectAll"));
    selectAllButton.addActionListener(new ActionListener() {
        //@Override
        /*public*/ void actionPerformed(ActionEvent event) {
            fm.setIncludeColToValue(true);
        }
    });
    pane.add(selectAllButton);

    JButton deselectAllButton = new JButton(tr("ButtonDeselectAll"));
    deselectAllButton.addActionListener(new ActionListener() {
        //@Override
        /*public*/ void actionPerformed(ActionEvent event) {
            fm.setIncludeColToValue(false);
        }
    });
    pane.add(deselectAllButton);

    JButton selectUserNamedButton = new JButton(tr("ButtonSelectByUserName"));
    selectUserNamedButton.addActionListener(new ActionListener() {
        //@Override
        /*public*/ void actionPerformed(ActionEvent event) {
            fm.SetIncludeToUserNamed();
        }
    });
    pane.add(selectUserNamedButton);

    return pane;
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
/*public*/ void ControllerFilterFrame::tableChanged(TableModelEvent* e) {
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
        if(orientation == Qt::Horizontal)
        {
         switch(section)
         {
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
        return Qt::ItemIsEditable | Qt::ItemIsEnabled;
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
#if 0
//class TurnoutFilterModel extends AbstractFilterModel {

//    TurnoutManager mgr = InstanceManager.turnoutManagerInstance();

    TurnoutFilterModel::TurnoutFilterModel()
    {
     TurnoutManager* mgr = InstanceManager::turnoutManagerInstance();
        sysNameList = mgr->getSystemNameList();
        mgr->addPropertyChangeListener(QPointer<PropertyChangeListener>((PropertyChangeListener*)this));
    }

    //@Override
    /*public*/ QVariant TurnoutFilterModel::data(const QModelIndex &index, int role) const
    {
     if(role == Qt::DisplayRole)
     {
        // some error checking
        if (r >= sysNameList.size()) {
            log->debug("row is greater than turnout list size");
            return QVariant();
        }
        switch (index.column()) {
            case INCLUDECOL:
                QVariant o = mgr->getBySystemName(sysNameList.at(r))->getProperty("WifiControllable");
                if ((o.isNull()) && (o.toString().toLower() == "false")) {
                    return false;
                }
                return true;
            case SNAMECOL:
                return sysNameList.at(r);
            case UNAMECOL:
                return mgr->getBySystemName(sysNameList.at(r))->getUserName();
            default:
                return QVariant();
        }
     }
     return AbstractFilterModel::data(index, role);
    }

    //@Override
    /*public*/ bool TurnoutFilterModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
     if(role == Qt::EditRole)
     {
        switch (index.column()) {
            case INCLUDECOL:
                mgr->getBySystemName(sysNameList.get(r)).setProperty("WifiControllable", type);
                if (!isDirty) {
                    this->fireTableChanged(new TableModelEvent(this));
                    isDirty = true;
                }
                break;
        }
     }
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

    RouteFilterModel::RouteFilterModel() {

        sysNameList = mgr->getSystemNameList();
        mgr->addPropertyChangeListener(QPointer<PropertyChangeListener>((PropertyChangeListener*)this));
    }

    //@Override
    /*public*/ QVariant RouteFilterModel::data(const QModelIndex &index, int role) const
    {
     if(role == Qt::DisplayRole)
     {
        // some error checking
        if (r >= sysNameList.size()) {
//            log->debug("row is greater than turnout list size");
            return QVariant();
        }
        Route* rt = mgr->getBySystemName(sysNameList.get(r));
        switch (index.column()) {
            case INCLUDECOL:
                if (rt == nullptr) {
                    return QVariant();
                }
                QVariant o = rt->getProperty("WifiControllable");
                if ((o != NULL) && (o.toString().toLower()=="false")) {
                    return (false);
                }
                return (true);
            case SNAMECOL:
                return sysNameList.at(r);
            case UNAMECOL:
                if (rt == "") {
                    return QVariant();
                }
                return rt->getUserName();
            default:
                return QVariant();
        }
     }
     return AbstractFilterModel::data(index, role);
    }

    //@Override
    /*public*/ bool RouteFilterModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
     if(role == Qt::EditRole)
     {
        switch (index.column()) {
            case INCLUDECOL:
                Route* rt = mgr->getBySystemName(sysNameList.get(r));
                if (rt != NULL) {
                    rt->setProperty("WifiControllable", type);
                    if (!isDirty) {
                        this->fireTableChanged(new TableModelEvent(this));
                        isDirty = true;
                    }
                }
                break;
        }
     }
     return AbstractFilterModel::setData(index,value, role);
    }

    //@Override
    /*public*/ void RouteFilterModel::setIncludeColToValue(bool value) {
        for (QString sysName : sysNameList) {
            Route* rt = mgr->getBySystemName(sysName);
            if (rt != nullptr) {
                rt->setProperty("WifiControllable", value);
            }
        }
        fireTableDataChanged();
    }

    //@Override
    /*public*/ void RouteFilterModel::SetIncludeToUserNamed() {
        for (QString sysName : sysNameList) {
            NamedBean* bean = mgr->getBySystemName(sysName);
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

/*private*/ /*final*/ /*static*/ Logger* ControllerFilterFrame::log = LoggerFactory::getLogger("ControllerFilterFrame");
