#include "debugmenu.h"
#include "vsdecodercreationaction.h"
#include "vsdpreferencesaction.h"
#include "installdecoderfileaction.h"

//DebugMenu::DebugMenu(QWidget *parent) :
//  QMenu(parent)
//{
//}
/**
 * Create a "Debug" menu containing the JMRI system-independent debugging tools.
 *
 * @author	Bob Jacobsen Copyright 2003
 * @version $Revision: 29708 $
 */
///*public*/ class DebugMenu extends JMenu {

    /**
     *
     */
    //private static final long serialVersionUID = -954409766062724149L;

    /*public*/ DebugMenu::DebugMenu(QString name, QWidget* panel) :
 QMenu(panel){
        //this(panel);
 common(panel);
        setTitle(name);
    }

    /*public*/ DebugMenu::DebugMenu(QWidget* panel) :
 QMenu(panel) {

        //super();
 common(panel);

        setTitle(tr("Debug"));
}

void DebugMenu::common(QWidget* panel)
{
#if 0
        add(new MemoryFrameAction(tr("MenuItemMemoryUsageMonitor")));
        add(new JSeparator());
#endif
        addAction(new InstallDecoderFileAction(tr("Import Decoder File"), panel));
        addAction(new InstallDecoderURLAction(tr("Import Decoder URL"), (WindowInterface*)panel));
#if 0
        add(new decoderdefn.DecoderIndexCreateAction(tr("MenuItemRecreateDecoderIndex")));
        add(new roster.RecreateRosterAction(tr("MenuItemRecreateRoster")));
        add(new roster.UpdateDecoderDefinitionAction(tr("MenuItemUpdateDecoderDefinition")));
        add(new JSeparator());
        add(new XmlFileValidateAction(tr("MenuItemValidateXMLFile"), panel));
        add(new decoderdefn.NameCheckAction(tr("MenuItemCheckDecoderNames"), panel));
        add(new symbolicprog.tabbedframe.ProgCheckAction(tr("MenuItemCheckProgrammerNames"), panel));
        add(new JSeparator());
        add(new LogixLoadAction(tr("MenuItemLogixDisabled"), panel));
        add(new log.LogAction(tr("MenuItemLogAction")));
        add(new log.LogOutputWindowAction(tr("MenuItemLogOutputWindowAction")));
        add(new jmri.util.swing.JmriNamedPaneAction(tr("MenuItemLogTreeAction"),
                new jmri.util.swing.sdi.JmriJFrameInterface(),
                "log.Log4JTreePane"));
#endif
        addSeparator();

        QMenu* vsdMenu = new QMenu(tr("Virtual Sound Decoder"));
        vsdMenu->addAction(new VSDecoderCreationAction(tr("VSDecoder Manager"), true));
//        vsdMenu.add(new ManageLocationsAction(tr("Manage VSD Locations"), NULL));
        vsdMenu->addAction(new VSDPreferencesAction(tr("VSDecoder Preferences"),this));
        addMenu(vsdMenu);

    }
