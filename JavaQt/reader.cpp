#include "reader.h"
#include <qmath.h>
/**
 * Abstract class for reading character streams.  The only methods that a
 * subclass must implement are read(char[], int, int) and close().  Most
 * subclasses, however, will override some of the methods defined here in order
 * to provide higher efficiency, additional functionality, or both.
 *
 *
 * @see BufferedReader
 * @see   LineNumberReader
 * @see CharArrayReader
 * @see InputStreamReader
 * @see   FileReader
 * @see FilterReader
 * @see   PushbackReader
 * @see PipedReader
 * @see StringReader
 * @see Writer
 *
 * @author      Mark Reinhold
 * @since       JDK1.1
 */

// /*public*/ abstract class Reader implements Readable, Closeable {

/*private*/ /*static*/ /*final*/ int Reader::maxSkipBufferSize = 8192;

/**
 * Creates a new character-stream reader whose critical sections will
 * synchronize on the reader itself.
 */
/*protected*/ Reader::Reader(QObject* parent) : QObject(parent) {
    this->lock = this;
}

/**
 * Creates a new character-stream reader whose critical sections will
 * synchronize on the given object.
 *
 * @param lock  The Object to synchronize on.
 */
/*protected*/ Reader::Reader(QObject* lock, QObject* parent) : QObject(parent) {
    if (lock == NULL) {
        throw new NullPointerException();
    }
    this->lock = lock;
}

/**
 * Attempts to read characters into the specified character buffer.
 * The buffer is used as a repository of characters as-is: the only
 * changes made are the results of a put operation. No flipping or
 * rewinding of the buffer is performed.
 *
 * @param target the buffer to read characters into
 * @return The number of characters added to the buffer, or
 *         -1 if this source of characters is at its end
 * @throws IOException if an I/O error occurs
 * @throws NullPointerException if target is NULL
 * @throws java.nio.ReadOnlyBufferException if target is a read only buffer
 * @since 1.5
 */
/*public*/ int Reader::read(CharBuffer* target) /*throw (IOException)*/ {
    int len = target->remaining();
    QByteArray cbuf = QByteArray(len,0);
    int n = read(cbuf, 0, len);
    if (n > 0)
        target->put(cbuf, 0, n);
    return n;
}

/**
 * Reads a single character.  This method will block until a character is
 * available, an I/O error occurs, or the end of the stream is reached.
 *
 * <p> Subclasses that intend to support efficient single-character input
 * should override this method.
 *
 * @return     The character read, as an integer in the range 0 to 65535
 *             (<tt>0x00-0xffff</tt>), or -1 if the end of the stream has
 *             been reached
 *
 * @exception  IOException  If an I/O error occurs
 */
/*public*/ int Reader::read() /*throw (IOException)*/ {
    QByteArray cb = QByteArray(1,0);
    if (read(cb, 0, 1) == -1)
        return -1;
    else
        return cb[0];
}

/**
 * Reads characters into an array.  This method will block until some input
 * is available, an I/O error occurs, or the end of the stream is reached.
 *
 * @param       cbuf  Destination buffer
 *
 * @return      The number of characters read, or -1
 *              if the end of the stream
 *              has been reached
 *
 * @exception   IOException  If an I/O error occurs
 */
/*public*/ int Reader::read(QByteArray cbuf) /*throw (IOException)*/ {
    return read(cbuf, 0, cbuf.length());
}

/**
 * Reads characters into a portion of an array.  This method will block
 * until some input is available, an I/O error occurs, or the end of the
 * stream is reached.
 *
 * @param      cbuf  Destination buffer
 * @param      off   Offset at which to start storing characters
 * @param      len   Maximum number of characters to read
 *
 * @return     The number of characters read, or -1 if the end of the
 *             stream has been reached
 *
 * @exception  IOException  If an I/O error occurs
 */
/*abstract*/ /*public*/ int Reader::read(QByteArray cbuf, int off, int len) /*throw (IOException)*/ {return 0;}


/** Skip buffer, NULL until allocated */
/*private*/ QByteArray skipBuffer = NULL;

/**
 * Skips characters.  This method will block until some characters are
 * available, an I/O error occurs, or the end of the stream is reached.
 *
 * @param  n  The number of characters to skip
 *
 * @return    The number of characters actually skipped
 *
 * @exception  IllegalArgumentException  If <code>n</code> is negative.
 * @exception  IOException  If an I/O error occurs
 */
/*public*/ long Reader::skip(long n) /*throw (IOException)*/ {
    if (n < 0L)
        throw new IllegalArgumentException("skip value is negative");
    int nn = (int) qMin((int)n, (int)maxSkipBufferSize);
//    synchronized (lock)
    {
        if ((skipBuffer == NULL) || (skipBuffer.length() < nn))
            skipBuffer = new char[nn];
        long r = n;
        while (r > 0) {
            int nc = read(skipBuffer, 0, (int)qMin((int)r, (int)nn));
            if (nc == -1)
                break;
            r -= nc;
        }
        return n - r;
    }
}

/**
 * Tells whether this stream is ready to be read.
 *
 * @return True if the next read() is guaranteed not to block for input,
 * false otherwise.  Note that returning false does not guarantee that the
 * next read will block.
 *
 * @exception  IOException  If an I/O error occurs
 */
/*public*/ bool Reader::ready() /*throw (IOException)*/ {
    return false;
}

/**
 * Tells whether this stream supports the mark() operation. The default
 * implementation always returns false. Subclasses should override this
 * method.
 *
 * @return true if and only if this stream supports the mark operation.
 */
/*public*/ bool Reader::markSupported() {
    return false;
}

/**
 * Marks the present position in the stream.  Subsequent calls to reset()
 * will attempt to reposition the stream to this point.  Not all
 * character-input streams support the mark() operation.
 *
 * @param  readAheadLimit  Limit on the number of characters that may be
 *                         read while still preserving the mark.  After
 *                         reading this many characters, attempting to
 *                         reset the stream may fail.
 *
 * @exception  IOException  If the stream does not support mark(),
 *                          or if some other I/O error occurs
 */
/*public*/ void Reader::mark(int /*readAheadLimit*/) /*throw (IOException)*/ {
    throw new IOException("mark() not supported");
}

/**
 * Resets the stream.  If the stream has been marked, then attempt to
 * reposition it at the mark.  If the stream has not been marked, then
 * attempt to reset it in some way appropriate to the particular stream,
 * for example by repositioning it to its starting point.  Not all
 * character-input streams support the reset() operation, and some support
 * reset() without supporting mark().
 *
 * @exception  IOException  If the stream has not been marked,
 *                          or if the mark has been invalidated,
 *                          or if the stream does not support reset(),
 *                          or if some other I/O error occurs
 */
/*public*/ void Reader::reset() /*throw (IOException)*/ {
    throw new IOException("reset() not supported");
}

/**
 * Closes the stream and releases any system resources associated with
 * it.  Once the stream has been closed, further read(), ready(),
 * mark(), reset(), or skip() invocations will throw an IOException.
 * Closing a previously closed stream has no effect.
 *
 * @exception  IOException  If an I/O error occurs
 */
/*abstract*/ /*public*/ void Reader::close() /*throw (IOException)*/ {}

