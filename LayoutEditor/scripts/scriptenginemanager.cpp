#include "scriptenginemanager.h"
#include "simplebindings.h"
#include "scriptengine.h"
#include "scriptenginefactory.h"
#include "scriptcontext.h"
#include "logger.h"

//ScriptEngineManager::ScriptEngineManager(QObject *parent) : QObject(parent)
//{

//}
/**
 * The <code>ScriptEngineManager</code> implements a discovery and instantiation
 * mechanism for <code>ScriptEngine</code> classes and also maintains a
 * collection of key/value pairs storing state shared by all engines created
 * by the Manager. This class uses the <a href="../../../technotes/guides/jar/jar.html#Service%20Provider">service provider</a> mechanism to enumerate all the
 * implementations of <code>ScriptEngineFactory</code>. <br><br>
 * The <code>ScriptEngineManager</code> provides a method to return a list of all these factories
 * as well as utility methods which look up factories on the basis of language name, file extension
 * and mime type.
 * <p>
 * The <code>Bindings</code> of key/value pairs, referred to as the "Global Scope"  maintained
 * by the manager is available to all instances of <code>ScriptEngine</code> created
 * by the <code>ScriptEngineManager</code>.  The values in the <code>Bindings</code> are
 * generally exposed in all scripts.
 *
 * @author Mike Grogan
 * @author A. Sundararajan
 * @since 1.6
 */
///*public*/ class ScriptEngineManager  {
/*private*/ /*static*/ /*final*/ bool ScriptEngineManager::DEBUG = false;
/**
 * The effect of calling this constructor is the same as calling
 * <code>ScriptEngineManager(Thread.currentThread().getContextClassLoader())</code>.
 *
 * @see java.lang.Thread#getContextClassLoader
 */
/*public*/ ScriptEngineManager::ScriptEngineManager(QObject *parent) : QObject(parent)
{
// ClassLoader* ctxtLoader = Thread.currentThread().getContextClassLoader();
// init(ctxtLoader);
}

/**
 * This constructor loads the implementations of
 * <code>ScriptEngineFactory</code> visible to the given
 * <code>ClassLoader</code> using the <a href="../../../technotes/guides/jar/jar.html#Service%20Provider">service provider</a> mechanism.<br><br>
 * If loader is <code>NULL</code>, the script engine factories that are
 * bundled with the platform and that are in the usual extension
 * directories (installed extensions) are loaded. <br><br>
 *
 * @param loader ClassLoader used to discover script engine factories.
 */
/*public*/ ScriptEngineManager::ScriptEngineManager(ClassLoader* loader, QObject *parent) : QObject(parent) {
    init(loader);
}

/*private*/ void ScriptEngineManager::init(/*final*/ ClassLoader* loader) {
    globalScope =  new SimpleBindings();
    engineSpis = QSet<ScriptEngineFactory*>();
    nameAssociations = QMap<QString, ScriptEngineFactory*>();
    extensionAssociations = QMap<QString, ScriptEngineFactory*>();
    mimeTypeAssociations = QMap<QString, ScriptEngineFactory*>();
    initEngines(loader);
}
#if 0
/*private*/ ServiceLoader<ScriptEngineFactory*> getServiceLoader(/*final*/ ClassLoader loader) {
    if (loader != NULL) {
        return ServiceLoader.load(ScriptEngineFactory.class, loader);
    } else {
        return ServiceLoader.loadInstalled(ScriptEngineFactory.class);
    }
}
#endif
/*private*/ void ScriptEngineManager::initEngines(/*final*/ ClassLoader* loader)
{
#if 0
    Iterator<ScriptEngineFactory> itr = NULL;
    try {
        ServiceLoader<ScriptEngineFactory> sl = AccessController.doPrivileged(
            new PrivilegedAction<ServiceLoader<ScriptEngineFactory>>() {
                @Override
                /*public*/ ServiceLoader<ScriptEngineFactory> run() {
                    return getServiceLoader(loader);
                }
            });

        itr = sl.iterator();
    } catch (ServiceConfigurationError err) {
        System.err.println("Can't find ScriptEngineFactory providers: " +
                      err.getMessage());
        if (DEBUG) {
            err.printStackTrace();
        }
        // do not throw any exception here. user may want to
        // manage his/her own factories using this manager
        // by explicit registratation (by registerXXX) methods.
        return;
    }

    try {
        while (itr.hasNext()) {
            try {
                ScriptEngineFactory fact = itr.next();
                engineSpis.add(fact);
            } catch (ServiceConfigurationError err) {
                System.err.println("ScriptEngineManager providers.next(): "
                             + err.getMessage());
                if (DEBUG) {
                    err.printStackTrace();
                }
                // one factory failed, but check other factories...
                continue;
            }
        }
    } catch (ServiceConfigurationError err) {
        System.err.println("ScriptEngineManager providers.hasNext(): "
                        + err.getMessage());
        if (DEBUG) {
            err.printStackTrace();
        }
        // do not throw any exception here. user may want to
        // manage his/her own factories using this manager
        // by explicit registratation (by registerXXX) methods.
        return;
    }
#endif
}

