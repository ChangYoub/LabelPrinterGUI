#include "xml.h"
#include <QDomDocument>
#include <QTextStream>
#include <QDir>
#include <QDebug>

Q_GLOBAL_STATIC(Xml, _Xml)

Xml::Xml(QObject *parent) : QObject(parent) {
}

Xml *Xml::getInstance()
{
    return _Xml();
}

void Xml::createSettingXml(void)
{
    QFileInfo fileInfo(PATH_SETTING);
    QString strPath = fileInfo.absolutePath();
    QDir dir;

    /* path에 해당 폴더가 없을 경우 생성 */;
    dir.mkpath(strPath);
    /* file path 획득 */
    strPath = fileInfo.absoluteFilePath();
    QFile file(strPath);
    QDomDocument domDocument;
    QDomElement domRoot;

    /* 파일 유무 확인 */
    if(!file.exists())       /* xml 파일이 없을 경우 */
    {
        /* xml header write */
        QDomNode domNodeDeclaration = domDocument.createProcessingInstruction(XML_DECLARATION_TARGET, XML_DECLARATION_DATA);
        domDocument.insertBefore(domNodeDeclaration, domDocument.firstChild());

        /* create xml Element */
        domRoot = domDocument.createElement(XML_SETUP);
        domDocument.appendChild(domRoot);

        QDomElement domElementRoot = domDocument.documentElement();

        if(!domElementRoot.isNull() && domElementRoot.nodeName() == XML_SETUP)
        {
            QDomNodeList domNodeList;
            domNodeList = domElementRoot.elementsByTagName(XML_TAG_POS);

            QDomElement domPos;
            QDomElement domTableText;

            if(domNodeList.count() == 0)
            {
                domPos = domDocument.createElement(XML_TAG_POS);
                domTableText = domDocument.createElement(XML_TAG_TABLE_TEXT);
                domElementRoot.appendChild(domPos);
                domElementRoot.appendChild(domTableText);

                domPos.setAttribute(XML_POS_POSXVAL, XML_POS_X_DEFAULT_VALUE);
                domPos.setAttribute(XML_POS_POSYVAL, XML_POS_Y_DEFAULT_VALUE);
                domTableText.setAttribute(XML_TABLE_COLUMN0, XML_DEFAULT_VALUE);
                domTableText.setAttribute(XML_TABLE_COLUMN1, XML_DEFAULT_VALUE);
                domTableText.setAttribute(XML_TABLE_COLUMN2, XML_DEFAULT_VALUE);
                domTableText.setAttribute(XML_TABLE_COLUMN3, XML_DEFAULT_VALUE);
                domTableText.setAttribute(XML_TABLE_COLUMN4, XML_DEFAULT_VALUE);
                domTableText.setAttribute(XML_TABLE_COLUMN5, XML_DEFAULT_VALUE);
            }
        }

        if(file.open(QIODevice::ReadWrite | QIODevice::Truncate))
        {
            QTextStream textStream(&file);
            textStream.setCodec(XML_CODEC);
            textStream << domDocument.toString();

            file.close();
        }
    }
}

void Xml::readPosXml(void)
{
    QFile file(PATH_SETTING);

    if(file.open(QIODevice::ReadOnly))
    {
        QDomDocument domDocument;
        domDocument.setContent(&file);

        QDomElement domElementRoot = domDocument.documentElement();

        if(!domElementRoot.isNull() && domElementRoot.nodeName() == XML_SETUP)
        {
            QDomElement domElementSetup = domElementRoot.firstChildElement();

            while(!domElementSetup.isNull())
            {
                while(!domElementSetup.isNull())
                {
                    if(domElementSetup.nodeName() == XML_TAG_POS)
                    {
                        m_posX = domElementSetup.attribute(XML_POS_POSXVAL);
                        m_posY = domElementSetup.attribute(XML_POS_POSYVAL);
                    }
                    domElementSetup = domElementSetup.nextSiblingElement();
                }
            }
        }
        file.close();
    }
}

