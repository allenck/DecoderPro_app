#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "properties.h"
#include <uidefaults.h>
#include "swingpropertychangesupport.h"

class LookAndFeelInfo;
class LookAndFeel;
class LAFState;
class MultiUIDefaults;
class UIManager : public QObject
{
    Q_OBJECT
public:
    explicit UIManager(QObject *parent = nullptr);
    /*public*/ static UIDefaults* getDefaults();

signals:

private:
#if 0
    /*private*/ static void maybeInitialize();
    /*private*/ static LAFState* getLAFState();
    /**
     * This class defines the state managed by the <code>UIManager</code>.  For
     * Swing applications the fields in this class could just as well
     * be static members of <code>UIManager</code> however we give them
     * "AppContext"
     * scope instead so that applets (and potentially multiple lightweight
     * applications running in a single VM) have their own state. For example,
     * an applet can alter its look and feel, see <code>setLookAndFeel</code>.
     * Doing so has no affect on other applets (or the browser).
     */
    /*private*/ /*static*/ class LAFState
    {
        Properties* swingProps;
        /*private*/ QVector<UIDefaults*> tables = QVector<UIDefaults*>(2);

        bool initialized = false;
        bool focusPolicyInitialized = false;
        MultiUIDefaults* multiUIDefaults = new MultiUIDefaults(tables);
        LookAndFeel* lookAndFeel;
        LookAndFeel* multiLookAndFeel = nullptr;
        QVector<LookAndFeel*>* auxLookAndFeels = nullptr;
        SwingPropertyChangeSupport* changeSupport;

        QVector<LookAndFeelInfo*>* installedLAFs;

        UIDefaults* getLookAndFeelDefaults() { return tables[0]; }
        void setLookAndFeelDefaults(UIDefaults x) { tables[0] = x; }

        UIDefaults* getSystemDefaults() { return tables[1]; }
        void setSystemDefaults(UIDefaults x) { tables[1] = x; }

        /**
         * Returns the SwingPropertyChangeSupport for the current
         * AppContext.  If <code>create</code> is a true, a non-null
         * <code>SwingPropertyChangeSupport</code> will be returned, if
         * <code>create</code> is false and this has not been invoked
         * with true, null will be returned.
         */
    /*public*/ /*synchronized*/ SwingPropertyChangeSupport*
        getPropertyChangeSupport(bool create) {
            if (create && changeSupport == nullptr) {
                changeSupport = new SwingPropertyChangeSupport(
                    "UIManager");
            }
            return changeSupport;
        }
    };
#endif
    UIDefaults* defaults = new UIDefaults();
};

#endif // UIMANAGER_H
