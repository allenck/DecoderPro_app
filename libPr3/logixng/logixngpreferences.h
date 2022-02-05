#ifndef LOGIXNGPREFERENCES_H
#define LOGIXNGPREFERENCES_H
#include <QtCore>
#include "malesocket.h"

/**
 * Preferences for LogixNG
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class LogixNGPreferences {
 public:
    /**
     * Compare if the values are different from the other preferences.
     * @param prefs the other preferences to check
     * @return true if preferences differ, false otherwise
     */
    /*public*/ virtual bool compareValuesDifferent(LogixNGPreferences* prefs)=0;

    /**
     * Apply other preferences to this class
     * @param prefs the other preferences
     */
    /*public*/ virtual void apply(LogixNGPreferences* prefs)=0;

    /**
     * Save the preferences
     */
    /*public*/ virtual void save()=0;

    /**
     * Set whenether LogixNG should be started when the program starts or a
     * panel is loaded.
     * @param value true if LogixNG should start on program start or when a
     * panel is loaded, false otherwise
     */
    /*public*/ virtual void setStartLogixNGOnStartup(bool value)=0;

    /**
     * Get whenether LogixNG should be started when the program starts or a
     * panel is loaded.
     * @return true if LogixNG should start on program start or when a panel
     * is loaded, false otherwise
     */
    /*public*/ virtual bool getStartLogixNGOnStartup()=0;

    /**
     * Set whenether system names and user names should be visible for actions
     * and expressions.
     * @param value true if names should be visible, false otherwise
     */
    /*public*/ virtual void setShowSystemUserNames(bool value)=0;

    /**
     * Get whenether system names and user names should be visible for actions
     * and expressions.
     * @return true if names should be visible, false otherwise
     */
    /*public*/ virtual bool getShowSystemUserNames()=0;

    /**
     * Set whenether the debugger should be installed or nog.
     * @param value true if the debugger should be installed, false otherwise
     */
    /*public*/ virtual void setInstallDebugger(bool value)=0;

    /**
     * Get whenether the debugger should be installed or nog.
     * @return true if the debugger should be installed, false otherwise
     */
    /*public*/ virtual bool getInstallDebugger()=0;

    /**
     * Set the default error handling type.
     * @param type the error handling type
     */
    /*public*/ virtual void setErrorHandlingType(ErrorHandlingType::TYPES type)=0;

    /**
     * Get the default error handling type.
     * @return the error handling type
     */
    /*public*/ virtual ErrorHandlingType::TYPES getErrorHandlingType()=0;

    /**
     * Set whether row in tree editor should be highlighted or not.
     * @param value true if the row should be highlighted, false not
     */
    /*public*/ virtual void setTreeEditorHighlightRow(bool value)=0;

    /**
     * Get whether row in tree editor should be highlighted or not.
     * @return true if the row should be highlighted, false not
     */
    /*public*/ virtual bool getTreeEditorHighlightRow()=0;

    virtual QObject* self() =0;
};
Q_DECLARE_INTERFACE(LogixNGPreferences, "LogixNGPreferences")
#endif // LOGIXNGPREFERENCES_H
