#include "uriutil.h"

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
/** URI Holder.
 * This class assists with the decoding and encoding or HTTP URI's.
 * It differs from the java.net.URL class as it does not provide
 * communications ability, but it does assist with query string
 * formatting.
 * <P>UTF-8 encoding is used by default for % encoded characters. This
 * may be overridden with the org.eclipse.jetty.util.URI.charset system property.
 * @see UrlEncoded
 *
 */
///*public*/ class URIUtil
//    implements Cloneable
//{
/*public*/ /*static*/ /*final*/ QString URIUtil::SLASH="/";
/*public*/ /*static*/ /*final*/ QString URIUtil::HTTP="http";
/*public*/ /*static*/ /*final*/ QString URIUtil::HTTP_COLON="http:";
/*public*/ /*static*/ /*final*/ QString URIUtil::HTTPS="https";
/*public*/ /*static*/ /*final*/ QString URIUtil::HTTPS_COLON="https:";

// Use UTF-8 as per http://www.w3.org/TR/html40/appendix/notes.html#non-ascii-chars
//    /*public*/ static /*final*/ Charset __CHARSET;

//    static
//    {
//        String charset = System.getProperty("org.eclipse.jetty.util.URI.charset");
//        __CHARSET = charset == NULL ? StandardCharsets.UTF_8 : Charset.forName(charset);
//    }

/*private*/ URIUtil::URIUtil()
{}

/* ------------------------------------------------------------ */
/** Encode a URI path.
 * This is the same encoding offered by URLEncoder, except that
 * the '/' character is not encoded.
 * @param path The path the encode
 * @return The encoded path
 */
/*public*/ /*static*/ QString URIUtil::encodePath(QString path)
{
    if (path==NULL || path.length()==0)
        return path;
    QString buf = encodePath(NULL,path);
    return buf; //==NULL?path:buf.toString();
}

/* ------------------------------------------------------------ */
/** Encode a URI path.
 * @param path The path the encode
 * @param buf StringBuilder to encode path into (or NULL)
 * @return The StringBuilder or NULL if no substitutions required.
 */
/*public*/ /*static*/ QString URIUtil::encodePath(QString buf, QString path)
{
#if 0
    byte[] bytes=NULL;
    if (buf==NULL)
    {
    loop:
        for (int i=0;i<path.length();i++)
        {
            char c=path.charAt(i);
            switch(c)
            {
                case '%':
                case '?':
                case ';':
                case '#':
                case '\'':
                case '"':
                case '<':
                case '>':
                case ' ':
                    buf=new StringBuilder(path.length()*2);
                    break loop;
                default:
                    if (c>127)
                    {
                        bytes=path.getBytes(URIUtil.__CHARSET);
                        buf=new StringBuilder(path.length()*2);
                        break loop;
                    }

            }
        }
        if (buf==NULL)
            return NULL;
    }

    synchronized(buf)
    {
        if (bytes!=NULL)
        {
            for (int i=0;i<bytes.length;i++)
            {
                byte c=bytes[i];
                switch(c)
                {
                  case '%':
                      buf.append("%25");
                      continue;
                  case '?':
                      buf.append("%3F");
                      continue;
                  case ';':
                      buf.append("%3B");
                      continue;
                  case '#':
                      buf.append("%23");
                      continue;
                  case '"':
                      buf.append("%22");
                      continue;
                  case '\'':
                      buf.append("%27");
                      continue;
                  case '<':
                      buf.append("%3C");
                      continue;
                  case '>':
                      buf.append("%3E");
                      continue;
                  case ' ':
                      buf.append("%20");
                      continue;
                  default:
                      if (c<0)
                      {
                          buf.append('%');
                          TypeUtil.toHex(c,buf);
                      }
                      else
                          buf.append((char)c);
                      continue;
                }
            }

        }
        else
        {
            for (int i=0;i<path.length();i++)
            {
                char c=path.charAt(i);
                switch(c)
                {
                    case '%':
                        buf.append("%25");
                        continue;
                    case '?':
                        buf.append("%3F");
                        continue;
                    case ';':
                        buf.append("%3B");
                        continue;
                    case '#':
                        buf.append("%23");
                        continue;
                    case '"':
                        buf.append("%22");
                        continue;
                    case '\'':
                        buf.append("%27");
                        continue;
                    case '<':
                        buf.append("%3C");
                        continue;
                    case '>':
                        buf.append("%3E");
                        continue;
                    case ' ':
                        buf.append("%20");
                        continue;
                    default:
                        buf.append(c);
                        continue;
                }
            }
        }
    }
#endif
    QUrl url(path.toLocal8Bit());
    QByteArray enc = url.toEncoded();
    enc = enc.replace("%2F", "/");
    return QString(enc);
}
#if 0
/* ------------------------------------------------------------ */
/** Encode a URI path.
 * @param path The path the encode
 * @param buf StringBuilder to encode path into (or NULL)
 * @param encode String of characters to encode. % is always encoded.
 * @return The StringBuilder or NULL if no substitutions required.
 */
