#include "listedtableaction.h"
#include "tablesframe.h"
#include "libtables.h"

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
  QAction(s,parent) {
 //super(s);
 common();
  title = s;
  gotoListItem = selection;
}

/*public*/ ListedTableAction::ListedTableAction(QString s, QString selection, int divider, QObject *parent) :
  QAction(s,parent)
{
 //super(s);
 common();
 title = s;
 gotoListItem = selection;
 dividerLocation = divider;
}

/*public*/ ListedTableAction::ListedTableAction(QString s, int divider, QObject *parent) :
  QAction(s, parent)
{
 //super(s);
 common();
 title = s;
 dividerLocation = divider;
}

/*public*/ListedTableAction:: ListedTableAction(QString s,QObject *parent) :
  QAction(s, parent)
{
//super(s);
 common();
 title = s;
}

/*public*/ ListedTableAction::ListedTableAction(QObject *parent) :
  QAction(tr("Listed Table Access"), parent)
{
 //this(rbean.getString("TitleListedTable"));
 common();
}
void ListedTableAction::common()
{
 title = tr("Listed Table Access");
 dividerLocation = 0;
 libTables = NULL;
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void ListedTableAction::actionPerformed()
{
    // create the JTable model, with changes for specific NamedBean
    /* create the frame in a seperate thread outside of swing so that we do not
     hog the swing thread which is also used for connection traffic */
//    Runnable r = new Runnable() {
//        /*public*/ void run() {
//            f = new ListedTableFrame(title) {

//                /**
//                 *
//                 */
//                private static final long serialVersionUID = -2029385586619585289L;
//            };
//            f.initComponents();
//            addToFrame(f);

//            f.gotoListItem(gotoListItem);
//            f.pack();

//            f.setDividerLocation(dividerLocation);
//            f.setVisible(true);
//        }
//    };
//    Thread thr = new Thread(r, "Listed Table Generation");
//    thr.start();
 if(libTables == NULL)
  libTables = new LibTables();
 libTables->show(text());
}

///*public*/ void actionPerformed(ActionEvent e) {
//    actionPerformed();
//}

///*public*/ void addToFrame(ListedTableFrame f) {
//}

QString ListedTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.ListedTableAction";
}
