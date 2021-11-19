#include "helpmenuprovider.h"
#include "loggerfactory.h"
#include "helputil.h"
#include "application.h"
#include "systemtype.h"
#include "licenseaction.h"
#include "xmlfilelocationaction.h"
#include "checkforupdateaction.h"
#include "reportcontextaction.h"
#include "systemconsoleaction.h"
#include "issuereporteraction.h"
#include "aboutaction.h"

/**
 * Common utility methods for working with Java Help.
 * <p>
 * This class was created to contain common Java Help information.
 * <p>
 * It assumes that Java Help 1.1.8 is in use
 *
 * @author Bob Jacobsen Copyright 2007
 */
//@ServiceProvider(service = HelpUtil.MenuProvider.class)
// /*public*/ class HelpMenuProvider implements HelpUtil.MenuProvider {

    /*public*/ HelpMenuProvider::HelpMenuProvider(QObject* parent) :QObject(parent) {
        // do nothing
     this->parent = (QObject*)parent;
    }

    //@Override
    /*public*/ QList<JMenuItem*> HelpMenuProvider::getHelpMenuItems() {
        QList<JMenuItem*> items;// = new ArrayList<>();

        JMenuItem* item = new JMenuItem(tr("MenuItemHelp"), this);
//        HelpUtil::enableHelpOnButton(item, "index");
        items.append(item);

        JMenuItem* license = new JMenuItem(tr("License"),this);
        items.append(license);
        license->addActionListener((ActionListener*)(new LicenseAction(this)));

        JMenuItem* directories = new JMenuItem(tr("Locations"),this);
        items.append(directories);
        directories->addActionListener((ActionListener*)(new XmlFileLocationAction(this)));

        JMenuItem* updates = new JMenuItem(tr("CheckUpdates"),this);
        items.append(updates);
//        updates->addActionListener((ActionListener*)(new CheckForUpdateAction(this)));

        JMenuItem* context = new JMenuItem(tr("Context"),this);
        items.append(context);
//        context->addActionListener(new ReportContextAction());

        JMenuItem* console = new JMenuItem(tr("Console"),this);
        items.append(console);
        console->addActionListener((ActionListener*)(new SystemConsoleAction(HelpUtil::instance())));

//        items.append(new JMenuItem(new IssueReporterAction(this)));
#if 0
        // Put about dialog in Apple's prefered area on Mac OS X
        if (SystemType.isMacOSX()) {
            try {
                Application.getApplication().setAboutHandler((EventObject eo) -> {
                    new AboutDialog(null, true).setVisible(true);
                });
            } catch (java.lang.RuntimeException re) {
                log.error("Unable to put About handler in default location", re);
            }
        }
#endif
        // Include About in Help menu if not on Mac OS X or not using Aqua Look and Ffinaleel
//        if (!SystemType::isMacOSX() || !UIManager.getLookAndFeel().isNativeLookAndFeel()) {
            items.append(nullptr);
            JMenuItem* about = new JMenuItem(tr("About") + " " + Application::getApplicationName(),this);
            items.append(about);
            about->addActionListener((ActionListener*)(new AboutAction(this)));
//       }
        return items;
    }

    // initialize logging
    /*private*/ /*static*/ /*final*/ Logger* HelpMenuProvider::log = LoggerFactory::getLogger("HelpMenuProvider");
//}
