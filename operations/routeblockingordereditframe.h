#ifndef OPERATIONS_ROUTEBLOCKINGORDEREDITFRAME_H
#define OPERATIONS_ROUTEBLOCKINGORDEREDITFRAME_H

#include "operationsframe.h"
#include "route.h"
#include "routemanager.h"
#include "train.h"
#include "routeblockingorderedittablemodel.h"
#include "jtable.h"
#include "jbutton.h"
#include "jlabel.h"

class Logger;
namespace Operations {

 class RouteBlockingOrderEditTableModel;
 class RouteBlockingOrderEditFrame : public OperationsFrame, public PropertyChangeListener
 {
     Q_OBJECT
     Q_INTERFACES(PropertyChangeListener)
 public:
     RouteBlockingOrderEditFrame(Route* route, QWidget* parent=nullptr);
     /*public*/  void dispose()override;
     QObject* self() override {return (QObject*)this;}
     QString getClassName() override {return "jmri.jmrit.operations.routes.tools.RouteBlockingOrderEditFrame";}
 public slots:
     /*public*/  void buttonActionPerformed(QWidget* b )override;
     /*public*/  void propertyChange(PropertyChangeEvent* e)override;

 private:
     RouteBlockingOrderEditTableModel* routeModel;// = new RouteBlockingOrderEditTableModel();
     JTable* routeTable = new JTable(/*(TableModel*)routeModel, nullptr*/);
     JPanel* routePane;

     RouteManager* routeManager;

     Route* _route = nullptr;
     Train* _train = nullptr;
     Logger* log;

     // major buttons
     JButton* saveRouteButton = new JButton(tr("Save Route"));
     JButton* resetRouteButton = new JButton(tr("Reset"));

     JLabel* routeName = new JLabel();
     JLabel* routeComment = new JLabel();
     /*private*/ void initComponents(Route* route);
     /*private*/ void saveRoute();
     /*private*/ void enableButtons(bool enabled);

 };

} // namespace Operations

#endif // OPERATIONS_ROUTEBLOCKINGORDEREDITFRAME_H
