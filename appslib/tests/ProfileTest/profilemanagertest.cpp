#include "profilemanagertest.h"
#include "junitutil.h"
#include "profile.h"
#include "assert1.h"
#include "temporaryfolder.h"
#include "profilemanager.h"
#include "fileutil.h"
#include "nullprofile.h"

ProfileManagerTest::ProfileManagerTest(QObject *parent) : QObject(parent)
{
  folder = new TemporaryFolder();
}

/**
 *
 * @author Paul Bender Copyright (C) 2017
 * @author Randall Wood Copyright (C) 2017
 */
// /*public*/ class ProfileManagerTest {


//@Test
/*public*/ void ProfileManagerTest::testCTor() {
    ProfileManager* pm = new ProfileManager();
    Assert::assertNotNull("exists", pm);
}

//@Test
/*public*/ void ProfileManagerTest::testSetActiveProfile_Profile() throw (IOException) {
    ProfileManager* pm = new ProfileManager();
    // null profile
    pm->setActiveProfile(nullptr);
    Assert::assertNull(pm->getActiveProfile());
    // non-null profile
    File* profileFolder = new File(folder->newFolder(Profile::PROFILE), "test");
    NullProfile* p = new NullProfile("test", "test", profileFolder);
    Assert::assertNotNull(p);
    pm->setActiveProfile(p);
    Assert::assertEquals(p, pm->getActiveProfile());
}

//@Test
/*public*/ void ProfileManagerTest::testSetActiveProfile_String() throw (IOException) {
    ProfileManager* pm = new ProfileManager();
    // null profile
    pm->setActiveProfile("");
    Assert::assertNull(pm->getActiveProfile());
    // non-existant profile
    pm->setActiveProfile("NonExistantId");
    Assert::assertNull(pm->getActiveProfile());
//    JUnitAppender.assertWarnMessage("Unable to set active profile.  No profile with id NonExistantId could be found.");
    // existant non-profile directory (real directory, but no profile)
    QString folderName = folder->newFolder("non-profile")->getAbsolutePath();
    pm->setActiveProfile(folderName);
    Assert::assertNull(pm->getActiveProfile());
//    JUnitAppender.assertErrorMessage(folderName + " is not a profile folder.");
//    JUnitAppender.assertWarnMessage("Unable to set active profile.  No profile with id " + folderName + " could be found.");
    // existant profile directory
    folderName = folder->newFolder("profile")->getAbsolutePath();
    File* profileFolder = new File(folderName);
    QDir::setCurrent(FileUtil::getProgramPath());
    FileUtil::copy(new File("java/test/jmri/profile/samples/ln-simulator"), profileFolder); // where is existing profile?
    pm->setActiveProfile(folderName);
    Profile* p = new Profile(profileFolder);
    Assert::assertNotNull(pm->getActiveProfile());
    Assert::assertEquals(p, pm->getActiveProfile());
}

// The minimal setup for log4J
//@Before
/*public*/ void ProfileManagerTest::setUp() {
    JUnitUtil::setUp();
}

//@After
/*public*/ void ProfileManagerTest::tearDown() {
    JUnitUtil::tearDown();
}

// private final static Logger log = LoggerFactory.getLogger(ProfileManagerTest.class);
