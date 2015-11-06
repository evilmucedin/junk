#include <unordered_map>
#include <memory>

using namespace std;

class LRUCache
{
private:
    struct Node
    {
        int _key;
        int _value;
        shared_ptr<Node> _next;
        shared_ptr<Node> _prev;
    };

    int _capacity;
    typedef unordered_map<int, shared_ptr<Node>> TData;
    TData _data;
    shared_ptr<Node> _head;
    shared_ptr<Node> _tail;

    void setHead(shared_ptr<Node> n)
    {
        n->_next = _head;
        n->_prev = nullptr;

        if (nullptr != _head)
        {
            _head->_prev = n;
        }

        _head = n;

        if (nullptr == _tail)
        {
            _tail = n;
        }
    }

    void remove(shared_ptr<Node> n)
    {
        if (nullptr != n->_prev)
        {
            n->_prev->_next = n->_next;
        }
        else
        {
            _head = n->_next;
        }

        if (nullptr != n->_next)
        {
            n->_next->_prev = n->_prev;
        }
        else
        {
            _tail = n->_prev;
        }
    }

public:
    LRUCache(int capacity)
        : _capacity(capacity)
    {

    }

    int get(int key)
    {
        TData::iterator toData = _data.find(key);
        if (_data.end() == toData)
        {
            return -1;
        }
        remove(toData->second);
        setHead(toData->second);
        return toData->second->_value;
    }

    void set(int key, int value)
    {
        TData::iterator toData = _data.find(key);
        if (_data.end() == toData)
        {
            shared_ptr<Node> n(new Node());
            n->_key = key;
            n->_value = value;
            if (_data.size() == _capacity)
            {
                _data.erase(_tail->_key);
                remove(_tail);
            }
            setHead(n);
            _data.insert(TData::value_type(key, n));
        }
        else
        {
            toData->second->_value = value;
            remove(toData->second);
            setHead(toData->second);
        }
    }
};
