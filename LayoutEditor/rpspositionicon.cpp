#include "rpspositionicon.h"
#include "distributor.h"
#include "namedicon.h"
#include "helputil.h"
#include "joptionpane.h"
/**
 * An icon to display the position of an RPS input.
 *
 * In this initial version, it ignores the ID, so there's only one icon.
 *
 * @author Bob Jacobsen Copyright (C) 2007
 */
///*public*/ class RpsPositionIcon extends PositionableLabel implements MeasurementListener {

    /*public*/ RpsPositionIcon::RpsPositionIcon(Editor* editor) : PositionableLabel(new NamedIcon(":/resources/icons/smallschematics/tracksegments/circuit-error.gif",
                                                                                 "resources/icons/smallschematics/tracksegments/circuit-error.gif"), editor){
        // super ctor call to make sure this is an icon label
//        super(new NamedIcon("resources/icons/smallschematics/tracksegments/circuit-error.gif",
//                "resources/icons/smallschematics/tracksegments/circuit-error.gif"), editor);
 // display icon for a correct reading
 activeName = ":/resources/icons/smallschematics/tracksegments/circuit-occupied.gif";
 active = new NamedIcon(activeName, activeName);

 // display icon if the last reading not OK
 errorName = ":/resources/icons/smallschematics/tracksegments/circuit-error.gif";
 error = new NamedIcon(errorName, errorName);

        _control = true;
#if 1
        displayState();

        // blow up default font
        //setFont(jmri.util.FontUtil.deriveFont(getFont(), (float) 24.));
        QFont f = font();
        f.setPointSize(24);
        setFont(f);

        // connect
        Distributor::instance()->addMeasurementListener((MeasurementListener*)this);
#endif
    }


    /*public*/ NamedIcon* RpsPositionIcon::getActiveIcon() {
        return active;
    }

    /*public*/ void RpsPositionIcon::setActiveIcon(NamedIcon* i) {
        active = i;
        displayState();
    }

    /*public*/ NamedIcon* RpsPositionIcon::getErrorIcon() {
        return error;
    }

    /*public*/ void RpsPositionIcon::setErrorIcon(NamedIcon* i) {
        error = i;
        displayState();
    }
#if 1
    //@Override
    /*public*/ QString RpsPositionIcon::getNameString() {
        return "RPS Position Readout";
    }

    //@Override
    /*public*/ bool RpsPositionIcon::setEditIconMenu(QMenu* popup) {
        return false;
    }

    /**
     * Pop-up contents
     */
    //@Override
    /*public*/ bool RpsPositionIcon::showPopUp(QMenu* popup) {

        if (showIdItem == nullptr) {
            showIdItem = new QAction("Show ID",this);
            showIdItem->setCheckable(true);
            showIdItem->setChecked(false);
//            showIdItem.addActionListener(new ActionListener() {
//                //@Override
//                /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
            connect(showIdItem, &QAction::toggled, [=]{
                    toggleID(showIdItem->isChecked());
//                }
            });
        }
        popup->addAction(showIdItem);

        AbstractAction* act;
        popup->addAction(act = new AbstractAction("Set Origin", this));
//        {
//            //@Override
//            /*public*/ void actionPerformed(ActionEvent e) {
          connect(act, &AbstractAction::triggered, [=]{
                setRpsOrigin();
//            }
        });

        popup->addAction(act = new AbstractAction("Set Current Location", this));
//        {
//            //@Override
//              /*public*/ void actionPerformed(ActionEvent e) {
          connect(act, &AbstractAction::triggered, [=]{
                setRpsCurrentLocation();
//            }
        });

        _notify = new Notifier(this);
        popup->addAction(_notify);

        popup->addAction(act = new AbstractAction("Set Filter", this));
//        {
          connect(act, &AbstractAction::triggered, [=]{
                setFilterPopup();
//            }
        });

        // add help item
        QAction* item = new QAction("Help", this);
//        HelpUtil::addHelpToComponent(item, "package.jmri.jmrit.display.RpsIcon");
        connect(item, &QAction::triggered, [=]{
         HelpUtil::displayHelpRef("package.jmri.jmrit.display.RpsIcon");
        });
        popup->addAction(item);

        // update position
        _notify->setPosition(getX(), getY());
        return false;
    }

    /**
     * ****** popup AbstractAction.actionPerformed method overrides ********
     */
    //@Override
    /*protected*/ void RpsPositionIcon::rotateOrthogonal() {
        active->setRotation(active->getRotation() + 1, this);
        error->setRotation(error->getRotation() + 1, this);
        displayState();
        //bug fix, must repaint icons that have same width and height
        repaint();
    }

    //@Override
    /*public*/ void RpsPositionIcon::setScale(double s) {
        active->scale(s, this);
        error->scale(s, this);
        displayState();
    }

    //@Override
    /*public*/ void RpsPositionIcon::rotate(int deg) {
        active->rotate(deg, this);
        error->rotate(deg, this);
        displayState();
    }

    /**
     * Internal class to show position in the popup menu.
     * <P>
     * This is updated before the menu is shown, and then appears in the menu.
     */
