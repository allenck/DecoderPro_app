#include "resource.h"
#include "loggerfactory.h"
#include <QUrl>
#include <QFileInfo>
#include <QDir>
#include "uriutil.h"
#include "stringutil.h"

Resource::Resource(QObject *parent) : QObject(parent)
{

}
//
//  ========================================================================
//  Copyright (c) 1995-2014 Mort Bay Consulting Pty. Ltd.
//  ------------------------------------------------------------------------
//  All rights reserved. This program and the accompanying materials
//  are made available under the terms of the Eclipse Public License v1.0
//  and Apache License v2.0 which accompanies this distribution.
//
//      The Eclipse Public License is available at
//      http://www.eclipse.org/legal/epl-v10.html
//
//      The Apache License v2.0 is available at
//      http://www.opensource.org/licenses/apache2.0.php
//
//  You may elect to redistribute this code under either of these licenses.
//  ========================================================================
//


/* ------------------------------------------------------------ */
/**
 * Abstract resource class.
 * <p>
 * This class provides a resource abstraction, where a resource may be
 * a file, a URL or an entry in a jar file.
 * </p>
 */
///*public*/ abstract class Resource implements ResourceFactory, Closeable
//{
    /*private*/ /*static*/ /*final*/ Logger*
Resource::log = LoggerFactory::getLogger("Resource");
    /*public*/ /*static*/ bool
Resource::__defaultUseCaches = true;
//    volatile Object _associate;
#if 0
    /* ------------------------------------------------------------ */
    /**
     * Change the default setting for url connection caches.
     * Subsequent URLConnections will use this default.
     * @param useCaches
     */
    /*public*/ static void setDefaultUseCaches (boolean useCaches)
    {
        __defaultUseCaches=useCaches;
    }

    /* ------------------------------------------------------------ */
    /*public*/ static boolean getDefaultUseCaches ()
    {
        return __defaultUseCaches;
    }

    /* ------------------------------------------------------------ */
    /** Construct a resource from a uri.
     * @param uri A URI.
     * @return A Resource object.
     * @throws MalformedURLException Problem accessing URI
     */
    /*public*/ static Resource newResource(URI uri)
        throws MalformedURLException
    {
        return newResource(uri.toURL());
    }
#endif
    /* ------------------------------------------------------------ */
    /** Construct a resource from a url.
     * @param url A URL.
     * @return A Resource object.
     */
    /*public*/ /*static*/ Resource* Resource::newResource(QUrl url)
    {
        return newResource(url, __defaultUseCaches);
    }

    /* ------------------------------------------------------------ */
    /**
     * Construct a resource from a url.
     * @param url the url for which to make the resource
     * @param useCaches true enables URLConnection caching if applicable to the type of resource
     * @return
     */
    /*static*/ Resource* Resource::newResource(QUrl url, bool /*useCaches*/)
    {
        if (url.isEmpty())
            return NULL;
#if 0
        QString url_string=url.toExternalForm();
        if( url_string.startsWith( "file:"))
        {
            try
            {
                FileResource fileResource= new FileResource(url);
                return fileResource;
            }
            catch(Exception e)
            {
                LOG.warn(e.toString());
                LOG.debug(Log.EXCEPTION,e);
                return new BadResource(url,e.toString());
            }
        }
        else if( url_string.startsWith( "jar:file:"))
        {
            return new JarFileResource(url, useCaches);
        }
        else if( url_string.startsWith( "jar:"))
        {
            return new JarResource(url, useCaches);
        }

        return new URLResource(url,null,useCaches);
#endif
        return NULL;
    }



    /* ------------------------------------------------------------ */
    /** Construct a resource from a string.
     * @param resource A URL or filename.
     * @throws MalformedURLException Problem accessing URI
     * @return A Resource object.
     */
    /*public*/ /*static*/ Resource* Resource::newResource(QString resource)
        throw (MalformedURLException)
    {
     stringResource = resource;
        return newResource(resource, __defaultUseCaches);
    }

    /* ------------------------------------------------------------ */
    /** Construct a resource from a string.
     * @param resource A URL or filename.
     * @param useCaches controls URLConnection caching
     * @return A Resource object.
     * @throws MalformedURLException Problem accessing URI
     */
    /*public*/ /*static*/ Resource* Resource::newResource(QString resource, bool /*useCaches*/)
        throw (MalformedURLException)
    {
        QUrl url;
        try
        {
            // Try to format as a URL?
            url =  QUrl(resource);
            if(!url.isValid())
             throw MalformedURLException(tr("invalid url %s").arg(resource));
        }
        catch(MalformedURLException e)
        {
#if 0
            if(!resource.startsWith("ftp:") &&
               !resource.startsWith("file:") &&
               !resource.startsWith("jar:"))
            {
                try
                {
                    // It's a file.
                    if (resource.startsWith("./"))
                        resource=resource.substring(2);

                    File file=new File(resource).getCanonicalFile();
                    return new FileResource(file);
                }
                catch(Exception e2)
                {
                    LOG.debug(Log.EXCEPTION,e2);
                    throw e;
                }
            }
            else
            {
                LOG.warn("Bad Resource: "+resource);
                throw e;
            }
#endif
        }

        return newResource(url);
    }
