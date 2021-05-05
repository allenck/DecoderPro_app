#include "blockcurvaturejcombobox.h"
#include "block.h"
#include "vptr.h"

/**
 * JComboBox to display / select block curvature.
 * @see jmri.Block
 *
 * @author Bob Jacobsen Copyright (C) 2003, 2008
 * @author Egbert Broerse Copyright (C) 2017
 * @author Steve Young Copyright (C) 2021
 */
// /*public*/ class BlockCurvatureJComboBox extends JComboBox<String> {

    /*private*/ /*static*/ /*final*/ QString BlockCurvatureJComboBox::NONE_TEXT = tr("BlockNone"); // NOI18N
    /*private*/ /*static*/ /*final*/ QString BlockCurvatureJComboBox::GRADUAL_TEXT = tr("BlockGradual"); // NOI18N
    /*private*/ /*static*/ /*final*/ QString BlockCurvatureJComboBox::TIGHT_TEXT = tr("BlockTight"); // NOI18N
    /*private*/ /*static*/ /*final*/ QString BlockCurvatureJComboBox::SEVERE_TEXT = tr("BlockSevere"); // NOI18N
    /*private*/ /*static*/ /*final*/ QStringList BlockCurvatureJComboBox::CURVE_OPTIONS = {NONE_TEXT, GRADUAL_TEXT, TIGHT_TEXT, SEVERE_TEXT};

    /**
     * Create a new JComboBox to display / select block curvature.
     * <p>
     * Options are presented in localised String form and can be
     * set / retrieved in Block Constant format.
     * <p>
     * Block.NONE, Block.GRADUAL, Block.TIGHT, Block.SEVERE
     * <p>
     * Defaults to No curvature.
     */
    /*public*/ BlockCurvatureJComboBox::BlockCurvatureJComboBox() : JComboBox(new CurvatureComboBoxModel()){
        //super(new CurvatureComboBoxModel());
        setSelectedItem(NONE_TEXT);
    }

    /**
     * Create a new JComboBox to display / select block curvature.
     * <p>
     * Block.NONE, Block.GRADUAL, Block.TIGHT, Block.SEVERE
     * <p>
     * Defaults to No curvature if invalid number in curvature field.
     * @param curvature Block constant for Curvature.
     */
    /*public*/ BlockCurvatureJComboBox::BlockCurvatureJComboBox(int curvature): JComboBox(new CurvatureComboBoxModel()){
        //super(new CurvatureComboBoxModel());
        setCurvature(curvature);
    }

    /**
     * Set UI properties for a JTable cell.
     */
    /*public*/ void BlockCurvatureJComboBox::setJTableCellClientProperties(){
        //putClientProperty("JComponent.sizeVariant", "small"); // NOI18N
        setProperty("JComponent.sizeVariant", "small");
        //putClientProperty("JComboBox.buttonType", "square"); // NOI18N
        setProperty("JComboBox.buttonType", "square");
    }

    /**
     * Set the Block Curvature by Block Constant format.
     * If unrecognised constant, does not error or change selected value.
     * @param blockCurve e.g. "Block.TIGHT" or "Block.NONE"
     */
    /*public*/ /*final*/ void BlockCurvatureJComboBox::setCurvature(int blockCurve){
        setSelectedItem(getStringFromCurvature(blockCurve));
    }

    /**
     * Get the String of Block Curvature from Block Constant format.
     * .e.g. tr("BlockTight")
     * @param blockCurve Block Constant, e.g. Block.GRADUAL
     * @return localised String, or tr("BlockNone") if unmatched.
     */
    /*public*/ /*static*/ QString BlockCurvatureJComboBox::getStringFromCurvature(int blockCurve){
        switch (blockCurve) {
            case Block::GRADUAL:
                return GRADUAL_TEXT;
            case Block::TIGHT:
                return TIGHT_TEXT;
            case Block::SEVERE:
                return SEVERE_TEXT;
            default:
                return NONE_TEXT;
        }
    }

    /**
     * Get the Block Curvature in Block Constant format.
     * e.g. "Block.TIGHT" or "Block.NONE"
     * @return selected Block Curvature constant.
     */
    /*public*/ int BlockCurvatureJComboBox::getCurvature(){
        return getCurvatureFromString(/*(String)*/getSelectedItem());
    }

    /**
     * Get the Block Curvature in Block Constant format.e.g.
     * "Block.TIGHT" or "Block.NONE"
     *
     * @param s localised String, e.g. tr("BlockSevere")
     * @return Block Curvature constant, Block.NONE if String unrecognised.
     */
    /*public*/ /*static*/ int BlockCurvatureJComboBox::getCurvatureFromString(QString s){
        if (GRADUAL_TEXT == (s)){
            return Block::GRADUAL;
        } else if (TIGHT_TEXT == (s)){
            return Block::TIGHT;
        } else if (SEVERE_TEXT == (s)){
            return Block::SEVERE;
        } else {
            return Block::NONE;
        }
    }

    /**
     * Get the Curvature Constant from a JComboBox passed as an Object.
     * For use in setValueAt() in Table Models.
     * @param obj the object which should be a JComboBox.
     * @return Block curvature Constant if JComboBox found and selected item
     *         text matches, else Block.NONE
     */
    /*public*/ /*static*/ int BlockCurvatureJComboBox::getCurvatureFromObject(QVariant obj){
        if (VPtr<BlockCurvatureJComboBox>::asPtr(obj)){
            BlockCurvatureJComboBox* jcb = VPtr<BlockCurvatureJComboBox>::asPtr(obj);
            return getCurvatureFromString(/*(String)*/ jcb->getSelectedItem());
        }
        return Block::NONE;
    }

//    /*private*/ static class CurvatureComboBoxModel extends AbstractListModel<String> implements ComboBoxModel<String> {

//        /*private*/ String selection = null;

//        @Override
//        /*public*/ String getElementAt(int index) {
//            return CURVE_OPTIONS[index];
//        }

//        @Override
//        /*public*/ int getSize() {
//            return CURVE_OPTIONS.length;
//        }

//        @Override
//        /*public*/ void setSelectedItem(Object anItem) {
//            selection = (String) anItem; // to select and register an
//        } // item from the pull-down list

//        // Methods implemented from the interface ComboBoxModel
//        @Override
//        /*public*/ String getSelectedItem() {
//            return selection; // to add the selection to the combo box
//        }
//    }
