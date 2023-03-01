#include "importlogixframe.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "logixmanager.h"
#include "joptionpane.h"
#include <QMenuBar>
#include <QMenu>
#include <QButtonGroup>
#include "box.h"
#include "defaultlogixmanager.h"
#include "logix.h"
#include "runtimeexception.h"
#include "importlogix.h"
#include "jtitledseparator.h"
#include "jmriexception.h"

/**
 * Imports Logixs to LogixNG
 *
 * @author Daniel Bergqvist 2019
 */
// /*public*/  final class ImportLogixFrame extends JmriJFrame {


/*private*/ /*static*/ /*final*/ QString ImportLogixFrame::SYSLOGIX = "";//((LogixManager*)InstanceManager::getDefault("LogixManager"))->getSystemNamePrefix() + ":SYS";
/*private*/ /*static*/ /*final*/ QString ImportLogixFrame::RTXLOGIX = "RTX";
/*private*/ /*static*/ /*final*/ QString ImportLogixFrame::USSLOGIX = "USS CTC:OsIndicator";

/**
 * Construct a LogixNGEditor.
 */
/*public*/  ImportLogixFrame::ImportLogixFrame(QWidget* parent) : JmriJFrame(parent){
    setTitle(tr("Import Logix"));
}

//@Override
/*public*/  void ImportLogixFrame::initComponents() {
    JmriJFrame::initComponents();
   QMenuBar* menuBar = new QMenuBar();
   setMenuBar(menuBar);
   addHelpMenu("package.jmri.jmrit.logixng.LogixImport", true); // NOI18N

    QWidget* contentPanel = getContentPane();
//        contentPanel.setLayout(new GridLayout( 0, 1));
    contentPanel->setLayout(new QVBoxLayout());//contentPanel, BoxLayout.Y_AXIS));

    contentPanel->layout()->addWidget(new JTitledSeparator(tr("Which Logixs to import?")));
    _whichLogix_All = new QRadioButton(tr("Import all Logixs"));
    _whichLogix_AllActive = new QRadioButton(tr("Import all active Logixs (not supported yet)"));
    _whichLogix_AllActive->setEnabled(false);
    _whichLogix_Selected = new QRadioButton(tr("Import selected Logixs (not supported yet)"));
    _whichLogix_Selected->setEnabled(false);
    QButtonGroup* buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(_whichLogix_All);
    buttonGroup->addButton(_whichLogix_AllActive);
    buttonGroup->addButton(_whichLogix_Selected);
    _whichLogix_All->setChecked(true);
//        r2.setSelected(true);
    contentPanel->layout()->addWidget(_whichLogix_All);
    contentPanel->layout()->addWidget(_whichLogix_AllActive);
    contentPanel->layout()->addWidget(_whichLogix_Selected);

    contentPanel->layout()->addWidget(Box::createRigidArea(QSize(0, 15)));    // vertical space.

    contentPanel->layout()->addWidget(new JTitledSeparator(tr("What to do with the Logixs after the import?")));
    _whatToDo_Nothing = new QRadioButton(tr("Nothing"));
    _whatToDo_Disable = new QRadioButton(tr("Disable the Logixs (not supported yet)"));
    _whatToDo_Disable->setEnabled(false);
    _whatToDo_Delete = new QRadioButton(tr("Delete the Logixs - Warning! (not supported yet)"));
    _whatToDo_Delete->setEnabled(false);
    QButtonGroup* buttonGroup2 = new QButtonGroup();
    buttonGroup2->addButton(_whatToDo_Nothing);
    buttonGroup2->addButton(_whatToDo_Disable);
    buttonGroup2->addButton(_whatToDo_Delete);
    _whatToDo_Nothing->setChecked(true);
//        _whatToDo_Disable.setSelected(true);
    contentPanel->layout()->addWidget(_whatToDo_Nothing);
    contentPanel->layout()->addWidget(_whatToDo_Disable);
    contentPanel->layout()->addWidget(_whatToDo_Delete);

    contentPanel->layout()->addWidget(Box::createRigidArea(QSize(0, 15)));    // vertical space.

    contentPanel->layout()->addWidget(new JTitledSeparator(tr("Import system Logixs also?")));
    _includeSystemLogixs = new JCheckBox(tr("Import system Logixs also?"));
//        includeSystemLogixs.addItemListener((ItemEvent e) -> {
//            if (includeSystemLogixs.isSelected()) {
//                _systemName.setEnabled(false);
//                _sysNameLabel.setEnabled(false);
//            } else {
//                _systemName.setEnabled(true);
//                _sysNameLabel.setEnabled(true);
//            }
//        });
    contentPanel->layout()->addWidget(_includeSystemLogixs);

    contentPanel->layout()->addWidget(Box::createRigidArea(QSize(0, 15)));    // vertical space.

    contentPanel->layout()->addWidget(new JTitledSeparator(tr("Select which Logixs to import")));

    contentPanel->layout()->addWidget(Box::createRigidArea(QSize(0, 15)));    // vertical space.

    contentPanel->layout()->addWidget(new JTitledSeparator(tr("Warning")));

    JLabel* warning = new JLabel(tr("<html><table width=\"600\">                     \
The import tool will do its best to import the requested                    \
Logixs to LogixNG. But LogixNG works in a different way                     \
than Logix and therefore there may be subtle differences                    \
between the original Logix and the imported LogixNG                         \
<p>&nbsp;<p>                                                                \
Also, there may be special Logixs not known to the import                   \
tool that should not be imported to LogixNG, for example                    \
the Logix that handles sensor groups. The import tool                       \
knows about some of these Logix (SYS, RTX and USS CTC), but there           \
may be others not known to the import tool.                                 \
</table></html>"));
warning->setWordWrap(true);
    JPanel* warningPanel = new JPanel(new FlowLayout);
    warningPanel->layout()->addWidget(warning);
    contentPanel->layout()->addWidget(warningPanel);

    contentPanel->layout()->addWidget(Box::createRigidArea(QSize(0, 10)));    // vertical space.


    // set up import and cancel buttons
    JPanel* panel5 = new JPanel();
    panel5->setLayout(new FlowLayout());

    // Import
    _importLogix = new JButton(tr("Import"));    // NOI18N
    panel5->layout()->addWidget(_importLogix);
    connect(_importLogix, &JButton::clicked, [=] {
        doImport();
        _cancelDone->setText(tr("Done"));
//            dispose();
    });
//        cancel.setToolTipText(Bundle.getMessage("CancelLogixButtonHint"));      // NOI18N
    _importLogix->setToolTip("ImportLogixButtonHint");      // NOI18N
//        panel5.setAlignmentX(LEFT_ALIGNMENT);
    // Cancel
    _cancelDone = new JButton(tr("Cancel"));    // NOI18N
    panel5->layout()->addWidget(_cancelDone);
    connect(_cancelDone, &JButton::clicked, [=] {
        dispose();
    });
//        cancel.setToolTipText(Bundle.getMessage("CancelLogixButtonHint"));      // NOI18N
    _cancelDone->setToolTip("CancelLogixButtonHint");      // NOI18N
//        panel5.setAlignmentX(LEFT_ALIGNMENT);
    contentPanel->layout()->addWidget(panel5);
#if 0
    // Align all components to the left
    for (Component c : contentPanel.getComponents()) {
        ((JComponent)c).setAlignmentX(LEFT_ALIGNMENT);
    }
#endif
    pack();
//        setLocationRelativeTo(nullptr);
    setVisible(true);

//        initMinimumSize(new Dimension(panelWidth700, panelHeight500));
}

