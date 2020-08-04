/**
 * Segment tree for C++
 * Documentation coming soon!
*/

//Enable if you want to use static rather than dynamic memory to allocate new treap nodes:
//#define USE_STATIC

namespace segtree {
    typedef int64_t num_items;
    typedef int64_t num_nodes;
    //Change this constant to the maximum possible number of items in your segment tree.
    const num_items MAX_ITEMS = 100000;
    
    //node_info(i, l, r) represents a node in a segment tree which is located at index i and represents the interval [l, r]
    struct node_info {
        num_nodes index;
        //Here, B stands for "boundary"
        num_items leftB;
        num_items rightB;
        node_info(num_nodes i, num_items l, num_items r)
          : index(i), leftB(l), rightB(r) {}

       //Return the info of the left child of this node
       node_info leftChild() {
           num_items midB = (leftB+rightB)/2;
           return node_info(index+1, leftB, midB);
       }
       //Return the info of the right child of this node
       node_info rightChild() {
           num_items midB = (leftB+rightB)/2;
           return node_info(index+2*(midB-leftB+1), midB+1, rightB);
       }
    };

    //A segment tree representing a list of "item"s, which can updated using an "update" object
    //Here, both item and update must implement the operator+() function.
    //For both item and update, operator+() should be associative (not necessarily commutative).
    template<class item, class update> struct segtree {
       num_items size;
#ifdef USE_STATIC
       item nodes[2*MAX_ITEMS];
       //Is this node marked for an update?
       bool markedForUpdate[2*MAX_ITEMS];
       //Lazy updates for certain nodes
       update lazyUpdates[2*MAX_ITEMS];
#else
       std::vector<item> nodes;
       //Is this node marked for an update?
       std::vector<bool> markedForUpdate;
       //Lazy updates for certain nodes
       std::vector<update> lazyUpdates;
#endif
       //The identity of the operator+() function (this is not always 0, such as if operator+ is actually std::min or std::max)
       item identItem;

       //Given a node and its current value as well as an update, return the new value of the node after the update is applied
       typedef item (*updater)(node_info, item, update);
       updater applyUpdate;
       
       segtree() : size(0) {}
       //Initialize a segment tree with a given array, the length of that array, the identity of adding two items, and an updater
       template<class item_array> segtree(item_array arr, num_items numItems, item identityItem, updater curUpdater) {
           size = numItems;
           identItem = identityItem;
           applyUpdate = curUpdater;

#ifndef USE_STATIC
           nodes = std::vector<item>(2*size);
           markedForUpdate = std::vector<bool>(2*size);
           lazyUpdates = std::vector<update>(2*size);
#endif

           initializeWithArray(arr, rootNode());
       }

       //Return info about the root node of the segment tree
       node_info rootNode() {
           return node_info(0, 0, size-1);
       }

       //Initialize the given node in the segment tree and all of its children using the given array
       template<class item_array> void initializeWithArray(item_array arr, node_info curNode) {
           markedForUpdate[curNode.index] = false;
           
           //If this is a singleton node, then set the node to the appropriate value in the array:
           if (curNode.leftB == curNode.rightB) {
               nodes[curNode.index] = arr[curNode.leftB];
           } else {
               //Otherwise, calculate the two children nodes and merge:
               node_info leftC = curNode.leftChild(), rightC = curNode.rightChild();
               initializeWithArray(arr, leftC);
               initializeWithArray(arr, rightC);
               nodes[curNode.index] = nodes[leftC.index]+nodes[rightC.index];
           }
       }

       //Schedule an update to be performed at some later point on the given node
       void schedUpdate(node_info curNode, update futureUpdate) {
           //Merge the two updates if this node already has an update:
           if (markedForUpdate[curNode.index]) {
               lazyUpdates[curNode.index] = lazyUpdates[curNode.index]+futureUpdate;
           } else {
               //Otherwise, mark the node for an update and store the update:
               markedForUpdate[curNode.index] = true;
               lazyUpdates[curNode.index] = futureUpdate;
           }
       }
       //Apply the given update to the given node and propogate to its neighbors
       void updateNodeAndPropogate(node_info curNode, update curUpdate) {
           nodes[curNode.index] = applyUpdate(curNode, nodes[curNode.index], curUpdate);

           //If this is not a singleton interval, propogate the update to its neighbors:
           if (curNode.leftB < curNode.rightB) {
               schedUpdate(curNode.leftChild(), curUpdate);
               schedUpdate(curNode.rightChild(), curUpdate);
           }
       }
       //Apply a lazy update to the given node if the node is marked for updating
       void handleLazyUpdates(node_info curNode) {
           if (markedForUpdate[curNode.index]) {
               updateNodeAndPropogate(curNode, lazyUpdates[curNode.index]);
               markedForUpdate[curNode.index] = false;
           }
       }
       
       //Update all items in the interval [queryLeftB, queryRightB]
       void updateInterval(num_items queryLeftB, num_items queryRightB, update newUpdate) {
           return updateIntervalHelper(rootNode(), queryLeftB, queryRightB, newUpdate);
       }
       //Update all items in the interval [queryLeftB, queryRightB], assuming that the interval is a subset of the interval represented by the given node
       void updateIntervalHelper(node_info curNode, num_items queryLeftB, num_items queryRightB, update newUpdate) {
           //Handle any lazy updates first:
           handleLazyUpdates(curNode);
           //printf("%" PRId64 " %" PRId64 " | %" PRId64 " %" PRId64 " | %" PRId64 "\n", queryLeftB, queryRightB, curNode.leftB, curNode.rightB, nodes[curNode.index]);
           
           //Return if the interval is empty:
           if (queryLeftB > queryRightB) return;
           //Update the current node if the two intervals coincide:
           if ((curNode.leftB == queryLeftB) && (curNode.rightB == queryRightB)) {
               updateNodeAndPropogate(curNode, newUpdate);
               return;
           }
           
           //Otherwise, traverse the two children and merge:
           num_items midBound = (curNode.leftB+curNode.rightB)/2;
           node_info leftC = curNode.leftChild(), rightC = curNode.rightChild();
           updateIntervalHelper(leftC, queryLeftB, std::min(queryRightB, midBound), newUpdate);
           updateIntervalHelper(rightC, std::max(midBound+1, queryLeftB), queryRightB, newUpdate);
           nodes[curNode.index] = nodes[leftC.index]+nodes[rightC.index];
       }

       //Calculate the merge of all items in the interval [queryLeftBound, queryRightBound]
       item calcMerge(num_items queryLeftB, num_items queryRightB) {
           return calcMergeHelper(rootNode(), queryLeftB, queryRightB);
       }
       //Calculate the merge of all items in the interval [queryLeftB, queryRightB], assuming that the interval is a subset of the interval represented by the given node
       item calcMergeHelper(node_info curNode, num_items queryLeftB, num_items queryRightB) {
           //Handle any lazy updates first:
           handleLazyUpdates(curNode);
           //printf("%" PRId64 " %" PRId64 " | %" PRId64 " %" PRId64 " | %" PRId64 "\n", queryLeftB, queryRightB, curNode.leftB, curNode.rightB, nodes[curNode.index]);
           
           //Return the identity if the interval is empty:
           if (queryLeftB > queryRightB) return identItem;
           //Return the given node if the two intervals coincide:
           if ((curNode.leftB == queryLeftB) && (curNode.rightB == queryRightB)) return nodes[curNode.index];
           
           //Otherwise, traverse the two children and merge:
           num_items midBound = (curNode.leftB+curNode.rightB)/2;
           item queryChild1 = calcMergeHelper(curNode.leftChild(), queryLeftB, std::min(queryRightB, midBound));
           item queryChild2 = calcMergeHelper(curNode.rightChild(), std::max(midBound+1, queryLeftB), queryRightB);
           return queryChild1+queryChild2;
       }
    };
}