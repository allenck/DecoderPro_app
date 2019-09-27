#include "profiletest.h"
#include "assert1.h"
#include "temporaryfolder.h"
#include "profile.h"
#include "fileutil.h"
#include "junitutil.h"
#include "profileproperties.h"

ProfileTest::ProfileTest(QObject *parent) : QObject(parent)
{
 folder = new TemporaryFolder();
}

/**
 *
 * @author Randall Wood
 */
///*public*/ class ProfileTest {


//@BeforeClass
/*public*/ /*static*/ void ProfileTest::setUpClass() {
 JUnitUtil::setUp();
}

//@AfterClass
/*public*/ /*static*/ void ProfileTest::tearDownClass() {
 JUnitUtil::tearDown();
}

//@Before
/*public*/ void ProfileTest::setUp() {
}

//@After
/*public*/ void ProfileTest::tearDown() {
}

//@Test
/*public*/ void ProfileTest::testProfileWithExtension() {
 try
 {
    File* profileFolder = new File(folder->newFolder(Profile::PROFILE), "test" + Profile::EXTENSION);
    Profile* instance = new Profile("test", "test", profileFolder);
    Assert::assertEquals("Name has no extension", "test", instance->getName());
    Assert::assertEquals("Path name has extension", "test" + Profile::EXTENSION, instance->getPath()->getName(),__FILE__, __LINE__);
 }
 catch (IOException  ex) {
    Assert::fail(ex.getMessage(),__FILE__, __LINE__);
 }
 catch ( IllegalArgumentException ex) {
        Assert::fail(ex.getMessage(), __FILE__, __LINE__);
 }
}

/**
* Test of save method, of class Profile::
*
* @throws java.io.IOException on any unanticipated errors setting up test
*/
//@Test
/*public*/ void ProfileTest::testSave() throw (IOException) {
    File* profileFolder = new File(folder->newFolder(Profile::PROFILE), "test");
    Profile* instance = new Profile("test", "test", profileFolder);
    instance->setName("saved");
    instance->save();
    Assert::assertEquals("saved", (new ProfileProperties(instance->getPath()))->get(Profile::NAME, true));
}

/**
* Test of getName method, of class Profile::
*/
//@Test
/*public*/ void ProfileTest::testGetName() {
    try {
        File* profileFolder = new File(folder->newFolder(Profile::PROFILE), "test");
        Profile* instance = new Profile("test", "test", profileFolder);
        Assert::assertEquals("test", instance->getName());
    } catch (IOException  ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }
    catch (IOException  ex) {
            Assert::fail(ex.toString(),__FILE__, __LINE__);
        }
}

/**
* Test of setName method, of class Profile::
*/
//@Test
/*public*/ void ProfileTest::testSetName() {
try {
    File* profileFolder = new File(folder->newFolder(Profile::PROFILE), "test");
    Profile* instance = new Profile("test", "test", profileFolder);
    instance->setName("changed");
    Assert::assertEquals("changed", instance->getName());
    } catch (IOException ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }
    catch ( IllegalArgumentException ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }}

/**
* Test of getId method, of class Profile::
*/
//@Test
/*public*/ void ProfileTest::testGetId() {
try {
        File* profileFolder = new File(folder->newFolder(Profile::PROFILE), "test");
        Profile* instance = new Profile("test", "test", profileFolder);
        QString id = (new ProfileProperties(instance->getPath()))->get(Profile::ID, true);
        Assert::assertEquals(id, instance->getId());
    } catch (IOException  ex) {
    Assert::fail(ex.toString(),__FILE__, __LINE__);
    }
    catch ( IllegalArgumentException ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }
}

/**
* Test of getPath method, of class Profile::
*/
//@Test
/*public*/ void ProfileTest::testGetPath() {
try {
        File* profileFolder = new File(folder->newFolder(Profile::PROFILE), "test");
        File* profileExtFolder = new File(profileFolder->getParentFile(), "test" + Profile::EXTENSION);
        Profile* instance = new Profile("test", "test", profileFolder);
        Assert::assertNotEquals(profileFolder, instance->getPath());
        Assert::assertEquals(profileExtFolder, instance->getPath());
    } catch (IOException  ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }
    catch (IllegalArgumentException ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }
}

/**
* Test of toString method, of class Profile::
*/
//@Test
/*public*/ void ProfileTest::testToString() {
try {
    File* profileFolder = new File(folder->newFolder(Profile::PROFILE), "test");
    Profile* instance = new Profile("test", "test", profileFolder);
    Assert::assertEquals(instance->getName(), instance->toString());
    } catch (IOException  ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }
    catch ( IllegalArgumentException ex) {
            Assert::fail(ex.toString(),__FILE__, __LINE__);
        }
}

/**
* Test of hashCode method, of class Profile::
*/
//@Test
/*public*/ void ProfileTest::testHashCode() {
try {
    File* profileFolder = new File(folder->newFolder(Profile::PROFILE), "test" + Profile::EXTENSION);
    Profile* instance = new Profile("test", "test", profileFolder);
    QString id = (new ProfileProperties(profileFolder))->get(Profile::ID, true);
//    Assert::assertEquals(71 * 7 + id.hashCode(), instance.hashCode());
    } catch (IOException  ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }
    catch ( IllegalArgumentException ex) {
            Assert::fail(ex.toString(),__FILE__, __LINE__);
        }
}

