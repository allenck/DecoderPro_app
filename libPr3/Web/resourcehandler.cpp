#include "resourcehandler.h"
#include "loggerfactory.h"
#include "exceptions.h"

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
/** Resource Handler.
 *
 * This handle will serve static content and handle If-Modified-Since headers.
 * No caching is done.
 * Requests for resources that do not exist are let pass (Eg no 404's).
 *
 *
 * @org.apache.xbean.XBean
 */
///*public*/ class ResourceHandler extends HandlerWrapper
//{
    /*private*/ /*static*/ /*final*/ Logger* ResourceHandler::LOG = LoggerFactory::getLogger("ResourceHandler");


/* ------------------------------------------------------------ */
ResourceHandler::ResourceHandler(QObject *parent) : QObject(parent)
{
 _welcomeFiles = QStringList();
 _welcomeFiles << "index.html";
_minMemoryMappedContentLength=-1;
_minAsyncContentLength=0;

}
#if 0
/* ------------------------------------------------------------ */
/*public*/ MimeTypes getMimeTypes()
{
    return _mimeTypes;
}

/* ------------------------------------------------------------ */
/*public*/ void setMimeTypes(MimeTypes mimeTypes)
{
    _mimeTypes = mimeTypes;
}
#endif
/* ------------------------------------------------------------ */
/** Get the directory option.
 * @return true if directories are listed.
 */
/*public*/ bool ResourceHandler::isDirectoriesListed()
{
    return _directory;
}

/* ------------------------------------------------------------ */
/** Set the directory.
 * @param directory true if directories are listed.
 */
/*public*/ void ResourceHandler::setDirectoriesListed(bool directory)
{
    _directory = directory;
}
#if 0
/* ------------------------------------------------------------ */
/** Get minimum memory mapped file content length.
 * @return the minimum size in bytes of a file resource that will
 * be served using a memory mapped buffer, or -1 (default) for no memory mapped
 * buffers.
 */
/*public*/ int getMinMemoryMappedContentLength()
{
    return _minMemoryMappedContentLength;
}

/* ------------------------------------------------------------ */
/** Set minimum memory mapped file content length.
 * @param minMemoryMappedFileSize the minimum size in bytes of a file resource that will
 * be served using a memory mapped buffer, or -1 for no memory mapped
 * buffers.
 */
/*public*/ void setMinMemoryMappedContentLength(int minMemoryMappedFileSize)
{
    _minMemoryMappedContentLength = minMemoryMappedFileSize;
}

/* ------------------------------------------------------------ */
/** Get the minimum content length for async handling.
 * @return The minimum size in bytes of the content before asynchronous
 * handling is used, or -1 for no async handling or 0 (default) for using
 * {@link HttpServletResponse#getBufferSize()} as the minimum length.
 */
/*public*/ int getMinAsyncContentLength()
{
    return _minAsyncContentLength;
}

/* ------------------------------------------------------------ */
/** Set the minimum content length for async handling.
 * @param minAsyncContentLength The minimum size in bytes of the content before asynchronous
 * handling is used, or -1 for no async handling or 0 for using
 * {@link HttpServletResponse#getBufferSize()} as the minimum length.
 */
/*public*/ void setMinAsyncContentLength(int minAsyncContentLength)
{
    _minAsyncContentLength = minAsyncContentLength;
}

/* ------------------------------------------------------------ */
/**
 * @return True if ETag processing is done
 */
/*public*/ boolean isEtags()
{
    return _etags;
}

/* ------------------------------------------------------------ */
/**
 * @param etags True if ETag processing is done
 */
/*public*/ void setEtags(boolean etags)
{
    _etags = etags;
}

/* ------------------------------------------------------------ */
//@Override
/*public*/ void doStart()
throws Exception
{
    Context scontext = ContextHandler.getCurrentContext();
    _context = (scontext==null?null:scontext.getContextHandler());

    super.doStart();
}

/* ------------------------------------------------------------ */
/**
 * @return Returns the resourceBase.
 */
/*public*/ Resource getBaseResource()
{
    if (_baseResource==null)
        return null;
    return _baseResource;
}

/* ------------------------------------------------------------ */
/**
 * @return Returns the base resource as a string.
 */
/*public*/ String getResourceBase()
{
    if (_baseResource==null)
        return null;
    return _baseResource.toString();
}
#endif

/* ------------------------------------------------------------ */
/**
 * @param base The resourceBase to set.
 */
/*public*/ void ResourceHandler::setBaseResource(Resource* base)
{
    _baseResource=base;
}

/* ------------------------------------------------------------ */
/**
 * @param resourceBase The base resource as a string.
 */
/*public*/ void ResourceHandler::setResourceBase(QString resourceBase)
{
    try
    {
        setBaseResource(Resource::newResource(resourceBase));
    }
    catch (Exception* e)
    {
        LOG->warn(e->getMessage());
        LOG->debug(e->getMessage());
        throw new IllegalArgumentException(resourceBase);
    }
}
#if 0
/* ------------------------------------------------------------ */
/**
 * @return Returns the stylesheet as a Resource.
 */
