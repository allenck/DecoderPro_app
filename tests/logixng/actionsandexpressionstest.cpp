#include "actionsandexpressionstest.h"
#include "junitutil.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include <QDir>
#include "assert1.h"
#include "system.h"
#include "defaultanalogactionmanager.h"
#include "defaultanalogexpressionmanager.h"
#include "defaultdigitalactionmanager.h"
#include "defaultdigitalbooleanactionmanager.h"
#include "defaultdigitalexpressionmanager.h"
#include "defaultstringactionmanager.h"
#include "defaultstringexpressionmanager.h"
#include "logixng_thread.h"
#include "swingconfiguratorinterface.h"

ActionsAndExpressionsTest::ActionsAndExpressionsTest(QObject *parent) : QObject(parent)
{

}
/**
 * Test that all the action and expression classes are registed and have
 * configurexml and swing classes.
 * <P>
 * Requirements that this class checks for:
 *
 * Each action and expression needs to
 * * be registered in its manager
 * * have a configurexml class
 * * have a swing configurator class
 * * have a test class for its swing configurator class
 *
 * @author Daniel Bergqvist 2020
 */
// /*public*/  class ActionsAndExpressionsTest {

    QString ActionsAndExpressionsTest::root = "~Home/NetBeansProjects/JMRI/";

    /*private*/ void ActionsAndExpressionsTest::checkFolder(QString path, QString packageName, QHash<Category, QList</*Class<? extends Base>*/QString>*> registeredClasses, QStringList classesToIgnore) {

//        Set<String> files = Stream.of(path.toFile().listFiles())
//                  .filter(file -> !file.isDirectory())
//                  .map(File::getName)
//                  .collect(Collectors.toSet());
     QDir rootDir(path);
     QStringList filters;
     filters << "*.java";
     QStringList files = rootDir.entryList(filters, QDir::Files);

        filesLoop:
        for (QString file : files) {
            if (file.endsWith(".properties")) continue;

            file = file.mid(0, file.indexOf('.'));

            for (QString c : classesToIgnore) {
                if (file == (c)) continue;// filesLoop;
            }

            // Check that all actions and expressions is registered in its manager
            QSet</*Class<? extends Base>*/QString> setOfClasses = QSet<QString>();
            bool isRegistered = false;
            //for (Map.Entry<Category, List<Class<? extends Base>>> entry : registeredClasses.entrySet())
            QHashIterator<Category, QList<QString>*> entry(registeredClasses);
            while(entry.hasNext())
            {
             entry.next();
                for (/*Class<? extends Base>*/QString c : *entry.value()) {
//                    System.out.format("Registered class: %s%n", c.getName());
                    if (c/*.getName()*/ == (packageName+"."+file)) isRegistered = true;

                    Assert::assertFalse(tr("Class %1 is registered more than once in the manager").arg(packageName+"."+c/*.getName()*/), setOfClasses.contains(c), __FILE__, __LINE__);

                    setOfClasses.insert(c);
//                    if (setOfClasses.contains(c)) {
//                        System.out.format("Class %s is registered more than once in the manager", packageName+"."+c.getName());
//                        errorsFound = true;
//                    } else {
//                        setOfClasses.add(c);
//                    }
                }
            }

//            if (!isRegistered) {
//                System.out.format("Class %s.%s is not registered in the manager%n", packageName, file);
//                errorsFound = true;
//            }
             Assert::assertTrue(tr("Class %1 is registred%n").arg(file), isRegistered, __FILE__, __LINE__);

            QString fullConfigName;

            // Ignore this for now

            // Check that all actions and expressions has a xml class
            QObject* configureXml = nullptr;
            fullConfigName = packageName + ".configurexml." + file + "Xml";
            log->debug(tr("getAdapter looks for %1").arg(fullConfigName));
            try {
                Class/*<?>*/* configClass = Class::forName(fullConfigName);
                configureXml = (QObject*)configClass/*.getDeclaredConstructor()*/->newInstance();
            }
            catch (ClassNotFoundException*) {}
            catch (IllegalAccessException*) {}
            catch (InstantiationException*) {}
            catch (NoSuchMethodException*) {}
            catch (InvocationTargetException* e) {
            }
            if (configureXml == nullptr) {
                System::out(tr("Class %1.%2 has no configurexml class%n").arg(packageName, file));
                errorsFound = true;
            }

            // Disable for now
//             Assert::assertNotNull(String.format("Class %s has xml class%n", file), configureXml);

            // Check that all actions and expressions has a swing class
            SwingConfiguratorInterface* configureSwing = nullptr;
            fullConfigName = packageName + ".swing." + file + "Swing";
            log->debug(tr("getAdapter looks for %1").arg(fullConfigName));
            try {
                Class/*<?>*/* configClass = Class::forName(fullConfigName);
                configureSwing = (SwingConfiguratorInterface*)configClass/*.getDeclaredConstructor()*/->newInstance();
                configureSwing->getConfigPanel(new JPanel());
                MaleSocket* socket = configureSwing->createNewObject(configureSwing->getAutoSystemName(), "");
                MaleSocket* lastMaleSocket = socket;
                Base* base = socket;
                while ((base != nullptr) && (qobject_cast<MaleSocket*>(base->bself()))) {
                    lastMaleSocket = (MaleSocket*) base->bself();
                    base = ((MaleSocket*)base->bself())->getObject();
                }
                 Assert::assertNotNull(base->bself(), __FILE__, __LINE__);
                 Assert::assertEquals("SwingConfiguratorInterface creates an object of correct type", base->getClass()/*.getName()*/, packageName+"."+file, __FILE__, __LINE__);
//                System.out.format("Swing: %s, Class: %s, class: %s%n", configureSwing.toString(), socket.getShortDescription(), socket.getObject().getClass().getName());
                 Assert::assertEquals("Swing class has correct name", socket->getShortDescription(), configureSwing->toString(), __FILE__, __LINE__);
//                System.out.format("MaleSocket class: %s, socket class: %s%n",
//                        configureSwing.getManager().getMaleSocketClass().getName(),
//                        socket.getClass().getName());
                 Class* clazz = Class::forName(configureSwing->getManager()->getMaleSocketClass());
                 //Assert::assertTrue(configureSwing.getManager().getMaleSocketClass().isAssignableFrom(lastMaleSocket->getClass()), __FILE__, __LINE__);
                 Assert::assertTrue(clazz->isAssignableFrom(lastMaleSocket->getClass()), __FILE__, __LINE__);
            } catch (ClassNotFoundException*) {}
            catch(IllegalAccessException*) {}
            catch(InstantiationException*) {}
            catch(NoSuchMethodException*) {}
            catch(InvocationTargetException* e) {
            }
//            if (configureSwing == null) {
//                System.out.format("Class %s.%s has no swing class%n", packageName, file);
//                errorsFound = true;
//            }
             Assert::assertTrue(tr("Class %1 has swing class%2").arg(file), configureSwing, __FILE__, __LINE__);

            // Ignore for now
/*
            // Check that all actions and expressions has a test class for the swing class
//            Class configureSwingTest = null;
            fullConfigName = packageName + ".swing." + file + "SwingTest";
            log->debug("getAdapter looks for {}", fullConfigName);
            Class<?> configClass = null;
            try {
                configClass = Class.forName(fullConfigName);
            } catch (ClassNotFoundException e) {
            }
            if (configClass == null) {
                System.out.format("Class %s.%s has no test class for its swing class%n", packageName, file);
                errorsFound = true;
            }
//             Assert::assertNotNull("The swing class has a test class", configClass);
*/

/*
            System.out.format("Class: %s%n", packageName+"."+file);
            Level severity = Level.ERROR; // level at or above which we'll complain
            boolean unexpectedMessageSeen = JUnitAppender.unexpectedMessageSeen(severity);
            String unexpectedMessageContent = JUnitAppender.unexpectedMessageContent(severity);
            JUnitAppender.verifyNoBacklog();
            JUnitAppender.resetUnexpectedMessageFlags(severity);
             Assert::assertFalse("Unexpected "+severity+" or higher messages emitted: "+unexpectedMessageContent, unexpectedMessageSeen);
//            JUnitAppender.assertNoErrorMessage();
*/
        }
    }

    /*private*/ QString ActionsAndExpressionsTest::getPath(QString subFolder) {
        return root + "java/src/jmri/jmrit/logixng/" + subFolder;
    }

    /*public*/  QHash<Category, QList</*Class<? extends Base>*/QString>> ActionsAndExpressionsTest::getAnalogActionClasses() {
        return ((DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager"))->getActionClasses();
    }

    /*public*/  QHash<Category, QList</*Class<? extends Base>*/QString>> ActionsAndExpressionsTest::getAnalogExpressionClasses() {
        return ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))->getExpressionClasses();
    }

    /*public*/  QHash<Category, QList</*Class<? extends Base>*/QString>> ActionsAndExpressionsTest::getDigitalActionClasses() {
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->getActionClasses();
    }

    /*public*/  QHash<Category, QList</*Class<? extends Base>*/QString>> getDigitalBooleanActionClasses() {
        return ((DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))->getActionClasses();
    }

    /*public*/  QHash<Category, QList</*Class<? extends Base>*/QString>> getDigitalExpressionClasses() {
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->getExpressionClasses();
    }

    /*public*/  QHash<Category, QList</*Class<? extends Base>*/QString>> getStringActionClasses() {
        return ((DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager"))->getActionClasses();
    }

    /*public*/  QHash<Category, QList</*Class<? extends Base>*/QString>> getStringExpressionClasses() {
        return ((DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager"))->getExpressionClasses();
    }

    /*public*/  void ActionsAndExpressionsTest::addClasses(QHash<Category, QList</*Class<? extends Base>*/QString>*> classes, QHash<Category, QList</*Class<? extends Base>*/QString>> newClasses) {
            //newClasses.entrySet().forEach((entry) ->
     QHashIterator<Category, QList<QString>> entry(newClasses);
     while(entry.hasNext())
     {
      entry.next();
//                System.out.format("Add action: %s, %s%n", entry.getKey().name(), entry.getValue().getName());
                //entry.value().forEach((clazz) ->
      for(QString clazz : entry.value())
      {
                    classes.value(entry.key())->append(clazz);
                }//);
            }//);
    }

    //@Test
    /*public*/  void ActionsAndExpressionsTest::testGetBeanType() {
        QHash<Category, QList</*Class<? extends Base>*/QString>*> classes =QHash<Category, QList<QString>*> ();
        for (Category category : Category::values()) {
            classes.insert(category, new QList<QString>());
        }
        addClasses(classes, getAnalogActionClasses());
        addClasses(classes, getDigitalActionClasses());
        addClasses(classes, getDigitalBooleanActionClasses());
        addClasses(classes, getStringActionClasses());

        checkFolder(
                getPath("actions"),
                "jmri.jmrit.logixng.actions",
                classes,
                QStringList{
                    "Bundle",
                    "NamedBeanType",
                    "AbstractAnalogAction","AnalogFactory",         // Analog
                    "AbstractDigitalAction","ActionAtomicBoolean","AbstractScriptDigitalAction","DigitalFactory",   // Digital
                    "AbstractDigitalBooleanAction","DigitalBooleanFactory",     // Boolean digital
                    "AbstractStringAction","StringFactory"          // String
                });


        classes = QHash<Category, QList<QString>*>();
        for (Category category : Category::values()) {
            classes.insert(category, new QList<QString>());
        }
        addClasses(classes, getAnalogExpressionClasses());
        addClasses(classes, getDigitalExpressionClasses());
        addClasses(classes, getStringExpressionClasses());

        checkFolder(
                getPath("expressions"),
                "jmri.jmrit.logixng.expressions",
                classes,
                QStringList{
                    "Bundle",
                    "AbstractAnalogExpression","AnalogFactory",     // Analog
                    "AbstractDigitalExpression","AbstractScriptDigitalExpression","DigitalFactory",     // Digital
                    "AbstractStringExpression","StringFactory"      // String
                });

         Assert::assertFalse("No errors found", errorsFound, __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@BeforeEach
    /*public*/  void ActionsAndExpressionsTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        // Temporary let the error messages from this test be shown to the user
//        JUnitAppender.end();
    }

    //@AfterEach
    /*public*/  void ActionsAndExpressionsTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::deregisterBlockManagerShutdownTask();
        JUnitUtil::deregisterEditorManagerShutdownTask();
        JUnitUtil::tearDown();
    }


    /*private*/ /*final*/ /*static*/ Logger* ActionsAndExpressionsTest::log = LoggerFactory::getLogger("ActionsAndExpressionsTest");
