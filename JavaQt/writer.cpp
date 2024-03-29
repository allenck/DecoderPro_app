#include "writer.h"

/**
 * Abstract class for writing to character streams.  The only methods that a
 * subclass must implement are write(char[], int, int), flush(), and close().
 * Most subclasses, however, will override some of the methods defined here in
 * order to provide higher efficiency, additional functionality, or both.
 *
 * @see Writer
 * @see   BufferedWriter
 * @see   CharArrayWriter
 * @see   FilterWriter
 * @see   OutputStreamWriter
 * @see     FileWriter
 * @see   PipedWriter
 * @see   PrintWriter
 * @see   StringWriter
 * @see Reader
 *
 * @author      Mark Reinhold
 * @since       JDK1.1
 */

///*public*/ abstract class Writer implements Appendable, Closeable, Flushable {
/**
 * Size of writeBuffer, must be >= 1
 */
/*private*/ /*static*/ /*final*/ int Writer::WRITE_BUFFER_SIZE = 1024;


/**
 * Creates a new character-stream writer whose critical sections will
 * synchronize on the writer itself.
 */
/*protected*/ Writer::Writer() {
    this->lock = (QObject*)this;
}

/**
 * Creates a new character-stream writer whose critical sections will
 * synchronize on the given object.
 *
 * @param  lock
 *         Object to synchronize on
 */
/*protected*/ Writer::Writer(QObject* lock) {
//    if (lock == null) {
//        throw new NullPointerException();
//    }
    this->lock = lock;
}
#if 0
/**
 * Writes a single character.  The character to be written is contained in
 * the 16 low-order bits of the given integer value; the 16 high-order bits
 * are ignored.
 *
 * <p> Subclasses that intend to support efficient single-character output
 * should override this method.
 *
 * @param  c
 *         int specifying a character to be written
 *
 * @throws  IOException
 *          If an I/O error occurs
 */
/*public*/ void write(int c) throws IOException {
    synchronized (lock) {
        if (writeBuffer == null){
            writeBuffer = new char[WRITE_BUFFER_SIZE];
        }
        writeBuffer[0] = (char) c;
        write(writeBuffer, 0, 1);
    }
}
#endif
/**
 * Writes an array of characters.
 *
 * @param  cbuf
 *         Array of characters to be written
 *
 * @throws  IOException
 *          If an I/O error occurs
 */
/*public*/ void Writer::write(QByteArray cbuf) /*throw (IOException)*/ {
    write(cbuf, 0, cbuf.length());
}
#if 0
/**
 * Writes a portion of an array of characters.
 *
 * @param  cbuf
 *         Array of characters
 *
 * @param  off
 *         Offset from which to start writing characters
 *
 * @param  len
 *         Number of characters to write
 *
 * @throws  IOException
 *          If an I/O error occurs
 */
abstract /*public*/ void write(char cbuf[], int off, int len) throws IOException;
#endif
/**
 * Writes a string.
 *
 * @param  str
 *         String to be written
 *
 * @throws  IOException
 *          If an I/O error occurs
 */
/*public*/ void Writer::write(QString str) /*throw (IOException)*/
{
    //write(str, 0, str.length());
 //setString(&str);
 *this << str;
}
#if 0
/**
 * Writes a portion of a string.
 *
 * @param  str
 *         A String
 *
 * @param  off
 *         Offset from which to start writing characters
 *
 * @param  len
 *         Number of characters to write
 *
 * @throws  IndexOutOfBoundsException
 *          If <tt>off</tt> is negative, or <tt>len</tt> is negative,
 *          or <tt>off+len</tt> is negative or greater than the length
 *          of the given string
 *
 * @throws  IOException
 *          If an I/O error occurs
 */
/*public*/ void write(String str, int off, int len) throws IOException {
    synchronized (lock) {
        char cbuf[];
        if (len <= WRITE_BUFFER_SIZE) {
            if (writeBuffer == null) {
                writeBuffer = new char[WRITE_BUFFER_SIZE];
            }
            cbuf = writeBuffer;
        } else {    // Don't permanently allocate very large buffers.
            cbuf = new char[len];
        }
        str.getChars(off, (off + len), cbuf, 0);
        write(cbuf, 0, len);
    }
}

