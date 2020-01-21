#include "abstracttableaction.h"
#include "instancemanager.h"
#include "jmriuserpreferencesmanager.h"
#include "abstracttabletabaction.h"
#include <QSortFilterProxyModel>
#include "jtable.h"
#include <qheaderview.h>
#include <QPushButton>
#include "beantabledatamodel.h"
#include "mysortfilterproxymodel.h"

AbstractTableAction::AbstractTableAction(QObject *parent) :
    AbstractAction(parent)
{
}
/**
 * Swing action to create and register a
 * SignalHeadTable GUI
 *
 * @author	Bob Jacobsen    Copyright (C) 2003
 * @version     $Revision: 28013 $
 */

// /*abstract*/ /*public*/ class AbstractTableAction extends AbstractAction {

    /**
     *
     */
// /*private*/ static final long serialVersionUID = -7910901479004827844L;

/*public*/ AbstractTableAction::AbstractTableAction(QString actionName,QObject *parent) :
    AbstractAction(actionName, parent)
{
 //super(actionName);
 _includeAddButton = true;
 log = new Logger("AbstractTableAction");
 m=NULL;
 table = NULL;
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

///*public*/ AbstractTableAction(QString actionName, QObject option, QObject *parent) :
//    QObject(parent)
//{
// super(actionName);
//}


///*public*/ static final ResourceBundle rbean = ResourceBundle.getBundle("jmri.NamedBeanBundle");
///*public*/ static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.beantable.BeanTableBundle");

/**
 * Create the JTable DataModel, along with the changes
 * for the specific NamedBean type
 */

/*protected*/ /*abstract*/ void AbstractTableAction::createModel() {}

/**
 * Include the correct title
 */

/*protected*/ /*abstract*/ void AbstractTableAction::setTitle() {}


/*public*/ void AbstractTableAction::actionPerformed(ActionEvent* /*e*/)
{
 // create the JTable model, with changes for specific NamedBean
 createModel();
 if(m != NULL)
 {
 //TableSorter sorter = new TableSorter(m);
 MySortFilterProxyModel* sorter = new MySortFilterProxyModel(m);
 //sorter->setSourceModel((QAbstractItemModel*)m);
 dataTable = m->makeJTable(m->getMasterClassName(), m, sorter);
 dataTable->setSortingEnabled(true);
 //sorter.setTableHeader(dataTable.getTableHeader());

 // allow reordering of the columns
 //dataTable.getTableHeader().setReorderingAllowed(true);

 // create the frame
//    f = new BeanTableFrame(m, helpTarget(), dataTable){
//    /**
//     *
//     */
//    private static final long serialVersionUID = 1123302534258100353L;

//    /**
//     * Include an "add" button
//     */
//    void extras() {
//        if(includeAddButton){
//            JButton addButton = new JButton(this.tr("ButtonAdd"));
//            addToBottomBox(addButton, this.getClass().getName());
//            addButton.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    addPressed(e);
//                }
//            });
//        }
//        }
//    };
  f = new ATABeanTableFrame(m, helpTarget(), dataTable, this);
 }
 else
 {
  f= new ATABeanTableFrame(this);
 }
 buildMenus(f);
 setMenuBar(f);
 setTitle();
 addToFrame(f);
 f->adjustSize();
 f->setVisible(true);
}

ATABeanTableFrame::ATABeanTableFrame(AbstractTableAction *act)
{
 this->act = act;
}

ATABeanTableFrame::ATABeanTableFrame(BeanTableDataModel *m, QString helpTarget, JTable *table, AbstractTableAction *act) : BeanTableFrame(m, helpTarget,table)
{
 this->act = act;
}
void ATABeanTableFrame::extras()
{
 if(act->includeAddButton())
 {
  QPushButton* addButton = new QPushButton(tr("Add"));
  addToBottomBox(addButton, "this.getClass().getName()");
//  addButton.addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        addPressed(e);
//    }
//  });
  QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(addButton->sizePolicy().hasHeightForWidth());
  addButton->setSizePolicy(sizePolicy);
  connect(addButton, SIGNAL(clicked()),act, SLOT(addPressed()));
 }
}
/*public*/ QString ATABeanTableFrame::getClassName()
{
 return "jmri.jmrit.beantable.BeanTableFrame";
}


/*public*/ BeanTableDataModel* AbstractTableAction::getTableDataModel()
{
 createModel();
 return m;
}

/*public*/ void AbstractTableAction::setFrame(BeanTableFrame* frame){
    f=frame;
}

/**
 * Allow subclasses to add to the frame
 * without have to actually subclass the BeanTableDataFrame
 */
/*public*/ void AbstractTableAction::addToFrame(BeanTableFrame* /*f*/) {
}

/**
 * If the subClass is being included in a greater tabbed frame, then this
 * method is used to add the details to the tabbed frame
 */
 /*public*/ void AbstractTableAction::addToPanel(AbstractTableTabAction* f) { }

/**
 * If the subClass is being included in a greater tabbed frame, then this
 * is used to specify which manager the subclass should be using.
 */
/*protected*/ void AbstractTableAction::setManager(Manager* /*man*/) { }
/**
 * Allow subclasses to add alter the frames Menubar
 * without have to actually subclass the BeanTableDataFrame
 */
/*public*/ void AbstractTableAction::setMenuBar(BeanTableFrame* /*f*/){
}

/*public*/ QWidget* AbstractTableAction::getPanel(){
    return NULL;
}

/*public*/ void AbstractTableAction::dispose() {
//    if (m!=NULL){
//        m.dispose();
//    }
}

/**
 * Specify the JavaHelp target for this specific panel
 */
/*protected*/ QString AbstractTableAction::helpTarget() {
    return "index";  // by default, go to the top
}

/*public*/ QString AbstractTableAction::getClassDescription() { return "Abstract Table Action"; }

/*public*/ void AbstractTableAction::setMessagePreferencesDetails()
{
 QMap< int,QString>* options =  new QMap< int,QString>();
 options->insert(0x00, tr("Always Ask"));
 options->insert(0x01, tr("Never Delete"));
 options->insert(0x02, tr("Delete Without Prompting"));
 ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->setMessageItemDetails(getClassName(), "deleteInUse", tr("When Deleting an iten that is in use"), options, 0x00);

}

/*protected*/ /*abstract*/ QString AbstractTableAction::getClassName() {return "";}

/*public*/ bool AbstractTableAction::includeAddButton()
{ return _includeAddButton; }


/**
* Used with the Tabbed instances of table action, so that the print option
* is handled via that on the appropriate tab.
*/
/*public*/ void AbstractTableAction::print(JTable::PrintMode /*mode*/, QString /*headerFormat*/, QString /*footerFormat*/){ log->error("Caught here");}

/*protected*/ /*abstract*/ void AbstractTableAction::addPressed(ActionEvent* /*e*/) {}


