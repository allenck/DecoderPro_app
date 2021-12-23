#include "scriptoutput.h"
#include "jtextarea.h"
#include "loggerfactory.h"
#include "instancemanager.h"

ScriptOutput::ScriptOutput(QObject *parent) : QObject(parent)
{

}
/**
 *
 * @author rhwood
 */
///*public*/ class ScriptOutput {

/**
 * JTextArea containing the output
 */
/*private*/ /*final*/ /*static*/ Logger* ScriptOutput::log = LoggerFactory::getLogger("ScriptOutput");

/**
 * Provide access to the JTextArea containing all ScriptEngine output.
 * <P>
 * The output JTextArea is not created until this is invoked, so that code
 * that doesn't use this feature can run on GUI-less machines.
 *
 * @return component containing script output
 */
/*public*/ JTextArea* ScriptOutput::getOutputArea() {
    if (output == nullptr) {
        // convert to stored output

        try {
            // create the output area
            output = new JTextArea();
#if 0 // TODO:
            // Add the I/O pipes
            PipedWriter pw = new PipedWriter();

            ScriptContext context = JmriScriptEngineManager.getDefault().getDefaultContext();
            context.setErrorWriter(pw);
            context.setWriter(pw);

            // ensure the output pipe is read and stored into a
            // Swing TextArea data model
            PipedReader pr = new PipedReader(pw);
            PipeListener pl = new PipeListener(pr, output);
            pl.start();
#endif
        } catch (IOException e) {
            log->error("Exception creating script output area", &e);
            return nullptr;
        }
    }
    return output;
}

/*static*/ /*public*/ ScriptOutput* ScriptOutput::getDefault() {
    if (InstanceManager::getNullableDefault("ScriptOutput") == nullptr) {
        InstanceManager::store(new ScriptOutput(), "ScriptOutput");
    }
    return static_cast<ScriptOutput*>(InstanceManager::getDefault("ScriptOutput"));
}

/**
 * Write a script to the output area. The output is prepended with a leading
 * "&gt;&gt;&gt;" on the first line and a leading ellipsis on subsequent
 * lines.
 *
 * @param script The script to write.
 */
/*static*/ /*public*/ void ScriptOutput::writeScript(/*final*/ QString script) {
    QString output = ">>> " + script; // NOI18N
    // Strip ending newlines
    while (output.endsWith("\n")) { // NOI18N
        output = output.mid(0, output.length() - 1);
    }
    output = output.replace("\n", "\n... "); // NOI18N
    output += "\n"; // NOI18N
    ScriptOutput::getDefault()->getOutputArea()->append(output);
}
