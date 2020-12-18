#include "oblocktableframe.h"
#include "oblocktablepanel.h"
#include <QBoxLayout>

/**
 * Override to place the four OBlock tables in tabbed interface.
 * @see jmri.jmrit.beantable.oblock.TableFrames
 *
 * @author Bob Jacobsen Copyright (C) 2003
 * @author Matthew Harris copyright (c) 2009
 * @author Egbert Broerse copyright (c) 2020
 */
// /*public*/ class OBlockTableFrame extends BeanTableFrame<OBlock> {


    /*public*/ OBlockTableFrame::OBlockTableFrame(OBlockTablePanel* panel, QString helpTarget, QWidget *parent) : BeanTableFrame(parent) {

        //super();

        oblockPanel = panel;

        // general GUI config
        getContentPane()->setLayout(new QVBoxLayout());//(getContentPane(), BoxLayout.Y_AXIS));
#if 0
        // add save menu item
        JMenuBar menuBar = new JMenuBar();
        JMenu fileMenu = new JMenu(Bundle.getMessage("MenuFile"));
        menuBar.add(fileMenu);
        fileMenu.add(new jmri.configurexml.StoreMenu());
        fileMenu.add(panel.getPrintItem());

        menuBar.add(panel.getOptionMenu()); // configure to show up on oblock.TableFrames when called from Tools menu
        menuBar.add(panel.getTablesMenu());

        setJMenuBar(menuBar); // this menubar shows when table opened as unlisted/startup action

        addHelpMenu(helpTarget, true);

        // install items in GUI
        getContentPane().add(oblockPanel);
        bottomBox = Box.createHorizontalBox();
        bottomBox.add(Box.createHorizontalGlue()); // stays at end of box
        bottomBoxIndex = 0;

        getContentPane().add(bottomBox);

        // add extras, if desired by subclass
        extras();
#endif
    }

    //@Override
    /*public*/ void OBlockTableFrame::dispose() {
        if (oblockPanel != nullptr) {
            oblockPanel->dispose();
        }
        BeanTableFrame::dispose();
    }
