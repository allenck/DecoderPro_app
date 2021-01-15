#ifndef WARRANTROUTE_H
#define WARRANTROUTE_H
#include "jmrijframe.h"
#include "abstracttablemodel.h"
#include "windowlistener.h"
#include "actionlistener.h"
#include <QButtonGroup>
#include <QAbstractButton>
#include "jdialog.h"
#include "libpref_global.h"

class SpeedUtil;
class DefaultMutableTreeNode;
class DefaultTreeModel;
class Warrant;
class DccLocoAddress;
class OBlock;
class QComboBox;
class RosterEntry;
class JTextField;
class RouteFinder;
class BlockOrder;
class RouteTableModel;
class JDialog;
class RouteLocation;
class LIBPREFSHARED_EXPORT WarrantRoute : public JmriJFrame
{
 Q_OBJECT
public:
 explicit WarrantRoute(QWidget *parent = 0);
 enum Location {ORIGIN, DEST, VIA, AVOID};
 /*public*/ void dispose();
 /*public*/ /*abstract*/ virtual void selectedRoute(QList <BlockOrder*>* orders);

 /*public*/ int getDepth();
 /*public*/ void setDepth(int d) ;
 /*public*/ QWidget* searchDepthPanel(bool vertical);
 /*public*/ void setOrders(QList <BlockOrder*> oList);
 /*public*/ QList<BlockOrder*>* getOrders();
 /*public*/ void showWarning(QString msg);
 /*public*/ BlockOrder* getViaBlockOrder();
 /*public*/ BlockOrder* getAvoidBlockOrder();
 /*public*/ QWidget* calculatePanel(bool vertical);
 /*public*/ QWidget* makePickListPanel();

signals:

public slots:
  /*public*/ /*abstract*/ virtual void propertyChange(PropertyChangeEvent* e);
 void on_dccNumBox();
 void on_rosterBoxCurrentIndexChanged(QString);
 /*public*/ void actionPerformed(JActionEvent* /*e*/); // actionEvent required!
 void onButton();

private:
 RouteLocation* _focusedField;
 static int STRUT_SIZE;// = 10;
 static QString PAD;// = "               ";
 /*private*/ JDialog*         _pickRouteDialog;
 /*private*/ RouteTableModel* _routeModel;
 /*private*/ QList <BlockOrder*>* _orders;// = new ArrayList <BlockOrder>();
 /*private*/ JFrame*      _debugFrame;
 /*private*/ RouteFinder* _routeFinder;
 /*private*/ int         _depth;// =20;
 /*private*/ JTextField*  _searchDepth;// =  new JTextField(5);

