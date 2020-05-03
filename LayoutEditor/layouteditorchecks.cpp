#include "layouteditorchecks.h"
#include "layouteditor.h"
#include <QMenu>
#include <QAction>
#include <QSet>
#include "layouteditorfinditems.h"
#include "layouttrackeditors.h"
#include "mathutil.h"
#include <cmath>
#include <QToolTip>

/**
 * A collection of tools to check various things on the layout editor panel.
 *
 * @author George Warner Copyright (c) 2017-2018
 */
///*public*/ class LayoutEditorChecks {


/**
 * The constructor for this class
 *
 * @param layoutEditor the layout editor that uses this class
 */
/*public*/ LayoutEditorChecks::LayoutEditorChecks(/*@Nonnull*/ LayoutEditor* layoutEditor, QObject* parent) : QObject(parent){
 checkMenu = new QMenu(tr("Check"));
 checkInProgressMenuItem = new QAction(tr("Check In Progress..."),this);
 checkNoResultsMenuItem = new QAction(tr("No Results"),this);

 // Check for Un-Connected Tracks
 checkUnConnectedTracksMenu = new QMenu(tr("Un-Connected Tracks"));

 // Check for Un-Blocked Tracks
 checkUnBlockedTracksMenu = new QMenu(tr("Un-Blocked Tracks"));

 // Check for Non-Contiguous Blocks
 checkNonContiguousBlocksMenu = new QMenu(tr("Non-Contiguous Blocks"));

 // Check for Unnecessary Anchors
 checkUnnecessaryAnchorsMenu = new QMenu(tr("Unnecessary Anchors"));

 this->layoutEditor = layoutEditor;
}

/**
 * set the layout editor checks menu (in the tools menu)
 *
 * @param toolsMenu where to add our "Check" menu and sub-menus
 */
