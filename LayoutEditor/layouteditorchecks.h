#ifndef LAYOUTEDITORCHECKS_H
#define LAYOUTEDITORCHECKS_H

#include <QObject>
#include "actionlistener.h"
#include <QSet>

class Logger;
class QMenu;
class QAction;
class LayoutEditor;
class LayoutEditorChecks : public QObject
{
 Q_OBJECT
public:
 /*public*/ LayoutEditorChecks(/*@Nonnull*/ LayoutEditor* layoutEditor, QObject *parent = nullptr);

signals:

public slots:

private:
 static Logger* log;
 /*private*/ /*final*/ LayoutEditor* layoutEditor;
 /*private*/ QMenu* checkMenu;// = new JMenu(Bundle.getMessage("CheckMenuTitle"));
 /*private*/ QAction* checkInProgressMenuItem;// = new JMenuItem(Bundle.getMessage("CheckInProgressMenuItemTitle"));
 /*private*/ QAction* checkNoResultsMenuItem ;//= new JMenuItem(Bundle.getMessage("CheckNoResultsMenuItemTitle"));

 // Check for Un-Connected Tracks
 /*private*/ QMenu* checkUnConnectedTracksMenu;// = new JMenu(Bundle.getMessage("CheckUnConnectedTracksMenuTitle"));

 // Check for Un-Blocked Tracks
 /*private*/ QMenu* checkUnBlockedTracksMenu;// = new JMenu(Bundle.getMessage("CheckUnBlockedTracksMenuTitle"));

 // Check for Non-Contiguous Blocks
 /*private*/ QMenu* checkNonContiguousBlocksMenu;// = new JMenu(Bundle.getMessage("CheckNonContiguousBlocksMenuTitle"));

 // Check for Unnecessary Anchors
 /*private*/ QMenu* checkUnnecessaryAnchorsMenu;// = new JMenu(Bundle.getMessage("CheckUnnecessaryAnchorsMenuTitle"));
 // Check for Linear Bezier Track Segments
 /*private*/ QMenu* checkLinearBezierTrackSegmentsMenu;// = new JMenu(Bundle.getMessage("CheckLinearBezierTrackSegmentsMenuTitle"));

 // Check for Fixed Radius Bezier Track Segments
 /*private*/ QMenu* checkFixedRadiusBezierTrackSegmentsMenu;// = new JMenu(Bundle.getMessage("CheckFixedRadiusBezierTrackSegmentsMenuTitle"));

 /*private*/ QSet<QString> getCheckMarkedMenuItemNames(/*@Nonnull*/ QMenu* menu);
 /*private*/ void setupCheckUnConnectedTracksMenu();
 /*private*/ void setupCheckUnBlockedTracksMenu();
 /*private*/ void setupCheckNonContiguousBlocksMenu();
 /*private*/ void doCheckNonContiguousBlocksMenuItem(/*@Nonnull*/ QString blockName,
         /*@Nullable*/ QSet<QString> *trackNameSet);
 /*private*/ void setupCheckUnnecessaryAnchorsMenu();
 /*private*/ void doCheckUnnecessaryAnchorsMenuItem(
         /*@Nonnull*/ QString anchorName);
 /*private*/ void setupCheckLinearBezierTrackSegmentsMenu();
 /*private*/ void doCheckLinearBezierTrackSegmentsMenuItem(/*@Nonnull*/ QString trackSegmentName);
 /*private*/ void setupCheckFixedRadiusBezierTrackSegmentsMenu();
 /*private*/ void doCheckFixedRadiusBezierTrackSegmentsMenuItem(/*@Nonnull*/ QString trackSegmentName);
 //void testFunct();

private slots:
 /*private*/ void doCheckUnConnectedTracksMenuItem(/*@Nonnull String menuItemName*/);
 /*private*/ void doCheckUnBlockedTracksMenuItem(/*@Nonnull String menuItemName*/) ;

protected:
 /*protected*/ void setupChecksMenu(/*@Nonnull*/ QMenu* toolsMenu);
 friend class LayoutEditor;
 friend class SubMenuActionListener;
};

//class SubMenuActionListener : public ActionListener
//{
// Q_OBJECT
// LayoutEditorChecks* layoutEditorChecks;
// QString blockName;
// QSet<QString> trackNameSet;
//public:
// SubMenuActionListener(QString blockName, QSet<QString> trackNameSet, LayoutEditorChecks* layoutEditorChecks);
//public slots:
// void actionPerformed();
//};
#endif // LAYOUTEDITORCHECKS_H