/*public*/ Resource getStylesheet()
{
 if(_stylesheet != null)
 {
     return _stylesheet;
 }
 else
 {
     if(_defaultStylesheet == null)
     {
         _defaultStylesheet =  Resource.newResource(this.getClass().getResource("/jetty-dir.css"));
     }
     return _defaultStylesheet;
 }
}

/* ------------------------------------------------------------ */
/**
 * @param stylesheet The location of the stylesheet to be used as a String.
 */
/*public*/ void setStylesheet(String stylesheet)
{
    try
    {
        _stylesheet = Resource.newResource(stylesheet);
        if(!_stylesheet.exists())
        {
            LOG->warn("unable to find custom stylesheet: " + stylesheet);
            _stylesheet = null;
        }
    }
 catch(Exception* e)
 {
     LOG->warn(e.toString());
     LOG->debug(e);
     throw new IllegalArgumentException(stylesheet);
 }
}

/* ------------------------------------------------------------ */
/**
 * @return the cacheControl header to set on all static content.
 */
/*public*/ String getCacheControl()
{
    return _cacheControl;
}

/* ------------------------------------------------------------ */
/**
 * @param cacheControl the cacheControl header to set on all static content.
 */
/*public*/ void setCacheControl(String cacheControl)
{
    _cacheControl=cacheControl;
}

/* ------------------------------------------------------------ */
/*
 */
/*public*/ Resource getResource(String path) throws MalformedURLException
{
    if (path==null || !path.startsWith("/"))
        throw new MalformedURLException(path);

    Resource base = _baseResource;
    if (base==null)
    {
        if (_context==null)
            return null;
        base=_context.getBaseResource();
        if (base==null)
            return null;
    }

    try
    {
        path=URIUtil.canonicalPath(path);
        return base.addPath(path);
    }
    catch(Exception* e)
    {
        LOG->ignore(e);
    }

    return null;
}

/* ------------------------------------------------------------ */
/*protected*/  Resource getResource(HttpServletRequest request) throws MalformedURLException
{
    String servletPath;
    String pathInfo;
    Boolean included = request.getAttribute(RequestDispatcher.INCLUDE_REQUEST_URI) != null;
    if (included != null && included.booleanValue())
    {
        servletPath = (String)request.getAttribute(RequestDispatcher.INCLUDE_SERVLET_PATH);
        pathInfo = (String)request.getAttribute(RequestDispatcher.INCLUDE_PATH_INFO);

        if (servletPath == null && pathInfo == null)
        {
            servletPath = request.getServletPath();
            pathInfo = request.getPathInfo();
        }
    }
    else
    {
        servletPath = request.getServletPath();
        pathInfo = request.getPathInfo();
    }

    String pathInContext=URIUtil.addPaths(servletPath,pathInfo);
    return getResource(pathInContext);
}


/* ------------------------------------------------------------ */
/*public*/ String[] getWelcomeFiles()
{
    return _welcomeFiles;
}
#endif
/* ------------------------------------------------------------ */
/*public*/ void ResourceHandler::setWelcomeFiles(QStringList welcomeFiles)
{
    _welcomeFiles=welcomeFiles;
}
#if 0
/* ------------------------------------------------------------ */
/*protected*/  Resource getWelcome(Resource directory) throws MalformedURLException, IOException
{
    for (int i=0;i<_welcomeFiles.length;i++)
    {
        Resource welcome=directory.addPath(_welcomeFiles[i]);
        if (welcome.exists() && !welcome.isDirectory())
            return welcome;
    }

    return null;
}

/* ------------------------------------------------------------ */
/*
 * @see org.eclipse.jetty.server.Handler#handle(javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse, int)
 */