/*protected*/ void LayoutEditorChecks::setupChecksMenu(/*@Nonnull*/ QMenu* toolsMenu) {
    toolsMenu->addMenu(checkMenu);
//    checkMenu.addMenuListener(new MenuListener() {
//        @Override
//        /*public*/ void menuSelected(@Nonnull MenuEvent menuEvent) {
//            log.debug("menuSelected");
//            boolean enabled = layoutEditor.isEditable();
//            checkUnConnectedTracksMenu.setEnabled(enabled);
//            checkUnBlockedTracksMenu.setEnabled(enabled);
//            checkNonContiguousBlocksMenu.setEnabled(enabled);
//            checkUnnecessaryAnchorsMenu.setEnabled(enabled);
//        }

//        @Override

//        /*public*/ void menuDeselected(@Nonnull MenuEvent menuEvent) {
//            log.debug("menuDeselected");
//            //nothing to see here... move along...
//        }

//        @Override
//        /*public*/ void menuCanceled(@Nonnull MenuEvent menuEvent) {
//            log.debug("menuCanceled");
//            //nothing to see here... move along...
//        }
//    }
//    );
    connect(checkMenu, SIGNAL(aboutToShow()), this, SLOT(onMenuSelected()));
    checkMenu->setEnabled(layoutEditor->isEditable());
    checkMenu->setToolTip(tr("Select this menu to run layout editor checks"));
    checkMenu->setToolTipsVisible(true);
    checkNoResultsMenuItem->setToolTip(tr("This check passed: there are no results to report"));
    checkNoResultsMenuItem->setEnabled(false);
    connect(checkNoResultsMenuItem, &QAction::hovered, [=]{
        QToolTip::showText(QCursor::pos(), checkNoResultsMenuItem->toolTip(), layoutEditor);
    });
    checkInProgressMenuItem->setToolTip(tr("Checking is in progress... (please wait)"));
    checkInProgressMenuItem->setEnabled(false);
    connect(checkInProgressMenuItem, &QAction::hovered, [=]{
        QToolTip::showText(QCursor::pos(), checkInProgressMenuItem->toolTip(), layoutEditor);
    });

    //
    //  check for tracks with free connections
    //
    checkUnConnectedTracksMenu->setToolTip(tr("Select this to check for tracks that have unconnected ends"));
    checkUnConnectedTracksMenu->addAction(checkInProgressMenuItem);
    checkUnBlockedTracksMenu->setToolTipsVisible(true);
    checkMenu->addMenu(checkUnConnectedTracksMenu);

//    checkUnConnectedTracksMenu.addMenuListener(new MenuListener() {
//        @Override
//        /*public*/ void menuSelected(@Nonnull MenuEvent menuEvent) {
//            log.debug("menuSelected");
//            setupCheckUnConnectedTracksMenu();
//        }

//        @Override
//        /*public*/ void menuDeselected(@Nonnull MenuEvent menuEvent) {
//            log.debug("menuDeselected");
//            //nothing to see here... move along...
//        }

//        @Override
//        /*public*/ void menuCanceled(@Nonnull MenuEvent menuEvent) {
//            log.debug("menuCanceled");
//            //nothing to see here... move along...
//        }
//    });
connect(checkUnConnectedTracksMenu, SIGNAL(aboutToShow()), this, SLOT(onCheckUnConnectedTracksMenuSelected()));
    //
    //  check for tracks without assigned blocks
    //
    checkUnBlockedTracksMenu->setToolTip(tr("Select this to check for tracks that do not have an assigned block"));
    checkUnBlockedTracksMenu->setToolTipsVisible(true);
    checkUnBlockedTracksMenu->addAction(checkInProgressMenuItem);
    checkMenu->addMenu(checkUnBlockedTracksMenu);

//    checkUnBlockedTracksMenu.addMenuListener(new MenuListener() {
//        @Override
//        /*public*/ void menuSelected(@Nonnull MenuEvent menuEvent) {
//            log.debug("menuSelected");
//            setupCheckUnBlockedTracksMenu();
//        }

//        @Override
//        /*public*/ void menuDeselected(@Nonnull MenuEvent menuEvent) {
//            log.debug("menuDeselected");
//            //nothing to see here... move along...
//        }

//        @Override
//        /*public*/ void menuCanceled(@Nonnull MenuEvent menuEvent) {
//            log.debug("menuCanceled");
//            //nothing to see here... move along...
//        }
//    });

    //
    // check for non-contiguous blocks
    //
    checkNonContiguousBlocksMenu->setToolTip(tr("Select this to check for blocks that are not contiguous"));
    checkNonContiguousBlocksMenu->addAction(checkInProgressMenuItem);
    checkMenu->addMenu(checkNonContiguousBlocksMenu);

//    checkNonContiguousBlocksMenu.addMenuListener(new MenuListener() {
//        @Override
//        /*public*/ void menuSelected(@Nonnull MenuEvent menuEvent) {
//            log.debug("menuSelected");
//            setupCheckNonContiguousBlocksMenu();
//        }

//        @Override
//        /*public*/ void menuDeselected(@Nonnull MenuEvent menuEvent) {
//            log.debug("menuDeselected");
//            //nothing to see here... move along...
//        }

//        @Override
//        /*public*/ void menuCanceled(@Nonnull MenuEvent menuEvent) {
//            log.debug("menuCanceled");
//            //nothing to see here... move along...
//        }
//    });
    connect(checkNonContiguousBlocksMenu, SIGNAL(aboutToShow()), this, SLOT(onCheckNonContiguousBlocksMenu()));

    //
    // Check for Unnecessary Anchors
    //
    checkUnnecessaryAnchorsMenu->setToolTip(tr("Select this to check if the adjacent track segments can be merged"));
    checkUnnecessaryAnchorsMenu->addAction(checkInProgressMenuItem);
    checkMenu->addMenu(checkUnnecessaryAnchorsMenu);

//    checkUnnecessaryAnchorsMenu.addMenuListener(new MenuListener() {
//        @Override
//        /*public*/ void menuSelected(@Nonnull MenuEvent menuEvent) {
//            log.debug("menuSelected");
//            setupCheckUnnecessaryAnchorsMenu();
//        }

//        @Override
//        /*public*/ void menuDeselected(@Nonnull MenuEvent menuEvent) {
//            log.debug("menuDeselected");
//            //nothing to see here... move along...
//        }

//        @Override
//        /*public*/ void menuCanceled(@Nonnull MenuEvent menuEvent) {
//            log.debug("menuCanceled");
//            //nothing to see here... move along...
//        }
//    });
 connect(checkUnnecessaryAnchorsMenu, SIGNAL(aboutToShow()), this, SLOT(onCheckUnnecessaryAnchorsMenu()));
}

