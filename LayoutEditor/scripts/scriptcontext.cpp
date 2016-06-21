#include "scriptcontext.h"

/**
 * EngineScope attributes are visible during the lifetime of a single
 * <code>ScriptEngine</code> and a set of attributes is maintained for each
 * engine.
 */
/*public*/ /*static*/ /*final*/ int ScriptContext::ENGINE_SCOPE = 100;

/**
 * GlobalScope attributes are visible to all engines created by same ScriptEngineFactory.
 */
/*public*/ /*static*/ /*final*/ int ScriptContext::GLOBAL_SCOPE = 200;
