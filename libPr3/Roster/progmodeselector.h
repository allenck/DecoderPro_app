#ifndef PROGMODESELECTOR_H
#define PROGMODESELECTOR_H

#include "jpanel.h"

class Programmer;
class ProgModeSelector : public JPanel
{
    Q_OBJECT
public:
    explicit ProgModeSelector(QWidget *parent = 0);
    /**
     * Get the configured programmer
     */
    /*abstract*/ /*public*/ virtual Programmer*  getProgrammer();

    /**
     * Does this object have sufficient selection information to
     * provide a programmer?
     * @return true if a programmer is available
     */
    /*abstract*/ /*public*/ virtual bool isSelected();

    /**
     * Enable/Disable the selection aspect of whatever
     * GUI is presented
     * <p>
     * Default behavior is to do nothing.
     * @param enabled false disables GUI user changes
     */
    /*public*/ void setEnabled(bool enabled);

    /**
     * Clean up when done. Required.
     */
    /*abstract*/ /*public*/ virtual void dispose();
signals:

public slots:

};

#endif // PROGMODESELECTOR_H