 /*private*/ RosterEntry* _train;
 /*private*/ QString _trainId;// = NULL;
 /*private*/ QComboBox* _rosterBox;// = new JComboBox<String>();
 /*private*/ JTextField* _dccNumBox;// = new JTextField();
 /*private*/ JTextField* _trainNameBox;// = new JTextField(6);
 /*private*/ /*final*/ QPushButton* _viewProfile;// = new JButton(Bundle.getMessage("ViewProfile"));
 /*private*/ void getRoster();
 /*private*/ QWidget* makeLabelCombo(QString title, QComboBox* box, QString tooltip);
 static /*private*/ QString pathIsValid(OBlock* block, QString pathName);
 /*private*/ bool pathsAreValid(OBlock* block);
 Logger* log;
 /*private*/ void clearFrames();
 /*private*/ void clearFields();
 /*private*/ Warrant* _tempWarrant;   // only used in pickRoute() method
 void doAction(QObject* obj);
 /*private*/ bool setOriginBlock() ;
 /*private*/ bool setDestinationBlock() ;
 /*private*/ bool setViaBlock() ;
 /*private*/ bool setAvoidBlock();
 /*private*/ void showTempWarrant(QList<BlockOrder*>* orders);
 /*private*/ QPushButton* _calculateButton;
 /*private*/ JmriJFrame* _pickListFrame;

private slots:
 /*private*/ void calculate();

protected:
 static /*protected*/ QWidget* makeTextBoxPanel(bool vertical, QWidget* comp, QString label, QString tooltip);
 static /*protected*/ QWidget* makeTextAndButtonPanel(QWidget* comp, QWidget* button, QString label, QString tooltip);
 static /*protected*/ QWidget* makeTextBoxPanel(QWidget* textField, QString label, QString tooltip);
 /*protected*/ QWidget* makeTrainIdPanel(QWidget* comp);

protected:
 /*protected*/ RouteLocation*  _origin;// = new RouteLocation(Location::ORIGIN);
 /*protected*/ RouteLocation*  _destination;// = new RouteLocation(Location.DEST);
 /*protected*/ RouteLocation*  _via;// =  new RouteLocation(Location.VIA);
 /*protected*/ RouteLocation*  _avoid;// =  new RouteLocation(Location.AVOID);
 /*protected*/ QString setTrainInfo(QString name);
 /*protected*/ RosterEntry* getTrain() ;
 /*protected*/ void setTrainName(QString name);
 /*protected*/ QString getTrainName();
 /*protected*/ void setAddress(QString address);
 /*protected*/ QString getAddress();
 /*protected*/ QString getTrainId() ;
 /*protected*/ DccLocoAddress* getLocoAddress();
 /*protected*/ QString checkLocoAddress();
 /*protected*/ void clearRoute();
 /*protected*/ QWidget* makeBlockPanels();
 /*protected*/ QWidget* makeTrainPanel();
 /*protected*/ void mouseClickedOnBlock(OBlock* block);
 /*protected*/ QString routeIsValid();
 /*protected*/ QString findRoute();
 /*protected*/ void stopRouteFinder();
 /*protected*/ void debugRoute(DefaultTreeModel* tree, BlockOrder* origin, BlockOrder* dest);
 /*protected*/ void pickRoute(QList <DefaultMutableTreeNode*>* destNodes, DefaultTreeModel* routeTree);
 /*protected*/ void showRoute(DefaultMutableTreeNode* destNode, DefaultTreeModel* tree);
 /*protected*/ QWidget* makeRouteTablePanel();
 /*protected*/ QWidget* makeBlockPanels(bool add);
/*protected*/ SpeedUtil* _speedUtil;

protected slots:
 /*protected*/ void clearTempWarrant();
 //oid on_selectClicked();

 friend class WarrantPreferencesPanel;
 friend class RouteLocation;
 friend class RouteTableModel;
 friend class NXFrame;
 friend class WarrantTableAction;
 friend class WarrantFrame;
 friend class RouteFinder;
 friend class PRWindowListener;
 friend class SelectActionListener;
 friend class ShowActionListener;
};
/*********** route blocks **************************/

/*protected*/ class LIBPREFSHARED_EXPORT RouteLocation : public QObject /*java.awt.event.MouseAdapter*/
{
 Q_OBJECT
WarrantRoute* warrantRoute;
    WarrantRoute::Location location;
    /*private*/ BlockOrder* order;
    JTextField* blockBox;// = new JTextField();
    /*private*/ QComboBox* pathBox;// = new JComboBox<String>();
    /*private*/ QComboBox* portalBox;
public:
    RouteLocation(WarrantRoute::Location loc, WarrantRoute* warrantRoute);
    /*public*/ void mouseClicked(QMouseEvent* e) ;
public slots:
    void on_blockBox_editingCompleted();
    void on_pathBox_currentIndexChanged(int);
    void on_portalBox_currentIndexChanged(int);
signals:
    void actionPerformed(JActionEvent *e);

private:
    /*private*/ QWidget* makePanel(QString title, QString tooltip, QString box1Name, QString box2Name, WarrantRoute* parent);
    /*private*/ QWidget* makeBlockBox(QString tooltip);
    /*private*/ void clearFields() ;
    /*private*/ bool checkBlockBox(JTextField* box) ;
    /*private*/ bool checkPathBox(QComboBox* box);
    /*private*/ bool checkPortalBox(QComboBox* box) ;
    /*private*/ void setOrderEntryPortal();
    /*private*/ void setOrderExitPortal() ;
    /*private*/ BlockOrder* getOrder();
    /*private*/ void setPortalName(QString name) ;
    /*private*/ void setPathName(QString name);
    /*protected*/ QString getBlockName();
    /*private*/ OBlock* getEndPointBlock();
    /*private*/ bool setBlock();
    /*private*/ bool setBlock(OBlock* block);
    /*private*/ bool setPathBox(OBlock* block) ;
    /*private*/ void setPortalBox(BlockOrder* order) ;
    /*private*/ void setNextLocation() ;

protected:
    /*protected*/ void setOrder(BlockOrder* o) ;
 friend class WarrantRoute;
 friend class WarrantFrame;
};       // end RouteLocation

