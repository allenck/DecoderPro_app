#include "layoutlhturnouteditor.h"
#include "layoutturnout.h"

/**
 * MVC Editor component for LayoutLHTurnout objects.
 *
 * Note there might not be anything for this class to do;
 * LayoutTrackEditors has a comment saying that PositionablePoint
 * doesn't have an editor.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
///*public*/ class LayoutLHTurnoutEditor extends LayoutTurnoutEditor {

    /**
     * constructor method.
     * @param layoutEditor main layout editor.
     */
    /*public*/ LayoutLHTurnoutEditor::LayoutLHTurnoutEditor(/*@Nonnull*/ LayoutEditor* layoutEditor) :LayoutTurnoutEditor(layoutEditor) {
        //super(layoutEditor);
    }

    // set the continuing route Turnout State
    //@Override
    /*protected*/ void LayoutLHTurnoutEditor::setContinuingRouteTurnoutState() {
        layoutTurnout->setContinuingSense(Turnout::CLOSED);
        if (editLayoutTurnoutStateComboBox->currentIndex() == editLayoutTurnoutThrownIndex) {
            layoutTurnout->setContinuingSense(Turnout::THROWN);
        }
    }
