#include "scriptengine.h"
/**
 * Reserved key for a named value that passes
 * an array of positional arguments to a script.
 */
/*public*/ /*static*/ /*final*/ QString ScriptEngine::ARGV="javax.script.argv";

/**
 * Reserved key for a named value that is
 * the name of the file being executed.
 */
/*public*/ /*static*/ /*final*/ QString ScriptEngine::FILENAME = "javax.script.filename";

/**
 * Reserved key for a named value that is
 * the name of the <code>ScriptEngine</code> implementation.
 */
/*public*/ /*static*/ /*final*/ QString ScriptEngine::ENGINE = "javax.script.engine";

/**
 * Reserved key for a named value that identifies
 * the version of the <code>ScriptEngine</code> implementation.
 */
/*public*/ /*static*/ /*final*/ QString ScriptEngine::ENGINE_VERSION = "javax.script.engine_version";

/**
 * Reserved key for a named value that identifies
 * the short name of the scripting language.  The name is used by the
 * <code>ScriptEngineManager</code> to locate a <code>ScriptEngine</code>
 * with a given name in the <code>getEngineByName</code> method.
 */
/*public*/ /*static*/ /*final*/ QString ScriptEngine::NAME = "javax.script.name";

/**
 * Reserved key for a named value that is
 * the full name of Scripting Language supported by the implementation.
 */
/*public*/ /*static*/ /*final*/ QString ScriptEngine::LANGUAGE = "javax.script.language";

/**
 * Reserved key for the named value that identifies
 * the version of the scripting language supported by the implementation.
 */
/*public*/ /*static*/ /*final*/ QString ScriptEngine::LANGUAGE_VERSION ="javax.script.language_version";
