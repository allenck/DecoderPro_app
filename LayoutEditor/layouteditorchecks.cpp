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
 checkUnConnectedTracksMenu->setEnabled(false);
 // Check for Un-Blocked Tracks
 checkUnBlockedTracksMenu = new QMenu(tr("Un-Blocked Tracks"));
 checkUnBlockedTracksMenu->setEnabled(false);

 // Check for Non-Contiguous Blocks
 checkNonContiguousBlocksMenu = new QMenu(tr("Non-Contiguous Blocks"));
 checkNonContiguousBlocksMenu->setEnabled(false);

 // Check for Unnecessary Anchors
 checkUnnecessaryAnchorsMenu = new QMenu(tr("Unnecessary Anchors"));
 checkUnnecessaryAnchorsMenu->setEnabled(false);

 // Check for Linear Bezier Track Segments
 checkLinearBezierTrackSegmentsMenu = new QMenu(tr("Linear Bezier Track Segments"));
 checkLinearBezierTrackSegmentsMenu->setEnabled(false);

 // Check for Fixed Radius Bezier Track Segments
 checkFixedRadiusBezierTrackSegmentsMenu = new QMenu(tr("Fixed Radius Bezier Track Segments"));
 checkFixedRadiusBezierTrackSegmentsMenu->setEnabled(false);

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
    connect(checkMenu, &QMenu::aboutToShow, [=]{
            log->debug("menuSelected");
            bool enabled = layoutEditor->isEditable();
            checkUnConnectedTracksMenu->setEnabled(enabled);
            checkUnBlockedTracksMenu->setEnabled(enabled);
            checkNonContiguousBlocksMenu->setEnabled(enabled);
            checkUnnecessaryAnchorsMenu->setEnabled(enabled);
            checkLinearBezierTrackSegmentsMenu->setEnabled(enabled);
            checkFixedRadiusBezierTrackSegmentsMenu->setEnabled(enabled);
        });

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
    connect(checkUnConnectedTracksMenu, &QMenu::aboutToShow, [=]{
            log->debug("menuSelected");
            setupCheckUnConnectedTracksMenu();
        });

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
 \
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
    connect(checkUnBlockedTracksMenu, &QMenu::aboutToShow, [=]{
            log->debug("menuSelected");
            setupCheckUnBlockedTracksMenu();
        });

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
    connect(checkNonContiguousBlocksMenu, &QMenu::aboutToShow, [=]{
            log->debug("menuSelected");
            setupCheckNonContiguousBlocksMenu();
        });

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
    // Check for Unnecessary Anchors
    //
    checkUnnecessaryAnchorsMenu->setToolTip(tr("Select this to check if the adjacent track segments can be merged"));
    checkUnnecessaryAnchorsMenu->addAction(checkInProgressMenuItem);
    checkMenu->addMenu(checkUnnecessaryAnchorsMenu);

//    checkUnnecessaryAnchorsMenu.addMenuListener(new MenuListener() {
//        @Override
//        /*public*/ void menuSelected(@Nonnull MenuEvent menuEvent) {
    connect(checkUnnecessaryAnchorsMenu, &QMenu::aboutToShow, [=]{
            log->debug("menuSelected");
            setupCheckUnnecessaryAnchorsMenu();
        });

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
 // Check for linear bezier track segments
 //
 checkLinearBezierTrackSegmentsMenu->setToolTip(tr("Select this to check if bezier track segments are linear (strait lines)"));
 checkLinearBezierTrackSegmentsMenu->setToolTipsVisible(true);
 checkLinearBezierTrackSegmentsMenu->addAction(checkInProgressMenuItem);
 checkMenu->addMenu(checkLinearBezierTrackSegmentsMenu);

// checkLinearBezierTrackSegmentsMenu.addMenuListener(new MenuListener() {
//     @Override
//     public void menuSelected(@Nonnull MenuEvent menuEvent) {
 connect(checkLinearBezierTrackSegmentsMenu, &QMenu::aboutToShow, [=]{
         log->debug("menuSelected");
         setupCheckLinearBezierTrackSegmentsMenu();
     });

//     @Override
//     public void menuDeselected(@Nonnull MenuEvent menuEvent) {
//         log.debug("menuDeselected");
//         //nothing to see here... move along...
//     }

