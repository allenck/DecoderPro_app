#ifndef PANECONTAINER_H
#define PANECONTAINER_H

#include "busyglasspane.h"
#include <QAbstractButton>
#include <QObject>
#include "jtogglebutton.h"
/**
 * Interface for the container of a set of PaneProgPanes.
 * The panes use services provided here to
 * work with buttons and the busy cursor.
 *
 * @author    Bob Jacobsen Copyright (C) 2010
 */
/*public*/ /*interface*/ class LIBPR3SHARED_EXPORT PaneContainer //: public QObject
{
    //Q_OBJECT
public:
    /*public*/ virtual bool isBusy() {return false;}

    /*public*/ virtual void paneFinished() {}

    /**
     * Enable the read/write buttons.
     * <p>
     * In addition, if a programming mode pane is
     * present, it's "set" button is enabled.
     *
     * @param enable Are reads possible? If false, so not enable
     * the read buttons.
     */
    /*public*/ virtual void enableButtons(bool /*enable*/) {}

    /*public*/ virtual void prepGlassPane(JToggleButton* /*activeButton*/) {}

    /*public*/ virtual BusyGlassPane* getBusyGlassPane() {return NULL;}
    friend class PaneProgPane;
    friend class ThisProgPane;
};
Q_DECLARE_INTERFACE(PaneContainer, "PaneContainer")
#endif // PANECONTAINER_H
