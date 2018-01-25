#include "debugmenu.h"
#include "vsdecodercreationaction.h"
#include "vsdpreferencesaction.h"
#include "installdecoderfileaction.h"
#include "decoderindexcreateaction.h"
#include "recreaterosteraction.h"
#include "updatedecoderdefinitionaction.h"
#include "xmlfilevalidateaction.h"
#include "namecheckaction.h"
#include "progcheckaction.h"
#include "logixloadaction.h"
#include "logaction.h"

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
        addAction(new InstallDecoderURLAction(tr("Import Decoder URL"), panel));
        addAction(new DecoderIndexCreateAction(tr("Recreate Decoder Index"),panel));
        addAction(new RecreateRosterAction(tr("Recreate Roster"),panel));
        addAction(new UpdateDecoderDefinitionAction(tr("Update Decoder Definitions"),panel));
        addSeparator();
        addAction(new XmlFileValidateAction(tr("Validate XML File"), panel));

        addAction(new NameCheckAction(tr("Check Decoder Names"), panel));
        addAction(new ProgCheckAction(tr("Check Programmer Names"), panel));
        addSeparator();
        addAction(new LogixLoadAction(tr("Load Logix Disabled"), panel));
        addAction(new LogAction(tr("Log Message")));
#if 0
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
