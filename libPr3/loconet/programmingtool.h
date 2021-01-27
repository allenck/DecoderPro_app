#ifndef PROGRAMMINGTOOL_H
#define PROGRAMMINGTOOL_H
#include "rosterentry.h"

/**
 * An interface to allow for "callback" operations to open a symbolic programmer from connection tools.
 *
 * @author B. Milhaupt Copyright (c) 2020
 */
/*public*/ /*interface*/class ProgrammingTool {
 public:
    /**
     * Open a symbolic programmer for the device in the roster entry.
     *
     * @param re Roster Entry of the device to be programmed
     * @param name name of the device to be programmed
     * @param programmerFile the programmer file
     * @param p the programmer
     */
    /*public*/ virtual void openPaneOpsProgFrame(RosterEntry* re, QString name,
                                     QString programmerFile, Programmer* p) = 0;
};
Q_DECLARE_INTERFACE(ProgrammingTool, "ProgrammingTool")
#endif // PROGRAMMINGTOOL_H
