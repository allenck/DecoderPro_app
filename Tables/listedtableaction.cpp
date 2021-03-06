#include "listedtableaction.h"
#include "tablesframe.h"
#include "libtables.h"
#include "listedtableframe.h"
#include "instancemanager.h"

//ListedTableAction::ListedTableAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Table Action for dealing with all the tables in a single view with a list
 * option to the left hand side.
 * <P>
 * @author	Bob Jacobsen Copyright (C) 2003
 * @author	Kevin Dickerson Copyright (C) 2009
 * @version	$Revision: 28746 $
 */
/**
 * Table Action for dealing with all the tables in a single view with a list
 * option to the left hand side.
 * <P>
 * @author	Bob Jacobsen Copyright (C) 2003
 * @author	Kevin Dickerson Copyright (C) 2009
 * @version	$Revision: 28746 $
 */
///*public*/ class ListedTableAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = 6097143838837199839L;
///*public*/ static final ResourceBundle rbean = ResourceBundle.getBundle("jmri.jmrit.beantable.BeanTableBundle");

/**
 * Create an action with a specific title.
 * <P>
 * Note that the argument is the Action title, not the title of the
 * resulting frame. Perhaps this should be changed?
 *
 * @param s
 */
/*public*/ ListedTableAction::ListedTableAction(QString s, QString selection, QObject *parent) :
  AbstractAction(s,parent) {
 //super(s);
 common();
  title = s;
  gotoListItem = selection;
}

/*public*/ ListedTableAction::ListedTableAction(QString s, QString selection, int divider, QObject *parent) :
  AbstractAction(s,parent)
{
 //super(s);
 common();
 title = s;
 gotoListItem = selection;
 dividerLocation = divider;
}

/*public*/ ListedTableAction::ListedTableAction(QString s, int divider, QObject *parent) :
  AbstractAction(s, parent)
{
 //super(s);
 common();
 title = s;
 dividerLocation = divider;
}

/*public*/ListedTableAction:: ListedTableAction(QString s,QObject *parent) :
  AbstractAction(s, parent)
{
//super(s);
 common();
 title = s;
}

/*public*/ ListedTableAction::ListedTableAction(QObject *parent) :
  AbstractAction(tr("Listed Table Access"), parent)
{
 //this(rbean.getString("TitleListedTable"));
 common();
}

void ListedTableAction::common()
{
 title = tr("Listed Table Access");
 dividerLocation = 0;
 libTables = NULL;
 f = nullptr;
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void ListedTableAction::actionPerformed()
{
    // create the JTable model, with changes for specific NamedBean
    /* create the frame in a seperate thread outside of swing so that we do not
     hog the swing thread which is also used for connection traffic */
//    Runnable r = new Runnable() {
//        /*public*/ void run() {
 if(InstanceManager::getNullableDefault("ListedTableFrame")!= nullptr)
 {
  f = static_cast<ListedTableFrame*>(InstanceManager::getNullableDefault("ListedTableFrame"));
  f->setVisible(true);
  f->gotoListItem(gotoListItem);
  return;
 }
  f = new ListedTableFrame(title);
  f->setDefaultCloseOperation(JFrame::HIDE_ON_CLOSE);
  //                /**
  //                 *
  //                 */
  //                private static final long serialVersionUID = -2029385586619585289L;
  //            };
  f->initComponents();
  addToFrame(f);

  f->gotoListItem(gotoListItem);
  f->adjustSize();

  f->setDividerLocation(dividerLocation);
  f->setVisible(true);
  f->setFrameLocation();
//        }
//    };
//    Thread thr = new Thread(r, "Listed Table Generation");
//    thr.start();
}

///*public*/ void actionPerformed(ActionEvent e) {
//    actionPerformed();
//}

/*public*/ void ListedTableAction::addToFrame(ListedTableFrame* f) {
}

QString ListedTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.ListedTableAction";
}
