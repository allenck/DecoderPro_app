#include "yardmasterbytrackframe.h"
#include "yardmasterbytrackpanel.h"
#include "control.h"
/**
 * Yardmaster by track frame. Shows work at one location listed by track.
 *
 * @author Dan Boudreau Copyright (C) 2015
 *
 */
///*public*/ class YardmasterByTrackFrame extends OperationsFrame {

using namespace Operations;

/*public*/ YardmasterByTrackFrame::YardmasterByTrackFrame(Location* location, QWidget* parent)
 : OperationsFrame(tr("Yardmaster By Track"), /*new YardmasterByTrackPanel(location)*/parent)
{
    //super(Bundle.getMessage("Yardmaster By Track"), new YardmasterByTrackPanel(location));
 setContentPane(new YardmasterByTrackPanel(location,this));
    this->initComponents(location);
}

/*private*/ void YardmasterByTrackFrame::initComponents(Location* location) {
    OperationsFrame::initComponents();

    if (location != NULL) {
        setTitle(tr("Yardmaster By Track") + " (" + location->getName() + ")");
    }

    initMinimumSize(QSize(Control::panelWidth500, Control::panelHeight500));
}
/*public*/ QString YardmasterByTrackFrame::getClassName()
{
 return "jmri.jmrit.operations.locations.YardmasterByTrackFrame";
}