#if 0
    /* ------------------------------------------------------------ */
    /*public*/ static Resource newResource(File file)
    {
        return new FileResource(file);
    }

    /* ------------------------------------------------------------ */
    /** Construct a system resource from a string.
     * The resource is tried as classloader resource before being
     * treated as a normal resource.
     * @param resource Resource as string representation
     * @return The new Resource
     * @throws IOException Problem accessing resource.
     */
    /*public*/ static Resource newSystemResource(String resource)
        throws IOException
    {
        URL url=null;
        // Try to format as a URL?
        ClassLoader loader=Thread.currentThread().getContextClassLoader();
        if (loader!=null)
        {
            try
            {
                url = loader.getResource(resource);
                if (url == null && resource.startsWith("/"))
                    url = loader.getResource(resource.substring(1));
            }
            catch (IllegalArgumentException e)
            {
                // Catches scenario where a bad Windows path like "C:\dev" is
                // improperly escaped, which various downstream classloaders
                // tend to have a problem with
                url = null;
            }
        }
        if (url==null)
        {
            loader=Resource.class.getClassLoader();
            if (loader!=null)
            {
                url=loader.getResource(resource);
                if (url==null && resource.startsWith("/"))
                    url=loader.getResource(resource.substring(1));
            }
        }

        if (url==null)
        {
            url=ClassLoader.getSystemResource(resource);
            if (url==null && resource.startsWith("/"))
                url=ClassLoader.getSystemResource(resource.substring(1));
        }

        if (url==null)
            return null;

        return newResource(url);
    }

    /* ------------------------------------------------------------ */
    /** Find a classpath resource.
     */
    /*public*/ static Resource newClassPathResource(String resource)
    {
        return newClassPathResource(resource,true,false);
    }

    /* ------------------------------------------------------------ */
    /** Find a classpath resource.
     * The {@link java.lang.Class#getResource(String)} method is used to lookup the resource. If it is not
     * found, then the {@link Loader#getResource(Class, String)} method is used.
     * If it is still not found, then {@link ClassLoader#getSystemResource(String)} is used.
     * Unlike {@link ClassLoader#getSystemResource(String)} this method does not check for normal resources.
     * @param name The relative name of the resource
     * @param useCaches True if URL caches are to be used.
     * @param checkParents True if forced searching of parent Classloaders is performed to work around
     * loaders with inverted priorities
     * @return Resource or null
     */
    /*public*/ static Resource newClassPathResource(String name,boolean useCaches,boolean checkParents)
    {
        URL url=Resource.class.getResource(name);

        if (url==null)
            url=Loader.getResource(Resource.class,name);
        if (url==null)
            return null;
        return newResource(url,useCaches);
    }

    /* ------------------------------------------------------------ */
    /*public*/ static boolean isContainedIn (Resource r, Resource containingResource) throws MalformedURLException
    {
        return r.isContainedIn(containingResource);
    }

    /* ------------------------------------------------------------ */
    @Override
    protected void finalize()
    {
        close();
    }

    /* ------------------------------------------------------------ */
    /*public*/ abstract boolean isContainedIn (Resource r) throws MalformedURLException;


    /* ------------------------------------------------------------ */
    /** Release any temporary resources held by the resource.
     * @deprecated use {@link #close()}
     */
    /*public*/ final void release()
    {
        close();
    }

    /* ------------------------------------------------------------ */
    /** Release any temporary resources held by the resource.
     */
    @Override
    /*public*/ abstract void close();

    /* ------------------------------------------------------------ */
    /**
     * Returns true if the respresened resource exists.
     */
    /*public*/ abstract boolean exists();


    /* ------------------------------------------------------------ */
    /**
     * Returns true if the respresenetd resource is a container/directory.
     * If the resource is not a file, resources ending with "/" are
     * considered directories.
     */
    /*public*/ abstract boolean isDirectory();

    /* ------------------------------------------------------------ */
    /**
     * Returns the last modified time
     */
    /*public*/ abstract long lastModified();


    /* ------------------------------------------------------------ */
    /**
     * Return the length of the resource
     */
    /*public*/ abstract long length();


    /* ------------------------------------------------------------ */
    /**
     * Returns an URL representing the given resource
     */
    /*public*/ abstract URL getURL();

    /* ------------------------------------------------------------ */
    /**
     * Returns an URI representing the given resource
     */
    /*public*/ URI getURI()
    {
        try
        {
            return getURL().toURI();
        }
        catch(Exception e)
        {
            throw new RuntimeException(e);
        }
    }


    /* ------------------------------------------------------------ */
    /**
     * Returns an File representing the given resource or NULL if this
     * is not possible.
     */
    /*public*/ abstract File getFile()
        throws IOException;


    /* ------------------------------------------------------------ */
    /**
     * Returns the name of the resource
     */
    /*public*/ abstract String getName();


    /* ------------------------------------------------------------ */
    /**
     * Returns an input stream to the resource
     */
    /*public*/ abstract InputStream getInputStream()
        throws java.io.IOException;

    /* ------------------------------------------------------------ */
    /**
     * Returns an readable bytechannel to the resource or null if one is not available.
     */
    /*public*/ abstract ReadableByteChannel getReadableByteChannel()
        throws java.io.IOException;

    /* ------------------------------------------------------------ */
    /**
     * Deletes the given resource
     */
    /*public*/ abstract boolean delete()
        throws SecurityException;

    /* ------------------------------------------------------------ */
    /**
     * Rename the given resource
     */
    /*public*/ abstract boolean renameTo( Resource dest)
        throws SecurityException;

    /* ------------------------------------------------------------ */
    /**
     * Returns a list of resource names contained in the given resource
     * The resource names are not URL encoded.
     */
    /*public*/ abstract String[] list();

    /* ------------------------------------------------------------ */
    /**
     * Returns the resource contained inside the current resource with the
     * given name.
     * @param path The path segment to add, which is not encoded
     */
    /*public*/ abstract Resource addPath(String path)
        throws IOException,MalformedURLException;

    /* ------------------------------------------------------------ */
    /** Get a resource from within this resource.
     * <p>
     * This method is essentially an alias for {@link #addPath(String)}, but without checked exceptions.
     * This method satisfied the {@link ResourceFactory} interface.
     * @see org.eclipse.jetty.util.resource.ResourceFactory#getResource(java.lang.String)
     */
    @Override
    /*public*/ Resource getResource(String path)
    {
        try
        {
            return addPath(path);
        }
        catch(Exception e)
        {
            LOG.debug(e);
            return null;
        }
    }

    /* ------------------------------------------------------------ */
    /**
     * @deprecated
     */
    /*public*/ String encode(String uri)
    {
        return null;
    }

    /* ------------------------------------------------------------ */
    /*public*/ Object getAssociate()
    {
        return _associate;
    }

    /* ------------------------------------------------------------ */
    /*public*/ void setAssociate(Object o)
    {
        _associate=o;
    }

    /* ------------------------------------------------------------ */
    /**
     * @return The canonical Alias of this resource or null if none.
     */
    /*public*/ URI getAlias()
    {
        return null;
    }