void LayoutEditorChecks::onMenuSelected()
{
 log->debug("menuSelected");
 bool enabled = layoutEditor->isEditable();
 checkUnConnectedTracksMenu->setEnabled(enabled);
 checkUnBlockedTracksMenu->setEnabled(enabled);
 checkNonContiguousBlocksMenu->setEnabled(enabled);
 checkUnnecessaryAnchorsMenu->setEnabled(enabled);
}

void LayoutEditorChecks::onCheckUnConnectedTracksMenuSelected()
{
 log->debug("menuSelected");
 setupCheckUnConnectedTracksMenu();
}

void LayoutEditorChecks::onCheckUnBlockedTracksMenu()
{
 log->debug("menuSelected");
 setupCheckUnBlockedTracksMenu();
}

void LayoutEditorChecks::onCheckNonContiguousBlocksMenu()
{
  log->debug("menuSelected");
  setupCheckNonContiguousBlocksMenu();
}

void LayoutEditorChecks::onCheckUnnecessaryAnchorsMenu()
{
 log->debug("menuSelected");
 setupCheckUnnecessaryAnchorsMenu();
}
//
// run the un-connected tracks check and populate the checkUnConnectedTracksMenu
//
/*private*/ void LayoutEditorChecks::setupCheckUnConnectedTracksMenu() {
    log->debug("setupcheckUnConnectedTracksMenu");

    // collect the names of all menu items with checkmarks
    QSet<QString> checkMarkedMenuItemNamesSet = getCheckMarkedMenuItemNames(checkUnConnectedTracksMenu);

    // mark our menu as "in progress..."
    checkUnConnectedTracksMenu->clear();
    checkUnConnectedTracksMenu->addAction(checkInProgressMenuItem);

    // check all tracks for free connections
    QList<QString> trackNames = QList<QString>();
    for (LayoutTrack* layoutTrack : *layoutEditor->getLayoutTracks()) {
        QList<int> connections = layoutTrack->checkForFreeConnections();
        if (!connections.isEmpty()) {
            // add this track's name to the list of track names
            trackNames.append(layoutTrack->getName());
        }
    }

    // clear the "in progress..." menu item
    checkUnConnectedTracksMenu->clear();

    // for each un-connected track we found...
    if (trackNames.size() > 0) {
        for (QString trackName : trackNames) {
            // create a menu item for it
            QAction* jmi = new QAction(trackName, this);
            jmi->setCheckable(true);
            checkUnConnectedTracksMenu->addAction(jmi);
//            jmi.addActionListener((ActionEvent event) -> {
//                doCheckUnConnectedTracksMenuItem(trackName);
//            });
            connect(jmi, SIGNAL(triggered(bool)), this,SLOT(doCheckUnConnectedTracksMenuItem()));

            // if it's in the check marked set then (re-)checkmark it
            if (checkMarkedMenuItemNamesSet.contains(trackName)) {
                jmi->setChecked(true);
            }
        }
    } else {
        checkUnConnectedTracksMenu->addAction(checkNoResultsMenuItem);
    }
}   // setupCheckUnConnectedTracksMenu

//
// action to be performed when checkUnConnectedTracksMenu item is clicked
//
/*private*/ void LayoutEditorChecks::doCheckUnConnectedTracksMenuItem(/*@Nonnull String menuItemName*/) {
 QString menuItemName = ((QAction*)sender())->text();
    log->debug(tr("docheckUnConnectedTracksMenuItem(%1)").arg(menuItemName));
    LayoutTrack* layoutTrack = layoutEditor->getFinder()->findObjectByName(menuItemName);
    if (layoutTrack != nullptr) {
        QRectF trackBounds = layoutTrack->getBounds();
        layoutEditor->setSelectionRect(trackBounds);

        // setSelectionRect calls createSelectionGroups...
        // so we have to clear it before amending to it
        layoutEditor->clearSelectionGroups();
        layoutEditor->amendSelectionGroup(layoutTrack);
    } else {
        layoutEditor->clearSelectionGroups();
    }
}   // doCheckUnConnectedTracksMenuItem

