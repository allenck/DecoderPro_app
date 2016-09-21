#include "profileutils.h"
#include "profile.h"
#include "auxiliaryconfiguration.h"
#include "jmriuserinterfaceconfigurationprovider.h"
#include "jmriconfigurationprovider.h"

/**
 * Utility methods to get information about {@link jmri.profile.Profile}s.
 *
 * @author Randall Wood 2015
 */
///*public*/ class ProfileUtils {

/**
 * Get the XMl configuration container for a given configuration profile.
 *
 * @param project The configuration profile.
 * @return An XML configuration container, possibly empty.
 */
/*public*/ /*static*/ AuxiliaryConfiguration* ProfileUtils::getAuxiliaryConfiguration(Profile* project) {
    return JmriConfigurationProvider::getConfiguration(project);
}
#if 0
/**
 * Get the preferences needed by a class for a given configuration profile.
 *
 * @param project The configuration profile.
 * @param clazz   The class requesting preferences.
 * @param shared  True if the preferences are for all nodes (computers) this
 *                profile may run on, false if the preferences are only for
 *                this node.
 * @return The preferences.
 */
/*public*/ static Preferences getPreferences(Profile project, QString clazz, bool shared) {
    return JmriPreferencesProvider.getPreferences(project, clazz, shared);
}
#endif
/**
 * Get the XMl configuration container for a given configuration profile's
 * user interface state.
 *
 * @param project The configuration profile.
 * @return An XML configuration container, possibly empty.
 */
/*public*/ /*static*/ AuxiliaryConfiguration* ProfileUtils::getUserInterfaceConfiguration(Profile* project) {
    return JmriUserInterfaceConfigurationProvider::getConfiguration(project);
}
#if 0
/**
 * Copy one profile's configuration to another profile.
 *
 * @param source      The source profile.
 * @param destination The destination profile.
 * @throws IllegalArgumentException If the destination profile is the active
 *                                  profile.
 * @throws IOException              If the copy cannot be completed.
 */
/*public*/ static void copy(Profile source, Profile destination) throws IllegalArgumentException, IOException {
    if (destination.equals(ProfileManager.getDefault().getActiveProfile())) {
        throw new IllegalArgumentException("Target profile cannot be active profile.");
    }
    FileUtil.copy(source.getPath(), destination.getPath());
    File profile = new File(destination.getPath(), Profile.PROFILE);
    File[] files = profile.listFiles((File pathname) -> (pathname.getName().endsWith(source.getUniqueId())));
    if (files != null) {
        for (File file : files) {
            if (!file.renameTo(new File(profile, file.getName().replace(source.getUniqueId(), destination.getUniqueId())))) {
                throw new IOException("Unable to rename " + file + " to use new profile ID");
            }
        }
    }
    destination.save();
}
#endif