/**
 * <code>setBindings</code> stores the specified <code>Bindings</code>
 * in the <code>globalScope</code> field. ScriptEngineManager sets this
 * <code>Bindings</code> as global bindings for <code>ScriptEngine</code>
 * objects created by it.
 *
 * @param bindings The specified <code>Bindings</code>
 * @throws IllegalArgumentException if bindings is NULL.
 */
/*public*/ void ScriptEngineManager::setBindings(Bindings* bindings) {
    if (bindings == NULL) {
        //throw new IllegalArgumentException("Global scope cannot be NULL.");
     Logger::error("Global scope cannot be NULL.");
     return;
    }

    globalScope = bindings;
}

/**
 * <code>getBindings</code> returns the value of the <code>globalScope</code> field.
 * ScriptEngineManager sets this <code>Bindings</code> as global bindings for
 * <code>ScriptEngine</code> objects created by it.
 *
 * @return The globalScope field.
 */
/*public*/ Bindings* ScriptEngineManager::getBindings() {
    return globalScope;
}
#if 0
/**
 * Sets the specified key/value pair in the Global Scope.
 * @param key Key to set
 * @param value Value to set.
 * @throws NullPointerException if key is NULL.
 * @throws IllegalArgumentException if key is empty string.
 */
/*public*/ void put(String key, Object value) {
    globalScope.put(key, value);
}

/**
 * Gets the value for the specified key in the Global Scope
 * @param key The key whose value is to be returned.
 * @return The value for the specified key.
 */
/*public*/ Object get(String key) {
    return globalScope.get(key);
}
#endif
/**
 * Looks up and creates a <code>ScriptEngine</code> for a given  name.
 * The algorithm first searches for a <code>ScriptEngineFactory</code> that has been
 * registered as a handler for the specified name using the <code>registerEngineName</code>
 * method.
 * <br><br> If one is not found, it searches the set of <code>ScriptEngineFactory</code> instances
 * stored by the constructor for one with the specified name.  If a <code>ScriptEngineFactory</code>
 * is found by either method, it is used to create instance of <code>ScriptEngine</code>.
 * @param shortName The short name of the <code>ScriptEngine</code> implementation.
 * returned by the <code>getNames</code> method of its <code>ScriptEngineFactory</code>.
 * @return A <code>ScriptEngine</code> created by the factory located in the search.  Returns NULL
 * if no such factory was found.  The <code>ScriptEngineManager</code> sets its own <code>globalScope</code>
 * <code>Bindings</code> as the <code>GLOBAL_SCOPE</code> <code>Bindings</code> of the newly
 * created <code>ScriptEngine</code>.
 * @throws NullPointerException if shortName is NULL.
 */
/*public*/ ScriptEngine* ScriptEngineManager::getEngineByName(QString shortName)
{
 if (shortName == NULL)
 {
  //throw new NullPointerException();
  return NULL;
 }
 //look for registered name first
 QObject* obj;
 if (NULL != (obj = nameAssociations.value(shortName)))
 {
  ScriptEngineFactory* spi = (ScriptEngineFactory*)obj;
//     try {
      ScriptEngine* engine = spi->getScriptEngine();
      engine->setBindings(getBindings(), ScriptContext::GLOBAL_SCOPE);
      return engine;
//     } catch (Exception exp) {
//         if (DEBUG) exp.printStackTrace();
//     }
 }

 foreach (ScriptEngineFactory* spi, engineSpis) {
     QStringList names = QStringList();
     //try {
         names = spi->getNames();
//     } catch (Exception exp) {
//         if (DEBUG) exp.printStackTrace();
//     }

     if (names != QStringList()) {
         foreach (QString name, names) {
             if (shortName==(name)) {
//                 try {
                     ScriptEngine* engine = spi->getScriptEngine();
                     engine->setBindings(getBindings(), ScriptContext::GLOBAL_SCOPE);
                     return engine;
//                 } catch (Exception exp) {
//                     if (DEBUG) exp.printStackTrace();
//                 }
             }
         }
     }
 }

 return NULL;
}
#if 0
/**
 * Look up and create a <code>ScriptEngine</code> for a given extension.  The algorithm
 * used by <code>getEngineByName</code> is used except that the search starts
 * by looking for a <code>ScriptEngineFactory</code> registered to handle the
 * given extension using <code>registerEngineExtension</code>.
 * @param extension The given extension
 * @return The engine to handle scripts with this extension.  Returns <code>NULL</code>
 * if not found.
 * @throws NullPointerException if extension is NULL.
 */
