#include "fileinputstream.h"
#include <QFile>
#include "file.h"
/**
 * A <code>FileInputStream</code> obtains input bytes
 * from a file in a file system. What files
 * are  available depends on the host environment.
 *
 * <p><code>FileInputStream</code> is meant for reading streams of raw bytes
 * such as image data. For reading streams of characters, consider using
 * <code>FileReader</code>.
 *
 * @author  Arthur van Hoff
 * @see     java.io.File
 * @see     java.io.FileDescriptor
 * @see     java.io.FileOutputStream
 * @see     java.nio.file.Files#newInputStream
 * @since   JDK1.0
 */
///*public*/
//class FileInputStream extends InputStream
//{

/**
 * Creates a <code>FileInputStream</code> by
 * opening a connection to an actual file,
 * the file named by the path name <code>name</code>
 * in the file system.  A new <code>FileDescriptor</code>
 * object is created to represent this file
 * connection.
 * <p>
 * First, if there is a security
 * manager, its <code>checkRead</code> method
 * is called with the <code>name</code> argument
 * as its argument.
 * <p>
 * If the named file does not exist, is a directory rather than a regular
 * file, or for some other reason cannot be opened for reading then a
 * <code>FileNotFoundException</code> is thrown.
 *
 * @param      name   the system-dependent file name.
 * @exception  FileNotFoundException  if the file does not exist,
 *                   is a directory rather than a regular file,
 *                   or for some other reason cannot be opened for
 *                   reading.
 * @exception  SecurityException      if a security manager exists and its
 *               <code>checkRead</code> method denies read access
 *               to the file.
 * @see        java.lang.SecurityManager#checkRead(java.lang.String)
 */
/*public*/ FileInputStream::FileInputStream(QString name, QObject* parent) /*throw (FileNotFoundException)*/ {
    //this(name != NULL ? new File(name) : NULL);
 if(name == "")
  common(NULL);
 else
  common(new File(name));
}

/**
 * Creates a <code>FileInputStream</code> by
 * opening a connection to an actual file,
 * the file named by the <code>File</code>
 * object <code>file</code> in the file system.
 * A new <code>FileDescriptor</code> object
 * is created to represent this file connection.
 * <p>
 * First, if there is a security manager,
 * its <code>checkRead</code> method  is called
 * with the path represented by the <code>file</code>
 * argument as its argument.
 * <p>
 * If the named file does not exist, is a directory rather than a regular
 * file, or for some other reason cannot be opened for reading then a
 * <code>FileNotFoundException</code> is thrown.
 *
 * @param      file   the file to be opened for reading.
 * @exception  FileNotFoundException  if the file does not exist,
 *                   is a directory rather than a regular file,
 *                   or for some other reason cannot be opened for
 *                   reading.
 * @exception  SecurityException      if a security manager exists and its
 *               <code>checkRead</code> method denies read access to the file.
 * @see        java.io.File#getPath()
 * @see        java.lang.SecurityManager#checkRead(java.lang.String)
 */
/*public*/ FileInputStream::FileInputStream(File* file, QObject* parent) throw (FileNotFoundException) : QDataStream()
{
 common(file);
}

void FileInputStream::common(File * file)
{
    QString name = (file != NULL ? file->getPath() : NULL);
//    SecurityManager security = System.getSecurityManager();
//    if (security != NULL) {
//        security.checkRead(name);
//    }
    if (name == NULL) {
        throw new NullPointerException();
    }
    if (file->isInvalid()) {
        throw new FileNotFoundException("Invalid file path");
    }
//    fd = new FileDescriptor();
//    fd.attach(this);
    path = name;
    open(name);
}
#if 0
/**
 * Creates a <code>FileInputStream</code> by using the file descriptor
 * <code>fdObj</code>, which represents an existing connection to an
 * actual file in the file system.
 * <p>
 * If there is a security manager, its <code>checkRead</code> method is
 * called with the file descriptor <code>fdObj</code> as its argument to
 * see if it's ok to read the file descriptor. If read access is denied
 * to the file descriptor a <code>SecurityException</code> is thrown.
 * <p>
 * If <code>fdObj</code> is NULL then a <code>NullPointerException</code>
 * is thrown.
 * <p>
 * This constructor does not throw an exception if <code>fdObj</code>
 * is {@link java.io.FileDescriptor#valid() invalid}.
 * However, if the methods are invoked on the resulting stream to attempt
 * I/O on the stream, an <code>IOException</code> is thrown.
 *
 * @param      fdObj   the file descriptor to be opened for reading.
 * @throws     SecurityException      if a security manager exists and its
 *                 <code>checkRead</code> method denies read access to the
 *                 file descriptor.
 * @see        SecurityManager#checkRead(java.io.FileDescriptor)
 */
