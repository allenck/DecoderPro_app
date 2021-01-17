#ifndef ABSTRACTLIGHTMANAGER_H
#define ABSTRACTLIGHTMANAGER_H
#include "lightmanager.h"
#include "light.h"
#include "exceptions.h"
#include "abstractlight.h"

class SystemConnectionMemo;
class LIBPR3SHARED_EXPORT AbstractLightManager : public  LightManager
{
    Q_OBJECT
public:
    //explicit AbstractLightManager(QObject *parent = 0);
 /*public*/ AbstractLightManager(SystemConnectionMemo* memo, QObject *parent = 0);
    /*public*/ virtual int getXMLOrder() const override;
    /*public*/ virtual char typeLetter() const override;
    /**
     * Locate via user name, then system name if needed.
     * If that fails, create a new Light: If the name
     * is a valid system name, it will be used for the new
     * Light.  Otherwise, the makeSystemName method
     * will attempt to turn it into a valid system name.
     *
     * @param name
     * @return Never null unless valid systemName cannot
     *     be found
     */
    /*public*/ Light* provideLight(QString name) override;
    /**
     * Locate via user name, then system name if needed.
     * Does not create a new one if nothing found
     *
     * @param name
     * @return null if no match found
     */
    /*public*/ Light* getLight(QString name) override;
#if 1
    /**
     * Locate a Light by its system name
     */
    /*public*/ Light* getBySystemName(QString name)const;
    /**
     * Locate a Light by its user name
     */
    /*public*/ Light* getByUserName(QString key) const;
#endif
    /**
     * Return an instance with the specified system and user names.
     * Note that two calls with the same arguments will get the same instance;
     * there is only one Light object representing a given physical Light
     * and therefore only one with a specific system or user name.
     *<P>
     * This will always return a valid object reference; a new object will be
     * created if necessary. In that case:
     *<UL>
     *<LI>If a NULL reference is given for user name, no user name will be associated
     *    with the Light object created; a valid system name must be provided
     *<LI>If both names are provided, the system name defines the
     *    hardware access of the desired sensor, and the user address
     *    is associated with it. The system name must be valid.
     *</UL>
     * Note that it is possible to make an inconsistent request if both
     * addresses are provided, but the given values are associated with
     * different objects.  This is a problem, and we don't have a
     * good solution except to issue warnings.
     * This will mostly happen if you're creating Lights when you should
     * be looking them up.
     * @return requested Light object (never NULL)
     */
    /*public*/ Light* newLight(QString systemName, QString userName) override;
    /**
     * Activate the control mechanism for each Light controlled by
     *    this LightManager.  Note that some Lights don't require
     *    any activation.  The activateLight method in AbstractLight.java
     *    determines what needs to be done for each Light.
     */
    /*public*/ void activateAllLights() override;
    /**
     * Normalize the system name
     * <P>
     * This routine is used to ensure that each system name is uniquely linked to
     *      one C/MRI bit, by removing extra zeros inserted by the user.
     * <P>
     * If a system implementation has names that could be normalized, the
     *      system-specific Light Manager should override this routine and supply
     *      a normalized system name.
     */
    /*public*/ QString normalizeSystemName(QString systemName) override;
    /**
     * Convert the system name to a normalized alternate name
     * <P>
     * This routine is to allow testing to ensure that two Lights with
     *      alternate names that refer to the same output bit are not
     *      created.
     * <P>
     * If a system implementation has alternate names, the system specific
     *      Light Manager should override this routine and supply the alternate
     *      name.
     */
    /*public*/ QString convertSystemNameToAlternate(QString systemName) override;
    /**
     * Returns 'true' if the System can potentially support variable Lights
     *    Note: LightManagers for Systems that can support variable Lights should
     *         override this method and return 'true'.
     */
    /*public*/ bool supportsVariableLights(QString systemName) override;
    /**
    * A method that determines if it is possible to add a range of lights in numerical
    * order eg 11 thru 18, primarily used to show/not show the add range box in the add Light window
    **/
    /*public*/ bool allowMultipleAdditions(QString systemName) override;
    /*public*/ QString getBeanTypeHandled(bool plural)const override;
    /*public*/ QString getEntryToolTip() override;


signals:
 void newLightCreated(AbstractLightManager*,Light*);

public slots:
private:
    Logger* log;
protected:
    /**
     * Internal method to invoke the factory, after all the
     * logic for returning an existing method has been invoked.
     * @return new NULL
     */
    /*abstract protected*/ virtual Light* createNewLight(QString /*systemName*/, QString /*userName*/) { return NULL;}

};

#endif // ABSTRACTLIGHTMANAGER_H