/*public*/ ScriptEngine getEngineByExtension(String extension) {
    if (extension == NULL) throw new NullPointerException();
    //look for registered extension first
    Object obj;
    if (NULL != (obj = extensionAssociations.get(extension))) {
        ScriptEngineFactory spi = (ScriptEngineFactory)obj;
        try {
            ScriptEngine engine = spi.getScriptEngine();
            engine.setBindings(getBindings(), ScriptContext.GLOBAL_SCOPE);
            return engine;
        } catch (Exception exp) {
            if (DEBUG) exp.printStackTrace();
        }
    }

    for (ScriptEngineFactory spi : engineSpis) {
        List<String> exts = NULL;
        try {
            exts = spi.getExtensions();
        } catch (Exception exp) {
            if (DEBUG) exp.printStackTrace();
        }
        if (exts == NULL) continue;
        for (String ext : exts) {
            if (extension.equals(ext)) {
                try {
                    ScriptEngine engine = spi.getScriptEngine();
                    engine.setBindings(getBindings(), ScriptContext.GLOBAL_SCOPE);
                    return engine;
                } catch (Exception exp) {
                    if (DEBUG) exp.printStackTrace();
                }
            }
        }
    }
    return NULL;
}

/**
 * Look up and create a <code>ScriptEngine</code> for a given mime type.  The algorithm
 * used by <code>getEngineByName</code> is used except that the search starts
 * by looking for a <code>ScriptEngineFactory</code> registered to handle the
 * given mime type using <code>registerEngineMimeType</code>.
 * @param mimeType The given mime type
 * @return The engine to handle scripts with this mime type.  Returns <code>NULL</code>
 * if not found.
 * @throws NullPointerException if mimeType is NULL.
 */
/*public*/ ScriptEngine getEngineByMimeType(String mimeType) {
    if (mimeType == NULL) throw new NullPointerException();
    //look for registered types first
    Object obj;
    if (NULL != (obj = mimeTypeAssociations.get(mimeType))) {
        ScriptEngineFactory spi = (ScriptEngineFactory)obj;
        try {
            ScriptEngine engine = spi.getScriptEngine();
            engine.setBindings(getBindings(), ScriptContext.GLOBAL_SCOPE);
            return engine;
        } catch (Exception exp) {
            if (DEBUG) exp.printStackTrace();
        }
    }

    for (ScriptEngineFactory spi : engineSpis) {
        List<String> types = NULL;
        try {
            types = spi.getMimeTypes();
        } catch (Exception exp) {
            if (DEBUG) exp.printStackTrace();
        }
        if (types == NULL) continue;
        for (String type : types) {
            if (mimeType.equals(type)) {
                try {
                    ScriptEngine engine = spi.getScriptEngine();
                    engine.setBindings(getBindings(), ScriptContext.GLOBAL_SCOPE);
                    return engine;
                } catch (Exception exp) {
                    if (DEBUG) exp.printStackTrace();
                }
            }
        }
    }
    return NULL;
}

/**
 * Returns a list whose elements are instances of all the <code>ScriptEngineFactory</code> classes
 * found by the discovery mechanism.
 * @return List of all discovered <code>ScriptEngineFactory</code>s.
 */
/*public*/ List<ScriptEngineFactory> getEngineFactories() {
    List<ScriptEngineFactory> res = new ArrayList<ScriptEngineFactory>(engineSpis.size());
    for (ScriptEngineFactory spi : engineSpis) {
        res.add(spi);
    }
    return Collections.unmodifiableList(res);
}

/**
 * Registers a <code>ScriptEngineFactory</code> to handle a language
 * name.  Overrides any such association found using the Discovery mechanism.
 * @param name The name to be associated with the <code>ScriptEngineFactory</code>.
 * @param factory The class to associate with the given name.
 * @throws NullPointerException if any of the parameters is NULL.
 */
/*public*/ void registerEngineName(String name, ScriptEngineFactory factory) {
    if (name == NULL || factory == NULL) throw new NullPointerException();
    nameAssociations.put(name, factory);
}

/**
 * Registers a <code>ScriptEngineFactory</code> to handle a mime type.
 * Overrides any such association found using the Discovery mechanism.
 *
 * @param type The mime type  to be associated with the
 * <code>ScriptEngineFactory</code>.
 *
 * @param factory The class to associate with the given mime type.
 * @throws NullPointerException if any of the parameters is NULL.
 */
/*public*/ void registerEngineMimeType(String type, ScriptEngineFactory factory) {
    if (type == NULL || factory == NULL) throw new NullPointerException();
    mimeTypeAssociations.put(type, factory);
}

/**
 * Registers a <code>ScriptEngineFactory</code> to handle an extension.
 * Overrides any such association found using the Discovery mechanism.
 *
 * @param extension The extension type  to be associated with the
 * <code>ScriptEngineFactory</code>.
 * @param factory The class to associate with the given extension.
 * @throws NullPointerException if any of the parameters is NULL.
 */
/*public*/ void registerEngineExtension(String extension, ScriptEngineFactory factory) {
    if (extension == NULL || factory == NULL) throw new NullPointerException();
    extensionAssociations.put(extension, factory);
}

//}
#endif
