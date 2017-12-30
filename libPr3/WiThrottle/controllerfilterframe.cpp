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
#if 0
/*public*/ abstract class AbstractFilterModel extends AbstractTableModel implements PropertyChangeListener {

    List<String> sysNameList = NULL;
    boolean isDirty;

    //@Override
    /*public*/ Class<?> getColumnClass(int c) {
        if (c == INCLUDECOL) {
            return Boolean.class;
        } else {
            return String.class;
        }
    }

    //@Override
    /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
        if (e.getPropertyName().equals("length")) {
            fireTableDataChanged();
        }
    }

    /*public*/ void dispose() {
        InstanceManager.turnoutManagerInstance().removePropertyChangeListener(this);
        InstanceManager.getDefault(jmri.RouteManager.class).removePropertyChangeListener(this);
    }

    //@Override
    /*public*/ String getColumnName(int c) {
        return COLUMN_NAMES[c];
    }

    //@Override
    /*public*/ int getColumnCount() {
        return 3;
    }

    //@Override
    /*public*/ int getRowCount() {
        return sysNameList.size();
    }

    //@Override
    /*public*/ boolean isCellEditable(int r, int c) {
        return (c == INCLUDECOL);
    }

    abstract void setIncludeColToValue(boolean value);

    abstract void SetIncludeToUserNamed();

    /*public*/ static /*final*/ int SNAMECOL = 0;
    /*public*/ static /*final*/ int UNAMECOL = 1;
    /*public*/ static /*final*/ int INCLUDECOL = 2;
};

class TurnoutFilterModel extends AbstractFilterModel {

    TurnoutManager mgr = InstanceManager.turnoutManagerInstance();

    TurnoutFilterModel() {

        sysNameList = mgr.getSystemNameList();
        mgr.addPropertyChangeListener(this);
    }

    //@Override
    /*public*/ Object getValueAt(int r, int c) {

        // some error checking
        if (r >= sysNameList.size()) {
            log->debug("row is greater than turnout list size");
            return NULL;
        }
        switch (c) {
            case INCLUDECOL:
                Object o = mgr.getBySystemName(sysNameList.get(r)).getProperty("WifiControllable");
                if ((o != NULL) && (o.toString().equalsIgnoreCase("false"))) {
                    return Boolean.valueOf(false);
                }
                return Boolean.valueOf(true);
            case SNAMECOL:
                return sysNameList.get(r);
            case UNAMECOL:
                return mgr.getBySystemName(sysNameList.get(r)).getUserName();
            default:
                return NULL;
        }
    }

    //@Override
    /*public*/ void setValueAt(Object type, int r, int c) {

        switch (c) {
            case INCLUDECOL:
                mgr.getBySystemName(sysNameList.get(r)).setProperty("WifiControllable", type);
                if (!isDirty) {
                    this.fireTableChanged(new TableModelEvent(this));
                    isDirty = true;
                }
                break;
        }
    }

    //@Override
    /*public*/ void setIncludeColToValue(boolean value) {
        for (String sysName : sysNameList) {
            mgr.getBySystemName(sysName).setProperty("WifiControllable", value);
        }
        fireTableDataChanged();
    }

    //@Override
    /*public*/ void SetIncludeToUserNamed() {
        for (String sysName : sysNameList) {
            NamedBean bean = mgr.getBySystemName(sysName);
            String uname = bean.getUserName();
            if ((uname != NULL) && (uname.length() > 0)) {
                bean.setProperty("WifiControllable", true);
            } else {
                bean.setProperty("WifiControllable", false);
            }
        }
        fireTableDataChanged();
    }
};

class RouteFilterModel extends AbstractFilterModel {

    RouteManager mgr = InstanceManager.getDefault(jmri.RouteManager.class);

    RouteFilterModel() {

        sysNameList = mgr.getSystemNameList();
        mgr.addPropertyChangeListener(this);
    }

    //@Override
    /*public*/ Object getValueAt(int r, int c) {

        // some error checking
        if (r >= sysNameList.size()) {
            log->debug("row is greater than turnout list size");
            return NULL;
        }
        Route rt = mgr.getBySystemName(sysNameList.get(r));
        switch (c) {
            case INCLUDECOL:
                if (rt == NULL) {
                    return NULL;
                }
                Object o = rt.getProperty("WifiControllable");
                if ((o != NULL) && (o.toString().equalsIgnoreCase("false"))) {
                    return Boolean.valueOf(false);
                }
                return Boolean.valueOf(true);
            case SNAMECOL:
                return sysNameList.get(r);
            case UNAMECOL:
                if (rt == NULL) {
                    return NULL;
                }
                return rt.getUserName();
            default:
                return NULL;
        }
    }

    //@Override
    /*public*/ void setValueAt(Object type, int r, int c) {

        switch (c) {
            case INCLUDECOL:
                Route rt = mgr.getBySystemName(sysNameList.get(r));
                if (rt != NULL) {
                    rt.setProperty("WifiControllable", type);
                    if (!isDirty) {
                        this.fireTableChanged(new TableModelEvent(this));
                        isDirty = true;
                    }
                }
                break;
        }
    }

    //@Override
    /*public*/ void setIncludeColToValue(boolean value) {
        for (String sysName : sysNameList) {
            Route rt = mgr.getBySystemName(sysName);
            if (rt != NULL) {
                rt.setProperty("WifiControllable", value);
            }
        }
        fireTableDataChanged();
    }

    //@Override
    /*public*/ void SetIncludeToUserNamed() {
        for (String sysName : sysNameList) {
            NamedBean bean = mgr.getBySystemName(sysName);
            if (bean != NULL) {
                String uname = bean.getUserName();
                if ((uname != NULL) && (uname.length() > 0)) {
                    bean.setProperty("WifiControllable", true);
                } else {
                    bean.setProperty("WifiControllable", false);
                }
            } else {
                log->error("Failed to get bean from getBySystemName {}", sysName);
            }
        }
        fireTableDataChanged();
    }
};
#endif
/*private*/ /*final*/ /*static*/ Logger* ControllerFilterFrame::log = LoggerFactory::getLogger("ControllerFilterFrame");