//@Override
/*public*/ void handle(QString target, Request baseRequest, HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException
{
    if (baseRequest.isHandled())
        return;

    boolean skipContentBody = false;

    if(!HttpMethod.GET.is(request.getMethod()))
    {
        if(!HttpMethod.HEAD.is(request.getMethod()))
        {
            //try another handler
            super.handle(target, baseRequest, request, response);
            return;
        }
        skipContentBody = true;
    }

    Resource resource = getResource(request);
    // If resource is not found
    if (resource==null || !resource.exists())
    {
        // inject the jetty-dir.css file if it matches
        if (target.endsWith("/jetty-dir.css"))
        {
            resource = getStylesheet();
            if (resource==null)
                return;
            response.setContentType("text/css");
        }
        else
        {
            //no resource - try other handlers
            super.handle(target, baseRequest, request, response);
            return;
        }
    }

    // We are going to serve something
    baseRequest.setHandled(true);

    // handle directories
    if (resource.isDirectory())
    {
        if (!request.getPathInfo().endsWith(URIUtil.SLASH))
        {
            response.sendRedirect(response.encodeRedirectURL(URIUtil.addPaths(request.getRequestURI(),URIUtil.SLASH)));
            return;
        }

        Resource welcome=getWelcome(resource);
        if (welcome!=null && welcome.exists())
            resource=welcome;
        else
        {
            doDirectory(request,response,resource);
            baseRequest.setHandled(true);
            return;
        }
    }

    // Handle ETAGS
    long last_modified=resource.lastModified();
    QString etag=null;
    if (_etags)
    {
        // simple handling of only a single etag
        QString ifnm = request.getHeader(HttpHeader.IF_NONE_MATCH.asString());
        etag=resource.getWeakETag();
        if (ifnm!=null && resource!=null && ifnm.equals(etag))
        {
            response.setStatus(HttpStatus.NOT_MODIFIED_304);
            baseRequest.getResponse().getHttpFields().put(HttpHeader.ETAG,etag);
            return;
        }
    }

    // Handle if modified since
    if (last_modified>0)
    {
        long if_modified=request.getDateHeader(HttpHeader.IF_MODIFIED_SINCE.asString());
        if (if_modified>0 && last_modified/1000<=if_modified/1000)
        {
            response.setStatus(HttpStatus.NOT_MODIFIED_304);
            return;
        }
    }

    // set the headers
    QString mime=_mimeTypes.getMimeByExtension(resource.toString());
    if (mime==null)
        mime=_mimeTypes.getMimeByExtension(request.getPathInfo());
    doResponseHeaders(response,resource,mime);
    if (_etags)
        baseRequest.getResponse().getHttpFields().put(HttpHeader.ETAG,etag);

    if(skipContentBody)
        return;


    // Send the content
    OutputStream out =null;
    try {out = response.getOutputStream();}
    catch(IllegalStateException e) {out = new WriterOutputStream(response.getWriter());}

    // Has the output been wrapped
    if (!(out instanceof HttpOutput))
        // Write content via wrapped output
        resource.writeTo(out,0,resource.length());
    else
    {
        // select async by size
        int min_async_size=_minAsyncContentLength==0?response.getBufferSize():_minAsyncContentLength;

        if (request.isAsyncSupported() &&
            min_async_size>0 &&
            resource.length()>=min_async_size)
        {
            final AsyncContext async = request.startAsync();
            Callback callback = new Callback()
            {
                //@Override
                /*public*/ void succeeded()
                {
                    async.complete();
                }

                //@Override
                /*public*/ void failed(Throwable x)
                {
                    LOG->warn(x.toString());
                    LOG->debug(x);
                    async.complete();
                }
            };

            // Can we use a memory mapped file?
            if (_minMemoryMappedContentLength>0 &&
                resource.length()>_minMemoryMappedContentLength &&
                resource instanceof FileResource)
            {
                ByteBuffer buffer = BufferUtil.toMappedBuffer(resource.getFile());
                ((HttpOutput)out).sendContent(buffer,callback);
            }
            else  // Do a blocking write of a channel (if available) or input stream
            {
                // Close of the channel/inputstream is done by the async sendContent
                ReadableByteChannel channel= resource.getReadableByteChannel();
                if (channel!=null)
                    ((HttpOutput)out).sendContent(channel,callback);
                else
                    ((HttpOutput)out).sendContent(resource.getInputStream(),callback);
            }
        }
        else
        {
            // Can we use a memory mapped file?
            if (_minMemoryMappedContentLength>0 &&
                resource.length()>_minMemoryMappedContentLength &&
                resource instanceof FileResource)
            {
                ByteBuffer buffer = BufferUtil.toMappedBuffer(resource.getFile());
                ((HttpOutput)out).sendContent(buffer);
            }
            else  // Do a blocking write of a channel (if available) or input stream
            {
                ReadableByteChannel channel= resource.getReadableByteChannel();
                if (channel!=null)
                    ((HttpOutput)out).sendContent(channel);
                else
                    ((HttpOutput)out).sendContent(resource.getInputStream());
            }
        }
    }
}

/* ------------------------------------------------------------ */
/*protected*/  void doDirectory(HttpServletRequest request,HttpServletResponse response, Resource resource)
    throws IOException
{
    if (_directory)
    {
        QString listing = resource.getListHTML(request.getRequestURI(),request.getPathInfo().lastIndexOf("/") > 0);
        response.setContentType("text/html; charset=UTF-8");
        response.getWriter().println(listing);
    }
    else
        response.sendError(HttpStatus.FORBIDDEN_403);
}

/* ------------------------------------------------------------ */
/** Set the response headers.
 * This method is called to set the response headers such as content type and content length.
 * May be extended to add additional headers.
 * @param response
 * @param resource
 * @param mimeType
 */
/*protected*/  void doResponseHeaders(HttpServletResponse response, Resource resource, QString mimeType)
{
    if (mimeType!=null)
        response.setContentType(mimeType);

    long length=resource.length();

    if (response instanceof Response)
    {
        HttpFields fields = ((Response)response).getHttpFields();

        if (length>0)
            ((Response)response).setLongContentLength(length);

        if (_cacheControl!=null)
            fields.put(HttpHeader.CACHE_CONTROL,_cacheControl);
    }
    else
    {
        if (length>Integer.MAX_VALUE)
            response.setHeader(HttpHeader.CONTENT_LENGTH.asString(),Long.toString(length));
        else if (length>0)
            response.setContentLength((int)length);

        if (_cacheControl!=null)
            response.setHeader(HttpHeader.CACHE_CONTROL.asString(),_cacheControl);
    }
}

#endif
