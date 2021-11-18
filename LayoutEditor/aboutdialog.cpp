#include "aboutdialog.h"
#include "loggerfactory.h"
#include "jframe.h"
#include "borderfactory.h"
#include "application.h"
#include "fileutil.h"
#include "imageicon.h"
#include "box.h"
#include "connectionconfigmanager.h"
#include "instancemanager.h"
#include "connectionlabel.h"
#include "version.h"

/**
 * About dialog.
 *
 * @author Randall Wood Copyright (C) 2012
 */
// /*public*/ final class AboutDialog extends JDialog {

    // this should probably be changed to a JmriAbstractAction that opens a JOptionPane with the contents and an OK button instead.
    /*public*/ AboutDialog::AboutDialog(JFrame* frame, bool modal) : JDialog(frame, modal){

        //super(frame, modal);

        log->debug("Start UI");

        JPanel* pane = new JPanel();
        pane->setLayout(new QVBoxLayout());//pane, BoxLayout.Y_AXIS));
        pane->setBorder(BorderFactory::createEmptyBorder(10, 10, 10, 10));
        pane->layout()->addWidget(namePane());
        pane->layout()->addWidget(infoPane());
        //this->add(pane);
        QVBoxLayout* thisLayout;
        this->setLayout(thisLayout = new QVBoxLayout());
        this->pack();
//        this->setResizable(false);
//        this.setLocationRelativeTo(null); // center on screen
        this->setTitle(tr("About %1").arg(Application::getApplicationName()));
        log->debug("End constructor");
    }

    /*protected*/ JPanel* AboutDialog::namePane() {
        QString logo = Application::getLogo();
        JPanel* pane = new JPanel();
        pane->setLayout(new QVBoxLayout());//pane, BoxLayout.Y_AXIS));
        if (log->isDebugEnabled()) {
            log->debug(tr("Fetch main logo: %1 (%2)").arg(logo, FileUtil::findURL(logo, FileUtil::Location::INSTALLED).toString()));
        }
//        addCenteredComponent(new JLabel(new ImageIcon(getToolkit().getImage(FileUtil::findURL(logo, FileUtil::Location::INSTALLED)), "JMRI logo"), JLabel.CENTER), pane);
        pane->layout()->addWidget(Box::createRigidArea(QSize(0, 15)));
        QString name = Application::getApplicationName();
        name = checkCopyright(name);
        JLabel* appName = new JLabel(name, JLabel::CENTER);
        //appName.setFont(pane->getFont().deriveFont(Font.BOLD, pane.getFont().getSize() * 1.2f));
        QFont f = pane->getFont();
        f.setBold(true);
        f.setPixelSize(f.pixelSize()*1.2);
        appName->setFont(f);
        addCenteredComponent(appName, pane);
        addCenteredComponent(new JLabel(Application::getURL(), JLabel::CENTER), pane);
        pane->layout()->addWidget(Box::createRigidArea(QSize(0, 15)));
//        pane->setAlignmentX(Component::CENTER_ALIGNMENT);
        return pane;
    }

    /*protected*/ QString AboutDialog::checkCopyright(QString name) {
        if (name.toUpper() == ("DECODERPRO")) {
            name = name + "\u00ae";
        }
        return name;
    }

    /*protected*/ JPanel* AboutDialog::infoPane() {
        JPanel* pane1 = new JPanel();
        pane1->setLayout(new QVBoxLayout());//pane1, BoxLayout.Y_AXIS));

        log->debug("start labels");

        // add listener for Com port updates
        for (ConnectionConfig* conn : ((ConnectionConfigManager*)InstanceManager::getDefault("ConnectionConfigManager"))->getConnections()) {
            if (!conn->getDisabled()) {
                pane1->layout()->addWidget(new ConnectionLabel(conn));
            }
        }
        pane1->layout()->addWidget(Box::createRigidArea(QSize(0, 15)));

        pane1->layout()->addWidget(new JLabel(tr("DefaultVersionCredit %1").arg(Version::name())));
        pane1->layout()->addWidget(new JLabel(Version::getCopyright()));
//        pane1->layout()->addWidget(new JLabel(tr("JavaVersionCredit",
//                System.getProperty("java.version", "<unknown>"),
//                Locale.getDefault().toString())));
//        pane1.setAlignmentX(Component.CENTER_ALIGNMENT);
        return pane1;
    }

    /*protected*/ void AboutDialog::addCenteredComponent(JComponent* c, JPanel* p) {
//        c->setAlignmentX(Component::CENTER_ALIGNMENT); // doesn't work
         p->layout()->addWidget((QWidget*)c->jself());
    }

    /*private*/ /*static*/ /*final*/ Logger* AboutDialog::log = LoggerFactory::getLogger("AboutDialog");
