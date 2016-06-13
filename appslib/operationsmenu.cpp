#include "operationsmenu.h"
#include "routestableaction.h"
#include "enginestableaction.h"
#include "operationssetupaction.h"
#include "carstableaction.h"
#include "locationstableaction.h"
#include "trainstableaction.h"
#include "routestableaction.h"

//OperationsMenu::OperationsMenu(QWidget *parent) :
//    QMenu(parent)
//{
//}
/**
 * Create a "Operations" menu
 *
 * @author Bob Jacobsen Copyright 2003
 * @author Daniel Boudreau Copyright 2008
 * @version $Revision: 28746 $
 */
// /*public*/ class OperationsMenu extends JMenu {

/**
*
*/
//private static final long serialVersionUID = 701227477994394798L;

/*public*/ OperationsMenu::OperationsMenu(QString name,QWidget *parent) :
    QMenu(name, parent)
{
 //this();
 common();
 //setText(name);
}

/*public*/ OperationsMenu::OperationsMenu(QWidget *parent) :
    QMenu(parent)
{
 //super();
 common();
}

void OperationsMenu::common()
{

 setTitle(tr("Operations"));

 addAction(new OperationsSetupAction(this));

 addAction(new Operations::LocationsTableAction(this));
 addAction(new Operations::CarsTableAction(this));
 addAction(new EnginesTableAction(this));
 addAction(new Operations::RoutesTableAction(this));
 addAction(new Operations::TrainsTableAction(this));

}
