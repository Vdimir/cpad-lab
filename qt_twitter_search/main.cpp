#include <QApplication>
#include <QLoggingCategory>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDomDocument>
#include <QtNetworkAuth>

#include <cstdio>
const char g_cszUrl[] = "http://feeds.bbci.co.uk/news/rss.xml";

void outText(
    QTextStream& rOut, const QDomElement& rcParent,
    const QString& rcChildName, const QString& rcItemTitle);

int main(int nArgC, char* apszArgV[])
{
    QApplication app(nArgC, apszArgV);
    QTextStream out(stdout), err(stderr);


    //
    QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");
    //
    QString hostName { g_cszUrl };
    QNetworkAccessManager manager;
    manager.connectToHost(hostName);
    //
    QUrl url{ hostName };
    QNetworkRequest request(url);
    //
    QNetworkReply* pReply = manager.get(request);
    QEventLoop loop;
    QObject::connect(pReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    //
    const int cnError = pReply->error();
    if (cnError != 0) {
        err << "HTTP error: " << cnError << endl;
        return -1;
    }
    //
    QByteArray resData = pReply->readAll();
    QString strErrorMsg;
    int nErrorRow, nErrorCol;
    QDomDocument document;
    const bool cbSuccess = document.setContent(
        resData, true, &strErrorMsg, &nErrorRow, &nErrorCol);
    if (!cbSuccess) {
        err << "XML error at " << nErrorRow << " : " << nErrorCol << ": " << strErrorMsg << endl;
        return -1;
    }
    QDomElement elementRss = document.firstChildElement("rss");
    if (!elementRss.isNull()) {
        QDomElement elementChannel = elementRss.firstChildElement(
            "channel");
        while (!elementChannel.isNull()) {
            outText(out, elementChannel, "title", "Channel title");
            //
            QDomElement elementItem = elementChannel.firstChildElement(
                "item");
            while (!elementItem.isNull()) {
                out << " Item:" << endl;
                outText(out, elementItem, "title", " Title");
                outText(out, elementItem, "description", " Description");
                outText(out, elementItem, "pubDate", " Date");
                outText(out, elementItem, "link", " Link");
                //
                elementItem = elementItem.nextSiblingElement(
                    "item");
            } // while (!elementItem.isNull()
            //
            elementChannel = elementChannel.nextSiblingElement(
                "channel");
        } // while (!elementChannel.isNull())
    } // if (!elementRss.isNull())
} // main()
void outText(
    QTextStream& rOut, const QDomElement& rcParent,
    const QString& rcChildName, const QString& rcItemTitle)
{
    QDomElement element = rcParent.firstChildElement(rcChildName);
    if (element.isNull())
        return;
    //
    QDomNode node = element.firstChild();
    if (!node.isText())
        return;
    //
    QDomText section = node.toText();
    if (section.isNull())
        return;
    //
    rOut << rcItemTitle << ": " << section.data() << endl;
} // outText()
