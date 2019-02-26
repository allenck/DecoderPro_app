#include "jmriscriptenginemanager.h"
#include "scriptenginemanager.h"
#include "instancemanager.h"
#include "PythonQt.h"
#include "pythonwrappers.h"
#include "logger.h"
#include "scriptengine.h"
#include "scriptenginefactory.h"
#include "fileutil.h"
#include "properties.h"
#include "system.h"
#include "pythoninterpreter.h"

//JmriScriptEngineManager::JmriScriptEngineManager(QObject *parent) : QObject(parent)
//{

//}git
/**
 * Provide a manager for {@link javax.script.ScriptEngine}s.
 *
 * The following methods are the only mechanisms for evaluating a Python script
 * that respect the <code>jython.exec</code> property in the
 * <em>python.properties</em> file:
 * <ul>
 * <li>{@link #eval(java.io.File)}</li>
 * <li>{@link #eval(java.io.File, javax.script.Bindings)}</li>
 * <li>{@link #eval(java.io.File, javax.script.ScriptContext)}</li>
 * <li>{@link #eval(java.lang.String, javax.script.ScriptEngine)}</li>
 * <li>{@link #runScript(java.io.File)}</li>
 * </ul>
 * Evaluating a script using <code>getEngine*(java.lang.String).eval(...)</code>
 * methods will not respect the <code>jython.exec</code> property, although all
 * methods will respect all other properties of that file.
 *
 * @author Randall Wood
 */
///*public*/ final class JmriScriptEngineManager {


///*private*/ static /*final*/ Logger log = LoggerFactory.getLogger(JmriScriptEngineManager.class);
/*private*/ static /*final*/ QString jythonDefaults = "jmri_defaults.py"; // should be replaced with default context

/*public*/ /*static*/ /*final*/ QString JmriScriptEngineManager::PYTHON = "jython";

/**
 * Create a JmriScriptEngineManager. In most cases, it is preferable to use
 * {@link #getDefault()} to get existing {@link javax.script.ScriptEngine}
 * instances.
 */
/*public*/ JmriScriptEngineManager::JmriScriptEngineManager(QObject *parent) : QObject(parent)
{
 log = new Logger("JmriScriptEngineManager");
 manager = new ScriptEngineManager();
 names = QMap<QString, QString>();
 names.insert("PythonQt", "jython");
 factories = QMap<QString, ScriptEngineFactory*>();
 engines = QMap<QString, ScriptEngine*>();
 jython = NULL;
 firstTime = false;
#if 0
    this.manager.getEngineFactories().stream().forEach((factory) -> {
        log->info("{} {} is provided by {} {}",
                factory.getLanguageName(),
                factory.getLanguageVersion(),
                factory.getEngineName(),
                factory.getEngineVersion());
        factory.getExtensions().stream().forEach((extension) -> {
            names.put(extension, factory.getEngineName());
            log->debug("\tExtension: {}", extension);
        });
        factory.getExtensions().stream().forEach((mimeType) -> {
            names.put(mimeType, factory.getEngineName());
            log->debug("\tMime type: {}", mimeType);
        });
        factory.getNames().stream().forEach((name) -> {
            names.put(name, factory.getEngineName());
            log->debug("\tNames: {}", name);
        });
        this.names.put(factory.getLanguageName(), factory.getEngineName());
        this.factories.put(factory.getEngineName(), factory);
    });
    Bindings bindings = new SimpleBindings();
    bindings.put("turnouts", InstanceManager.getDefault(TurnoutManager.class));
    bindings.put("sensors", InstanceManager.getDefault(SensorManager.class));
    bindings.put("signals", InstanceManager.getDefault(SignalHeadManager.class));
    bindings.put("masts", InstanceManager.getDefault(SignalMastManager.class));
    bindings.put("lights", InstanceManager.getDefault(LightManager.class));
    bindings.put("dcc", InstanceManager.getDefault(CommandStation.class));
    bindings.put("reporters", InstanceManager.getDefault(ReporterManager.class));
    bindings.put("memories", InstanceManager.getDefault(MemoryManager.class));
    bindings.put("routes", InstanceManager.getDefault(RouteManager.class));
    bindings.put("blocks", InstanceManager.getDefault(BlockManager.class));
    bindings.put("powermanager", InstanceManager.getDefault(PowerManager.class));
    bindings.put("programmers", InstanceManager.getDefault(ProgrammerManager.class));
    bindings.put("shutdown", InstanceManager.getDefault(ShutDownManager.class));
    bindings.put("audio", InstanceManager.getDefault(AudioManager.class));
    bindings.put("layoutblocks", InstanceManager.getDefault(LayoutBlockManager.class));
    bindings.put("warrants", InstanceManager.getDefault(WarrantManager.class));
    bindings.put("CLOSED", Turnout.CLOSED);
    bindings.put("THROWN", Turnout.THROWN);
    bindings.put("CABLOCKOUT", Turnout.CABLOCKOUT);
    bindings.put("PUSHBUTTONLOCKOUT", Turnout.PUSHBUTTONLOCKOUT);
    bindings.put("UNLOCKED", Turnout.UNLOCKED);
    bindings.put("LOCKED", Turnout.LOCKED);
    bindings.put("ACTIVE", Sensor.ACTIVE);
    bindings.put("INACTIVE", Sensor.INACTIVE);
    bindings.put("ON", Light.ON);
    bindings.put("OFF", Light.OFF);
    bindings.put("UNKNOWN", NamedBean.UNKNOWN);
    bindings.put("INCONSISTENT", NamedBean.INCONSISTENT);
    bindings.put("DARK", SignalHead.DARK);
    bindings.put("RED", SignalHead.RED);
    bindings.put("YELLOW", SignalHead.YELLOW);
    bindings.put("GREEN", SignalHead.GREEN);
    bindings.put("LUNAR", SignalHead.LUNAR);
    bindings.put("FLASHRED", SignalHead.FLASHRED);
    bindings.put("FLASHYELLOW", SignalHead.FLASHYELLOW);
    bindings.put("FLASHGREEN", SignalHead.FLASHGREEN);
    bindings.put("FLASHLUNAR", SignalHead.FLASHLUNAR);
    bindings.put("FileUtil", FileUtil.class);
    this.context = new SimpleScriptContext();
    this.context.setBindings(bindings, ScriptContext.GLOBAL_SCOPE);
#endif
}