//     @Override
//     public void menuCanceled(@Nonnull MenuEvent menuEvent) {
//         log.debug("menuCanceled");
//         //nothing to see here... move along...
//     }
// });

 //
 // Check for fixed radius bezier track segments (circle arcs)
 //
 checkFixedRadiusBezierTrackSegmentsMenu->setToolTip(tr("Select this to check if bezier track segments are of fixed radius (arc of circle)"));
 checkFixedRadiusBezierTrackSegmentsMenu->setToolTipsVisible(true);
 checkFixedRadiusBezierTrackSegmentsMenu->addAction(checkInProgressMenuItem);
 checkMenu->addMenu(checkFixedRadiusBezierTrackSegmentsMenu);

// checkFixedRadiusBezierTrackSegmentsMenu.addMenuListener(new MenuListener() {
//     @Override
//     public void menuSelected(@Nonnull MenuEvent menuEvent) {
 connect(checkFixedRadiusBezierTrackSegmentsMenu, &QMenu::aboutToShow, [=]{
         log->debug("menuSelected");
         setupCheckFixedRadiusBezierTrackSegmentsMenu();
     });

//     @Override
//     public void menuDeselected(@Nonnull MenuEvent menuEvent) {
//         log.debug("menuDeselected");
//         //nothing to see here... move along...
//     }

//     @Override
//     public void menuCanceled(@Nonnull MenuEvent menuEvent) {
//         log.debug("menuCanceled");
//         //nothing to see here... move along...
//     }
// });
#if 0
 QAction* testAct = new QAction(tr("test"),this);
 connect(testAct, &QAction::triggered, [=]{
  testFunct();
 });
 checkMenu->addSeparator();
 checkMenu->addAction(testAct);
#endif
}


