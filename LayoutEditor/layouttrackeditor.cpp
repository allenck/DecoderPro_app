#include "layouttrackeditor.h"
#include "layoutrhturnout.h"
#include "layoutrhturnouteditor.h"
#include "layoutlhturnout.h"
#include "layoutwye.h"
#include "userpreferencesmanager.h"
#include "layoutxover.h"
#include "layoutlhturnouteditor.h"
#include "layoutwyeeditor.h"
#include "layoutrhxover.h"
#include "layoutlhxover.h"
#include "layoutdoublexover.h"
#include "layoutrhxovereditor.h"
#include "layoutlhxovereditor.h"
#include "layoutdoublexovereditor.h"
#include "layoutsingleslip.h"
#include "layoutsingleslipeditor.h"
#include "layoutdoubleslip.h"
#include "layoutdoubleslipeditor.h"
#include "tracksegmenteditor.h"
#include "positionablepointeditor.h"
#include "levelxingeditor.h"
#include "layoutturntableeditor.h"
#include "layoutturntable.h"
#include "blockmanager.h"
#include "positionablepoint.h"
#include "entryexitpairs.h"
#include "loggerfactory.h"

/**
 * MVC root Editor component for LayoutTrack hierarchy objects.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
//abstract /*public*/ class LayoutTrackEditor {

    /**
     * constructor method.
     * @param layoutEditor main layout editor.
     */
    /*public*/ LayoutTrackEditor::LayoutTrackEditor(/*@Nonnull*/ LayoutEditor* layoutEditor) {
         this->layoutEditor = layoutEditor;
    }

    // temporary method to get a correct-type *Editor or subclass.
    // Eventually, this will go away once *Editor's are created
    // in type-specific *View classes
    // @Deprecated // should be made not necessary
    /*@Nonnull*/
    /*static*/ /*public*/ LayoutTrackEditor* LayoutTrackEditor::makeTrackEditor(/*@Nonnull*/ LayoutTrack* layoutTrack, /*@Nonnull*/ LayoutEditor* layoutEditor) {

        if (qobject_cast<LayoutTurnout*>(layoutTrack)) {

            if (qobject_cast<LayoutRHTurnout*>(layoutTrack)) { return new LayoutRHTurnoutEditor(layoutEditor); }
            if (qobject_cast<LayoutLHTurnout*>(layoutTrack)) { return new LayoutLHTurnoutEditor(layoutEditor); }
            if (qobject_cast<LayoutWye*>(layoutTrack)) { return new LayoutWyeEditor(layoutEditor); }

            if (qobject_cast<LayoutXOver*>(layoutTrack)) {
                if (qobject_cast<LayoutRHXOver*>(layoutTrack)) { return new LayoutRHXOverEditor(layoutEditor); }
                if (qobject_cast<LayoutLHXOver*>(layoutTrack)) { return new LayoutLHXOverEditor(layoutEditor); }
                if (qobject_cast<LayoutDoubleXOver*>(layoutTrack)) { return new LayoutDoubleXOverEditor(layoutEditor); }

                return new LayoutXOverEditor(layoutEditor);
            }

            if (qobject_cast<LayoutSlip*>(layoutTrack)) {
                if (qobject_cast<LayoutSingleSlip*>(layoutTrack)) { return new LayoutSingleSlipEditor(layoutEditor); }
                if (qobject_cast<LayoutDoubleSlip*>(layoutTrack)) { return new LayoutDoubleSlipEditor(layoutEditor); }

                return new LayoutSlipEditor(layoutEditor);
            }

            return new LayoutTurnoutEditor(layoutEditor);
        }
        if (qobject_cast<TrackSegment*>(layoutTrack)) { return new TrackSegmentEditor(layoutEditor); }
        if (qobject_cast<PositionablePoint*>(layoutTrack)) { return new PositionablePointEditor(layoutEditor); }
        if (qobject_cast<LevelXing*>(layoutTrack)) { return new LevelXingEditor(layoutEditor); }
        if (qobject_cast<LayoutTurntable*>(layoutTrack)) { return new LayoutTurntableEditor(layoutEditor); }

        log->error(tr("makeTrackEditor did not match type of %1").arg(layoutTrack->metaObject()->className()), Exception("traceback"));
        return new LTE_LayoutTrackEditor(layoutEditor);
//        {
//            //@Override
//            /*public*/ void editLayoutTrack(/*@Nonnull*/ LayoutTrack* layoutTrack) {
//                log->error("Not a valid LayoutTrackEditor implementation", new Exception("traceback"));
//            }
//        };
    }

    /**
     * Launch the editor for a particular LayoutTrack-tree object.
     * @param layoutTrack the layout track to edit.
     */
    //abstract /*public*/ void editLayoutTrack(/*@Nonnull*/ LayoutTrack layoutTrack);



    /*protected*/ void LayoutTrackEditor::addDoneCancelButtons(JPanel* target, JRootPane* rp, ActionListener* doneCallback, ActionListener* cancelCallback) {
        // Done
        QPushButton* doneButton = new QPushButton(tr("Done"));
        target->layout()->addWidget(doneButton);  // NOI18N
        //doneButton->addActionListener(doneCallback);
        connect(doneButton, SIGNAL(clicked(bool)), doneCallback->self(), SLOT(actionPerformed()));
        doneButton->setToolTip(tr("Click [%1] to accept any changes made above and close this dialog.").arg(tr("Done")));  // NOI18N

        // Cancel
        QPushButton* cancelButton = new QPushButton(tr("Cancel")); // NOI18N
        target->layout()->addWidget(cancelButton);
        //cancelButton.addActionListener(cancelCallback);
        connect(cancelButton, SIGNAL(clicked(bool)), cancelCallback->self(), SLOT(actionPerformed()));
        cancelButton->setToolTip(tr("Click [%1] to dismiss this dialog without making changes.").arg(tr("Cancel")));  // NOI18N
#if 0
        rp.setDefaultButton(doneButton);
        // bind ESC to close window
        rp.getInputMap(JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT).put(
                KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0), "close"); // NOI18N
#endif
    }


    /**
     * Display a message describing the reason for the block selection combo box
     * being disabled. An option is provided to hide the message. Note: The
     * PanelMenu class is being used to satisfy the showInfoMessage requirement
     * for a default manager type class.
     *
     * @since 4.11.2
     */
    //@InvokeOnGuiThread
    void LayoutTrackEditor::showSensorMessage() {
        if (sensorList.isEmpty()) {
            return;
        }
        QString msg = tr("<html>Block selection is disabled because the current block is being used by Entry/Exit Pairs.<p>");  // NOI18N
        msg.append(tr("The Entry/Exit sensors are listed below."));  // NOI18N
        QString chkDup = "";
//        sensorList.sort(null);
        for (QString sName : sensorList) {
            if (sName !=(chkDup)) {
                msg.append("<br>&nbsp;&nbsp;&nbsp; " + sName);  // NOI18N
            }
            chkDup = sName;
        }
        msg.append("<br>&nbsp;</html>");  // NOI18N
        ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
                showInfoMessage(
                        tr("Block Entry/Exit Sensor Notification"), // NOI18N
                        msg,
                        "jmri.jmrit.display.PanelMenu", // NOI18N
                        "BlockSensorMessage");  // NOI18N
    }


    /**
     * Create a list of NX sensors that refer to the current layout block. This
     * is used to disable block selection in the edit dialog. The list is built
     * by {@link jmri.jmrit.entryexit.EntryExitPairs#layoutBlockSensors}.
     *
     * @since 4.11.2
     * @param loBlk The current layout block.
     * @return true if sensors are affected.
     */
    bool LayoutTrackEditor::hasNxSensorPairs(LayoutBlock* loBlk) {
        if (loBlk == nullptr) {
            return false;
        }
        QStringList blockSensors = ((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"))
                ->layoutBlockSensors(loBlk);
        if (blockSensors.isEmpty()) {
            return false;
        }
        //sensorList.addAll(blockSensors);
        foreach (QString s, blockSensors) {
         sensorList.append(s);
        }
        return true;
    }


    /*private*/ /*final*/ /*static*/ Logger* LayoutTrackEditor::log = LoggerFactory::getLogger("LayoutTrackEditor");