/**
 * Get the default instance of a JmriScriptEngineManager. Using the default
 * instance ensures that a script retains the context of the prior script.
 *
 * @return the default JmriScriptEngineManager
 */
/*public*/ /*static*/  JmriScriptEngineManager* JmriScriptEngineManager::getDefault()
{
    if (InstanceManager::getDefault("JmriScriptEngineManager") == NULL) {
        InstanceManager::setDefault("JmriScriptEngineManager", new JmriScriptEngineManager());
    }
    return (JmriScriptEngineManager*)InstanceManager::getDefault("JmriScriptEngineManager");
}

/**
 * Get the Java ScriptEngineManager that this object contains.
 *
 * @return the ScriptEngineManager
 */
/*public*/ ScriptEngineManager* JmriScriptEngineManager::getManager() {
    return this->manager;
}

/**
 * Given a file extension, get the ScriptEngine registered to handle that
 * extension.
 *
 * @return a ScriptEngine or NULL
 */
/*public*/ ScriptEngine* JmriScriptEngineManager::getEngineByExtension(QString extension) {
    QString name = this->names.value(extension);
    if (name == NULL) {
        log->error(tr("Could not find script engine name for extension \"%1\"").arg(extension));
    }
    return this->getEngine(name);
}
#if 0
/**
 * Given a mime type, get the ScriptEngine registered to handle that mime
 * type.
 *
 * @return a ScriptEngine or NULL
 */
/*public*/ ScriptEngine getEngineByMimeType(String mimeType) {
    String name = this.names.get(mimeType);
    if (name == NULL) {
        log->error("Could not find script engine name for mime type \"{}\"", mimeType);
    }
    return this.getEngine(name);
}
#endif
/**
 * Given a short name, get the ScriptEngine registered by that name.
 *
 * @return a ScriptEngine or NULL
 */
/*public*/ ScriptEngine* JmriScriptEngineManager::getEngineByName(QString shortName) {
    QString name = this->names.value(shortName);
    if (name == NULL) {
        log->error(tr("Could not find script engine name for short name \"%1\"").arg( shortName));
    }
    return this->getEngine(name);
}

/**
 * Get a ScriptEngine by it's name.
 *
 * @return a ScriptEngine or NULL
 */
/*public*/ ScriptEngine* JmriScriptEngineManager::getEngine(QString engineName)
{
 if (!this->engines.contains(engineName))
 {
  if (PYTHON==(engineName))
  {
    // Setup the default python engine to use the JMRI python properties
    this->initializePython();
  }
  else
  {
    log->debug(tr("Create engine for %1").arg(engineName));
    ScriptEngine* engine = this->factories.value(engineName)->getScriptEngine();
    engine->setContext(this->context);
    this->engines.insert(engineName, engine);
  }
 }
 return this->engines.value(engineName);
}

