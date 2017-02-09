#include "qtableviewcontextmenu.h"
#include <QContextMenuEvent>
#include <QMenu>
#include <QButtonGroup>

QTableViewContextMenu::QTableViewContextMenu(QWidget* parent)
 : QTableView(parent)
{
 contextService = new QAction(tr("Programming Track"),this);
 contextService->setCheckable(true);
 contextOps = new QAction(tr("Programming On Main"),this);
 contextOps->setCheckable(true);
 contextEdit = new QAction(tr("Edit"),this);
 contextEdit->setCheckable(true);
 serviceSelected=true;
 opsSelected=false;
 editSelected = false;
}

void QTableViewContextMenu::contextMenuEvent(QContextMenuEvent * evt)
{
 QPoint gpt = evt->globalPos();
 QPoint pt = viewport()->mapFromGlobal(gpt);
 int row = rowAt(pt.y());

 //emit callMenu(row);
 showPopup(row);
}

/*protected*/ void QTableViewContextMenu::showPopup(int row) {
//        if (!rtable.getTable().isRowSelected(row)) {
//            rtable.getTable().changeSelection(row, 0, false, false);
//        }
        QMenu* popupMenu = new QMenu();
        QAction* menuItem = new QAction("Program", this);

//        menuItem.addActionListener((ActionEvent e1) -> {
//            startProgrammer(null, re, programmer1);
//        });
//        if (re == null) {
//            menuItem.setEnabled(false);
//        }
        popupMenu->addAction(menuItem);

        QButtonGroup* group = new QButtonGroup();
        group->add(contextService);
        group->add(contextOps);
        group->add(contextEdit);
        QMenu* progMenu = new QMenu("Programmer type");
//        contextService.addActionListener((ActionEvent e1) -> {
//            service.setSelected(true);
//            updateProgMode();
//        });
//        progMenu->addAction(contextService);
//        contextOps.addActionListener((ActionEvent e1) -> {
//            ops.setSelected(true);
//            updateProgMode();
//        });
        progMenu->addAction(contextOps);
//        contextEdit.addActionListener((ActionEvent e1) -> {
//            edit.setSelected(true);
//            updateProgMode();
//        });
        if (serviceSelected) {
            contextService->setChecked(true);
        } else if (opsSelected) {
            contextOps->setChecked(true);
        } else {
            contextEdit->setChecked(true);
        }
        progMenu->addAction(contextEdit);
        popupMenu->addMenu(progMenu);
        popupMenu->addSeparator();
        menuItem = new QAction("Labels and Media",this);
//        menuItem.addActionListener((ActionEvent e1) -> {
//            editMediaButton();
//        });
        if (re == NULL) {
            menuItem->setEnabled(false);
        }
        popupMenu->addAction(menuItem);
        menuItem = new QAction("Throttle", this);
//        menuItem.addActionListener((ActionEvent e1) -> {
//            ThrottleFrame tf = ThrottleFrameManager.instance().createThrottleFrame();
//            tf.toFront();
//            tf.getAddressPanel().getRosterEntrySelector().setSelectedRosterGroup(getSelectedRosterGroup());
//            tf.getAddressPanel().setRosterEntry(re);
//        });
        if (re == NULL) {
            menuItem->setEnabled(false);
        }
        popupMenu->addAction(menuItem);
        popupMenu->addSeparator();
        menuItem = new QAction("Duplicate");
//        menuItem.addActionListener((ActionEvent e1) -> {
//            copyLoco();
//        });
        if (re == NULL) {
            menuItem->setEnabled(false);
        }
        popupMenu->addAction(menuItem);
        menuItem = new QAction(this->selectedRosterGroup != "" ? tr("Delete From Group") : tr("Delete From Roster")); // NOI18N
//        menuItem.addActionListener((ActionEvent e1) -> {
//            deleteLoco();
//        });
        popupMenu.add(menuItem);
        menuItem.setEnabled(this.getSelectedRosterEntries().length > 0);

        popupMenu.show(e.getComponent(), e.getX(), e.getY());
#endif
        popupMenu->exec(QCursor::pos());
    }

