/**
 * heap for C++
 * Documentation coming soon!
*/

#include <cstdint>

namespace heap {
    typedef int64_t num_items;
    //Change this constant to the maximum possible number of items in your heap.
    const num_items MAX_ITEMS = 400000;

    //This class should be used if you want to make something simple, like a heap<singleton<int64_t>> or a heap<singleton<double>>.
    //However, in most cases, a std::priority_queue<int64_t> is much better than using a heap<singleton<k>>, because that way, you can use the standard library and you do not have to copy and paste in all this code.
    template<class item_key> struct singleton {
        item_key key;
        bool operator<(singleton other) { return key < other.key; }

        singleton() {}
        singleton(item_key k) : key(k) {}
    };

    //This class should be used if you want to identify elements by some identifier key, but you want to compare them using some val which is separate from the identifier key.
    //This is useful for Dijkstra's algorithm, where we want to identify elements by their vertex number in the graph, but we want to compare elements by their distance from the source vertex.
    template<class item_key, class item_value> struct pair {
        item_key key;
        item_value val;
        bool operator<(pair other) { return val < other.val; }
        
        pair() {}
        pair(item_key k, item_value v) : key(k), val(v) {}
    };
        
    template<class item> struct heap {
        item list[MAX_ITEMS];
        num_items length;
        num_items inverseList[MAX_ITEMS];
        typedef decltype(list[0].key) item_key;
        
        heap() : length(0) {}
        
        bool itemExists(item_key key) {
            return (inverseList[key] < length) && (list[inverseList[key]].key == key);
        }
        
        bool updateHeap(item_key key, item newItem) {
            if (!itemExists(key)) return false;
            updateHeapByIndex(inverseList[key], newItem);
            return true;
        }
        
        void updateHeapByIndex(num_items index, item newItem) {
            //First, just put the item in the right index:
            list[index] = newItem;
            inverseList[list[index].key] = index;
            
            //Then, if the item has a parent, keep moving it up until it is no longer less than its parent:
            while (index && (newItem < list[(index-1)/2])) {
                list[index] = list[(index-1)/2];
                inverseList[list[index].key] = index;

                index = (index-1)/2;
                list[index] = newItem;
                inverseList[list[index].key] = index;
            }
            
            //If the item has a child:
            while (2*index+1 < length) {
                num_items nextIndex = -1;
                //If the item's first child is less than the item, then they need to switch.
                if (list[2*index+1] < newItem) nextIndex = 2*index+1;
                //If the item's second child is less than both the item and the first child, then item needs to switch with the second child instead of the first child. (This ensures that the lesser child always becomes the parent.)
                if (2*index+2 < length && (list[2*index+2] < newItem) && (list[2*index+2] < list[2*index+1])) nextIndex = 2*index+2;
                //Finally, if we needed to switch the child and parent, then we do so here:
                if (nextIndex >= 0) {
                    list[index] = list[nextIndex];
                    inverseList[list[index].key] = index;

                    index = nextIndex;
                    list[index] = newItem;
                    inverseList[list[index].key] = index;
                }
                //If no switch was necessary, then the item is finally in the right place.
                else break;
            }
        }
        
        bool insertItem(item newItem) {
            //Check if there is already an item with the same key:
            if (!itemExists(newItem.key)) {
                //If not, append the heap with the new item and return true:
                updateHeapByIndex(length++, newItem);
                return true;
            }
            //Otherwise, insertion failed, so return false:
            else return false;
        }
        
        bool deleteItem(item_key key) {
            //Check if there is actually an item with the given key:
            if (itemExists(key)) {
                //If so, delete this item by moving the last item to where the item with item_key key was, and then return true:
                length--;
                if (inverseList[key] != length) updateHeapByIndex(inverseList[key], list[length]);
                return true;
            }
            //Otherwise, deletion failed, so return false:
            else return false;
        }
        
        item extractTop() {
            //Return garbage if heap is empty:
            if (length == 0) return list[0];

            //To get rid of the top element, just update the heap by replacing the top element with the last element:
            item top = list[0];
            updateHeapByIndex(0, list[--length]);
            return top;
        }
    };
}