#include "connectionlist.h"

ConnectionList::ConnectionList():
    m_uidCounter(1)
{
}

int ConnectionList::addItem(ConnectionItem Item)
{
    if(Item.Name != "") {
        emit preItemAppended();
        m_uidCounter++;
        Item.uid = m_uidCounter;
        m_connectionItemList.append(Item);
        emit postItemAppended();
        return m_uidCounter;
    }
    return 0;
}

bool ConnectionList::removeByPath(const QString &p_path)
{
    int index = findPathPos(p_path);
    if(index < 0)
        return false;

    emit preItemRemoved(index);
    m_connectionItemList.removeAt(index);
    emit postItemRemoved(index);
    emit dataChanged(index);
    return true;
}

QList<ConnectionItem> ConnectionList::items() const
{
    return m_connectionItemList;
}

ConnectionItem ConnectionList::itemByPath(QString p_path)
{
    int i = findPathPos(p_path);
    if(i==-1)
        return ConnectionItem();
    return m_connectionItemList.at(i);
}

bool ConnectionList::setItemByPath(QString p_path, const ConnectionItem &p_item)
{
    int index = findPathPos(p_path);
    if(index < 0)
        return false;

    m_connectionItemList[index]=p_item;
    emit dataChanged(index);
    return true;
}

int ConnectionList::findPathPos(const QString &Path)
{
    int index = -1;
    for(int i = 0; i < m_connectionItemList.size(); ++i){
        if(m_connectionItemList.at(i).NmPath==Path){
            index = i;
            break;
        }
    }
    return index;
}