//
// run the un-connected tracks check and populate the checkUnConnectedTracksMenu
//
/*private*/ void LayoutEditorChecks::setupCheckUnConnectedTracksMenu()
{
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
 if (trackNames.size() > 0)
 {
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
 if (layoutTrack != nullptr)
 {
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
/*private*/ void LayoutEditorChecks::setupCheckUnBlockedTracksMenu()
{
 log->debug("setupCheckUnBlockedTracksMenu");

 // collect the names of all menu items with checkmarks
 QSet<QString> checkMarkedMenuItemNamesSet = getCheckMarkedMenuItemNames(checkUnBlockedTracksMenu);

 // mark our menu as "in progress..."
 checkUnBlockedTracksMenu->clear();
 checkUnBlockedTracksMenu->addAction(checkInProgressMenuItem);

 // check all tracks for un-assigned blocks
 QList<QString> trackNames = QList<QString> ();
 for (LayoutTrack* layoutTrack : *layoutEditor->getLayoutTracks())
 {
  if (!layoutTrack->checkForUnAssignedBlocks()) {
      // add this track to the list of un-assigned track names
      trackNames.append(layoutTrack->getName());
  }
 }

 // clear the "in progress..." menu item
 checkUnBlockedTracksMenu->clear();

 // for each tracks with un-assigned blocks that we found...
 if (trackNames.size() > 0)
 {
  for (QString trackName : trackNames)
  {
   // create a menu item for it
   QAction* jmi = new QAction(trackName, this);
   //jmi->setCheckable(true);
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
 QString menuItemName = ((QAction*)sender())->text();
 log->debug(tr("doCheckUnBlockedTracksMenuItem(%1)").arg(menuItemName));

 LayoutTrack* layoutTrack = layoutEditor->getFinder()->findObjectByName(menuItemName);
 if (layoutTrack != nullptr)
 {
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
/*private*/ void LayoutEditorChecks::setupCheckNonContiguousBlocksMenu()
{
 log->debug("setupCheckNonContiguousBlocksMenu");

 // mark our menu as "in progress..."
 checkNonContiguousBlocksMenu->clear();
 checkNonContiguousBlocksMenu->addAction(checkInProgressMenuItem);

 // collect all contiguous blocks
 QMap<QString, QList<QSet<QString>*>*>* blockNamesToTrackNameSetMaps =  new QMap<QString, QList<QSet<QString>*>*>();
 for (LayoutTrack* layoutTrack : *layoutEditor->getLayoutTracks()) {
     layoutTrack->checkForNonContiguousBlocks(blockNamesToTrackNameSetMaps);
 }

 // clear the "in progress..." menu item
 checkNonContiguousBlocksMenu->clear();

 // for each bad block we found...
 //for (Map.Entry<String, List<Set<String>>> entry : blockNamesToTrackNameSetMaps.entrySet())
 QMapIterator<QString, QList<QSet<QString>*>*> entry(*blockNamesToTrackNameSetMaps);
 while(entry.hasNext())
 {
  entry.next();
  QString blockName = entry.key();
  QList<QSet<QString>*>* trackNameSets = entry.value();
  if (trackNameSets->size() > 1)
  {
   QMenu* jmi = new QMenu(blockName);
   checkNonContiguousBlocksMenu->addMenu(jmi);

   int idx = 1;
   for (QSet<QString>* trackNameSet : *trackNameSets)
   {
    QAction* subMenuItem = new QAction(tr("%1").arg(blockName) + "#" + QString::number(idx++),this);
    jmi->addAction(subMenuItem);
//                subMenuItem.addActionListener((ActionEvent event) -> {
    connect(subMenuItem, &QAction::triggered, [=]{
        doCheckNonContiguousBlocksMenuItem(blockName, trackNameSet);
    });
//                SubMenuActionListener* listener = new SubMenuActionListener(blockName, trackNameSet, this);
//                connect(subMenuItem, SIGNAL(triggered(bool)), listener, SLOT(actionPerformed()));
   }
  }
 }

 // if we didn't find any...
 if (checkNonContiguousBlocksMenu->children().count() == 0) {
     checkNonContiguousBlocksMenu->addAction(checkNoResultsMenuItem);
 }
}   // setupCheckNonContiguousBlocksMenu

//SubMenuActionListener::SubMenuActionListener(QString blockName, QSet<QString> trackNameSet, LayoutEditorChecks *layoutEditorChecks)
//{
// this->blockName = blockName;
// this->trackNameSet = trackNameSet;
// this->layoutEditorChecks = layoutEditorChecks;
//}
//void SubMenuActionListener::actionPerformed()
//{
// layoutEditorChecks->doCheckNonContiguousBlocksMenuItem(blockName, trackNameSet);
//}

//
// action to be performed when checkNonContiguousBlocksMenu item is clicked
//
/*private*/ void LayoutEditorChecks::doCheckNonContiguousBlocksMenuItem(
        /*@Nonnull*/ QString blockName,
        /*@Nullable*/ QSet<QString>* trackNameSet)
{
 log->debug(tr("doCheckNonContiguousBlocksMenuItem(%1)").arg(blockName));

 if (!trackNameSet->isEmpty())
 {
  // collect all the bounds...
  QRectF bounds = QRectF();
  for (LayoutTrack* layoutTrack : *layoutEditor->getLayoutTracks())
  {
   if (trackNameSet->contains(layoutTrack->getName()))
   {
    QRectF trackBounds = layoutTrack->getBounds();
    if (bounds.isNull()) {
        bounds =QRectF(trackBounds.x(), trackBounds.y(), trackBounds.width(), trackBounds.height());
    } else {
        bounds = bounds.united(trackBounds);
    }
   }
  }
  layoutEditor->setSelectionRect(bounds);

  // setSelectionRect calls createSelectionGroups...
  // so we have to clear it before amending to it
  layoutEditor->clearSelectionGroups();

  // amend all tracks in this block to the layout editor selection group
  for (LayoutTrack* layoutTrack : *layoutEditor->getLayoutTracks()) {
      if (trackNameSet->contains(layoutTrack->getName())) {
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
/*private*/ void LayoutEditorChecks::setupCheckUnnecessaryAnchorsMenu()
{
 log->debug("setupCheckUnnecessaryAnchorsMenu");

 // collect the names of all menu items with checkmarks
 QSet<QString> checkMarkedMenuItemNamesSet = getCheckMarkedMenuItemNames(checkUnBlockedTracksMenu);
 // mark our menu as "in progress..."
 checkUnnecessaryAnchorsMenu->clear();
 checkUnnecessaryAnchorsMenu->addAction(checkInProgressMenuItem);

 // check all PositionablePoints
 QList<PositionablePoint*> aatzlts = QList<PositionablePoint*>();
 for (PositionablePoint* pp : layoutEditor->getPositionablePoints())
 {
  // has to be an anchor...
  if (pp->getType() == PositionablePoint::ANCHOR)
  {
   // adjacent track segments must be defined...
   TrackSegment* ts1 = pp->getConnect1();
   TrackSegment* ts2 = pp->getConnect2();
   if ((ts1 != nullptr) && (ts2 != nullptr))
   {
    // can't be an arc, circle or bezier...
    if (!ts1->isArc() && !ts1->isCircle() && !ts1->isBezier()
            && !ts2->isArc() && !ts2->isCircle() && !ts2->isBezier())
    {
     // must be in same block...
     QString blockName1 = ts1->getBlockName();
     QString blockName2 = ts2->getBlockName();
     if (blockName1 == (blockName2))
     {
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
 for (PositionablePoint* pp : aatzlts)
 {
  QString anchorName = pp->getName();
  QAction* jmi = new QAction(anchorName, this);
  jmi->setCheckable(true);
  checkUnnecessaryAnchorsMenu->addAction(jmi);
//        jmi.addActionListener((ActionEvent event) -> {
  connect(jmi, &QAction::triggered, [=]{
      doCheckUnnecessaryAnchorsMenuItem(anchorName);
  });
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

//
// action to be performed when CheckUnnecessaryAnchorsMenu item is clicked
//
/*private*/ void LayoutEditorChecks::doCheckUnnecessaryAnchorsMenuItem(
     /*@Nonnull*/ QString anchorName) {
 log->debug(tr("doCheckUnnecessaryAnchorsMenuItem(%1)").arg(anchorName));

 LayoutTrack* layoutTrack = layoutEditor->getFinder()->findObjectByName(anchorName);
 if (layoutTrack != nullptr) {
     layoutEditor->setSelectionRect(layoutTrack->getBounds());
     // setSelectionRect calls createSelectionGroups...
     // so we have to clear it before amending to it
     layoutEditor->clearSelectionGroups();
     layoutEditor->amendSelectionGroup(layoutTrack);
     // show its popup menu
     layoutTrack->showPopup();
 } else {
     layoutEditor->clearSelectionGroups();
 }
}   // doCheckUnnecessaryAnchorsMenuItem

//
// run the linear bezier track segments check and
// populate the checkLinearBezierTrackSegmentsMenu
//
/*private*/ void LayoutEditorChecks::setupCheckLinearBezierTrackSegmentsMenu()
{
 log->debug("setupCheckLinearBezierTrackSegmentsMenu");

 // collect the names of all menu items with checkmarks
 QSet<QString> checkMarkedMenuItemNamesSet = getCheckMarkedMenuItemNames(checkLinearBezierTrackSegmentsMenu);
 // mark our menu as "in progress..."
 checkLinearBezierTrackSegmentsMenu->clear();
 checkLinearBezierTrackSegmentsMenu->addAction(checkInProgressMenuItem);

 // check all TrackSegments
 QList<TrackSegment*> linearBezierTrackSegments;// = new ArrayList<>();
 for (TrackSegment* ts : layoutEditor->getTrackSegments())
 {
  // has to be a bezier
  if (ts->isBezier())
  {
//                if (ts.getName().equals("T104")) {
//                    log.debug("T104");
//                }
   // adjacent connections must be defined...
   LayoutTrack* c1 = ts->getConnect1();
   LayoutTrack* c2 = ts->getConnect2();
   if ((c1 != nullptr) && (c2 != nullptr))
   {
    // if length is zero...
    QPointF end1 = LayoutEditor::getCoords(ts->getConnect1(), ts->getType1());
    QPointF end2 = LayoutEditor::getCoords(ts->getConnect2(), ts->getType2());
    if (MathUtil::distance(end1, end2) <= 4.0) {
        linearBezierTrackSegments.append(ts);
        continue;   // so we don't get added again
    }
    // if control points are collinear...
    bool good = true; //assume success (optimist!)
    for (QPointF cp : ts->getBezierControlPoints()) {
        if (qAbs(MathUtil::distance(end1, end2, cp)) > 1.0) {
            good = false;
            break;
        }
    }
    if (good) {
        linearBezierTrackSegments.append(ts);
//                        ts.setBezier(false);
    }
   }   // c1 & c2 aren't null
  }   // is bezier
 }   // for ts

 // clear the "in progress..." menu item
 checkLinearBezierTrackSegmentsMenu->clear();
 // if we didn't find any...
 if (linearBezierTrackSegments.size() == 0) {
     checkLinearBezierTrackSegmentsMenu->addAction(checkNoResultsMenuItem);
 } else {
  // for each linear bezier track segment we found
  for (TrackSegment* ts : linearBezierTrackSegments) {
      QString name = ts->getName();
      QAction* jmi = new QAction(name, this);
      jmi->setCheckable(true);
      checkLinearBezierTrackSegmentsMenu->addAction(jmi);
      //jmi.addActionListener((ActionEvent event) -> {
      connect(jmi, &QAction::triggered, [=]{
          doCheckLinearBezierTrackSegmentsMenuItem(name);
      });

      // if it's in the check marked set then (re-)checkmark it
      if (checkMarkedMenuItemNamesSet.contains(name)) {
          jmi->setChecked(true);
      }
      //ts.setBezier(false);
  }
 }   //count == 0
}   // setupCheckLinearBezierTrackSegmentsMenu

//
// action to be performed when checkLinearBezierTrackSegmentsMenu item is clicked
//
/*private*/ void LayoutEditorChecks::doCheckLinearBezierTrackSegmentsMenuItem(
        /*@Nonnull*/ QString trackSegmentName)
{
 log->debug(tr("doCheckLinearBezierTrackSegmentsMenuItem(%1)").arg(trackSegmentName));

 LayoutTrack* layoutTrack = layoutEditor->getFinder()->findObjectByName(trackSegmentName);
 if (layoutTrack != nullptr) {
     layoutEditor->setSelectionRect(layoutTrack->getBounds());
     // setSelectionRect calls createSelectionGroups...
     // so we have to clear it before amending to it
     layoutEditor->clearSelectionGroups();
     layoutEditor->amendSelectionGroup(layoutTrack);
     // show its popup menu
     layoutTrack->showPopup();
 } else {
     layoutEditor->clearSelectionGroups();
 }
}   // doCheckLinearBezierTrackSegmentsMenuItem

//
// run the linear bezier track segments check and
// populate the checkFixedRadiusBezierTrackSegmentsMenu
//
/*private*/ void LayoutEditorChecks::setupCheckFixedRadiusBezierTrackSegmentsMenu()
{
 log->debug("setupCheckFixedRadiusBezierTrackSegmentsMenu");

 // collect the names of all menu items with checkmarks
 QSet<QString> checkMarkedMenuItemNamesSet = getCheckMarkedMenuItemNames(checkFixedRadiusBezierTrackSegmentsMenu);
 // mark our menu as "in progress..."
 checkFixedRadiusBezierTrackSegmentsMenu->clear();
 checkFixedRadiusBezierTrackSegmentsMenu->addAction(checkInProgressMenuItem);

 // check all TrackSegments
 QList<TrackSegment*> linearBezierTrackSegments = QList<TrackSegment*>();
 for (TrackSegment* ts : layoutEditor->getTrackSegments())
 {
  // has to be a bezier
  if (ts->isBezier())
  {
   // adjacent connections must be defined...
   LayoutTrack* c1 = ts->getConnect1();
   LayoutTrack* c2 = ts->getConnect2();
   if ((c1 != nullptr) && (c2 != nullptr))
   {
    QPointF end1 = LayoutEditor::getCoords(c1, ts->getType1());
    QPointF end2 = LayoutEditor::getCoords(c2, ts->getType2());
    double chordLength = MathUtil::distance(end1, end2);
    if (chordLength <= 4.0) {
        continue;   //skip short segments
    }

    //get first and last control points
    int cnt = ts->getNumberOfBezierControlPoints();
    if (cnt > 0)
    {
     QPointF cp0 = ts->getBezierControlPoint(0);
     QPointF cpN = ts->getBezierControlPoint(cnt - 1);
     //calculate orthoginal points
     QPointF op1 = MathUtil::add(end1, MathUtil::orthogonal(MathUtil::subtract(cp0, end1)));
     QPointF op2 = MathUtil::subtract(end2, MathUtil::orthogonal(MathUtil::subtract(cpN, end2)));
     //use them to find center point
     QPointF ip = MathUtil::intersect(end1, op1, end2, op2);
     if (!ip.isNull())
     {   //single intersection point found
      double r1 = MathUtil::distance(ip, end1);
      double r2 = MathUtil::distance(ip, end2);
      if (qAbs(r1 - r2) <= 1.0)
      {
       // the sign of the distance tells what side of the line the center point is on
       //double ipSide = Math.signum(MathUtil.distance(end1, end2, ip));
       double ipSide;
       if(MathUtil::distance(end1, end2, ip)>0) ipSide = 1;
       if(MathUtil::distance(end1, end2, ip)<0) ipSide = -1;

       // if all control midpoints are equal distance from intersection point
       bool good = true; //assume success (optimist!)

       for (int idx = 0; idx < cnt - 1; idx++)
       {
        QPointF cp1 = ts->getBezierControlPoint(idx);
        QPointF cp2 = ts->getBezierControlPoint(idx + 1);
        QPointF mp = MathUtil::midPoint(cp1, cp2);
        double rM = MathUtil::distance(ip, mp);
        if (qAbs(r1 - rM) > 1.0) {
            good = false;
            break;
        }
        // the sign of the distance tells what side of line the midpoint is on
        //double cpSide = qSignum(MathUtil::distance(end1, end2, mp));
        double cpSide;
        if(MathUtil::distance(end1, end2, mp)>0) cpSide = 1;
        if(MathUtil::distance(end1, end2, mp)<0) cpSide = -1;
        if (MathUtil::equals(ipSide, cpSide)) {
            //can't be on same side as center point (if so then not circular)
            good = false;
            break;
        }
       }
       if (good) {
           linearBezierTrackSegments.append(ts);
           ts->setCircle(true);
       }
      } else {
          log->error("checkFixedRadiusBezierTrackSegments(): unequal radius");
      }
     }
    }
   }   // c1 & c2 aren't null
  }   // is bezier
 }   // for ts

 // clear the "in progress..." menu item
 checkFixedRadiusBezierTrackSegmentsMenu->clear();
 // if we didn't find any...
 if (checkFixedRadiusBezierTrackSegmentsMenu->actions().count() == 0) {
     checkFixedRadiusBezierTrackSegmentsMenu->addAction(checkNoResultsMenuItem);
 } else {
  // for each linear bezier track segment we found
  for (TrackSegment* ts : linearBezierTrackSegments)
  {
   QString name = ts->getName();
   QAction* jmi = new QAction(name, this);
   jmi->setCheckable(true);
   checkFixedRadiusBezierTrackSegmentsMenu->addAction(jmi);
   //jmi.addActionListener((ActionEvent event) -> {
   connect(jmi, &QAction::triggered, [=]{
       doCheckFixedRadiusBezierTrackSegmentsMenuItem(name);
   });

   // if it's in the check marked set then (re-)checkmark it
   if (checkMarkedMenuItemNamesSet.contains(name)) {
       jmi->setChecked(true);
   }
   ///ts.setBezier(false);
  }
 }   //count == 0
}   // setupCheckFixedRadiusBezierTrackSegmentsMenu

//
// action to be performed when checkFixedRadiusBezierTrackSegmentsMenu item is clicked
//
/*private*/ void LayoutEditorChecks::doCheckFixedRadiusBezierTrackSegmentsMenuItem(
        /*@Nonnull*/ QString trackSegmentName)
{
 log->debug(tr("doCheckFixedRadiusBezierTrackSegmentsMenuItem({})").arg(trackSegmentName));

 LayoutTrack* layoutTrack = layoutEditor->getFinder()->findObjectByName(trackSegmentName);
 if (layoutTrack != nullptr) {
     layoutEditor->setSelectionRect(layoutTrack->getBounds());
     // setSelectionRect calls createSelectionGroups...
     // so we have to clear it before amending to it
     layoutEditor->clearSelectionGroups();
     layoutEditor->amendSelectionGroup(layoutTrack);
     // show its popup menu
     layoutTrack->showPopup();
 } else {
     layoutEditor->clearSelectionGroups();
 }
}   // doCheckFixedRadiusBezierTrackSegmentsMenuItem

//
// collect the names of all checkbox menu items with checkmarks
//
/*private*/ QSet<QString> LayoutEditorChecks::getCheckMarkedMenuItemNames(/*@Nonnull*/ QMenu* menu)
{
 QSet<QString> results = QSet<QString>();
 for (int idx = 0; idx < menu->children().count(); idx++)
 {
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

//void LayoutEditorChecks::testFunct()
//{
// QMap<QString, QList<QSet<QString>*>*>* blockNamesToTrackNameSetMaps =  new QMap<QString, QList<QSet<QString>*>*>();
// for (LayoutTrack* layoutTrack : *layoutEditor->getLayoutTracks()) {
//     layoutTrack->checkForNonContiguousBlocks(blockNamesToTrackNameSetMaps);
// }
// log->debug(tr("count = %1").arg(blockNamesToTrackNameSetMaps->count()));
//}

/*private*/ /*final*/ /*static*/ Logger* LayoutEditorChecks::log = LoggerFactory::getLogger("LayoutEditorChecks");