//
// run the un-blocked tracks check and populate the checkUnBlockedTracksMenu
//
/*private*/ void LayoutEditorChecks::setupCheckUnBlockedTracksMenu() {
    log->debug("setupCheckUnBlockedTracksMenu");

    // collect the names of all menu items with checkmarks
    QSet<QString> checkMarkedMenuItemNamesSet = getCheckMarkedMenuItemNames(checkUnBlockedTracksMenu);

    // mark our menu as "in progress..."
    checkUnBlockedTracksMenu->clear();
    checkUnBlockedTracksMenu->addAction(checkInProgressMenuItem);

    // check all tracks for un-assigned blocks
    QList<QString> trackNames = QList<QString> ();
    for (LayoutTrack* layoutTrack : *layoutEditor->getLayoutTracks()) {
        if (!layoutTrack->checkForUnAssignedBlocks()) {
            // add this track to the list of un-assigned track names
            trackNames.append(layoutTrack->getName());
        }
    }

    // clear the "in progress..." menu item
    checkUnBlockedTracksMenu->clear();

    // for each tracks with un-assigned blocks that we found...
    if (trackNames.size() > 0) {
        for (QString trackName : trackNames) {
            // create a menu item for it
            QAction* jmi = new QAction(trackName, this);
            jmi->setCheckable(true);
            checkUnBlockedTracksMenu->addAction(jmi);
//            jmi.addActionListener((ActionEvent event) -> {
//                doCheckUnBlockedTracksMenuItem(trackName);
//            });
connect(jmi, SIGNAL(triggered(bool)), this, SLOT(doCheckUnBlockedTracksMenuItem()));
            // if it's in the check marked set then (re-)checkmark it
            if (checkMarkedMenuItemNamesSet.contains(trackName)) {
                jmi->setChecked(true);
            }
        }
    } else {
        checkUnBlockedTracksMenu->addAction(checkNoResultsMenuItem);
    }
}   // setupCheckUnBlockedTracksMenu

//
// action to be performed when checkUnBlockedTracksMenuItem is clicked
//
/*private*/ void LayoutEditorChecks::doCheckUnBlockedTracksMenuItem(/*@Nonnull String menuItemName*/) {
 QString menuItemName = ((QAction)sender()).text();
    log->debug(tr("doCheckUnBlockedTracksMenuItem(%1)").arg(menuItemName));

    LayoutTrack* layoutTrack = layoutEditor->getFinder()->findObjectByName(menuItemName);
    if (layoutTrack != nullptr) {
        layoutEditor->setSelectionRect(layoutTrack->getBounds());
        // setSelectionRect calls createSelectionGroups...
        // so we have to clear it before amending to it
        layoutEditor->clearSelectionGroups();
        layoutEditor->amendSelectionGroup(layoutTrack);

        layoutEditor->getLayoutTrackEditors()->editLayoutTrack(layoutTrack);
    } else {
        layoutEditor->clearSelectionGroups();
    }
}   // doCheckUnBlockedTracksMenuItem

//
// run the non-contiguous blocks check and populate the checkNonContiguousBlocksMenu
//
/*private*/ void LayoutEditorChecks::setupCheckNonContiguousBlocksMenu() {
    log->debug("setupCheckNonContiguousBlocksMenu");

    // mark our menu as "in progress..."
    checkNonContiguousBlocksMenu->clear();
    checkNonContiguousBlocksMenu->addAction(checkInProgressMenuItem);

    // collect all contiguous blocks
    QMap<QString, QList<QSet<QString> > > blockNamesToTrackNameSetMaps =  QMap<QString, QList<QSet<QString> > >();
    for (LayoutTrack* layoutTrack : *layoutEditor->getLayoutTracks()) {
        layoutTrack->checkForNonContiguousBlocks(blockNamesToTrackNameSetMaps);
    }

    // clear the "in progress..." menu item
    checkNonContiguousBlocksMenu->clear();

    // for each bad block we found...
    //for (Map.Entry<String, List<Set<String>>> entry : blockNamesToTrackNameSetMaps.entrySet())
    QMapIterator<QString, QList<QSet<QString> > > entry(blockNamesToTrackNameSetMaps);
    while(entry.hasNext())
    {
     entry.next();
        QString blockName = entry.key();
        QList<QSet<QString> > trackNameSets = entry.value();
        if (trackNameSets.size() > 1) {
            QMenu* jmi = new QMenu(blockName);
            checkNonContiguousBlocksMenu->addMenu(jmi);

            int idx = 1;
            for (QSet<QString> trackNameSet : trackNameSets) {
                QAction* subMenuItem = new QAction(
                        tr("MakeLabel %1").arg(blockName) + "#" + QString::number(idx++),this);
                jmi->addAction(subMenuItem);
//                subMenuItem.addActionListener((ActionEvent event) -> {
//                    doCheckNonContiguousBlocksMenuItem(blockName, trackNameSet);
//                });
                SubMenuActionListener* listener = new SubMenuActionListener(blockName, trackNameSet, this);
                connect(subMenuItem, SIGNAL(triggered(bool)), listener, SLOT(actionPerformed()));
            }
        }
    }
    // if we didn't find any...
    if (checkNonContiguousBlocksMenu->children().count() == 0) {
        checkNonContiguousBlocksMenu->addAction(checkNoResultsMenuItem);
    }
}   // setupCheckNonContiguousBlocksMenu