void Xml::writeXmlPos(const QString posX, const QString posY)
{
    QFileInfo fileInfo(PATH_SETTING);
    QString strPath = fileInfo.absoluteFilePath();

    QFile file(strPath);
    QDomDocument domDocument;
    QDomElement domRoot;

    if(file.exists())
    {
        file.open(QIODevice::ReadOnly);
        domDocument.setContent(&file);
        domRoot = domDocument.documentElement();
        file.close();

        QDomElement domElementRoot = domDocument.documentElement();

        if(!domElementRoot.isNull() && domElementRoot.nodeName() == XML_SETUP)
        {
            QDomElement domPos;
            QDomNodeList domNodeList;
            domNodeList = domElementRoot.elementsByTagName(XML_TAG_POS);

            if(domNodeList.count() > 0) {
                domPos = domNodeList.at(0).toElement();
            }

            domPos.setAttribute(XML_POS_POSXVAL, posX);
            domPos.setAttribute(XML_POS_POSYVAL, posY);
        }

        if(file.open(QIODevice::ReadWrite | QIODevice::Truncate))
        {
            QTextStream textStream(&file);
            textStream.setCodec(XML_CODEC);
            textStream << domDocument.toString();

            file.close();
        }
    }
}

void Xml::writeXmlTableText(const QStringList columnText)
{
    QFileInfo fileInfo(PATH_SETTING);
    QString strPath = fileInfo.absoluteFilePath();

    QFile file(strPath);
    QDomDocument domDocument;
    QDomElement domRoot;

    if(file.exists())
    {
        file.open(QIODevice::ReadOnly);
        domDocument.setContent(&file);
        domRoot = domDocument.documentElement();
        file.close();

        QDomElement domElementRoot = domDocument.documentElement();

        if(!domElementRoot.isNull() && domElementRoot.nodeName() == XML_SETUP)
        {
            QDomElement domTableText;
            QDomNodeList domNodeList;
            domNodeList = domElementRoot.elementsByTagName(XML_TAG_TABLE_TEXT);

            if(domNodeList.count() > 0)
            {
                domTableText = domNodeList.at(0).toElement();
            }

            domTableText.setAttribute(XML_TABLE_COLUMN0, columnText.at(0));
            domTableText.setAttribute(XML_TABLE_COLUMN1, columnText.at(1));
            domTableText.setAttribute(XML_TABLE_COLUMN2, columnText.at(2));
            domTableText.setAttribute(XML_TABLE_COLUMN3, columnText.at(3));
            domTableText.setAttribute(XML_TABLE_COLUMN4, columnText.at(4));
            domTableText.setAttribute(XML_TABLE_COLUMN5, columnText.at(5));
        }

        if(file.open(QIODevice::ReadWrite | QIODevice::Truncate))
        {
            QTextStream textStream(&file);
            textStream.setCodec(XML_CODEC);
            textStream << domDocument.toString();

            file.close();
        }
    }
}

bool Xml::readXmlTableText(void)
{
    bool bReturn = false;

    QFile file(PATH_SETTING);

    if(file.open(QIODevice::ReadOnly))
    {
        QDomDocument domDocument;
        domDocument.setContent(&file);

        QDomElement domElementRoot = domDocument.documentElement();

        if(!domElementRoot.isNull() && domElementRoot.nodeName() == XML_SETUP)
        {
            QDomElement domElementSetting = domElementRoot.firstChildElement();

            while(!domElementSetting.isNull())
            {
                while(!domElementSetting.isNull())
                {
                    if(domElementSetting.nodeName() == XML_TAG_TABLE_TEXT)
                    {
                        m_column[0] = domElementSetting.attribute(XML_TABLE_COLUMN0);
                        m_column[1] = domElementSetting.attribute(XML_TABLE_COLUMN1);
                        m_column[2] = domElementSetting.attribute(XML_TABLE_COLUMN2);
                        m_column[3] = domElementSetting.attribute(XML_TABLE_COLUMN3);
                        m_column[4] = domElementSetting.attribute(XML_TABLE_COLUMN4);
                        m_column[5] = domElementSetting.attribute(XML_TABLE_COLUMN5);
                        bReturn = true;
                    }
                    domElementSetting = domElementSetting.nextSiblingElement();
                }
            }
        }
        file.close();
    }

    return bReturn;
}


int Xml::getXmlPosX(void)
{
    readPosXml();
    return m_posX.toInt();
}

int Xml::getXmlPosY(void)
{
    readPosXml();
    return m_posY.toInt();
}

QString Xml::getXmlTableText(const int columnCnt)
{
    QString strColumnText;

    bool state = readXmlTableText();
    if(columnCnt <= XML_TABLE_COLUMN_COUNT_MAX && state == true) {
        strColumnText = m_column[columnCnt];
    }

    return strColumnText;
}
