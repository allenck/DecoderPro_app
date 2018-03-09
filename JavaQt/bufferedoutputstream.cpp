#include "bufferedoutputstream.h"

/**
 * The class implements a buffered output stream. By setting up such
 * an output stream, an application can write bytes to the underlying
 * output stream without necessarily causing a call to the underlying
 * system for each byte written.
 *
 * @author  Arthur van Hoff
 * @since   JDK1.0
 */
/*public*/
//class BufferedOutputStream extends FilterOutputStream {

/**
 * Creates a new buffered output stream to write data to the
 * specified underlying output stream.
 *
 * @param   out   the underlying output stream.
 */
/*public*/ BufferedOutputStream::BufferedOutputStream(QDataStream* out, QObject* parent) : QObject(parent)
{
    common(out, 8192);
}

/**
 * Creates a new buffered output stream to write data to the
 * specified underlying output stream with the specified buffer
 * size.
 *
 * @param   out    the underlying output stream.
 * @param   size   the buffer size.
 * @exception IllegalArgumentException if size &lt;= 0.
 */
/*public*/ BufferedOutputStream::BufferedOutputStream(QDataStream* out, int size, QObject* parent) {
    //super(out);
 common(out, size);
}

void BufferedOutputStream::common(QDataStream *out, int size)
{
 this->out = out;
 if (size <= 0) {
        throw new IllegalArgumentException("Buffer size <= 0");
    }
    buf = QByteArray(size, '\0');
}

/** Flush the internal buffer */
/*private*/ void BufferedOutputStream::flushBuffer() throw (IOException)
{
 if (count > 0) {
     out->writeRawData(buf.constData(), count);
     count = 0;
 }
}

/**
 * Writes the specified byte to this buffered output stream.
 *
 * @param      b   the byte to be written.
 * @exception  IOException  if an I/O error occurs.
 */
/*public*/ /*synchronized*/ void BufferedOutputStream::write(int b) throw (IOException) {
    if (count >= buf.length()) {
        flushBuffer();
    }
    buf[count++] = (char)b;
}
#if 0
/**
 * Writes <code>len</code> bytes from the specified byte array
 * starting at offset <code>off</code> to this buffered output stream.
 *
 * <p> Ordinarily this method stores bytes from the given array into this
 * stream's buffer, flushing the buffer to the underlying output stream as
 * needed.  If the requested length is at least as large as this stream's
 * buffer, however, then this method will flush the buffer and write the
 * bytes directly to the underlying output stream.  Thus redundant
 * <code>BufferedOutputStream</code>s will not copy data unnecessarily.
 *
 * @param      b     the data.
 * @param      off   the start offset in the data.
 * @param      len   the number of bytes to write.
 * @exception  IOException  if an I/O error occurs.
 */
/*public*/ synchronized void write(byte b[], int off, int len) throws IOException {
    if (len >= buf.length) {
        /* If the request length exceeds the size of the output buffer,
           flush the output buffer and then write the data directly.
           In this way buffered streams will cascade harmlessly. */
        flushBuffer();
        out.write(b, off, len);
        return;
    }
    if (len > buf.length - count) {
        flushBuffer();
    }
    System.arraycopy(b, off, buf, count, len);
    count += len;
}
#endif
/**
 * Flushes this buffered output stream. This forces any buffered
 * output bytes to be written out to the underlying output stream.
 *
 * @exception  IOException  if an I/O error occurs.
 * @see        java.io.FilterOutputStream#out
 */
/*public*/ /*synchronized*/ void BufferedOutputStream::flush() throw (IOException) {
    flushBuffer();
    //out->flush();
}

/**
 * Closes this output stream and releases any system resources
 * associated with the stream.
 * <p>
 * The <code>close</code> method of <code>FilterOutputStream</code>
 * calls its <code>flush</code> method, and then calls the
 * <code>close</code> method of its underlying output stream.
 *
 * @exception  IOException  if an I/O error occurs.
 * @see        java.io.FilterOutputStream#flush()
 * @see        java.io.FilterOutputStream#out
 */
//@SuppressWarnings("try")
/*public*/ void BufferedOutputStream::close() throw (IOException) {
//    try (OutputStream* ostream = out) {
//        flush();
//    }
 flush();
 out->device()->close();
}
