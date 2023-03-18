#include "connectionlist.h"
#include <QException>

ConnectionList::ConnectionList():
    m_uidCounter(1)
{

}

int ConnectionList::addItem(connectionItem Item)
{
    if(Item.Name != ""){
        emit preItemAppended();
        m_uidCounter++;
        Item.uid = m_uidCounter;
        m_list.append(Item);
        emit postItemAppended();
        return m_uidCounter;
    }
    return 0;
}

bool ConnectionList::removeItem(int index)
{
    bool ret = true;
    try {
        if(index < 0 || index>=m_list.size()){
            throw false;
        }
         emit preItemRemoved(index);
         m_list.removeAt(index);
         emit postItemRemoved(index);
    } catch (bool &e) {
        ret = e;
    }
    return ret;
}

bool ConnectionList::removeByKey(int p_key)
{
    bool ret = true;
    try {
        int index=-1;
        index=findKeyPos(p_key);
        if(index < 0){
            throw false;
        }

         emit preItemRemoved(index);
         m_list.removeAt(index);
         emit postItemRemoved(index);
    } catch (bool &e) {
        ret = e;
    }
    return ret;
}

bool ConnectionList::removeByPath(const QString &p_path)
{
    bool ret = true;
    try {
        int index=-1;
        index=findPathPos(p_path);
        if(index < 0){
            throw false;
        }
        emit preItemRemoved(index);
        m_list.removeAt(index);
        emit postItemRemoved(index);
        emit dataChanged(index);
    } catch (bool &e) {
        ret = e;
    }
    return ret;
}

QList<connectionItem> ConnectionList::items() const
{
    return m_list;
}

QList<QString> ConnectionList::paths() const
{
    QList<QString> keys;
    for(connectionItem itm: m_list){
        keys.append(itm.NmPath);
    }
    return keys;
}

connectionItem ConnectionList::itemByKey(int p_key)
{
    try {
        int index=-1;
        index=findKeyPos(p_key);
        if(index < 0){
            throw false;
        }
       return  m_list[index];
        emit dataChanged(index);
    } catch (bool &e) {
        return connectionItem();
    }
}

connectionItem ConnectionList::itemByPath(QString p_path)
{
    int i = findPathPos(p_path);

    if(i==-1){
        return connectionItem();
    }

    return m_list.at(i);
}

bool ConnectionList::setItemAt(int index, const connectionItem &p_item)
{
    bool ret = true;
    try {
        if(index < 0 || index>=m_list.size()){
            throw false;
        }
         m_list[index]=p_item;
         emit dataChanged(index);
    } catch (bool &e) {
        ret = e;
    }

    return ret;
}

bool ConnectionList::setItemByKey(int p_key,const connectionItem &p_item)
{
    bool ret = true;
    try {
        int index=-1;
        index=findKeyPos(p_key);
        if(index < 0){
            throw false;
        }
        m_list[index]=p_item;
        emit dataChanged(index);
    } catch (bool &e) {
        ret = e;
    }
    return ret;
}

bool ConnectionList::setItemByPath(QString p_path, const connectionItem &p_item)
{
    bool ret = true;
    try {
        int index=-1;
        index=findPathPos(p_path);
        if(index < 0){
            throw false;
        }
        m_list[index]=p_item;
        emit dataChanged(index);
    } catch (bool &e) {
        ret = e;
    }
    return ret;
}

int ConnectionList::findKeyPos(int p_key)
{
    int index=-1;
    for(int i = 0; i < m_list.size(); ++i){
        if(m_list.at(i).uid==p_key){
            index=i;
            break;
        }
    }
    return index;
}

int ConnectionList::findPathPos(const QString &Path)
{
    int index=-1;
    for(int i = 0; i < m_list.size(); ++i){
        if(m_list.at(i).NmPath==Path){
            index=i;
            break;
        }
    }
    return index;
}
