#include "profileutilstest.h"
#include "profile.h"
#include "profilemanager.h"
#include "loggerfactory.h"
#include "temporaryfolder.h"
#include "junitutil.h"
#include "profileutils.h"
#include "assert1.h"

ProfileUtilsTest::ProfileUtilsTest(QObject *parent) : QObject(parent)
{
  folder = new TemporaryFolder();

}
/**
 * Tests for {@link jmri.profile.ProfileUtils} methods.
 *
 * @author Randall Wood
 */
// /*public*/ class ProfileUtilsTest {

    /*private*/ /*static*/ /*final*/ Logger* ProfileUtilsTest::log = LoggerFactory::getLogger("ProfileUtilsTest");

    //@Rule

    //@Before
    /*public*/ void ProfileUtilsTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetProfileManager();
    }

    //@After
    /*public*/ void ProfileUtilsTest::tearDown() {
        JUnitUtil::resetProfileManager();
        JUnitUtil::tearDown();
    }

    //@Test
    /*public*/ void ProfileUtilsTest::testCopy() {
        Profile* source;
        Profile* destination;
        try {
            File* dir = folder->newFolder("source");
            source = new Profile("source", dir->getName(), dir);
            dir = folder->newFolder("dest");
            destination = new Profile("destination", dir->getName(), dir);
        } catch (IOException ex) {
            // skip test if unable to create temporary profiles
            Assert::fail("Unable to create temporary profiles",__FILE__, __LINE__);
            return;
        }
        try {
            ProfileUtils::copy(source, destination);
        } catch (IllegalArgumentException ex) {
            Assert::fail("Unable to copy profiles with IllegalArgumentException.",__FILE__, __LINE__);
            return;
        } catch (IOException ex) {
            log->error("Failure copying profiles", ex);
            Assert::fail("Unable to copy profiles with IOException.",__FILE__, __LINE__);
            return;
        }
        File* profile = new File(destination->getPath(), Profile::PROFILE);
        //if (profile.listFiles((File pathname) -> (pathname.getName().endsWith(source.getUniqueId()))).length > 0) {
        foreach(File* pathname, profile->listFiles())
        {
            if(pathname->getName().endsWith(source->getUniqueId()))
            Assert::fail("Source ID remains in destination profile.",__FILE__, __LINE__);
        }
    }

    //@Test
    /*public*/ void ProfileUtilsTest::testCopyToActive() {
        Profile* source;
        Profile* destination;
        try {
            File* dir = folder->newFolder("source");
            source = new Profile("source", dir->getName(), dir);
            dir = folder->newFolder("dest");
            destination = new Profile("destination", dir->getName(), dir);
            // Should cause copy() to throw IllegalArgumentException
            ProfileManager::getDefault()->setActiveProfile(destination);
        } catch (IOException ex) {
            // skip test if unable to create temporary profiles
            Assert::fail("Unable to create temporary profiles",__FILE__, __LINE__);
            return;
        }
        try {
            // Should throw IllegalArgumentException
            ProfileUtils::copy(source, destination);
        } catch (IllegalArgumentException ex) {
            // This exception is expected and throwing it passes the test
        } catch (IOException ex) {
            log->error("Failure copying profiles", ex);
            Assert::fail("Unable to copy profiles with IOException.",__FILE__, __LINE__);
        }
    }
