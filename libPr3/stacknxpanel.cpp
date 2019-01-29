#include "stacknxpanel.h"
#include "entryexitpairs.h"
#include "instancemanager.h"
#include "joptionpane.h"
#include <QPushButton>
#include "jlist.h"
#include <QVBoxLayout>
#include "destinationpoints.h"
#include "defaultlistmodel.h"

//public class StackNXPanel extends JPanel {


/*public*/ StackNXPanel::StackNXPanel(QWidget* parent) : JPanel(parent){
    //super();
    listToDest = QMap<QString, DestinationPoints*>();
    manager = static_cast<EntryExitPairs*>(InstanceManager::getDefault("EntryExitPairs"));
    list = new JList/*<QString>*/();
    initGUI();
}

/*private*/ void StackNXPanel::initGUI() {
    listModel = new DefaultListModel/*<QString>*/();
    //setLayout(new BorderLayout());
    QVBoxLayout* thisLayout = new QVBoxLayout(this);
    entryExitPanel = new JPanel();
//    entryExitPanel->setDoubleBuffered(true);
    //entryExitPanel.setLayout(new BoxLayout(entryExitPanel, BoxLayout.Y_AXIS));
    QVBoxLayout* entryExitPanelLayout = new QVBoxLayout(entryExitPanel);
    entryExitPanelLayout->addWidget(list);
    QPushButton* cancelButton = new QPushButton(tr("Cancel"));  // NOI18N
//    cancelButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent e) {
//            //This method can be called only if
//            //there's a valid selection
//            //so go ahead and remove whatever's selected.
//            if (list.getSelectedValue() != null) {
//                // basic check to see if anything was selected
//            manager.cancelStackedRoute(listToDest.get(list.getSelectedValue()), false);
//            } else {
//                JOptionPane.showMessageDialog(entryExitPanel,
//                        Bundle.getMessage("Error1", Bundle.getMessage("ButtonCancel")),  // NOI18N
//                        Bundle.getMessage("WarningTitle"), JOptionPane.WARNING_MESSAGE);  // NOI18N
//                // Keep Panel open
//            }
//        }

//    });
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(onCancel()));
    thisLayout->addWidget(cancelButton, 0, Qt::AlignBottom); //BorderLayout.SOUTH);
    thisLayout->addWidget(entryExitPanel, 0, Qt::AlignCenter); //BorderLayout.CENTER);

    updateGUI();
}

/*public*/ void StackNXPanel::onCancel() {
    //This method can be called only if
    //there's a valid selection
    //so go ahead and remove whatever's selected.
    if (list->getSelectedValue().toString() != "") {
        // basic check to see if anything was selected
    manager->cancelStackedRoute(listToDest.value(list->getSelectedValue().toString()), false);
    } else {
        JOptionPane::showMessageDialog(entryExitPanel,
                tr("No item was selected in the list.\nPlease do so and click %1 or leave Route Stacked.").arg(tr("Cancel")),  // NOI18N
                tr("Warning"), JOptionPane::WARNING_MESSAGE);  // NOI18N
        // Keep Panel open
    }
}


/*public*/ void StackNXPanel::updateGUI() {
    listModel->clear();
    listToDest = QMap<QString, DestinationPoints*>();
    for (DestinationPoints* dp : manager->getStackedInterlocks()) {
        listToDest.insert(dp->getDisplayName(), dp);
        listModel->addElement(dp->getDisplayName());
    }
    list->setModel(listModel);
//    list->setVisibleRowCount(10);
}
