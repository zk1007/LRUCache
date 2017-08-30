#include<iostream>
#include<map>

using namespace std;

struct  CacheNode
{
    int key;    //¼ü
    int value;  //Öµ
    CacheNode *pre,*next;   //
    CacheNode(int k,int v):key(k),value(v),pre(NULL),next(NULL){}
};

//Ë«ÏòÁ´±í+map
class LRUCache
{
    public:
        LRUCache(int capacity)
        {
            size=capacity;
            head=NULL;
            tail=NULL;
        }

        void remove(CacheNode *node)
        {
            if(node->pre!=NULL)
            {
                node->pre->next=node->next;
            }
            else
            {
                head=node->next;
            }
            if(node->next!=NULL)
            {
                node->next->pre=node->pre;
            }
            else
            {
                tail=node->pre;
            }
        }

        void setHead(CacheNode *node)
        {
            node->next=head;
            node->pre=NULL;
            if(head!=NULL)
                head->pre=node;
            head=node;
            if(tail==NULL)
                tail=head;
        }

        int get(int key)
        {
            map<int,CacheNode*>::iterator it=mp.find(key);
            if(it!=mp.end())
            {
                CacheNode *node=it->second;
                remove(node);
                setHead(node);
                return node->value;
            }
            else
            {
                return -1;
            }
        }

        void set(int key,int val)
        {
            map<int,CacheNode*>::iterator it=mp.find(key);
            if(it!=mp.end())
            {
                CacheNode *node=it->second;
                node->value=val;
                remove(node);
                setHead(node);
            }
            else
            {
                CacheNode *newNode=new CacheNode(key,val);
                if(mp.size()>=size)
                {
                    map<int,CacheNode*>::iterator iter=mp.find(tail->key);
                    mp.erase(iter);
                    remove(tail);
                }
                setHead(newNode);
                mp[key]=newNode;
            }
        }
    private:
        int size;
        CacheNode *head;
        CacheNode *tail;
        map<int,CacheNode*>mp;
};

int main()
{
    LRUCache *lru=new LRUCache(10);
    lru->set(5,3);
    lru->set(3,2);
    cout<<lru->get(3)<<endl;
    return 0;
}