/*public*/ FileInputStream(FileDescriptor fdObj) {
    SecurityManager security = System.getSecurityManager();
    if (fdObj == NULL) {
        throw new NullPointerException();
    }
    if (security != NULL) {
        security.checkRead(fdObj);
    }
    fd = fdObj;
    path = NULL;

    /*
     * FileDescriptor is being shared by streams.
     * Register this stream with FileDescriptor tracker.
     */
    fd.attach(this);
}

/**
 * Opens the specified file for reading.
 * @param name the name of the file
 */
/*private*/ /*native*/ void open0(String name) throws FileNotFoundException;
#endif
// wrap native call to allow instrumentation
/**
 * Opens the specified file for reading.
 * @param name the name of the file
 */
/*private*/ void FileInputStream::open(QString name) /*throw (FileNotFoundException)*/ {
   // open0(name);
 QFile f(name);
 if(!f.open(QIODevice::ReadOnly))
   throw new FileNotFoundException(QString("error opening %1 %2").arg(name).arg(f.errorString()));
}

/**
 * Reads a byte of data from this input stream. This method blocks
 * if no input is yet available.
 *
 * @return     the next byte of data, or <code>-1</code> if the end of the
 *             file is reached.
 * @exception  IOException  if an I/O error occurs.
 */
/*public*/ QChar FileInputStream::read() /*throw (IOException)*/ {
// if(this->atEnd())
//  return -1;

    return read0();
}

/*private*/ /*native*/ int FileInputStream::read0() /*throw (IOException)*/
{
 char* buf = new char[2];
 if(this->readRawData(buf, 1) < 0)
  return -1;
 return buf[0];

}
#if 0
/**
 * Reads a subarray as a sequence of bytes.
 * @param b the data to be written
 * @param off the start offset in the data
 * @param len the number of bytes that are written
 * @exception IOException If an I/O error has occurred.
 */
/*private*/ native int readBytes(byte b[], int off, int len) throws IOException;

/**
 * Reads up to <code>b.length</code> bytes of data from this input
 * stream into an array of bytes. This method blocks until some input
 * is available.
 *
 * @param      b   the buffer into which the data is read.
 * @return     the total number of bytes read into the buffer, or
 *             <code>-1</code> if there is no more data because the end of
 *             the file has been reached.
 * @exception  IOException  if an I/O error occurs.
 */
/*public*/ int read(byte b[]) throws IOException {
    return readBytes(b, 0, b.length);
}

/**
 * Reads up to <code>len</code> bytes of data from this input stream
 * into an array of bytes. If <code>len</code> is not zero, the method
 * blocks until some input is available; otherwise, no
 * bytes are read and <code>0</code> is returned.
 *
 * @param      b     the buffer into which the data is read.
 * @param      off   the start offset in the destination array <code>b</code>
 * @param      len   the maximum number of bytes read.
 * @return     the total number of bytes read into the buffer, or
 *             <code>-1</code> if there is no more data because the end of
 *             the file has been reached.
 * @exception  NullPointerException If <code>b</code> is <code>NULL</code>.
 * @exception  IndexOutOfBoundsException If <code>off</code> is negative,
 * <code>len</code> is negative, or <code>len</code> is greater than
 * <code>b.length - off</code>
 * @exception  IOException  if an I/O error occurs.
 */
/*public*/ int read(byte b[], int off, int len) throws IOException {
    return readBytes(b, off, len);
}

