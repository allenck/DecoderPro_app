#include "jynstrumentpopupmenu.h"
#include "jythonwindow.h"

///*public*/ class JynstrumentPopupMenu extends JPopupMenu {

    //private static final ResourceBundle jythonBundle = ResourceBundle.getBundle("jmri/jmrit/jython/JythonBundle");


/*public*/ JynstrumentPopupMenu::JynstrumentPopupMenu(Jynstrument* it) : Menu(it->objectName()){
    //super(it.getName());
    jynstrument = it;
    initMenu();
#if 0
    it.addMouseListener(new MouseAdapter() {
        @Override
        /*public*/ void mousePressed(MouseEvent e) {
            maybeShowPopup(e);
        }

        @Override
        /*public*/ void mouseReleased(MouseEvent e) {
            maybeShowPopup(e);
        }

        private void maybeShowPopup(MouseEvent e) {
            Component cmp = e.getComponent();
            while ((cmp != null) && (!(cmp instanceof Jynstrument))) {
                cmp = cmp.getParent();
            }
            if (cmp == null) {
                return;
            }
            Jynstrument it = (Jynstrument) cmp;
            if (e.isPopupTrigger()) {
                it.getPopUpMenu().show(e.getComponent(), e.getX(), e.getY());
            }
        }
    });
#endif
}

/*private*/ void JynstrumentPopupMenu::initMenu() {
    // Quit option
    QAction* quitMenuItem = new QAction(tr("JynstrumentPopupMenuQuit"), this);
//    quitMenuItem.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            jynstrument.exit();
//            jynstrument = null;
//        }
//    });
    connect(quitMenuItem, SIGNAL(triggered(QAction*)), this, SLOT());
    addAction(quitMenuItem);
// Edit option
/*  JMenuItem editMenuItem = new JMenuItem(jythonBundle.getString("JynstrumentPopupMenuEdit"));
     editMenuItem.addActionListener(new ActionListener() {
     public void actionPerformed(ActionEvent e) {
     //   if (!java.awt.Desktop.isDesktopSupported()) //TODO: Need Java 6
     //        return;
     log.debug("Not implemented");
     }
     } );
     editMenuItem.setEnabled(false);
     add(editMenuItem);
     // Reload option
     JMenuItem reloadMenuItem = new JMenuItem(jythonBundle.getString("JynstrumentPopupMenuReload"));
     reloadMenuItem.addActionListener(new ActionListener() {
     public void actionPerformed(ActionEvent e) {
     log.debug("Not implemented"); // TODO
     }
     } );
     reloadMenuItem.setEnabled(false);
     add(reloadMenuItem);*/
    // Debug option
    addAction(new JythonWindow(tr("JynstrumentPopupMenuDebug"),this));
    // A separator to differentiate Jynstrument private menu items
    addSeparator();
}
