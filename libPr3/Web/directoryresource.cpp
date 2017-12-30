#include "directoryresource.h"
#include <QDir>
#include <QFileInfo>
#include "uriutil.h"
#include "fileutil.h"
#include "servletutil.h"

/**
 * Override
 * {@link org.eclipse.jetty.util.resource.Resource#getListHTML(java.lang.String, boolean)}
 * in {@link org.eclipse.jetty.util.resource.Resource} so that directory
 * listings can include the complete JMRI look and feel.
 *
 * @author Randall Wood (C) 2016
 */
///*public*/ class DirectoryResource extends Resource {


/*public*/ DirectoryResource::DirectoryResource(QLocale locale, Resource* resource, QObject* parent) : Resource(parent) {
    this->resource = resource;
    this->locale = locale;
}

//@Override
/*public*/ QString DirectoryResource::getListHTML(QString _base, bool parent)
        throw (IOException) {
     QString base = resource->getResourceString();
     base = URIUtil::canonicalPath(base);

     QFileInfo info(base);
    if (base == NULL || !info.isDir()) {
        return NULL;
    }

    //String[] ls = list();
    QDir dir(base);
    QFileInfoList ls = dir.entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot);
    if (ls.isEmpty()) {
        return NULL;
    }
    //Arrays.sort(ls);

    QString decodedBase = URIUtil::decodePath(base);
    QString title = tr(/*this->locale,*/ "Directory: %1").arg(deTag(decodedBase)); // NOI18N

    QString table; // = new StringBuilder(4096);
    QString row = tr(/*this->locale,*/ "<tr><td><a href=\"%1$s\">%2$s</a></td><td align=\"right\">%3$s</td><td>%4$s</td></tr>"); // NOI18N
    if (parent)
    {
//        table.append(String.format(this->locale, row,
//                URIUtil::addPaths(base, "../"),
//                tr(this->locale, "Parent Directory"),
//                "",
//                ""));
     QString paths = URIUtil::addPaths(base, "../");
     row = row.replace("%1$s", paths);
     row = row.replace("%2$s", tr("Parent Directory"));
     row = row.replace("%3$s", "");
     row = row.replace("%4$s", "");
     table.append(row);
    }

    QString encodedBase = hrefEncodeURI(base);

    //DateFormat dfmt = DateFormat.getDateTimeInstance(DateFormat.MEDIUM, DateFormat.MEDIUM, this->locale);
    //for (String l : ls)
    for(int i = 0; i < ls.count(); i++)
    {
     QString l = ls.at(i).fileName();
     //   Resource item = addPath(l);
     QFileInfo item = ls.at(i);
     QString path = URIUtil::addPaths(encodedBase, URIUtil::encodePath(l));
        if (item.isDir() && !path.endsWith("/")) {
            path = path + URIUtil::SLASH;
        }
//        table.append(String.format(this->locale, row,
//                path,
//                deTag(l),
//                tr(this->locale, "SizeInBytes", item.length()),
//                dfmt.format(new Date(item.lastModified())))
//        );
        row = tr(/*this->locale,*/ "<tr><td><a href=\"%1$s\">%2$s</a></td><td align=\"right\">%3$s</td><td>%4$s</td></tr>");
        row = row.replace("%1$s", path);
        row = row.replace("%2$s",deTag(l));
        row = row.replace("%3$s", tr("%1 bytes").arg(item.size()));
        row = row.replace("%4$s", item.lastModified().toString());
        table.append(row);
    }