/**
 * Appends the specified character sequence to this writer.
 *
 * <p> An invocation of this method of the form <tt>out.append(csq)</tt>
 * behaves in exactly the same way as the invocation
 *
 * <pre>
 *     out.write(csq.toString()) </pre>
 *
 * <p> Depending on the specification of <tt>toString</tt> for the
 * character sequence <tt>csq</tt>, the entire sequence may not be
 * appended. For instance, invoking the <tt>toString</tt> method of a
 * character buffer will return a subsequence whose content depends upon
 * the buffer's position and limit.
 *
 * @param  csq
 *         The character sequence to append.  If <tt>csq</tt> is
 *         <tt>null</tt>, then the four characters <tt>"null"</tt> are
 *         appended to this writer.
 *
 * @return  This writer
 *
 * @throws  IOException
 *          If an I/O error occurs
 *
 * @since  1.5
 */
/*public*/ Writer append(CharSequence csq) throws IOException {
    if (csq == null)
        write("null");
    else
        write(csq.toString());
    return this;
}

/**
 * Appends a subsequence of the specified character sequence to this writer.
 * <tt>Appendable</tt>.
 *
 * <p> An invocation of this method of the form <tt>out.append(csq, start,
 * end)</tt> when <tt>csq</tt> is not <tt>null</tt> behaves in exactly the
 * same way as the invocation
 *
 * <pre>
 *     out.write(csq.subSequence(start, end).toString()) </pre>
 *
 * @param  csq
 *         The character sequence from which a subsequence will be
 *         appended.  If <tt>csq</tt> is <tt>null</tt>, then characters
 *         will be appended as if <tt>csq</tt> contained the four
 *         characters <tt>"null"</tt>.
 *
 * @param  start
 *         The index of the first character in the subsequence
 *
 * @param  end
 *         The index of the character following the last character in the
 *         subsequence
 *
 * @return  This writer
 *
 * @throws  IndexOutOfBoundsException
 *          If <tt>start</tt> or <tt>end</tt> are negative, <tt>start</tt>
 *          is greater than <tt>end</tt>, or <tt>end</tt> is greater than
 *          <tt>csq.length()</tt>
 *
 * @throws  IOException
 *          If an I/O error occurs
 *
 * @since  1.5
 */
/*public*/ Writer append(CharSequence csq, int start, int end) throws IOException {
    CharSequence cs = (csq == null ? "null" : csq);
    write(cs.subSequence(start, end).toString());
    return this;
}

/**
 * Appends the specified character to this writer.
 *
 * <p> An invocation of this method of the form <tt>out.append(c)</tt>
 * behaves in exactly the same way as the invocation
 *
 * <pre>
 *     out.write(c) </pre>
 *
 * @param  c
 *         The 16-bit character to append
 *
 * @return  This writer
 *
 * @throws  IOException
 *          If an I/O error occurs
 *
 * @since 1.5
 */
/*public*/ Writer append(char c) throws IOException {
    write(c);
    return this;
}
#endif
/**
 * Flushes the stream.  If the stream has saved any characters from the
 * various write() methods in a buffer, write them immediately to their
 * intended destination.  Then, if that destination is another character or
 * byte stream, flush it.  Thus one flush() invocation will flush all the
 * buffers in a chain of Writers and OutputStreams.
 *
 * <p> If the intended destination of this stream is an abstraction provided
 * by the underlying operating system, for example a file, then flushing the
 * stream guarantees only that bytes previously written to the stream are
 * passed to the operating system for writing; it does not guarantee that
 * they are actually written to a physical device such as a disk drive.
 *
 * @throws  IOException
 *          If an I/O error occurs
 */
///*abstract*/ /*public*/ void Writer::flush() {}//throws IOException;

/**
 * Closes the stream, flushing it first. Once the stream has been closed,
 * further write() or flush() invocations will cause an IOException to be
 * thrown. Closing a previously closed stream has no effect.
 *
 * @throws  IOException
 *          If an I/O error occurs
 */
/*abstract*/ /*public*/ void Writer::close()  /*throw (IOException)*/ {}

