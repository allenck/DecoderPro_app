#include "layoutwyeeditor.h"
#include "layoutturnout.h"

/**
 * MVC Editor component for LayoutWye objects.
 *
 * Note there might not be anything for this class to do;
 * LayoutTrackEditors has a comment saying that PositionablePoint
 * doesn't have an editor.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
///*public*/ class LayoutWyeEditor extends LayoutTurnoutEditor {

    /**
     * constructor method.
     * @param layoutEditor main layout editor.
     */
    /*public*/ LayoutWyeEditor::LayoutWyeEditor(/*@Nonnull*/ LayoutEditor* layoutEditor) : LayoutTurnoutEditor(layoutEditor){
        //super(layoutEditor);
    }

    // set the continuing route Turnout State
    //@Override
    /*protected*/ void LayoutWyeEditor::setContinuingRouteTurnoutState() {
        layoutTurnout->setContinuingSense(Turnout::CLOSED);
        if (editLayoutTurnoutStateComboBox->currentIndex() == editLayoutTurnoutThrownIndex) {
            layoutTurnout->setContinuingSense(Turnout::THROWN);
        }
    }