//    return String.format(this->locale,
//            FileUtil.readURL(FileUtil.findURL(tr(this->locale, "Directory.html"))), // NOI18N
//            String.format(this->locale,
//                    tr(this->locale, "HtmlTitle"), // NOI18N
//                    ServletUtil.getInstance().getRailroadName(false),
//                    title
//            ),
//            ServletUtil.getInstance().getNavBar(this->locale, base),
//            ServletUtil.getInstance().getRailroadName(false),
//            ServletUtil.getInstance().getFooter(this->locale, base),
//            title,
//            table
//    );
    QString html = FileUtil::readURL(FileUtil::findURL(tr(/*this->locale,*/ "web/servlet/directory/Directory.html")));
    QString htmlTitle = "%2$s | %1$s";
    htmlTitle = htmlTitle.replace("%1s", ServletUtil::getInstance()->getRailroadName(false));
    htmlTitle = htmlTitle.replace("%2s", title);
    html = html.replace("%1$s", htmlTitle);
    html = html.replace("%2$s", ServletUtil::getInstance()->getNavBar(this->locale, base ));
    html = html.replace("%3$s", ServletUtil::getInstance()->getRailroadName(false));
    html = html.replace("%4$s", ServletUtil::getInstance()->getFooter(this->locale, base));
    html = html.replace("%5$s", title);
    html = html.replace("%6$s", table);
    return html;
}

/*
 * TODO: Do we already have something like this elsewhere in the JMRI code or in a required library?
 */
/**
 * Encode any characters that could break the URI string in an HREF. Such as
 * <a
 * href="/path/to;<script>Window.alert("XSS"+'%20'+"here");</script>">Link</a>
 *
 * The above example would parse incorrectly on various browsers as the "<"
 * or '"' characters would end the href attribute value string prematurely.
 *
 * @param raw the raw text to encode.
 * @return the defanged text.
 */
/*private*/ /*static*/ QString DirectoryResource::hrefEncodeURI(QString raw) {
    QString buf = NULL;

    loop:
    for (int i = 0; i < raw.length(); i++) {
        QChar c = raw.at(i);
//        switch (c) {
//            case '\'':
//            case '"':
//            case '<':
//            case '>':
        if(c == '\\' || c == '"' || c == '<' || c == '>')
        {
                buf = QString();//new StringBuffer(raw.length() << 1);
                goto loop;//break loop;
        }
    }
    if (buf == NULL) {
        return raw;
    }

    for (int i = 0; i < raw.length(); i++) {
        QChar c = raw.at(i);
        if(c == '"')
        {
                buf.append("%22");
                continue;
        }
        else if(c == '\'')
        {
                buf.append("%27");
                continue;
        }
        else if(c ==  '<')
        {
                buf.append("%3C");
                continue;
        }
        else if(c ==  '>')
        {
                buf.append("%3E");
                continue;
        }
        else
        {
                buf.append(c);
        }
    }

    return buf/*.toString()*/;
}
#if 0
/*
 * TODO: Do we already have something like this elsewhere in the JMRI code or in a required library?
 */
private static String deTag(String raw) {
    return StringUtil.replace(StringUtil.replace(raw, "<", "&lt;"), ">", "&gt;");
}

/*
 * Abstract methods of Resource that must be overridden.
 */
//@Override
/*public*/ boolean isContainedIn(Resource rsrc) throws MalformedURLException {
    return this->resource.isContainedIn(rsrc);
}

//@Override
/*public*/ void close() {
    this->resource.close();
}

//@Override
/*public*/ boolean exists() {
    return this->resource.exists();
}

//@Override
/*public*/ boolean isDirectory() {
    return this->resource.isDirectory();
}

//@Override
/*public*/ long lastModified() {
    return this->resource.lastModified();
}

//@Override
/*public*/ long length() {
    return this->resource.length();
}

//@Override
@Deprecated
/*public*/ URL getURL() {
    return this->resource.getURL();
}

//@Override
/*public*/ File getFile() throws IOException {
    return this->resource.getFile();
}

//@Override
/*public*/ String getName() {
    return this->resource.getName();
}

//@Override
/*public*/ InputStream getInputStream() throws IOException {
    return this->resource.getInputStream();
}

//@Override
/*public*/ boolean delete() throws SecurityException {
    return this->resource.delete();
}

//@Override
/*public*/ boolean renameTo(Resource rsrc) throws SecurityException {
    return this->resource.renameTo(rsrc);
}

//@Override
/*public*/ String[] list() {
    return this->resource.list();
}

//@Override
/*public*/ Resource addPath(String string) throws IOException, MalformedURLException {
    return this->resource.addPath(string);
}

//@Override
/*public*/ ReadableByteChannel getReadableByteChannel() throws IOException {
    return this->resource.getReadableByteChannel();
}
#endif
