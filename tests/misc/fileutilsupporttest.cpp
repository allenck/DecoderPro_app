#include "fileutilsupporttest.h"
#include "junitutil.h"
#include "assert1.h"
#include "system.h"
#include <QUuid>

FileUtilSupportTest::FileUtilSupportTest(QObject *parent) : QObject(parent)
{

}
/**
 * Tests for the jmri.util.FileUtilSupport class.
 *
 * Most tests use a deliberately non-existent filename since FileUtil appends a
 * / to the end of a portable directory name, and tests could fail if they
 * expect a File* or non-existent filename and a directory exists at that path.
 *
 * @author Bob Jacobsen Copyright 2003, 2009
 * @author Randall Wood Copyright 2016, 2017
 */
///*public*/ class FileUtilSupportTest {


    // tests of internal to external mapping
    // relative File* with no prefix: Leave relative in system-specific form
    //@Test
    /*public*/ void FileUtilSupportTest::testGEFRel() {
        QString name = FileUtilSupportTest::instance->getExternalFilename("resources/non-existant-file-foo");
        Assert::assertEquals("resources" + File::separator + "non-existant-file-foo", name, __FILE__, __LINE__);
    }

    // relative File* with no prefix: Leave relative in system-specific form
    //@Test
    /*public*/ void FileUtilSupportTest::testGEFAbs() {
        File* f = new File("resources/non-existant-file-foo");
        QString name = instance->getExternalFilename(f->getAbsolutePath());
        Assert::assertEquals(f->getAbsolutePath(), name, __FILE__, __LINE__);
    }

    // program: prefix with relative path, convert to relative in system-specific form
    //@Test
    /*public*/ void FileUtilSupportTest::testGEFProgramRel() {
        QString name = instance->getExternalFilename("program:jython");
        Assert::assertEquals((new File("jython"))->getAbsolutePath(), name, __FILE__, __LINE__);
    }

    // program: prefix with absolute path, convert to absolute in system-specific form
    //@Test
    /*public*/ void FileUtilSupportTest::testGEFProgramAbs() {
        File* f = new File("resources/non-existant-file-foo");
        QString name = instance->getExternalFilename("program:" + f->getAbsolutePath());
        Assert::assertEquals(f->getAbsolutePath(), name, __FILE__, __LINE__);
    }

    // preference: prefix with relative path, convert to absolute in system-specific form
    //@Test
    /*public*/ void FileUtilSupportTest::testGEFPrefRel() {
        QString name = instance->getExternalFilename("preference:non-existant-file-foo");
        Assert::assertEquals(instance->getUserFilesPath() + "non-existant-file-foo", name, __FILE__, __LINE__);
    }

    // preference: prefix with absolute path, convert to absolute in system-specific form
    //@Test
    /*public*/ void FileUtilSupportTest::testGEFPrefAbs() {
        File* f = new File("resources/non-existant-file-foo");
        QString name = instance->getExternalFilename("preference:" + f->getAbsolutePath());
        Assert::assertEquals(f->getAbsolutePath(), name, __FILE__, __LINE__);
    }

    // home: prefix with relative path, convert to absolute in system-specific form
    //@Test
    /*public*/ void FileUtilSupportTest::testGEFHomeRel() {
        QString name = instance->getExternalFilename("home:non-existant-file-foo");
        Assert::assertEquals(System::getProperty("user.home") + File::separator + "non-existant-file-foo", name, __FILE__, __LINE__);
    }

    // home: prefix with absolute path, convert to absolute in system-specific form
    //@Test
    /*public*/ void FileUtilSupportTest::testGEFHomeAbs() {
        File* f = new File("resources/non-existant-file-foo");
        QString name = instance->getExternalFilename("home:" + f->getAbsolutePath());
        Assert::assertEquals(f->getAbsolutePath(), name, __FILE__, __LINE__);
    }

    // tests of external to internal mapping
    //@Test
    /*public*/ void FileUtilSupportTest::testGetpfPreferenceF() throw (IOException) {
        File* f = new File(instance->getUserFilesPath() + "non-existant-file-foo");
        QString name = instance->getPortableFilename(f);
        Assert::assertEquals("preference:non-existant-file-foo", name, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void FileUtilSupportTest::testGetpfPreferenceS() {
        QString name = instance->getPortableFilename("preference:non-existant-file-foo");
        Assert::assertEquals("preference:non-existant-file-foo", name, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void FileUtilSupportTest::testGetpfResourceF() throw (IOException) {
        File* f = new File(instance->getUserFilesPath() + "resources" + File::separator + "non-existant-file-foo");
        QString name = instance->getPortableFilename(f);
        Assert::assertEquals("preference:resources/non-existant-file-foo", name, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void FileUtilSupportTest::testGetpfPrefF() throw (IOException) {
        File* f = new File(instance->getUserFilesPath() + "resources" + File::separator + "non-existant-file-foo");
        QString name = instance->getPortableFilename(f);
        Assert::assertEquals("preference:resources/non-existant-file-foo", name, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void FileUtilSupportTest::testGetpfProgramF() throw (IOException) {
        File* f = new File("resources" + File::separator + "non-existant-file-foo");
        QString name = instance->getPortableFilename(f);
        Assert::assertEquals("program:resources/non-existant-file-foo", name, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void FileUtilSupportTest::testGetpfProgramS() {
        QString name = instance->getPortableFilename("program:resources/non-existant-file-foo");
        Assert::assertEquals("program:resources/non-existant-file-foo", name, __FILE__, __LINE__);
    }

    /*
     * Test a real directory. It should end with a separator.
     */
    //@Test
    /*public*/ void FileUtilSupportTest::testGetpfProgramDirS() {
        QString name = instance->getPortableFilename("program:resources/icons");
        Assert::assertEquals("program:resources/icons/", name, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void FileUtilSupportTest::testGetpfHomeS() {
        QString name = instance->getPortableFilename("home:non-existant-file-foo");
        Assert::assertEquals("home:non-existant-file-foo", name, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void FileUtilSupportTest::testGetpfHomeF() throw (IOException) {
        File* f = new File(System::getProperty("user.home") + File::separator + "resources" + File::separator + "non-existant-file-foo");
        QString name = instance->getPortableFilename(f);
        Assert::assertEquals("home:resources/non-existant-file-foo", name, __FILE__, __LINE__);
    }

    /*
     * test getAbsoluteFilename()
     */
    // relative File* with no prefix: Should become null
    //@Test
    /*public*/ void FileUtilSupportTest::testGAFRel() {
        QString name = instance->getAbsoluteFilename("resources/non-existant-file-foo");
        Assert::assertEquals("", name, __FILE__, __LINE__);
    }

    // program: prefix with relative path, convert to relative in system-specific form
    //@Test
    /*public*/ void FileUtilSupportTest::testGAFProgRel() throw (IOException) {
        QString name = instance->getAbsoluteFilename(FileUtil::PROGRAM + "jython");
        Assert::assertEquals((new File("jython"))->getCanonicalPath(), name, __FILE__, __LINE__);
    }

    // program: prefix with absolute path, convert to absolute in system-specific form
    //@Test
    /*public*/ void FileUtilSupportTest::testGAFProgAbs() throw (IOException) {
        File* f = new File("resources/non-existant-file-foo");
        QString name = instance->getAbsoluteFilename(FileUtil::PROGRAM + f->getAbsolutePath());
        Assert::assertEquals(f->getCanonicalPath(), name, __FILE__, __LINE__);
    }

    // preference: prefix with relative path, convert to absolute in system-specific form
    //@Test
    /*public*/ void FileUtilSupportTest::testGAFPrefRel() throw (IOException) {
        QString name = instance->getAbsoluteFilename(FileUtil::PREFERENCES + "non-existant-file-foo");
        Assert::assertEquals((new File(instance->getUserFilesPath() + "non-existant-file-foo"))->getCanonicalPath(), name, __FILE__, __LINE__);
    }

    // preference: prefix with absolute path, convert to absolute in system-specific form
    //@Test
    /*public*/ void FileUtilSupportTest::testGAFPrefAbs() throw (IOException) {
        File* f = new File("resources/non-existant-file-foo");
        QString name = instance->getAbsoluteFilename(FileUtil::PREFERENCES + f->getAbsolutePath());
        Assert::assertEquals(f->getCanonicalPath(), name, __FILE__, __LINE__);
    }

    // home: prefix with relative path, convert to absolute in system-specific form
    //@Test
    /*public*/ void FileUtilSupportTest::testGAFHomeRel() throw (IOException) {
        QString name = instance->getAbsoluteFilename(FileUtil::HOME + "non-existant-file-foo");
        Assert::assertEquals((new File(System::getProperty("user.home") + File::separator + "non-existant-file-foo"))->getCanonicalPath(), name, __FILE__, __LINE__);
    }

    // home: prefix with absolute path, convert to absolute in system-specific form
    //@Test
    /*public*/ void FileUtilSupportTest::testGAFHomeAbs() throw (IOException) {
        File* f = new File("resources/non-existant-file-foo");
        QString name = instance->getAbsoluteFilename(FileUtil::HOME + f->getAbsolutePath());
        Assert::assertEquals(f->getCanonicalPath(), name, __FILE__, __LINE__);
    }
#if 0
    //@Test
    /*public*/ void FileUtilSupportTest::testCopyFile() throw (FileNotFoundException) {
        File* src = instance->getFile(instance->getAbsoluteFilename("program:default.lcf"));
        File* dest = new File(instance->getAbsoluteFilename("program:fileUtilTest.lcf"));
        QStringList sl = QStringList();
        QStringList dl = QStringList();
        try {
            instance->copy(src, dest);
            Scanner s = new Scanner(src);
            while (s.hasNext()) {
                sl.add(s.next());
            }
            s.close();
            s = new Scanner(dest);
            while (s.hasNext()) {
                dl.add(s.next());
            }
            s.close();
        } catch (IOException* ex) {
            instance->_delete(dest);
            fail("Unable to copy");
        }
        instance->_delete(dest);
        Assert::assertTrue(sl == (dl), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void FileUtilSupportTest::testCopyDirectoryToExistingDirectory() throw (FileNotFoundException, IOException) {
        File* src = instance->getFile(instance->getAbsoluteFilename("program:web/fonts"));
        File* dest = Files.createTempDirectory("FileUtilTest").toFile();
        instance->copy(src, dest);
        String[] destFiles = dest.list();
        String[] srcFiles = src.list();
        Arrays.sort(destFiles);
        Arrays.sort(srcFiles);
        instance->delete(dest);
        Assert::assertTrue(Arrays.equals(srcFiles, destFiles), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void FileUtilSupportTest::testDeleteFile() throw (IOException) {
        File* file = File::createTempFile("FileUtilTest", null);
        instance->copy(instance->getFile(instance->getAbsoluteFilename("program:default.lcf")), file);
        instance->_delete(file);
        Assert::assertFalse(File::exists(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void FileUtilSupportTest::testAppendTextToFile() throw (IOException) {
        File* File* = File::createTempFile("FileUtilTest", null);
        QString text = "jmri.util.FileUtil#appendTextToFile";
        instance->appendTextToFile(file, text);
        List<String> lines = Files.readAllLines(Paths->get(File::toURI()), StandardCharsets.UTF_8);
        Assert::assertEquals(text, lines->get(0), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void FileUtilSupportTest::testFindURIPath() {
        URI uri = this->programTestFile::toURI();
        Assert::assertNotNull(uri, __FILE__, __LINE__);
        Assert::assertEquals(uri, instance->findURI(this->programTestFile->getName()), __FILE__, __LINE__);
        Assert::assertEquals(uri, instance->findURI(FileUtil::PROGRAM + this->programTestFile->getName()), __FILE__, __LINE__);
        Assert::assertNull(instance->findURI(FileUtil::PREFERENCES + this->programTestFile->getName()), __FILE__, __LINE__);
        uri = this->preferencesTestFile::toURI();
        Assert::assertNotNull(uri, __FILE__, __LINE__);
        Assert::assertEquals(uri, instance->findURI(this->preferencesTestFile->getName()), __FILE__, __LINE__);
        Assert::assertEquals(uri, instance->findURI(FileUtil::PREFERENCES + this->preferencesTestFile->getName()), __FILE__, __LINE__);
        Assert::assertNull(instance->findURI(FileUtil::PROGRAM + this->preferencesTestFile->getName()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void FileUtilSupportTest::testFindURIPathLocation() {
        URI uri = this->programTestFile::toURI();
        Assert::assertNotNull(uri, __FILE__, __LINE__);
        Assert::assertEquals(uri, instance->findURI(this->programTestFile->getName(), FileUtil::Location.INSTALLED), __FILE__, __LINE__);
        Assert::assertEquals(uri, instance->findURI(this->programTestFile->getName(), FileUtil::Location.ALL), __FILE__, __LINE__);
        Assert::assertNull(instance->findURI(this->programTestFile->getName(), FileUtil::Location.USER), __FILE__, __LINE__);
        uri = this->preferencesTestFile::toURI();
        Assert::assertNotNull(uri, __FILE__, __LINE__);
        Assert::assertEquals(uri, instance->findURI(this->preferencesTestFile->getName(), FileUtil::Location.USER), __FILE__, __LINE__);
        Assert::assertEquals(uri, instance->findURI(this->preferencesTestFile->getName(), FileUtil::Location.ALL), __FILE__, __LINE__);
        Assert::assertNull(instance->findURI(this->preferencesTestFile->getName(), FileUtil::Location.INSTALLED), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void FileUtilSupportTest::testFindURIPathSearchPaths() {
        URI uri = this->programTestFile::toURI();
        Assert::assertNotNull(uri, __FILE__, __LINE__);
        Assert::assertEquals(uri, instance->findURI(this->programTestFile->getName(), new String[]{instance->getProgramPath()}), __FILE__, __LINE__);
        Assert::assertEquals(uri, instance->findURI(this->programTestFile->getName(), new String[]{instance->getPreferencesPath(), instance->getProgramPath()}), __FILE__, __LINE__);
        Assert::assertEquals(uri, instance->findURI(this->programTestFile->getName(), new String[]{instance->getPreferencesPath()}), __FILE__, __LINE__);
        uri = this->preferencesTestFile::toURI();
        Assert::assertNotNull(uri, __FILE__, __LINE__);
        Assert::assertEquals(uri, instance->findURI(this->preferencesTestFile->getName(), new String[]{instance->getPreferencesPath()}), __FILE__, __LINE__);
        Assert::assertEquals(uri, instance->findURI(this->preferencesTestFile->getName(), new String[]{instance->getPreferencesPath(), instance->getProgramPath()}), __FILE__, __LINE__);
        Assert::assertEquals(uri, instance->findURI(this->preferencesTestFile->getName(), new String[]{instance->getProgramPath()}), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void FileUtilSupportTest::testFindExternalFilename() {
        URI uri = this->programTestFile::toURI();
        Assert::assertNotNull(uri, __FILE__, __LINE__);
        Assert::assertEquals(uri, instance->findExternalFilename(this->programTestFile->getName()), __FILE__, __LINE__);
        Assert::assertEquals(uri, instance->findExternalFilename(FileUtil::PROGRAM + this->programTestFile->getName()), __FILE__, __LINE__);
        Assert::assertNull(instance->findExternalFilename(FileUtil::PREFERENCES + this->programTestFile->getName()), __FILE__, __LINE__);
        uri = this->preferencesTestFile::toURI();
        Assert::assertNotNull(uri, __FILE__, __LINE__);
        Assert::assertEquals(uri, instance->findExternalFilename(this->preferencesTestFile->getName()), __FILE__, __LINE__);
        Assert::assertEquals(uri, instance->findExternalFilename(FileUtil::PREFERENCES + this->preferencesTestFile->getName()), __FILE__, __LINE__);
        Assert::assertNull(instance->findExternalFilename(FileUtil::PROGRAM + this->preferencesTestFile->getName()), __FILE__, __LINE__);
    }
#endif
    //@BeforeEach
    /*public*/ void FileUtilSupportTest::FileUtilSupportTest::setUp() throw (Exception) {
        JUnitUtil::setUp();
        JUnitUtil::resetProfileManager();
        this->instance = new FileUtilSupport();
        this->programTestFile = new File(QUuid::createUuid().toString(QUuid::WithoutBraces));
        this->programTestFile->createNewFile();
//        JUnitUtil::waitFor(() -> {
//            return this->programTestFile->exists();
//        }, "Create program test file");
        File* profile = new File(instance->getProfilePath());
        profile->mkdir();
        this->preferencesTestFile = new File(profile, QUuid::createUuid().toString(QUuid::WithoutBraces));
        this->preferencesTestFile->createNewFile();
//        JUnitUtil::waitFor(() -> {
//            return this->preferencesTestFile->exists();
//        }, "Create program test file");
    }

    //@AfterEach
    /*public*/ void FileUtilSupportTest::FileUtilSupportTest::tearDown() {
        this->programTestFile->_delete();
//        JUnitUtil::waitFor(() -> {
//            return !this->programTestFile::exists();
//        }, "Remove program test file");
        this->preferencesTestFile->_delete();
//        JUnitUtil::waitFor(() -> {
//            return !this->preferencesTestFile->exists();
//        }, "Remove program test file");
        JUnitUtil::tearDown();
    }