/*public*/ static StringBuilder encodeString(StringBuilder buf,
                                         String path,
                                         String encode)
{
    if (buf==NULL)
    {
    loop:
        for (int i=0;i<path.length();i++)
        {
            char c=path.charAt(i);
            if (c=='%' || encode.indexOf(c)>=0)
            {
                buf=new StringBuilder(path.length()<<1);
                break loop;
            }
        }
        if (buf==NULL)
            return NULL;
    }

    synchronized(buf)
    {
        for (int i=0;i<path.length();i++)
        {
            char c=path.charAt(i);
            if (c=='%' || encode.indexOf(c)>=0)
            {
                buf.append('%');
                StringUtil.append(buf,(byte)(0xff&c),16);
            }
            else
                buf.append(c);
        }
    }

    return buf;
}
#endif
/* ------------------------------------------------------------ */
/* Decode a URI path and strip parameters
 * @param path The path the encode
 * @param buf StringBuilder to encode path into
 */
/*public*/ /*static*/ QString URIUtil::decodePath(QString path)
{
#if 0
 if (path==NULL)
     return NULL;
 // Array to hold all converted characters
 QVector<QChar> chars;
 int n=0;
 // Array to hold a sequence of %encodings
 QByteArray bytes;
 int b=0;

 int len=path.length();

 for (int i=0;i<len;i++)
 {
  QChar c = path.at(i);

  if (c=='%' && (i+2)<len)
  {
   if (chars.isEmpty())
   {
    chars=QVector<QChar>(len);
    bytes=QByteArray(len, 0);
    //path.getChars(0,i,chars,0);
    for(j=0; j < i; j++)
     chars.replace(j, path.at(j));
   }
   //bytes[b++]=(byte)(0xff&TypeUtil.parseInt(path,i+1,2,16));
   bytes.replace(b++,
   i+=2;
   continue;
  }
  else if (c==';')
  {
      if (chars==NULL)
      {
          chars=new char[len];
          path.getChars(0,i,chars,0);
          n=i;
      }
      break;
  }
  else if (bytes==NULL)
  {
      n++;
      continue;
  }

  // Do we have some bytes to convert?
  if (b>0)
  {
      QString s=new QString(bytes,0,b,__CHARSET);
      s.getChars(0,s.length(),chars,n);
      n+=s.length();
      b=0;
  }

  chars[n++]=c;
 }

 if (chars==NULL)
     return path;

 // if we have a remaining sequence of bytes
 if (b>0)
 {
  QString s=new QString(bytes,0,b,__CHARSET);
  s.getChars(0,s.length(),chars,n);
  n+=s.length();
 }

 return new QString(chars,0,n);
#endif
 QString str = QUrl::fromEncoded(path.toLocal8Bit()).toString();
 return str.replace("%2F", "/");
}
#if 0
/* ------------------------------------------------------------ */
/* Decode a URI path and strip parameters.
 * @param path The path the encode
 * @param buf StringBuilder to encode path into
 */
/*public*/ static String decodePath(byte[] buf, int offset, int length)
{
    byte[] bytes=NULL;
    int n=0;

    for (int i=0;i<length;i++)
    {
        byte b = buf[i + offset];

        if (b=='%' && (i+2)<length)
        {
            b=(byte)(0xff&TypeUtil.parseInt(buf,i+offset+1,2,16));
            i+=2;
        }
        else if (b==';')
        {
            length=i;
            break;
        }
        else if (bytes==NULL)
        {
            n++;
            continue;
        }

        if (bytes==NULL)
        {
            bytes=new byte[length];
            for (int j=0;j<n;j++)
                bytes[j]=buf[j + offset];
        }

        bytes[n++]=b;
    }

    if (bytes==NULL)
        return new String(buf,offset,length,__CHARSET);
    return new String(bytes,0,n,__CHARSET);
}

#endif
/* ------------------------------------------------------------ */
/** Add two URI path segments.
 * Handles NULL and empty paths, path and query params (eg ?a=b or
 * ;JSESSIONID=xxx) and avoids duplicate '/'
 * @param p1 URI path segment (should be encoded)
 * @param p2 URI path segment (should be encoded)
 * @return Legally combined path segments.
 */
/*public*/ /*static*/ QString URIUtil::addPaths(QString p1, QString p2)
{
    if (p1==NULL || p1.length()==0)
    {
        if (p1!=NULL && p2==NULL)
            return p1;
        return p2;
    }
    if (p2==NULL || p2.length()==0)
        return p1;

    int split=p1.indexOf(';');
    if (split<0)
        split=p1.indexOf('?');
    if (split==0)
        return p2+p1;
    if (split<0)
        split=p1.length();

    QString buf;// = new StringBuilder(p1.length()+p2.length()+2);
    buf.append(p1);

    if (buf.at(split-1)=='/')
    {
        if (p2.startsWith(URIUtil::SLASH))
        {
            buf.remove(split-1);  //deleteCharAt(split-1);
            buf.insert(split-1,p2);
        }
        else
            buf.insert(split,p2);
    }
    else
    {
        if (p2.startsWith(URIUtil::SLASH))
            buf.insert(split,p2);
        else
        {
            buf.insert(split,'/');
            buf.insert(split+1,p2);
        }
    }

    return buf/*.toString()*/;
}

/* ------------------------------------------------------------ */
/** Return the parent Path.
 * Treat a URI like a directory path and return the parent directory.
 */
/*public*/ /*static*/ QString URIUtil::parentPath(QString p)
{
    if (p==NULL || URIUtil::SLASH == (p))
        return NULL;
    int slash=p.lastIndexOf('/',p.length()-2);
    if (slash>=0)
        return p.mid(0,slash+1);
    return NULL;
}

/* ------------------------------------------------------------ */
/** Convert a path to a cananonical form.
 * All instances of "." and ".." are factored out.  Null is returned
 * if the path tries to .. above its root.
 * @param path
 * @return path or NULL.
 */
/*public*/ /*static*/ QString URIUtil::canonicalPath(QString path)
{
    if (path==NULL || path.length()==0)
        return path;

    int end=path.length();
    int start = path.lastIndexOf('/', end);

search:
    while (end>0)
    {
        switch(end-start)
        {
          case 2: // possible single dot
              if (path.at(start+1)!='.')
                  break;
              goto search;//break search;
          case 3: // possible double dot
              if (path.at(start+1)!='.' || path.at(start+2)!='.')
                  break;
              goto search;//break search;
        }

        end=start;
        start=path.lastIndexOf('/',end-1);
    }

    // If we have checked the entire string
    if (start>=end)
        return path;

    QString buf;// = new StringBuilder(path);
    int delStart=-1;
    int delEnd=-1;
    int skip=0;

    while (end>0)
    {
        switch(end-start)
        {
          case 2: // possible single dot
              if (buf.at(start+1)!='.')
              {
                  if (skip>0 && --skip==0)
                  {
                      delStart=start>=0?start:0;
                      if(delStart>0 && delEnd==buf.length() && buf.at(delEnd-1)=='.')
                          delStart++;
                  }
                  break;
              }

              if(start<0 && buf.length()>2 && buf.at(1)=='/' && buf.at(2)=='/')
                  break;

              if(delEnd<0)
                  delEnd=end;
              delStart=start;
              if (delStart<0 || delStart==0&&buf.at(delStart)=='/')
              {
                  delStart++;
                  if (delEnd<buf.length() && buf.at(delEnd)=='/')
                      delEnd++;
                  break;
              }
              if (end==buf.length())
                  delStart++;

              end=start--;
              while (start>=0 && buf.at(start)!='/')
                  start--;
              continue;

          case 3: // possible double dot
              if (buf.at(start+1)!='.' || buf.at(start+2)!='.')
              {
                  if (skip>0 && --skip==0)
                  {   delStart=start>=0?start:0;
                      if(delStart>0 && delEnd==buf.length() && buf.at(delEnd-1)=='.')
                          delStart++;
                  }
                  break;
              }

              delStart=start;
              if (delEnd<0)
                  delEnd=end;

              skip++;
              end=start--;
              while (start>=0 && buf.at(start)!='/')
                  start--;
              continue;

          default:
              if (skip>0 && --skip==0)
              {
                  delStart=start>=0?start:0;
                  if(delEnd==buf.length() && buf.at(delEnd-1)=='.')
                      delStart++;
              }
        }

        // Do the delete
        if (skip<=0 && delStart>=0 && delEnd>=delStart)
        {
            buf.remove(delStart,delEnd);
            delStart=delEnd=-1;
            if (skip>0)
                delEnd=end;
        }

        end=start--;
        while (start>=0 && buf.at(start)!='/')
            start--;
    }

    // Too many ..
    if (skip>0)
        return NULL;

    // Do the delete
    if (delEnd>=0)
        buf.remove(delStart,delEnd);

    return buf/*.toString()*/;
}
#if 0
/* ------------------------------------------------------------ */
/** Convert a path to a compact form.
 * All instances of "//" and "///" etc. are factored out to single "/"
 * @param path
 * @return path
 */
/*public*/ static String compactPath(String path)
{
    if (path==NULL || path.length()==0)
        return path;

    int state=0;
    int end=path.length();
    int i=0;

    loop:
    while (i<end)
    {
        char c=path.charAt(i);
        switch(c)
        {
            case '?':
                return path;
            case '/':
                state++;
                if (state==2)
                    break loop;
                break;
            default:
                state=0;
        }
        i++;
    }

    if (state<2)
        return path;

    StringBuffer buf = new StringBuffer(path.length());
    buf.append(path,0,i);

    loop2:
    while (i<end)
    {
        char c=path.charAt(i);
        switch(c)
        {
            case '?':
                buf.append(path,i,end);
                break loop2;
            case '/':
                if (state++==0)
                    buf.append(c);
                break;
            default:
                state=0;
                buf.append(c);
        }
        i++;
    }

    return buf.toString();
}

/* ------------------------------------------------------------ */
/**
 * @param uri URI
 * @return True if the uri has a scheme
 */
/*public*/ static boolean hasScheme(String uri)
{
    for (int i=0;i<uri.length();i++)
    {
        char c=uri.charAt(i);
        if (c==':')
            return true;
        if (!(c>='a'&&c<='z' ||
              c>='A'&&c<='Z' ||
              (i>0 &&(c>='0'&&c<='9' ||
                      c=='.' ||
                      c=='+' ||
                      c=='-'))
              ))
            break;
    }
    return false;
}

/*public*/ static void appendSchemeHostPort(StringBuilder url,String scheme,String server, int port)
{
    if (server.indexOf(':')>=0&&server.charAt(0)!='[')
        url.append(scheme).append("://").append('[').append(server).append(']');
    else
        url.append(scheme).append("://").append(server);

    if (port > 0 && (("http".equalsIgnoreCase(scheme) && port != 80) || ("https".equalsIgnoreCase(scheme) && port != 443)))
        url.append(':').append(port);
}

/*public*/ static void appendSchemeHostPort(StringBuffer url,String scheme,String server, int port)
{
    synchronized (url)
    {
        if (server.indexOf(':')>=0&&server.charAt(0)!='[')
            url.append(scheme).append("://").append('[').append(server).append(']');
        else
            url.append(scheme).append("://").append(server);

        if (port > 0 && (("http".equalsIgnoreCase(scheme) && port != 80) || ("https".equalsIgnoreCase(scheme) && port != 443)))
            url.append(':').append(port);
    }
}

#endif