SubMenuActionListener::SubMenuActionListener(QString blockName, QSet<QString> trackNameSet, LayoutEditorChecks *layoutEditorChecks)
{
 this->blockName = blockName;
 this->trackNameSet = trackNameSet;
 this->layoutEditorChecks = layoutEditorChecks;
}
void SubMenuActionListener::actionPerformed()
{
 layoutEditorChecks->doCheckNonContiguousBlocksMenuItem(blockName, trackNameSet);
}
//
// action to be performed when checkNonContiguousBlocksMenu item is clicked
//
/*private*/ void LayoutEditorChecks::doCheckNonContiguousBlocksMenuItem(
        /*@Nonnull*/ QString blockName,
        /*@Nullable*/ QSet<QString> trackNameSet) {
    log->debug(tr("doCheckNonContiguousBlocksMenuItem(%1)").arg(blockName));

    if (!trackNameSet.isEmpty()) {
        // collect all the bounds...
        QRectF bounds = QRectF();
        for (LayoutTrack* layoutTrack : *layoutEditor->getLayoutTracks()) {
            if (trackNameSet.contains(layoutTrack->getName())) {
                QRectF trackBounds = layoutTrack->getBounds();
                if (bounds.isNull()) {
                    bounds =QRectF(trackBounds.x(), trackBounds.y(), trackBounds.width(), trackBounds.height());
                } else {
                    bounds.united(trackBounds);
                }
            }
        }
        layoutEditor->setSelectionRect(bounds);

        // setSelectionRect calls createSelectionGroups...
        // so we have to clear it before amending to it
        layoutEditor->clearSelectionGroups();

        // amend all tracks in this block to the layout editor selection group
        for (LayoutTrack* layoutTrack : *layoutEditor->getLayoutTracks()) {
            if (trackNameSet.contains(layoutTrack->getName())) {
                layoutEditor->amendSelectionGroup(layoutTrack);
            }
        }
    } else {
        layoutEditor->setSelectionRect(MathUtil::zeroRectangle2D());
    }
}   // doCheckNonContiguousBlocksMenuItem