/**
* Test of equals method, of class Profile::
*/
//@Test
//@SuppressWarnings("unlikely-arg-type") // String seems to be unrelated to Profile
/*public*/ void ProfileTest::testEquals() {
try {
    File* rootFolder = folder->newFolder(Profile::PROFILE);
    File* profileFolder = new File(rootFolder, "test");
    File* profileFolder2 = new File(rootFolder, "test2");
    File* profileFolder3 = new File(rootFolder, "test3");
    Profile* instance = new Profile("test", "test", profileFolder);
    Profile* instance2 = new Profile("test", "test2", profileFolder2);
    FileUtil::copy(instance->getPath(), profileFolder3);
    Profile* instance3 = new Profile(profileFolder3);
    Assert::assertFalse(instance ==(nullptr));
//    Assert::assertFalse(instance ==(QString()));
    Assert::assertFalse(instance ==(instance2));
    Assert::assertTrue(instance ==(instance3));
} catch (IOException  ex) {
    Assert::fail(ex.toString(),__FILE__, __LINE__);
}
    catch (IllegalArgumentException ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }
}

/**
* Test of isComplete method, of class Profile::
*/
//@Test
/*public*/ void ProfileTest::testIsComplete() {
try {
    File* profileFolder = new File(folder->newFolder(Profile::PROFILE), "test");
    Profile* instance = new Profile("test", "test", profileFolder);
    Assert::assertTrue(instance->isComplete());
    } catch (IOException ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }
    catch (IOException  ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }
}

/**
* Test of getUniqueId method, of class Profile::
*/
//@Test
/*public*/ void ProfileTest::testGetUniqueId() {
try {
    File* profileFolder = new File(folder->newFolder(Profile::PROFILE), "test" + Profile::EXTENSION);
    Profile* instance = new Profile("test", "test", profileFolder);
    QString id = (new ProfileProperties(profileFolder))->get(Profile::ID, true);
    id = id.mid(id.lastIndexOf(".") + 1);
    Assert::assertEquals(id, instance->getUniqueId());
    } catch (IOException  ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }
    catch (IllegalArgumentException ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }}

/**
* Test of containsProfile method, of class Profile::
*/
//@Test
/*public*/ void ProfileTest::testContainsProfile() {
try {
    File* rootFolder = folder->newFolder(Profile::PROFILE);
    File* profileFolder = new File(rootFolder, "test");
    File* rootFolder2 = folder->newFolder(Profile::PATH);
    (new File(rootFolder2, "test2"))->mkdirs();
    new Profile("test", "test", profileFolder);
    Assert::assertTrue(Profile::containsProfile(rootFolder));
    Assert::assertFalse(Profile::containsProfile(rootFolder2));
} catch (IOException ex) {
    Assert::fail(ex.toString(),__FILE__, __LINE__);
}
    catch (IllegalArgumentException ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }
}

/**
* Test of inProfile method, of class Profile::
*/
//@Test
/*public*/ void ProfileTest::testInProfile() {
try {
    File* rootFolder = folder->newFolder(Profile::PROFILE);
    File* profileFolder = new File(rootFolder, "test" + Profile::EXTENSION);
    File* innerFolder = new File(profileFolder, "test");
    innerFolder->mkdirs();
    File* rootFolder2 = folder->newFolder(Profile::PATH);
    new Profile("test", "test", profileFolder);
    Assert::assertTrue(Profile::inProfile(innerFolder));
    Assert::assertFalse(Profile::inProfile(rootFolder2));
    } catch (IOException ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }
    catch (IllegalArgumentException ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }
}

/**
* Test of isProfile method, of class Profile::
*/
//@Test
/*public*/ void ProfileTest::testIsProfile() {
try {
    File* rootFolder = folder->newFolder(Profile::PROFILE);
    File* profileFolder = new File(rootFolder, "test" + Profile::EXTENSION);
    new Profile("test", "test", profileFolder);
    File* innerFolder = new File(profileFolder, "test");
    innerFolder->mkdirs();
    Assert::assertTrue(Profile::isProfile(profileFolder));
    Assert::assertFalse(Profile::isProfile(rootFolder));
    Assert::assertFalse(Profile::isProfile(innerFolder));
    } catch (IOException ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }
    catch (IllegalArgumentException ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }
}

/**
* Test of compareTo method, of class Profile::
*/
//@Test
/*public*/ void ProfileTest::testCompareTo() {
try {
    File* rootFolder = folder->newFolder(Profile::PROFILE);
    File* profileFolder = new File(rootFolder, "test");
    File* profileFolder2 = new File(rootFolder, "test2");
    File* profileFolder3 = new File(rootFolder, "test3");
    Profile* instance = new Profile("test", "test", profileFolder);
    Profile* instance2 = new Profile("test", "test2", profileFolder2);
    FileUtil::copy(instance->getPath(), profileFolder3);
    Profile* instance3 = new Profile(profileFolder3);
    // the contract for .compareTo is to return <= -1, 0, >= 1
    Assert::assertTrue(-1 >= instance->compareTo(instance2));
    Assert::assertEquals(0, instance->compareTo(instance3));
    Assert::assertTrue(1 <= instance2->compareTo(instance));
    } catch (IOException ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }
    catch (IllegalArgumentException ex) {
        Assert::fail(ex.toString(),__FILE__, __LINE__);
    }
}