#endif
    /* ------------------------------------------------------------ */
    /** Get the resource list as a HTML directory listing.
     * @param base The base URL
     * @param parent True if the parent directory should be included
     * @return String of HTML
     */
    /*public*/ QString Resource::getListHTML(QString base, bool parent)
        throw (IOException)
    {
        //base=URIUtil.canonicalPath(base);

     QDir dir(base);
     base = dir.canonicalPath();
     QFileInfo info(base);
        if (base=="" || !info.isDir())
            return "";

        QFileInfoList ls = dir.entryInfoList();
        if (ls.isEmpty())
            return "";
// TOODO:        Arrays.sort(ls);

        QString decodedBase = URIUtil::decodePath(base);
        QString title = "Directory: "+deTag(decodedBase);

        QString buf; //=new StringBuilder(4096);
        buf.append("<HTML><HEAD>");
        buf.append("<LINK HREF=\"").append("jetty-dir.css").append("\" REL=\"stylesheet\" TYPE=\"text/css\"/><TITLE>");
        buf.append(title);
        buf.append("</TITLE></HEAD><BODY>\n<H1>");
        buf.append(title);
        buf.append("</H1>\n<TABLE BORDER=0>\n");

        if (parent)
        {
            buf.append("<TR><TD><A HREF=\"");
            buf.append(URIUtil::addPaths(base,"../"));
            buf.append("\">Parent Directory</A></TD><TD></TD><TD></TD></TR>\n");
        }

        QString encodedBase = hrefEncodeURI(base);

//        DateFormat dfmt=DateFormat.getDateTimeInstance(DateFormat.MEDIUM,
//                                                       DateFormat.MEDIUM);
        for (int i=0 ; i< ls.length() ; i++)
        {
            //Resource* item = addPath(ls[i]);
         QFileInfo item = ls.at(i);

            buf.append("\n<TR><TD><A HREF=\"");
            QString path=URIUtil::addPaths(encodedBase,URIUtil::encodePath(ls[i].absolutePath()));

            buf.append(path);

            if (item.isDir() && !path.endsWith("/"))
                buf.append(URIUtil::SLASH);

            // URIUtil.encodePath(buf,path);
            buf.append("\">");
            buf.append(deTag(ls[i].fileName()));
            buf.append("&nbsp;");
            buf.append("</A></TD><TD ALIGN=right>");
            buf.append( QString::number(item.size()).toLocal8Bit());//item.length());
            buf.append(" bytes&nbsp;</TD><TD>");
            buf.append(item.lastModified().toString(Qt::ISODate)); //dfmt.format(new Date(item.lastModified())));
            buf.append("</TD></TR>");
        }
        buf.append("</TABLE>\n");
 buf.append("</BODY></HTML>\n");

        return buf/*.toString()*/;
    }

    /**
     * Encode any characters that could break the URI string in an HREF.
     * Such as <a href="/path/to;<script>Window.alert("XSS"+'%20'+"here");</script>">Link</a>
     *
     * The above example would parse incorrectly on various browsers as the "<" or '"' characters
     * would end the href attribute value string prematurely.
     *
     * @param raw the raw text to encode.
     * @return the defanged text.
     */
    /*private*/ /*static*/ QString Resource::hrefEncodeURI(QString raw)
    {
//        QString buf = "";

//        loop:
//        for (int i=0;i<raw.length();i++)
//        {
//            QChar c=raw.at(i);
//            switch(c)
//            {
//                case '\'':
//                case '"':
//                case '<':
//                case '>':
//                    buf=new StringBuffer(raw.length()<<1);
//                    break loop;
//            }
//        }
//        if (buf==null)
//            return raw;

//        for (int i=0;i<raw.length();i++)
//        {
//            char c=raw.charAt(i);
//            switch(c)
//            {
//              case '"':
//                  buf.append("%22");
//                  continue;
//              case '\'':
//                  buf.append("%27");
//                  continue;
//              case '<':
//                  buf.append("%3C");
//                  continue;
//              case '>':
//                  buf.append("%3E");
//                  continue;
//              default:
//                  buf.append(c);
//                  continue;
//            }
//        }

//        return buf.toString();
     return QString(QUrl::toPercentEncoding(raw));
    }

    /*private*/ /*static*/ QString Resource::deTag(QString raw)
    {
        //return StringUtil::replace( StringUtil::replace(raw,"<","&lt;"), ">", "&gt;");
     QString out = raw.replace("<","&lt;");
     return out.replace( ">", "&gt;");
    }