//
// run the Unnecessary Anchors check and
// populate the CheckUnnecessaryAnchorsMenu
//
/*private*/ void LayoutEditorChecks::setupCheckUnnecessaryAnchorsMenu() {
    log->debug("setupCheckUnnecessaryAnchorsMenu");

    // collect the names of all menu items with checkmarks
    QSet<QString> checkMarkedMenuItemNamesSet = getCheckMarkedMenuItemNames(checkUnBlockedTracksMenu);
    // mark our menu as "in progress..."
    checkUnnecessaryAnchorsMenu->clear();
    checkUnnecessaryAnchorsMenu->addAction(checkInProgressMenuItem);

    // check all PositionablePoints
    QList<PositionablePoint*> aatzlts = QList<PositionablePoint*>();
    for (PositionablePoint* pp : layoutEditor->getPositionablePoints()) {
        // has to be an anchor...
        if (pp->getType() == PositionablePoint::ANCHOR) {
            // adjacent track segments must be defined...
            TrackSegment* ts1 = pp->getConnect1();
            TrackSegment* ts2 = pp->getConnect2();
            if ((ts1 != nullptr) && (ts2 != nullptr)) {
                // can't be an arc, circle or bezier...
                if (!ts1->isArc() && !ts1->isCircle() && !ts1->isBezier()
                        && !ts2->isArc() && !ts2->isCircle() && !ts2->isBezier()) {
                    // must be in same block...
                    QString blockName1 = ts1->getBlockName();
                    QString blockName2 = ts2->getBlockName();
                    if (blockName1 == (blockName2)) {
                        // if length of ts1 is zero...
                        QRectF bounds1 = ts1->getBounds();
                        double length1 = hypot(bounds1.width(), bounds1.height());
                        if (length1 < 1.0) {
                            aatzlts.append(pp);
                            continue;   // so we don't get added again
                        }
                        // if length of ts2 is zero...
                        QRectF bounds = ts2->getBounds();
                        double length = hypot(bounds.width(), bounds.height());
                        if (length < 1.0) {
                            aatzlts.append(pp);
                            continue;   // so we don't get added again
                        }
                        // if either track segment has decorations
                        if (ts1->hasDecorations() || ts2->hasDecorations()) {
                            continue;   // skip it
                        }
                        // if adjacent tracks are collinear...
                        double dir1 = ts1->getDirectionRAD();
                        double dir2 = ts2->getDirectionRAD();
                        double diffRAD = MathUtil::absDiffAngleRAD(dir1, dir2);
                        if (MathUtil::equals(diffRAD, 0.0)
                                || MathUtil::equals(diffRAD, M_PI)) {
                            aatzlts.append(pp);
                            continue;   // so we don't get added again
                        }
                    }   // if blocknames are equal
                }   // isn't arc, circle or bezier
            }   // isn't null
        }   // is anchor
    }   // for pp

    // clear the "in progress..." menu item
    checkUnnecessaryAnchorsMenu->clear();

    // for each anchor we found
    for (PositionablePoint* pp : aatzlts) {
        QString anchorName = pp->getName();
        QAction* jmi = new QAction(anchorName, this);
        jmi->setCheckable(true);
        checkUnnecessaryAnchorsMenu->addAction(jmi);
//        jmi.addActionListener((ActionEvent event) -> {
//            doCheckUnnecessaryAnchorsMenuItem(anchorName);
//        });
connect(jmi, SIGNAL(triggered(bool)), this, SLOT(onCheckUnnecessaryAnchorsMenu()));
        // if it's in the check marked set then (re-)checkmark it
        if (checkMarkedMenuItemNamesSet.contains(anchorName)) {
            jmi->setChecked(true);
        }
    }
    // if we didn't find any...
    if (checkUnnecessaryAnchorsMenu->children().count() == 0) {
        checkUnnecessaryAnchorsMenu->addAction(checkNoResultsMenuItem);
    }
}   // setupCheckUnnecessaryAnchorsMenu
#if 0
//
// action to be performed when CheckUnnecessaryAnchorsMenu item is clicked
//
/*private*/ void doCheckUnnecessaryAnchorsMenuItem(
        @Nonnull String anchorName) {
    log.debug("doCheckUnnecessaryAnchorsMenuItem({})", anchorName);

    LayoutTrack layoutTrack = layoutEditor.getFinder().findObjectByName(anchorName);
    if (layoutTrack != null) {
        layoutEditor.setSelectionRect(layoutTrack.getBounds());
        // setSelectionRect calls createSelectionGroups...
        // so we have to clear it before amending to it
        layoutEditor.clearSelectionGroups();
        layoutEditor.amendSelectionGroup(layoutTrack);
        // show its popup menu
        layoutTrack.showPopup();
    } else {
        layoutEditor.clearSelectionGroups();
    }
}   // doCheckUnnecessaryAnchorsMenuItem
#endif
//
// collect the names of all checkbox menu items with checkmarks
//
/*private*/ QSet<QString> LayoutEditorChecks::getCheckMarkedMenuItemNames(/*@Nonnull*/ QMenu* menu) {
    QSet<QString> results = QSet<QString>();
    for (int idx = 0; idx < menu->children().count(); idx++) {
        QObject* menuComponent = menu->children().at(idx);
        //if (menuComponent instanceof JCheckBoxMenuItem)
        if(qobject_cast<QAction*>(menuComponent))
        {
            QAction* checkBoxMenuItem = (QAction*) menuComponent;
            checkBoxMenuItem->setCheckable(true);
            if (checkBoxMenuItem->isChecked()) {
                results.insert(checkBoxMenuItem->text());
            }
        }
    }
    return results;
}   // getCheckMarkedMenuItemNames

/*private*/ /*final*/ /*static*/ Logger* LayoutEditorChecks::log
        = LoggerFactory::getLogger("LayoutEditorChecks");


