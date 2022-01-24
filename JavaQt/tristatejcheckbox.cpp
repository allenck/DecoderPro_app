#include "tristatejcheckbox.h"
#include "loggerfactory.h"
#include <QPainter>
#include <QIcon>

/**
 *
 * Extension of JCheckBox allowing a partial state to be displayed.
 *
 * The partial state is in the form of a small square, a style similar to Google Earth.
 *
 * If Checkbox is pressed when unchecked, state changes to checked.
 * If Checkbox is pressed when checked, state changes to unchecked.
 * If Checkbox is pressed when partial, state changes to unchecked.
 *
 * User can only check / un-check the checkbox,
 * the partial state is only available programatically.
 *
 * State can be set by enum or an array of boolean values.
 *
 * The enum of the actual state can be obtained,
 * isSelected() returns false when in a partial state.
 *
 * <p>
 * Inspired by postings of
 * 843806 https://community.oracle.com/tech/developers/discussion/1354306/is-there-a-tri-state-check-box-in-swing
 * s1w_ https://stackoverflow.com/questions/1263323/tristate-checkboxes-in-java
 *
 *
 * @author Steve Young Copyright (c) 2021
 */
// /*public*/ class TriStateJCheckBox extends JCheckBox implements Icon  {


    /**
     * Creates a check box.
     * Defaults to unchecked state.
     *
     */
    /*public*/ TriStateJCheckBox::TriStateJCheckBox () : JCheckBox(){
        //super();
        initProperties();
    }

    /**
     * Creates a check box with text.
     * Defaults to unchecked state.
     *
     * @param text the text of the check box.
     */
    /*public*/ TriStateJCheckBox::TriStateJCheckBox (QString text) : JCheckBox(){
        JCheckBox::setText(text);
        initProperties();
    }

    /*private*/ void TriStateJCheckBox::initProperties(){
        setModel(new TriStateModel(State::UNCHECKED));
        setIcon(QIcon());
        setRolloverEnabled( false );
        setOpaque(true);
    }

    /**
     * Set the new state to either CHECKED, PARTIAL or UNCHECKED.
     * @param state enum of new state.
     */
    /*public*/ void TriStateJCheckBox::setState(/*@Nonnull*/ State state) {
        ((TriStateModel*) model)->setState(state);
    }

    /**
     * Set the new state using values within a boolean array.
     *
     * boolean[]{false,false} = UNCHECKED
     * boolean[]{true,true} = CHECKED
     * boolean[]{true,false} = PARTIAL
     *
     * @param booleanArray boolean values to compare
     */
    /*public*/ void TriStateJCheckBox::setState(QVector<bool> booleanArray){
        if (arrayDoesNotContainsTrueOrFalse(booleanArray,true)){
            ((TriStateModel*) model)->setState(State::UNCHECKED);
        } else if (arrayDoesNotContainsTrueOrFalse(booleanArray,false)){
            ((TriStateModel*) model)->setState(State::CHECKED);
        } else {
            ((TriStateModel*) model)->setState(State::PARTIAL);
        }
    }

    /*private*/ bool TriStateJCheckBox::arrayDoesNotContainsTrueOrFalse(QVector<bool> booleanArray, bool condition){
        for(bool value: booleanArray){
            if ( value == condition ) {
                return false;
            }
        }
        return true;
    }

    /**
     * Return the current state, which is determined by the selection status of
     * the model.
     * @return enum of current state.
     */
    //@Nonnull
    /*public*/ TriStateJCheckBox::State TriStateJCheckBox::getState() {
        return ((TriStateModel*) model)->getState();
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void TriStateJCheckBox::setSelected(bool selected) {
        ((TriStateModel*) model)->setSelected(selected);
    }

    #if 1
    void TriStateJCheckBox::paintEvent(QPaintEvent* evt)
    {
     QCheckBox::paintEvent(evt);
     QPainter g(this);
     QRect rect = evt->rect();
     paintIcon(this, g, rect.x(), rect.y());
    }

    /*private*/ /*final*/ /*static*/ QIcon TriStateJCheckBox::icon = QIcon();//UIManager.getIcon("CheckBox.icon");

    /**
     * Paint the Icon dependant on state, special handling for Nimbus LAF.
     * {@inheritDoc}
     */
//    @SuppressWarnings("unchecked")
//    @Override
    /*public*/ void TriStateJCheckBox::paintIcon(QWidget* c, QPainter& g, int x, int y) {
//        String laf = UIManager.getLookAndFeel().getName();
//        log.debug("laf is: {}",laf);
//        if ("Nimbus".equals(laf)){

//            // Nimbus handled differently in that no .icon is available.
//            // There may well be a better way of doing this?

//            Painter<JComponent> painter;
//            if (getState() == TriStateJCheckBox.State.CHECKED){
//                painter = (Painter)UIManager.get("CheckBox[Selected].iconPainter");
//            } else {
//                painter = (Painter)UIManager.get("CheckBox[Enabled].iconPainter");
//            }
//            if (painter != null && g instanceof Graphics2D){
//                JComponent jc = (c instanceof JComponent) ? (JComponent)c : null;
//                Graphics2D gfx = (Graphics2D)g;
//                gfx.translate(x, y);
//                painter.paint(gfx, jc , getIconWidth(), getIconHeight());
//                gfx.translate(-x, -y);
//            }

//        } else { // not Nimbus so use Default L&F Icon.
//            icon.paintIcon(c, g, x, y);
//        }

        if ((((TriStateModel*) model)->getState() != TriStateJCheckBox::State::PARTIAL)
            || c == nullptr /*|| g == QPainter()*/){
            return;
        }

        int w = getIconWidth();
        int h = getIconHeight();
        //g.setColor(c.isEnabled() ? new Color(51, 51, 51) : new Color(122, 138, 153));
        g.setBrush(QBrush(c->isEnabled() ? QColor(51, 51, 51) : QColor(122, 138, 153)));
        g.fillRect(x+4, y+4, w-8, h-8, Qt::SolidPattern);

        if (!c->isEnabled()) return;
        //g.setColor(new Color(81, 81, 81));
        g.setBrush(QBrush(QColor(81, 81, 81)));
        g.drawRect(x+4, y+4, w-9, h-9);

    }
#endif
    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ int TriStateJCheckBox::getIconWidth() {
        //return (icon.isNull() ? 16 : icon.getIconWidth());
     return 16;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ int TriStateJCheckBox::getIconHeight() {
        //return (icon.isNull() ? 16 : icon.getIconHeight());
     return 16;
    }

    #if 0
    /**
     * Model for checkbox
     */
    /*private*/ static class TriStateModel extends JToggleButton.ToggleButtonModel {

        protected State state;

        /*public*/ TriStateModel(State state) {
            this.state = state;
        }

        /**
         * {@inheritDoc}
         */
        @Override
        /*public*/ boolean isSelected() {
            return state == State.CHECKED;
        }

        /*public*/ State getState() {
            return state;
        }

        /*public*/ void setState(State state) {
            this.state = state;
            fireStateChanged();
        }

        /**
         * {@inheritDoc}
         */
        @Override
        /*public*/ void setPressed(boolean pressed) {
            if (pressed) {
                state = ( state==State.UNCHECKED ? State.CHECKED : State.UNCHECKED );
                fireStateChanged();
                fireActionPerformed(
                    new ActionEvent(this, ActionEvent.ACTION_PERFORMED,getActionCommand()));
            }
        }

        /**
         * {@inheritDoc}
         */
        @Override
        /*public*/ void setSelected(boolean selected) {
            this.state = ( selected ? State.CHECKED : State.UNCHECKED );
        }
    }
    #endif
    /*private*/ /*final*/ /*static*/ Logger* TriStateJCheckBox::log = LoggerFactory::getLogger("TriStateJCheckBox");