/*public*/  void ImportLogixFrame::initMinimumSize(QSize dimension) {
    setMinimumSize(dimension);
    pack();
    setVisible(true);
}

/*private*/ void ImportLogixFrame::doImport() {
//        /*private*/ JRadioButton _whichLogix_All;
//        /*private*/ JRadioButton _whichLogix_AllActive;
//        /*private*/ JRadioButton _whichLogix_Selected;
//        /*private*/ JRadioButton _whatToDo_Nothing;
//        /*private*/ JRadioButton _whatToDo_Disable;
//        /*private*/ JRadioButton _whatToDo_Delete;
//        /*private*/ JCheckBox _includeSystemLogixs;
    QList<Logix*> logixs = QList<Logix*>();
    if (_whichLogix_All->isChecked()) {
        for (NamedBean* nb : ((DefaultLogixManager*)InstanceManager::getDefault("LogixManager"))->getNamedBeanSet()) {
           Logix* logix = (Logix*)nb->self();
           if(SYSLOGIX.isEmpty() )
            SYSLOGIX = ((DefaultLogixManager*)InstanceManager::getDefault("LogixManager"))->getSystemNamePrefix() + ":SYS";
         bool isSystemLogix =
                    logix->AbstractNamedBean::getSystemName() == (SYSLOGIX) ||
                    logix->AbstractNamedBean::getSystemName().contains(RTXLOGIX) ||
                    logix->AbstractNamedBean::getSystemName().contains(USSLOGIX);
            if (!isSystemLogix || _includeSystemLogixs->isChecked()) {
                logixs.append(logix);
            }
        }
    } else if (_whichLogix_All->isChecked()) {
        throw new RuntimeException("Currently not supported");
    } else if (_whichLogix_All->isChecked()) {
        throw new RuntimeException("Currently not supported");
    } else {
        throw new RuntimeException("No choice selected");
    }

    bool error = false;
    QString errorMessage = QString("<html><table border=\"1\" cellspacing=\"0\" cellpadding=\"2\">");
    errorMessage.append("<tr><th>");
    errorMessage.append("System name");
    errorMessage.append("</th><th>");
    errorMessage.append("User name");
    errorMessage.append("</th><th>");
    errorMessage.append("Error");
    errorMessage.append("</th></tr>");

    for (Logix* logix : logixs) {
        try {
            ImportLogix* importLogix = new ImportLogix(logix, _includeSystemLogixs->isSelected(), true);
            importLogix->doImport();
        } catch (JmriException* e) {
            errorMessage.append("<tr><td>");
            errorMessage.append(logix->AbstractNamedBean::getSystemName());
            errorMessage.append("</td><td>");
            errorMessage.append(logix->AbstractNamedBean::getUserName() != nullptr ? logix->AbstractNamedBean::getUserName() : "");
            errorMessage.append("</td><td>");
            errorMessage.append(e->getMessage());
            errorMessage.append("</td></tr>");
            log->error(tr("Error thrown: %1").arg(e->getMessage()), e);
            error = true;
        }
    }

    if (!error) {
        for (Logix* logix : logixs) {
            try {
                ImportLogix* importLogix = new ImportLogix(logix, _includeSystemLogixs->isSelected(), false);
                importLogix->doImport();
            } catch (JmriException* e) {
                throw new RuntimeException("Unexpected error: "+e->getMessage(), e);
            }
        }
    } else {
        errorMessage.append("</table></html>");
        JOptionPane::showMessageDialog(this, errorMessage, "Error during import", JOptionPane::ERROR_MESSAGE);
    }
}


/*private*/ /*final*/ /*static*/ Logger* ImportLogixFrame::log = LoggerFactory::getLogger("ImportLogixFrame");