/**
 * Evaluate a script using the given ScriptEngine.
 *
 */
/*public*/ QObject* JmriScriptEngineManager::eval(QString script, ScriptEngine* engine) throw (ScriptException) {
    if (PYTHON == (engine->getFactory()->getEngineName()) && this->jython != nullptr) {
        this->jython->exec(script);
        return nullptr;
    }
    return engine->eval(script);
}
#if 0
/**
 * Evaluate a script using the given ScriptEngine.
 *
 */
/*public*/ Object eval(Reader reader, ScriptEngine engine) throws ScriptException {
    return engine.eval(reader);
}
#endif
/**
 * Evaluate a script contained in a file. Uses the extension of the file to
 * determine which ScriptEngine to use.
 *
 */
/*public*/ QObject* JmriScriptEngineManager::eval(File* file) //throws ScriptException, FileNotFoundException, IOException
{
#if 0
    ScriptEngine engine = this.getEngineByExtension(FilenameUtils.getExtension(file.getName()));
    if (PYTHON.equals(engine.getFactory().getEngineName()) && this.jython != NULL) {
        try (FileInputStream fi = new FileInputStream(file)) {
            this.jython.execfile(fi);
        }
        return NULL;
    }
    try (FileReader fr = new FileReader(file)) {
        return engine.eval(fr);
    }
#else
 disconnect(PythonQt::self(),SIGNAL(pythonStdErr(QString)));

 //PythonWrappers::defineClasses();
 //jmri.util.PythonInterp.runScript(jmri.util.FileUtil.getExternalFilename(file.toString()));
 if(firstTime)
  connect(PythonQt::self(), SIGNAL(pythonStdErr(QString)), this, SLOT(On_stdErr(QString)));
 firstTime = false;
 PythonQt::self()->getMainModule().evalFile(file->getPath());
 PythonQt::self()->clearError();

#endif
}
#if 0
/**
 * Evaluate a script contained in a file given a set of
 * {@link javax.script.Bindings} to add to the script's context. Uses the
 * extension of the file to determine which ScriptEngine to use.
 *
 */
/*public*/ Object eval(File file, Bindings n) throws ScriptException, FileNotFoundException, IOException {
    ScriptEngine engine = this.getEngineByExtension(FilenameUtils.getExtension(file.getName()));
    if (PYTHON.equals(engine.getFactory().getEngineName()) && this.jython != NULL) {
        try (FileInputStream fi = new FileInputStream(file)) {
            this.jython.execfile(fi);
        }
        return NULL;
    }
    try (FileReader fr = new FileReader(file)) {
        return engine.eval(fr, n);
    }
}

/**
 * Evaluate a script contained in a file given a special context for the
 * script. Uses the extension of the file to determine which ScriptEngine to
 * use.
 *
 */
/*public*/ Object eval(File file, ScriptContext context) throws ScriptException, FileNotFoundException, IOException {
    ScriptEngine engine = this.getEngineByExtension(FilenameUtils.getExtension(file.getName()));
    if (PYTHON.equals(engine.getFactory().getEngineName()) && this.jython != NULL) {
        try (FileInputStream fi = new FileInputStream(file)) {
            this.jython.execfile(fi);
        }
        return NULL;
    }
    try (FileReader fr = new FileReader(file)) {
        return engine.eval(fr, context);
    }
}
#endif
/**
 * Run a script, suppressing common errors. Note that the file needs to have
 * a registered extension, or a NullPointerException will be thrown.
 *
 * @param file the script to run.
 */
/*public*/ void JmriScriptEngineManager::runScript(File* file) {
    //try {
        this->eval(file);
//    } catch (FileNotFoundException ex) {
//        log->error("File {} not found.", file);
//    } catch (IOException ex) {
//        log->error("Exception working with file {}", file);
//    } catch (ScriptException ex) {
//        log->error("Error in script {}.", file, ex);
//    }

}
#if 0
/**
 * Initialize all ScriptEngines. This can be used to prevent the on-demand
 * initialization of a ScriptEngine from causing a pause in JMRI.
 */
/*public*/ void initializeAllEngines() {
    this.factories.keySet().stream().forEach((name) -> {
        this.getEngine(name);
    });
}
#endif
/**
 * Get the default {@link javax.script.ScriptContext} for all
 * {@link javax.script.ScriptEngine}s.
 *
 * @return the default ScriptContext;
 */
