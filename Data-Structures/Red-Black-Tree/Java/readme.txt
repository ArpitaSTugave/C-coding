Problem: Build Efficient Red Black Tree with following functionality:
? Include ID and its corresponding count as each node. Arrange the tree with respect to the ID.
? As the count of an ID is increased, count is incremented if ID is present else ID should be inserted.
? As the count of an ID is reduced, count is decremented if ID is present else if count goes below 0; remove the corresponding ID.
? Previous n: command should display the previous closest ID to the n.
? Next n: command should display the next closest ID to the n.
? In Range n: command should display the sum of the count of the IDs in the given range.
? Count n: should display the respective count of n.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Solution: In the program solution presented JAVA complier has been used.
Program Structure: The program implements the following methods: TotalcountItems, createNode , createBlackNode , createRedNode , createNullLeafNode , 
sortedArray , insertElement , deleteElement , increaseCount , increasecountId , reduceCount , reducecountId , searchElement , nextMethod , previousMethod , 
countItems , printcount , inRangeSearch , printTree, rotateRight , rotateLeft , findingSiblingNode , leftChild , insertNode , insertPart , deleteNode , 
deleteOneChild , deleteCase, redBlackTreePrint.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1. Tree Initialization: Tree is initialized with the time complexity of O(n).
Program Flow: main -> sortedArray -> createNode (recursively)
Function Prototype:
public sortedArray(int IDarr[], int countarr[], int start, int end)
public Node createNode(int data, int count, Node left , Node right)
Algorithm:
? ‘Main’ function calls ‘sortedArray’ with array of the IDs to be initialized.
? Sorted array in turn calls ‘createNode’ recursively to initialize each node with its right and left counterparts.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
2. Increase count: Display count if ID is present happens in one go. Whereas, if ID is not present ID is inseted in O(logn).
Program Flow: main - > insertElement - > insertNode -> insertPart -> rotateRight / rotateLeft
Function Prototype:
public Node insertElement(Node root, int data, int countItems)
private Node insertNode(Node parentNode, Node root, int data, int countItems)
private Node insertPart(Node parentNode, Node root, int data, int countItems, boolean isLeft)
private void rotateRight(Node root, boolean colorChange)
private void rotateLeft(Node root, boolean colorChange)
Algorithm:
? The ‘main’ function calls ‘insertElement’ method. Which in turn calls ‘insetNode’.
? In ‘insetNode’ In Case empty node, create black node. Else create red leaf node. Check for various conditions of: parent is black, parent sibling is 
red, parent's parent is root using loops. ? Rotate Right, Rotate left conditions are implemented in the method ‘inserPart’.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
3. Decrease count: Display count if ID is present in one go. If count goes below 0, node with the respective ID is deleted in O(logn) time complexity.
Program Flow: main - > deleteNode -> deleteOneChild -> deleteCase
Function Prototype:
private void deleteNode(Node root, int data, AtomicReference<Node> rootReference)
private void deleteOneChild(Node nodeToBeDelete, AtomicReference<Node> rootReference)
private void deleteCase(Node doubleBlackNode, AtomicReference<Node> rootReference)
Algorithm: ? Find the node to be deleted using binary search tree traversal. ? If node to be deleted has 2 non- null children, 
replace it with its in order successor. ? If node to be deleted is red, then just delete it. ? If node to be deleted is black but has one red child, 
replace it with that child, and change colour of child to black. ? Otherwise, double black situation, which gives 6 cases.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
4. Display Count: Count is displayed after searching for the ID in O(logn) complexity.
Program Flow: main -> countItems -> printcount
Function Prototype:
public void countItems (Node root, int data)
public void printcount(Node root, int data)
Algorithm:
? Main function calls 'countItems’, which in turn calls ‘printcount’.
? In 'countItems’ corresponding count of the root is displayed.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
5. Display Previous ID: Highest previous ID is displayed.
Program Flow: main -> previousMethod
Function Prototype:
public int previousMethod(Node root, int data)
Algorithm:
? Main function calls ‘previousMethod’ which iteratively finds previous highest ID.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
6. Display Next ID: Smallest previous ID is displayed.
Program Flow: main -> nextMethod
Function Prototype:
public Node nextMethod(Node root, int data)
Algorithm:
? Main function calls ‘previousMethod’ which iteratively finds lowest next ID.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
7. Display sum of count of IDs in range: Total count of the respective IDs in the range specified is displayed.
Program Flow: main -> inRangeSearch
Function Prototype:
public void inRangeSearch(Node root, int data1 , int data2)
Algorithm:
? Main function calls ‘inRangeSearch’ which iteratively find total of counts of the respective IDs in this range.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#############################################################################################################################################################
To compile: In order to complie and run bbst.java file use command:
~@make
~@java bbst [filename]
When using 8GB machine:
~@make
~@java –d64 –Xmx6g bbst [filename]

################################################################################################################################################################
Conclusion: Efficient Red Black tree is implemented for features of increase, reduce, count, inrange, next and previous operations.