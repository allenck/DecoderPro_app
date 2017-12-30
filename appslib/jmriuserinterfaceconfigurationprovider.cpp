#include "jmriuserinterfaceconfigurationprovider.h"
#include <QMap>
#include "profile.h"
#include "jmriconfiguration.h"

/**
 * Provides a general purpose XML element storage mechanism for the storage of
 * user interface configuration.
 *
 * There are two configuration files per {@link jmri.profile.Profile} and
 * {@link jmri.util.node.NodeIdentity}, both stored in the directory
 * <code>profile:profile</code>:
 * <ul>
 * <li><code>user-interface.xml</code> preferences that are shared across
 * multiple nodes for a single profile. An example of such a preference would be
 * the Railroad Name preference.</li>
 * <li><code>&lt;node-identity&gt;/user-interface.xml</code> preferences that
 * are specific to the profile running on a specific host (&lt;node-identity&gt;
 * is the identity returned by {@link jmri.util.node.NodeIdentity#identity()}).
 * An example of such a preference would be a file location.</li>
 * </ul>
 *
 * @author Randall Wood 2015, 2016
 */
///*public*/ final class JmriUserInterfaceConfigurationProvider extends AbstractConfigurationProvider {


    /*public*/ /*static*/ /*final*/ QString JmriUserInterfaceConfigurationProvider::NAMESPACE = "http://www.netbeans.org/ns/auxiliary-configuration/1"; // NOI18N
#if 0
    static {
        try {
            DocumentBuilderFactory.newInstance().newDocumentBuilder();
        } catch (ParserConfigurationException e) {
            throw new AssertionError(e);
        }
    }
#endif
    /*private*/ /*static*/ /*final*/ QMap<Profile*, JmriUserInterfaceConfigurationProvider*> JmriUserInterfaceConfigurationProvider::providers = QMap<Profile*, JmriUserInterfaceConfigurationProvider*>();

    /**
     * Get the JmriPrefererncesProvider for the specified profile.
     *
     * @param project The profile. This is most often the profile returned by
     *                the {@link jmri.profile.ProfileManager#getActiveProfile()}
     *                method of the ProfileManager returned by
     *                {@link jmri.profile.ProfileManager#getDefault()}
     * @return The shared or private JmriPreferencesProvider for the project.
     */
    /*static*/ /*synchronized*/ JmriUserInterfaceConfigurationProvider* JmriUserInterfaceConfigurationProvider::findProvider(Profile* project) {
        if (providers.value(project) == NULL) {
            providers.insert(project, new JmriUserInterfaceConfigurationProvider(project));
        }
        return providers.value(project);
    }

    /**
     * Get the {@link java.util.prefs.Preferences} for the specified class in
     * the specified profile.
     *
     * @param project The profile. This is most often the profile returned by
     *                the {@link jmri.profile.ProfileManager#getActiveProfile()}
     *                method of the ProfileManager returned by
     *                {@link jmri.profile.ProfileManager#getDefault()}
     * @return The shared or private AuxiliaryConfiguration for project.
     */
    /*public*/ /*static*/ AuxiliaryConfiguration* JmriUserInterfaceConfigurationProvider::getConfiguration(/*final*/ Profile* project) {
        return findProvider(project)->getConfiguration();
    }

    /**
     * Get the {@link jmri.profile.AuxiliaryConfiguration}.
     *
     * @return The AuxiliaryConfiguration.
     */
    //@Override
    /*protected*/ AuxiliaryConfiguration* JmriUserInterfaceConfigurationProvider::getConfiguration() {
        return this->configuration;
    }

    //@Override
    /*protected*/ File* JmriUserInterfaceConfigurationProvider::getConfigurationFile(bool shared) {
        if (this->project == NULL) {
            return new File(this->getConfigurationDirectory(shared), /*Profile::UI_CONFIG*/"user-interface.xml"); // NOI18N
        } else {
            return new File(this->getConfigurationDirectory(shared), /*Profile::UI_CONFIG*/"user-interface.xml"); // NOI18N
        }
    }

    JmriUserInterfaceConfigurationProvider::JmriUserInterfaceConfigurationProvider(Profile* project)
     : AbstractConfigurationProvider(project)
    {
        //super(project);
        this->configuration = new Configuration(this);
    }

    ///*private*/ class Configuration : public JmriConfiguration {

        /*private*/ JmriUserInterfaceConfigurationProvider::Configuration::Configuration(JmriUserInterfaceConfigurationProvider* provider) : JmriConfiguration(){
            //super();
      this->provider = provider;
        }

        //@Override
        /*protected*/ File* JmriUserInterfaceConfigurationProvider::Configuration::getConfigurationFile(bool shared) {
            return provider->getConfigurationFile(shared);
        }

        //@Override
        /*protected*/ bool JmriUserInterfaceConfigurationProvider::Configuration::isSharedBackedUp() {
            return provider->isSharedBackedUp();
        }

        //@Override
        /*protected*/ void JmriUserInterfaceConfigurationProvider::Configuration::setSharedBackedUp(bool backedUp) {
            provider->setSharedBackedUp(backedUp);
        }

        //@Override
        /*protected*/ bool JmriUserInterfaceConfigurationProvider::Configuration::isPrivateBackedUp() {
            return provider->isPrivateBackedUp();
        }

        //@Override
        /*protected*/ void JmriUserInterfaceConfigurationProvider::Configuration::setPrivateBackedUp(bool backedUp) {
            provider->setPrivateBackedUp(backedUp);
        }

    //}