/*public*/ ScriptContext* JmriScriptEngineManager::getDefaultContext() {
    return this->context;
}
#if 0
/**
 * Given a file extension, get the ScriptEngineFactory registered to handle
 * that extension.
 *
 * @return a ScriptEngineFactory or NULL
 */
/*public*/ ScriptEngineFactory getFactoryByExtension(String extension) {
    String name = this.names.get(extension);
    if (name == NULL) {
        log->error("Could not find script engine factory name for extension \"{}\"", extension);
    }
    return this.getFactory(name);
}

/**
 * Given a mime type, get the ScriptEngineFactory registered to handle that
 * mime type.
 *
 * @return a ScriptEngineFactory or NULL
 */
/*public*/ ScriptEngineFactory getFactoryByMimeType(String mimeType) {
    String name = this.names.get(mimeType);
    if (name == NULL) {
        log->error("Could not find script engine factory name for mime type \"{}\"", mimeType);
    }
    return this.getFactory(name);
}

/**
 * Given a short name, get the ScriptEngineFactory registered by that name.
 *
 * @return a ScriptEngineFactory or NULL
 */
/*public*/ ScriptEngineFactory getFactoryByName(String shortName) {
    String name = this.names.get(shortName);
    if (name == NULL) {
        log->error("Could not find script engine factory name for short name \"{}\"", shortName);
    }
    return this.getFactory(name);
}

/**
 * Get a ScriptEngineFactory by it's name.
 *
 * @return a ScriptEngineFactory or NULL
 */
/*public*/ ScriptEngineFactory getFactory(String factoryName) {
    return this.factories.get(factoryName);
}
#endif
/**
 * The Python ScriptEngine can be configured using a custom
 * python.properties file and will run jmri_defaults.py if found in the
 * user's configuration profile or settings directory. See python.properties
 * in the JMRI installation directory for details of how to configure the
 * Python ScriptEngine.
 */
/*public*/ void JmriScriptEngineManager::initializePython()
{
 if (!this->engines.contains(PYTHON))
 {
  // Get properties for interpreter
  // Search in user files, the settings directory, and in the program path
  QTextStream* is = FileUtil::findInputStream("python.properties", QStringList() <<FileUtil::getUserFilesPath() <<FileUtil::getPreferencesPath() <<FileUtil::getProgramPath());
//  {
//      FileUtil.getUserFilesPath(),
//      FileUtil.getPreferencesPath(),
//      FileUtil.getProgramPath()
//  });
  bool execJython = false;
  if (is != NULL) {
      Properties* properties;
      try {
          properties = new Properties(System::getProperties());
          properties->setProperty("python.console.encoding", "UTF-8"); // NOI18N
          properties->setProperty("python.cachedir", FileUtil::getAbsoluteFilename(properties->getProperty("python.cachedir", "settings:jython/cache"))); // NOI18N
          properties->load(is);
          QString path = properties->getProperty("python.path", "");
          if (path.length() != 0) {
              path = path + (File::pathSeparator);
          }
          properties->setProperty("python.path", path + (FileUtil::getScriptsPath() + (File::pathSeparator) + (FileUtil::getAbsoluteFilename("program:jython"))));
          execJython = /*Boolean.valueOf*/(properties->getProperty("jython.exec", /*Boolean.toString(false)*/ "false").toLower()== "true");
      } catch (IOException ex) {
          log->error("Found, but unable to read python.properties: {}", ex);
          properties = NULL;
      }
#if 0
      PySystemState.initialize(NULL, properties);
      log->debug(tr("Jython path is %1").arg(PySystemState::getBaseProperties().getProperty("python.path")));
#endif
  }
#if 1
  // Create the interpreter
//  try {
      log->debug("create interpreter");
      ScriptEngine* python = this->manager->getEngineByName(PYTHON);
      python->setContext(this->context);
      is = FileUtil::findInputStream(jythonDefaults, QStringList() <<
          FileUtil::getUserFilesPath() <<
          FileUtil::getPreferencesPath()
      );
      if (execJython)
      {
          this->jython = new PythonInterpreter();
      }
      if (is != NULL)
      {
//       python->eval(new InputStreamReader(is));
       if (this->jython != NULL)
       {
        this->jython->execfile(is);
       }
      }
      this->engines.insert(PYTHON, python);
//  } catch (ScriptException e) {
//      log->error("Exception creating jython system objects", e);
//  }
#endif
 }
}

