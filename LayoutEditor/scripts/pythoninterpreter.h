#ifndef PYTHONINTERPRETER_H
#define PYTHONINTERPRETER_H
#include "PythonQt.h"
 /*public*/ class PythonInterpreter : public QObject //implements AutoCloseable, Closeable {
 {
  Q_OBJECT
public:
 /*public*/ void execfile(QTextStream* s);
#if 0
     /*protected*/ PySystemState systemState;
    PyObject globals;
     /*protected*/ final boolean useThreadLocalState;
     /*protected*/ static ThreadLocal<Object[]> threadLocals;
     /*protected*/ CompilerFlags cflags;
    /*private*/ /*volatile*/ boolean closed;

     /*public*/ static void initialize(Properties preProperties, Properties postProperties, String[] argv) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: aload_2
         * 3: invokestatic  org/python/core/PySystemState.initialize:(Ljava/util/Properties;Ljava/util/Properties;[Ljava/lang/String;)V
         * 6: return
         *  */
        // </editor-fold>
    }
#endif
     /*public*/ PythonInterpreter() ;
#if 0
     /*public*/ static PythonInterpreter threadLocalStateInterpreter(PyObject dict) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: new           org/python/util/PythonInterpreter
         * 3: dup
         * 4: aload_0
         * 5: aconst_null
         * 6: iconst_1
         * 7: invokespecial org/python/util/PythonInterpreter."<init>":(Lorg/python/core/PyObject;Lorg/python/core/PySystemState;Z)V
         * 10: areturn
         *  */
        // </editor-fold>
    }

     /*public*/ PythonInterpreter(PyObject dict) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: aconst_null
         * 3: invokespecial org/python/util/PythonInterpreter."<init>":(Lorg/python/core/PyObject;Lorg/python/core/PySystemState;)V
         * 6: return
         *  */
        // </editor-fold>
    }

     /*public*/ PythonInterpreter(PyObject dict, PySystemState systemState) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: aload_2
         * 3: iconst_0
         * 4: invokespecial org/python/util/PythonInterpreter."<init>":(Lorg/python/core/PyObject;Lorg/python/core/PySystemState;Z)V
         * 7: return
         *  */
        // </editor-fold>
    }

     /*protected*/ PythonInterpreter(PyObject dict, PySystemState systemState, boolean useThreadLocalState) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokespecial java/lang/Object."<init>":()V
         * 4: aload_0
         * 5: new           org/python/core/CompilerFlags
         * 8: dup
         * 9: invokespecial org/python/core/CompilerFlags."<init>":()V
         * 12: putfield      org/python/util/PythonInterpreter.cflags:Lorg/python/core/CompilerFlags;
         * 15: aload_0
         * 16: iconst_0
         * 17: putfield      org/python/util/PythonInterpreter.closed:Z
         * 20: aload_1
         * 21: ifnonnull     28
         * 24: invokestatic  org/python/core/Py.newStringMap:()Lorg/python/core/PyStringMap;
         * 27: astore_1
         * 28: aload_0
         * 29: aload_1
         * 30: putfield      org/python/util/PythonInterpreter.globals:Lorg/python/core/PyObject;
         * 33: aload_2
         * 34: ifnonnull     41
         * 37: invokestatic  org/python/core/Py.getSystemState:()Lorg/python/core/PySystemState;
         * 40: astore_2
         * 41: aload_0
         * 42: aload_2
         * 43: putfield      org/python/util/PythonInterpreter.systemState:Lorg/python/core/PySystemState;
         * 46: aload_0
         * 47: invokevirtual org/python/util/PythonInterpreter.setSystemState:()V
         * 50: aload_0
         * 51: iload_3
         * 52: putfield      org/python/util/PythonInterpreter.useThreadLocalState:Z
         * 55: iload_3
         * 56: ifne          82
         * 59: new           org/python/core/PyModule
         * 62: dup
         * 63: ldc           __main__
         * 65: aload_1
         * 66: invokespecial org/python/core/PyModule."<init>":(Ljava/lang/String;Lorg/python/core/PyObject;)V
         * 69: astore        4
         * 71: aload_2
         * 72: getfield      org/python/core/PySystemState.modules:Lorg/python/core/PyObject;
         * 75: ldc           __main__
         * 77: aload         4
         * 79: invokevirtual org/python/core/PyObject.__setitem__:(Ljava/lang/String;Lorg/python/core/PyObject;)V
         * 82: invokestatic  org/python/core/Py.importSiteIfSelected:()Z
         * 85: pop
         * 86: return
         *  */
        // </editor-fold>
    }

     /*public*/ PySystemState getSystemState() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: getfield      org/python/util/PythonInterpreter.systemState:Lorg/python/core/PySystemState;
         * 4: areturn
         *  */
        // </editor-fold>
    }

     /*protected*/ void setSystemState() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokevirtual org/python/util/PythonInterpreter.getSystemState:()Lorg/python/core/PySystemState;
         * 4: invokestatic  org/python/core/Py.setSystemState:(Lorg/python/core/PySystemState;)Lorg/python/core/PySystemState;
         * 7: pop
         * 8: return
         *  */
        // </editor-fold>
    }

     /*public*/ void setIn(PyObject inStream) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokevirtual org/python/util/PythonInterpreter.getSystemState:()Lorg/python/core/PySystemState;
         * 4: aload_1
         * 5: putfield      org/python/core/PySystemState.stdin:Lorg/python/core/PyObject;
         * 8: return
         *  */
        // </editor-fold>
    }

     /*public*/ void setIn(Reader inStream) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: new           org/python/core/PyFileReader
         * 4: dup
         * 5: aload_1
         * 6: invokespecial org/python/core/PyFileReader."<init>":(Ljava/io/Reader;)V
         * 9: invokevirtual org/python/util/PythonInterpreter.setIn:(Lorg/python/core/PyObject;)V
         * 12: return
         *  */
        // </editor-fold>
    }

     /*public*/ void setIn(InputStream inStream) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: new           org/python/core/PyFile
         * 4: dup
         * 5: aload_1
         * 6: invokespecial org/python/core/PyFile."<init>":(Ljava/io/InputStream;)V
         * 9: invokevirtual org/python/util/PythonInterpreter.setIn:(Lorg/python/core/PyObject;)V
         * 12: return
         *  */
        // </editor-fold>
    }

     /*public*/ void setOut(PyObject outStream) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokevirtual org/python/util/PythonInterpreter.getSystemState:()Lorg/python/core/PySystemState;
         * 4: aload_1
         * 5: putfield      org/python/core/PySystemState.stdout:Lorg/python/core/PyObject;
         * 8: return
         *  */
        // </editor-fold>
    }

     /*public*/ void setOut(Writer outStream) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: new           org/python/core/PyFileWriter
         * 4: dup
         * 5: aload_1
         * 6: invokespecial org/python/core/PyFileWriter."<init>":(Ljava/io/Writer;)V
         * 9: invokevirtual org/python/util/PythonInterpreter.setOut:(Lorg/python/core/PyObject;)V
         * 12: return
         *  */
        // </editor-fold>
    }

     /*public*/ void setOut(OutputStream outStream) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: new           org/python/core/PyFile
         * 4: dup
         * 5: aload_1
         * 6: invokespecial org/python/core/PyFile."<init>":(Ljava/io/OutputStream;)V
         * 9: invokevirtual org/python/util/PythonInterpreter.setOut:(Lorg/python/core/PyObject;)V
         * 12: return
         *  */
        // </editor-fold>
    }

     /*public*/ void setErr(PyObject outStream) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokevirtual org/python/util/PythonInterpreter.getSystemState:()Lorg/python/core/PySystemState;
         * 4: aload_1
         * 5: putfield      org/python/core/PySystemState.stderr:Lorg/python/core/PyObject;
         * 8: return
         *  */
        // </editor-fold>
    }

     /*public*/ void setErr(Writer outStream) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: new           org/python/core/PyFileWriter
         * 4: dup
         * 5: aload_1
         * 6: invokespecial org/python/core/PyFileWriter."<init>":(Ljava/io/Writer;)V
         * 9: invokevirtual org/python/util/PythonInterpreter.setErr:(Lorg/python/core/PyObject;)V
         * 12: return
         *  */
        // </editor-fold>
    }

     /*public*/ void setErr(OutputStream outStream) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: new           org/python/core/PyFile
         * 4: dup
         * 5: aload_1
         * 6: invokespecial org/python/core/PyFile."<init>":(Ljava/io/OutputStream;)V
         * 9: invokevirtual org/python/util/PythonInterpreter.setErr:(Lorg/python/core/PyObject;)V
         * 12: return
         *  */
        // </editor-fold>
    }

     /*public*/ PyObject eval(String s) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokevirtual org/python/util/PythonInterpreter.setSystemState:()V
         * 4: new           org/python/core/PyString
         * 7: dup
         * 8: aload_1
         * 9: invokespecial org/python/core/PyString."<init>":(Ljava/lang/String;)V
         * 12: aload_0
         * 13: invokevirtual org/python/util/PythonInterpreter.getLocals:()Lorg/python/core/PyObject;
         * 16: invokestatic  org/python/core/__builtin__.eval:(Lorg/python/core/PyObject;Lorg/python/core/PyObject;)Lorg/python/core/PyObject;
         * 19: areturn
         *  */
        // </editor-fold>
    }

     /*public*/ PyObject eval(PyObject code) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokevirtual org/python/util/PythonInterpreter.setSystemState:()V
         * 4: aload_1
         * 5: aload_0
         * 6: invokevirtual org/python/util/PythonInterpreter.getLocals:()Lorg/python/core/PyObject;
         * 9: invokestatic  org/python/core/__builtin__.eval:(Lorg/python/core/PyObject;Lorg/python/core/PyObject;)Lorg/python/core/PyObject;
         * 12: areturn
         *  */
        // </editor-fold>
    }

     /*public*/ void exec(QString s) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokevirtual org/python/util/PythonInterpreter.setSystemState:()V
         * 4: aload_1
         * 5: ldc           <string>
         * 7: getstatic     org/python/core/CompileMode.exec:Lorg/python/core/CompileMode;
         * 10: aload_0
         * 11: getfield      org/python/util/PythonInterpreter.cflags:Lorg/python/core/CompilerFlags;
         * 14: invokestatic  org/python/core/Py.compile_flags:(Ljava/lang/String;Ljava/lang/String;Lorg/python/core/CompileMode;Lorg/python/core/CompilerFlags;)Lorg/python/core/PyCode;
         * 17: aload_0
         * 18: invokevirtual org/python/util/PythonInterpreter.getLocals:()Lorg/python/core/PyObject;
         * 21: aconst_null
         * 22: invokestatic  org/python/core/Py.exec:(Lorg/python/core/PyObject;Lorg/python/core/PyObject;Lorg/python/core/PyObject;)V
         * 25: invokestatic  org/python/core/Py.flushLine:()V
         * 28: return
         *  */
        // </editor-fold>
    }

     /*public*/ void exec(PyObject code) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokevirtual org/python/util/PythonInterpreter.setSystemState:()V
         * 4: aload_1
         * 5: aload_0
         * 6: invokevirtual org/python/util/PythonInterpreter.getLocals:()Lorg/python/core/PyObject;
         * 9: aconst_null
         * 10: invokestatic  org/python/core/Py.exec:(Lorg/python/core/PyObject;Lorg/python/core/PyObject;Lorg/python/core/PyObject;)V
         * 13: invokestatic  org/python/core/Py.flushLine:()V
         * 16: return
         *  */
        // </editor-fold>
    }

     /*public*/ void execfile(String filename) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokevirtual org/python/util/PythonInterpreter.getLocals:()Lorg/python/core/PyObject;
         * 4: astore_2
         * 5: aload_0
         * 6: invokevirtual org/python/util/PythonInterpreter.setSystemState:()V
         * 9: aload_1
         * 10: aload_2
         * 11: aload_2
         * 12: aload_0
         * 13: getfield      org/python/util/PythonInterpreter.cflags:Lorg/python/core/CompilerFlags;
         * 16: invokestatic  org/python/core/__builtin__.execfile_flags:(Ljava/lang/String;Lorg/python/core/PyObject;Lorg/python/core/PyObject;Lorg/python/core/CompilerFlags;)V
         * 19: invokestatic  org/python/core/Py.flushLine:()V
         * 22: return
         *  */
        // </editor-fold>
    }

     /*public*/ void execfile(InputStream s) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: ldc           <iostream>
         * 4: invokevirtual org/python/util/PythonInterpreter.execfile:(Ljava/io/InputStream;Ljava/lang/String;)V
         * 7: return
         *  */
        // </editor-fold>
    }

     /*public*/ void execfile(InputStream s, String name) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokevirtual org/python/util/PythonInterpreter.setSystemState:()V
         * 4: aload_1
         * 5: aload_2
         * 6: getstatic     org/python/core/CompileMode.exec:Lorg/python/core/CompileMode;
         * 9: aload_0
         * 10: getfield      org/python/util/PythonInterpreter.cflags:Lorg/python/core/CompilerFlags;
         * 13: invokestatic  org/python/core/Py.compile_flags:(Ljava/io/InputStream;Ljava/lang/String;Lorg/python/core/CompileMode;Lorg/python/core/CompilerFlags;)Lorg/python/core/PyCode;
         * 16: aconst_null
         * 17: aload_0
         * 18: invokevirtual org/python/util/PythonInterpreter.getLocals:()Lorg/python/core/PyObject;
         * 21: invokestatic  org/python/core/Py.runCode:(Lorg/python/core/PyCode;Lorg/python/core/PyObject;Lorg/python/core/PyObject;)Lorg/python/core/PyObject;
         * 24: pop
         * 25: invokestatic  org/python/core/Py.flushLine:()V
         * 28: return
         *  */
        // </editor-fold>
    }

     /*public*/ PyCode compile(String script) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: ldc           <script>
         * 4: invokevirtual org/python/util/PythonInterpreter.compile:(Ljava/lang/String;Ljava/lang/String;)Lorg/python/core/PyCode;
         * 7: areturn
         *  */
        // </editor-fold>
    }

     /*public*/ PyCode compile(Reader reader) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: ldc           <script>
         * 4: invokevirtual org/python/util/PythonInterpreter.compile:(Ljava/io/Reader;Ljava/lang/String;)Lorg/python/core/PyCode;
         * 7: areturn
         *  */
        // </editor-fold>
    }

     /*public*/ PyCode compile(String script, String filename) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: new           java/io/StringReader
         * 4: dup
         * 5: aload_1
         * 6: invokespecial java/io/StringReader."<init>":(Ljava/lang/String;)V
         * 9: aload_2
         * 10: invokevirtual org/python/util/PythonInterpreter.compile:(Ljava/io/Reader;Ljava/lang/String;)Lorg/python/core/PyCode;
         * 13: areturn
         *  */
        // </editor-fold>
    }

     /*public*/ PyCode compile(Reader reader, String filename) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_1
         * 1: aload_2
         * 2: aload_0
         * 3: getfield      org/python/util/PythonInterpreter.cflags:Lorg/python/core/CompilerFlags;
         * 6: invokestatic  org/python/core/ParserFacade.parseExpressionOrModule:(Ljava/io/Reader;Ljava/lang/String;Lorg/python/core/CompilerFlags;)Lorg/python/antlr/base/mod;
         * 9: astore_3
         * 10: aload_0
         * 11: invokevirtual org/python/util/PythonInterpreter.setSystemState:()V
         * 14: aload_3
         * 15: aload_2
         * 16: getstatic     org/python/core/CompileMode.eval:Lorg/python/core/CompileMode;
         * 19: aload_0
         * 20: getfield      org/python/util/PythonInterpreter.cflags:Lorg/python/core/CompilerFlags;
         * 23: invokestatic  org/python/core/Py.compile_flags:(Lorg/python/antlr/base/mod;Ljava/lang/String;Lorg/python/core/CompileMode;Lorg/python/core/CompilerFlags;)Lorg/python/core/PyCode;
         * 26: areturn
         *  */
        // </editor-fold>
    }

     /*public*/ PyObject getLocals() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: getfield      org/python/util/PythonInterpreter.useThreadLocalState:Z
         * 4: ifne          12
         * 7: aload_0
         * 8: getfield      org/python/util/PythonInterpreter.globals:Lorg/python/core/PyObject;
         * 11: areturn
         * 12: getstatic     org/python/util/PythonInterpreter.threadLocals:Ljava/lang/ThreadLocal;
         * 15: invokevirtual java/lang/ThreadLocal.get:()Ljava/lang/Object;
         * 18: checkcast     "[Ljava/lang/Object;"
         * 21: iconst_0
         * 22: aaload
         * 23: checkcast     org/python/core/PyObject
         * 26: astore_1
         * 27: aload_1
         * 28: ifnull        33
         * 31: aload_1
         * 32: areturn
         * 33: aload_0
         * 34: getfield      org/python/util/PythonInterpreter.globals:Lorg/python/core/PyObject;
         * 37: areturn
         *  */
        // </editor-fold>
    }

     /*public*/ void setLocals(PyObject d) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: getfield      org/python/util/PythonInterpreter.useThreadLocalState:Z
         * 4: ifne          15
         * 7: aload_0
         * 8: aload_1
         * 9: putfield      org/python/util/PythonInterpreter.globals:Lorg/python/core/PyObject;
         * 12: goto          27
         * 15: getstatic     org/python/util/PythonInterpreter.threadLocals:Ljava/lang/ThreadLocal;
         * 18: invokevirtual java/lang/ThreadLocal.get:()Ljava/lang/Object;
         * 21: checkcast     "[Ljava/lang/Object;"
         * 24: iconst_0
         * 25: aload_1
         * 26: aastore
         * 27: return
         *  */
        // </editor-fold>
    }

     /*public*/ void set(QString name, QObject* value) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokevirtual org/python/util/PythonInterpreter.getLocals:()Lorg/python/core/PyObject;
         * 4: aload_1
         * 5: invokevirtual java/lang/String.intern:()Ljava/lang/String;
         * 8: aload_2
         * 9: invokestatic  org/python/core/Py.java2py:(Ljava/lang/Object;)Lorg/python/core/PyObject;
         * 12: invokevirtual org/python/core/PyObject.__setitem__:(Ljava/lang/String;Lorg/python/core/PyObject;)V
         * 15: return
         *  */
        // </editor-fold>
    }

     /*public*/ void set(String name, PyObject value) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokevirtual org/python/util/PythonInterpreter.getLocals:()Lorg/python/core/PyObject;
         * 4: aload_1
         * 5: invokevirtual java/lang/String.intern:()Ljava/lang/String;
         * 8: aload_2
         * 9: invokevirtual org/python/core/PyObject.__setitem__:(Ljava/lang/String;Lorg/python/core/PyObject;)V
         * 12: return
         *  */
        // </editor-fold>
    }

     /*public*/ PyObject get(QString name) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokevirtual org/python/util/PythonInterpreter.getLocals:()Lorg/python/core/PyObject;
         * 4: aload_1
         * 5: invokevirtual java/lang/String.intern:()Ljava/lang/String;
         * 8: invokevirtual org/python/core/PyObject.__finditem__:(Ljava/lang/String;)Lorg/python/core/PyObject;
         * 11: areturn
         *  */
        // </editor-fold>
    }

     /*public*/ <T extends Object> T get(String name, Class<T> javaclass) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokevirtual org/python/util/PythonInterpreter.getLocals:()Lorg/python/core/PyObject;
         * 4: aload_1
         * 5: invokevirtual java/lang/String.intern:()Ljava/lang/String;
         * 8: invokevirtual org/python/core/PyObject.__finditem__:(Ljava/lang/String;)Lorg/python/core/PyObject;
         * 11: astore_3
         * 12: aload_3
         * 13: ifnonnull     18
         * 16: aconst_null
         * 17: areturn
         * 18: aload_3
         * 19: aload_2
         * 20: invokestatic  org/python/core/Py.tojava:(Lorg/python/core/PyObject;Ljava/lang/Class;)Ljava/lang/Object;
         * 23: areturn
         *  */
        // </editor-fold>
    }

     /*public*/ void cleanup() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokevirtual org/python/util/PythonInterpreter.setSystemState:()V
         * 4: invokestatic  org/python/core/Py.getSystemState:()Lorg/python/core/PySystemState;
         * 7: astore_1
         * 8: aload_1
         * 9: invokevirtual org/python/core/PySystemState.callExitFunc:()V
         * 12: aload_1
         * 13: getfield      org/python/core/PySystemState.stdout:Lorg/python/core/PyObject;
         * 16: ldc_w         flush
         * 19: invokevirtual org/python/core/PyObject.invoke:(Ljava/lang/String;)Lorg/python/core/PyObject;
         * 22: pop
         * 23: goto          27
         * 26: astore_2
         * 27: aload_1
         * 28: getfield      org/python/core/PySystemState.stderr:Lorg/python/core/PyObject;
         * 31: ldc_w         flush
         * 34: invokevirtual org/python/core/PyObject.invoke:(Ljava/lang/String;)Lorg/python/core/PyObject;
         * 37: pop
         * 38: goto          42
         * 41: astore_2
         * 42: getstatic     org/python/util/PythonInterpreter.threadLocals:Ljava/lang/ThreadLocal;
         * 45: invokevirtual java/lang/ThreadLocal.remove:()V
         * 48: aload_1
         * 49: invokevirtual org/python/core/PySystemState.cleanup:()V
         * 52: return
         * Exception table:
         * from    to  target type
         * 12    23    26   Class org/python/core/PyException
         * 27    38    41   Class org/python/core/PyException
         *  */
        // </editor-fold>
    }

     /*public*/ void close() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: getfield      org/python/util/PythonInterpreter.closed:Z
         * 4: ifne          16
         * 7: aload_0
         * 8: iconst_1
         * 9: putfield      org/python/util/PythonInterpreter.closed:Z
         * 12: aload_0
         * 13: invokevirtual org/python/util/PythonInterpreter.cleanup:()V
         * 16: return
         *  */
        // </editor-fold>
    }
#endif
};
#endif // PYTHONINTERPRETER_H