/**
 * Skips over and discards <code>n</code> bytes of data from the
 * input stream.
 *
 * <p>The <code>skip</code> method may, for a variety of
 * reasons, end up skipping over some smaller number of bytes,
 * possibly <code>0</code>. If <code>n</code> is negative, the method
 * will try to skip backwards. In case the backing file does not support
 * backward skip at its current position, an <code>IOException</code> is
 * thrown. The actual number of bytes skipped is returned. If it skips
 * forwards, it returns a positive value. If it skips backwards, it
 * returns a negative value.
 *
 * <p>This method may skip more bytes than what are remaining in the
 * backing file. This produces no exception and the number of bytes skipped
 * may include some number of bytes that were beyond the EOF of the
 * backing file. Attempting to read from the stream after skipping past
 * the end will result in -1 indicating the end of the file.
 *
 * @param      n   the number of bytes to be skipped.
 * @return     the actual number of bytes skipped.
 * @exception  IOException  if n is negative, if the stream does not
 *             support seek, or if an I/O error occurs.
 */
/*public*/ native long skip(long n) throws IOException;

/**
 * Returns an estimate of the number of remaining bytes that can be read (or
 * skipped over) from this input stream without blocking by the next
 * invocation of a method for this input stream. Returns 0 when the file
 * position is beyond EOF. The next invocation might be the same thread
 * or another thread. A single read or skip of this many bytes will not
 * block, but may read or skip fewer bytes.
 *
 * <p> In some cases, a non-blocking read (or skip) may appear to be
 * blocked when it is merely slow, for example when reading large
 * files over slow networks.
 *
 * @return     an estimate of the number of remaining bytes that can be read
 *             (or skipped over) from this input stream without blocking.
 * @exception  IOException  if this file input stream has been closed by calling
 *             {@code close} or an I/O error occurs.
 */
/*public*/ native int available() throws IOException;
#endif
/**
 * Closes this file input stream and releases any system resources
 * associated with the stream.
 *
 * <p> If this stream has an associated channel then the channel is closed
 * as well.
 *
 * @exception  IOException  if an I/O error occurs.
 *
 * @revised 1.4
 * @spec JSR-51
 */
/*public*/ void FileInputStream::close() /*throw (IOException)*/ {
#if 0
    synchronized (closeLock) {
        if (closed) {
            return;
        }
        closed = true;
    }
    if (channel != NULL) {
       channel.close();
    }

    fd.closeAll(new Closeable() {
        /*public*/ void close() throws IOException {
           close0();
       }
    });
#endif
}
#if 0
/**
 * Returns the <code>FileDescriptor</code>
 * object  that represents the connection to
 * the actual file in the file system being
 * used by this <code>FileInputStream</code>.
 *
 * @return     the file descriptor object associated with this stream.
 * @exception  IOException  if an I/O error occurs.
 * @see        java.io.FileDescriptor
 */
/*public*/ /*final*/ FileDescriptor getFD() throws IOException {
    if (fd != NULL) {
        return fd;
    }
    throw new IOException();
}

/**
 * Returns the unique {@link java.nio.channels.FileChannel FileChannel}
 * object associated with this file input stream.
 *
 * <p> The initial {@link java.nio.channels.FileChannel#position()
 * position} of the returned channel will be equal to the
 * number of bytes read from the file so far.  Reading bytes from this
 * stream will increment the channel's position.  Changing the channel's
 * position, either explicitly or by reading, will change this stream's
 * file position.
 *
 * @return  the file channel associated with this file input stream
 *
 * @since 1.4
 * @spec JSR-51
 */
/*public*/ FileChannel getChannel() {
    synchronized (this) {
        if (channel == NULL) {
            channel = FileChannelImpl.open(fd, path, true, false, this);
        }
        return channel;
    }
}

/*private*/ static native void initIDs();

/*private*/ native void close0() throws IOException;

static {
    initIDs();
}

/**
 * Ensures that the <code>close</code> method of this file input stream is
 * called when there are no more references to it.
 *
 * @exception  IOException  if an I/O error occurs.
 * @see        java.io.FileInputStream#close()
 */
protected void /*final*/ize() throws IOException {
    if ((fd != NULL) &&  (fd != FileDescriptor.in)) {
        /* if fd is shared, the references in FileDescriptor
         * will ensure that /*final*/izer is only called when
         * safe to do so. All references using the fd have
         * become unreachable. We can call close()
         */
        close();
    }
}
#endif
