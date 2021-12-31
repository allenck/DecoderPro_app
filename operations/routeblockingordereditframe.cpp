#include "routeblockingordereditframe.h"
#include "instancemanager.h"
#include "borderfactory.h"
#include "jscrollpane.h"
#include "gridbaglayout.h"
#include <QMenuBar>
#include "control.h"
#include "loggerfactory.h"
#include "setup.h"
#include "logger.h"
#include "operationsxml.h"
#include "propertychangeevent.h"
#include "jtablepersistencemanager.h"


namespace Operations {

/**
 * Frame for user edit of q route's blocking order.
 *
 * @author Dan Boudreau Copyright (C) 2021
 */
///*public*/  class RouteBlockingOrderEditFrame extends OperationsFrame implements java.beans.PropertyChangeListener {



/*public*/  RouteBlockingOrderEditFrame::RouteBlockingOrderEditFrame(Route* route, QWidget* parent)
    : Operations::OperationsFrame(parent)
{
    //super(Bundle.getMessage("Blocking Order"));
    log = new Logger("RouteBlockingOrderEditFrame");
    routeModel = new RouteBlockingOrderEditTableModel();
    routeTable->setModel(routeModel);

    initComponents(route);
}

/*private*/ void RouteBlockingOrderEditFrame::initComponents(Route* route) {
    _route = route;

    // load managers
    routeManager = (RouteManager*)InstanceManager::getDefault("RouteManager");

    // Set up the jtable in a Scroll Pane..
    //routePane = new JScrollPane(routeTable);
    JPanel* routePane = new JPanel(new QVBoxLayout());
    //routePane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
    routePane->setBorder(BorderFactory::createTitledBorder(""));
    routePane->layout()->addWidget(routeTable);

    routeModel->initTable(this, routeTable, _route);

    if (_route != nullptr) {
        _route->addPropertyChangeListener(this);
        routeName->setText(_route->getName());
        routeComment->setText(_route->getComment());
        enableButtons(route->getStatus() != (Route::TRAIN_BUILT)); // do not allow user to modify a built train
    }

    getContentPane()->setLayout(new QVBoxLayout());//getContentPane(), BoxLayout.Y_AXIS));

    // Set up the panels
    JPanel* p1 = new JPanel();
    p1->setLayout(new QHBoxLayout());//p1, BoxLayout.X_AXIS));
//    JScrollPane* p1Pane = new JScrollPane();
//    p1Pane->setWidget(p1);
//    //p1Pane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_NEVER);
//    p1Pane->setMaximumSize(QSize(2000, 200));
//    p1Pane->setBorder(BorderFactory::createTitledBorder(""));

    // name panel
    JPanel* pName = new JPanel();
    pName->setLayout(new GridBagLayout());
    pName->setBorder(BorderFactory::createTitledBorder(tr("Name")));
    addItem(pName, routeName, 0, 0);

    // comment panel
    JPanel* pComment = new JPanel();
    pComment->setLayout(new GridBagLayout());
    pComment->setBorder(BorderFactory::createTitledBorder(tr("Comment")));
    addItem(pComment, routeComment, 0, 0);

    p1->layout()->addWidget(pName);
    p1->layout()->addWidget(pComment);

    JPanel* pF = new JPanel(new GridBagLayout());
    addItem(pF, new JLabel(tr("Train Front")), 0, 0);

    JPanel* pR = new JPanel(new GridBagLayout());
    addItem(pR, new JLabel(tr("Train Rear")), 0, 0);

    JPanel* pB = new JPanel();
    pB->setLayout(new GridBagLayout());
//    QScrollArea* pBPane = new QScrollArea(/*pB*/);
////    pBPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_NEVER);
//    pBPane->setMaximumSize(QSize(2000, 200));
//    JPanel* pBPaneBorder = new JPanel(new QVBoxLayout());
//    pBPaneBorder->layout()->addWidget(pBPane);
//    pBPane->setWidget(pB);
//    pBPaneBorder->setBorder(BorderFactory::createTitledBorder(""));


    addItem(pB, resetRouteButton, 2, 0);
    addItem(pB, saveRouteButton, 3, 0);

    getContentPane()->layout()->addWidget(p1/*Pane*/);
    getContentPane()->layout()->addWidget(pF);
    getContentPane()->layout()->addWidget(routePane);
    getContentPane()->layout()->addWidget(pR);
    getContentPane()->layout()->addWidget(pB);

    // setup buttons
    addButtonAction(resetRouteButton);
    addButtonAction(saveRouteButton);

    // build menu
    QMenuBar* menuBar = new QMenuBar();
    setMenuBar(menuBar);
    addHelpMenu("package.jmri.jmrit.operations.Operations_RouteBlockingOrder", true); // NOI18N

    // set frame size and route for display
    initMinimumSize(QSize(Control::panelWidth500, Control::panelHeight400));
}

// Save, Delete, Add
//@Override
/*public*/  void RouteBlockingOrderEditFrame::buttonActionPerformed(QWidget *b) {
    if (b == saveRouteButton) {
        log->debug("route save button activated");
        saveRoute();
        if (Setup::isCloseWindowOnSaveEnabled()) {
            dispose();
        }
    }
    if (b == resetRouteButton) {
        log->debug("route reset button activated");
        if (_route != nullptr) {
            _route->resetBlockingOrder();
        }
    }
}

/*private*/ void RouteBlockingOrderEditFrame::saveRoute() {
//    if (routeTable->isEditing()) {
//        log->debug("route table edit true");
//        routeTable->getCellEditor()->stopCellEditing();
//    }
    // save route file
    OperationsXml::save();
}

/*private*/ void RouteBlockingOrderEditFrame::enableButtons(bool enabled) {
    resetRouteButton->setEnabled(enabled);
    saveRouteButton->setEnabled(enabled);
    routeTable->setEnabled(enabled);
}

//@Override
/*public*/  void RouteBlockingOrderEditFrame::dispose() {
    JTablePersistenceManager* tpm =
    ((JTablePersistenceManager*)InstanceManager::getOptionalDefault("JTablePersistenceManager"));
    if(tpm)
        tpm->stopPersisting(routeTable);
//    });
    if (_route != nullptr) {
        _route->removePropertyChangeListener(this);
    }
    routeModel->dispose();
    OperationsFrame::dispose();
}

//@Override
/*public*/  void RouteBlockingOrderEditFrame::propertyChange(PropertyChangeEvent* e) {
    if (Control::SHOW_PROPERTY) {
        log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName(), e->getOldValue().toString(), e
                ->getNewValue().toString()));
    }
    if (e->getPropertyName() == (Route::ROUTE_STATUS_CHANGED_PROPERTY)) {
        enableButtons(_route->getStatus() !=(Route::TRAIN_BUILT)); // do not allow user to modify a built train
    }
}

///*private*/ /*final*/ /*static*/ Logger* RouteBlockingOrderEditFrame::log = LoggerFactory::getLogger("RouteBlockingOrderEditFrame");

} // namespace Operations