#if 0
    /* ------------------------------------------------------------ */
    /**
     * @param out
     * @param start First byte to write
     * @param count Bytes to write or -1 for all of them.
     */
    /*public*/ void writeTo(OutputStream out,long start,long count)
        throws IOException
    {
        try (InputStream in = getInputStream())
        {
            in.skip(start);
            if (count<0)
                IO.copy(in,out);
            else
                IO.copy(in,out,count);
        }
    }

    /* ------------------------------------------------------------ */
    /*public*/ void copyTo(File destination)
        throws IOException
    {
        if (destination.exists())
            throw new IllegalArgumentException(destination+" exists");
        try (OutputStream out = new FileOutputStream(destination))
        {
            writeTo(out,0,-1);
        }
    }

    /* ------------------------------------------------------------ */
    /*public*/ String getWeakETag()
    {
        try
        {
            StringBuilder b = new StringBuilder(32);
            b.append("W/\"");

            String name=getName();
            int length=name.length();
            long lhash=0;
            for (int i=0; i<length;i++)
                lhash=31*lhash+name.charAt(i);

            B64Code.encode(lastModified()^lhash,b);
            B64Code.encode(length()^lhash,b);
            b.append('"');
            return b.toString();
        }
        catch (IOException e)
        {
            throw new RuntimeException(e);
        }
    }

    /* ------------------------------------------------------------ */
    /*public*/ Collection<Resource> getAllResources()
    {
        try
        {
            ArrayList<Resource> deep=new ArrayList<>();
            {
                String[] list=list();
                if (list!=null)
                {
                    for (String i:list)
                    {
                        Resource r=addPath(i);
                        if (r.isDirectory())
                            deep.addAll(r.getAllResources());
                        else
                            deep.add(r);
                    }
                }
            }
            return deep;
        }
        catch(Exception e)
        {
            throw new IllegalStateException(e);
        }
    }

    /* ------------------------------------------------------------ */
    /** Generate a properly encoded URL from a {@link File} instance.
     * @param file Target file.
     * @return URL of the target file.
     * @throws MalformedURLException
     */
    /*public*/ static URL toURL(File file) throws MalformedURLException
    {
        return file.toURI().toURL();
    }
}
#endif
 /*static*/ QString Resource::stringResource = "";

/*public*/ QString Resource::getResourceString() //ACK shortcut
{
 return stringResource;
}