//    class Notifier extends AbstractAction {

        /*public*/ Notifier::Notifier(RpsPositionIcon* icon) {
            //super();
         this->icon = icon;
        }

        /**
         * Does nothing, here to make this work
         */
        //@Override
        /*>(c) !=NULL)*/ void Notifier::actionPerformed(/*ActionEvent e*/) {
        }

        /**
         *
         * @param x display coordinate
         * @param y display coordinate
         */
        void Notifier::setPosition(int x, int y) {
            // convert to RPS coordinates
            double epsilon = .00001;
            if ((icon->sxScale > -epsilon && icon->sxScale < epsilon)
                    || (icon->syScale > -epsilon && icon->syScale < epsilon)) {
                putValue("Name", "Not Calibrated");
                return;
            }

            double xn = (x - icon->sxOrigin) / icon->sxScale;
            double yn = (y - icon->syOrigin) / icon->syScale;

            putValue("Name", "At: " + QString::number(xn) + "," + QString::number(yn));
        }
//    }

#endif
    /**
     * Drive the current state of the display from whether a valid measurement
     * has been received
     */
    void RpsPositionIcon::displayState() {

        if (state) {
            if (isIcon()) {
                PositionableLabel::setIcon(active);
            }
        } else {
            if (isIcon()) {
                PositionableLabel::setIcon(error);
            }
        }

        updateSize();
        update();
        return;
    }
#if 1
    //@Override
    /*public*/ int RpsPositionIcon::maxHeight() {
        return getPreferredSize().height();
    }

    //@Override
    /*public*/ int RpsPositionIcon::maxWidth() {
        return getPreferredSize().width();
    }

    /*public*/ bool RpsPositionIcon::getMomentary() {
        return momentary;
    }

    /*public*/ void RpsPositionIcon::setMomentary(bool m) {
        momentary = m;
    }

    void RpsPositionIcon::toggleID(bool value) {
        if (value) {
            _text = true;
        } else {

            _text = false;
            setText("");
        }
        displayState();
    }

    /*public*/ bool RpsPositionIcon::isShowID() {
        return _text;
    }

    /*public*/ void RpsPositionIcon::setShowID(bool mode) {
        _text = mode;
        displayState();
    }

    /**
     * Respond to a measurement by moving to new position
     */
    //@Override
    /*public*/ void RpsPositionIcon::notify(Measurement* m) {
        // only honor measurements to this icon if filtered
        if (filterNumber != nullptr && m->getReading() != nullptr
                && filterNumber != (m->getReading()->getID())) {
            return;
        }

        // remember this measurement for last position, e.g. for
        // alignment
        lastMeasurement = m;

        // update state based on if valid measurement, fiducial volume
        if (!m->isOkPoint() || m->getZ() < -20 || m->getZ() > 20) {
            state = false;
        } else {
            state = true;
        }

        if (_text) {
            PositionableLabel::setText(m->getReading()->getID());
        }
        displayState();

        // if the state is bad, leave icon in last position
        if (!state) {
            return;
        }

        // Do a 2D, no-rotation conversion using the saved constants.
        // xn, yn are the RPS coordinates; x, y are the display coordinates.
        double xn = m->getX();
        double yn = m->getY();

        int x = sxOrigin + (int) (sxScale * xn);
        int y = syOrigin + (int) (syScale * yn);

        // and set position
        setLocation(x, y);
    }

    /*public*/ void RpsPositionIcon::setFilterPopup() {
        // Popup menu has trigger request for filter value
        QString inputValue = JOptionPane::showInputDialog("Please enter a filter value");
        if (inputValue == "") {
            return; // cancelled
        }
        setFilter(inputValue);
    }

    /*public*/ void RpsPositionIcon::setFilter(QString val) {
        filterNumber = val;
    }

    /*public*/ QString RpsPositionIcon::getFilter() {
        return filterNumber;
    }

    //@Override
    /*public*/ void RpsPositionIcon::dispose() {
        Distributor::instance()->removeMeasurementListener((MeasurementListener*)this);
        active = nullptr;
        error = nullptr;

        PositionableLabel::dispose();
    }

    /**
     * Set the current icon position as the origin (0,0) of the RPS space.
     */
    /*public*/ void RpsPositionIcon::setRpsOrigin() {
        sxOrigin = getX();
        syOrigin = getY();
    }

    /*public*/ double RpsPositionIcon::getXScale() {
        return sxScale;
    }

    /*public*/ double RpsPositionIcon::getYScale() {
        return syScale;
    }

    /*public*/ int RpsPositionIcon::getXOrigin() {
        return sxOrigin;
    }

    /*public*/ int RpsPositionIcon::getYOrigin() {
        return syOrigin;
    }

    /*public*/ void RpsPositionIcon::setTransform(double sxScale, double syScale, int sxOrigin, int syOrigin) {
        this->sxScale = sxScale;
        this->syScale = syScale;
        this->sxOrigin = sxOrigin;
        this->syOrigin = syOrigin;
    }

    /**
     * Matches the icon position on the screen to it's position in the RPS
     * coordinate system.
     * <P>
     * Typically invoked from the popup menu, you move the icon (e.g. via drag
     * and drop) to the correct position on the screen for it's current measured
     * position, and then invoke this method.
     * <P>
     * Requires the origin to have been set, and some other measurement to have
     * been made (and current).
     */
    /*public*/ void RpsPositionIcon::setRpsCurrentLocation() {
        if (lastMeasurement == nullptr) {
            return;
        }

        if (sxOrigin == getX()) {
            return;
        }
        if (syOrigin == getY()) {
            return;
        }
        // if (lastMeasurement.getX()<10. && lastMeasurement.getX()>-10) return;
        // if (lastMeasurement.getY()<10. && lastMeasurement.getY()>-10) return;

        sxScale = (getX() - sxOrigin) / lastMeasurement->getX();
        syScale = (getY() - syOrigin) / lastMeasurement->getY();
    }
#endif