/************************* Route Table ******************************/
class RouteTableModel : public AbstractTableModel
{
 Q_OBJECT
    /**
     *
     */
//    /*private*/ static final long serialVersionUID = 1966890806689115258L;
 WarrantRoute* warrantRoute;
public:
 enum COLUMNS
 {
   BLOCK_COLUMN = 0,
   ENTER_PORTAL_COL =1,
   PATH_COLUMN = 2,
   DEST_PORTAL_COL = 3,
   NUMCOLS = 4
 };

    /*public*/ RouteTableModel(WarrantRoute* warrantRoute);
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ QString getColumnClass(int col);
    /*public*/ int getPreferredWidth(int col);
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
};
class PRWindowListener :public WindowListener
{
 Q_OBJECT
 WarrantRoute* caller;
public:
 PRWindowListener(WarrantRoute* caller) { this->caller = caller;}
 void windowClosing(QCloseEvent */*e*/)
 {
  caller->clearTempWarrant();
 }
};

class SelectActionListener : public ActionListener
{
 Q_OBJECT
 QButtonGroup* buts;
 JDialog* dialog;
 QList <DefaultMutableTreeNode*>* dNodes;
 DefaultTreeModel* tree;
 WarrantRoute* caller;
public slots:
 /*public*/ void actionPerformed(JActionEvent* /*e*/ = 0)
 {
  if (buts->checkedButton()!=NULL)
  {
   caller->clearTempWarrant();
   int i = buts->checkedButton()->text().toInt();
   caller->showRoute(dNodes->at(i), tree);
   caller->selectedRoute(caller->_orders);
   dialog->close();
  }
  else
  {
   caller->showWarning(tr("SelectRoute"));
  }
 }
public:
 ActionListener* init(QButtonGroup* bg, JDialog* d, QList <DefaultMutableTreeNode*>* dn, DefaultTreeModel* t, WarrantRoute* caller) {
 buts = bg;
 dialog = d;
 dNodes = dn;
 tree = t;
 this->caller = caller;
 return this;
 }
};
class ShowActionListener : public ActionListener
{
 Q_OBJECT
 QButtonGroup* buts;
 QList <DefaultMutableTreeNode*>* destinationNodes;
 DefaultTreeModel* tree;
 WarrantRoute* caller;
public slots:
 /*public*/ void actionPerformed(JActionEvent* /*e*/ = 0)
 {
  if (buts->checkedButton()!=NULL)
  {
   caller->clearTempWarrant();
   int i = buts->checkedButton()->text().toInt();
   caller->showRoute(destinationNodes->at(i), tree);
   caller->showTempWarrant(caller->_orders);
  }
  else
  {
   caller->showWarning(tr("SelectRoute"));
  }
 }
public:
 ActionListener* init(QButtonGroup*bg, QList <DefaultMutableTreeNode*>* dn, DefaultTreeModel* t, WarrantRoute* caller) {
     buts = bg;
     destinationNodes = dn;
     tree = t;
     this->caller = caller;
     return this;
 }
};
#endif // WARRANTROUTE_H
