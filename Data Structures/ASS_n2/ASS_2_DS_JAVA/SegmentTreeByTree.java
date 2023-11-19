/**
 * An abstract base class for a segment tree data structure implemented using a tree structure.
 * Subclasses must implement the {@code queryRange} method to provide specific range query functionality.
 */
public abstract class SegmentTreeByTree implements SegmentTree {

    protected SegmentTreeNode root;
    protected int size;

    /**
     * Constructor for creating a Segment Tree from an input array
     * @param arr Input array for which Segment Tree needs to be constructed
     */
    public SegmentTreeByTree(int[] arr) {
        build(arr);
    }

    /**
     * Builds the segment tree from the given array of integers.
     *
     * @param arr the array of integers to build the segment tree from
     */
    @Override
    public void build(int[] arr) {
        size = 0;
        this.root = buildTree(arr, 0, arr.length - 1);
    }

    /**
     * Recursive function that helps to "build" function generate segment tree
     * @param arr the array of integers to build the segment tree from
     * @return SegmentTreeNode that represents the root of the generated tree
     */
    private SegmentTreeNode buildTree(int[] arr, int startingIndex,int endingIndex){
        if(startingIndex == endingIndex) {
            size++;
            return new SegmentTreeNode(startingIndex, endingIndex, arr[startingIndex], arr[startingIndex], arr[startingIndex], null, null);
        }
        int middle = startingIndex + (int) Math.floor((endingIndex - startingIndex)/2) ;
        SegmentTreeNode leftChild = buildTree(arr, startingIndex, middle);
        SegmentTreeNode rightChild = buildTree(arr, middle + 1, endingIndex);
        SegmentTreeNode parentNode = HelperRangeWithCal(startingIndex, endingIndex, leftChild, rightChild);
        this.size ++; // Increment the tree size
        parentNode.leftChild = leftChild;
        parentNode.rightChild = rightChild;
        return parentNode;
    }

    /**
     * Updates the element at the specified index in the original array and updates the segment tree accordingly.
     *
     * @param index the index of the element to update
     * @param value the new value of the element at the specified index
     */
    @Override
    public void update(int index, int value) {
       RecursiveUpdate(this.root, index, value);
    }

    /**
     * Recursive function to help update the whole tree after updating
     * the new value to the node located at index i
     * @param runner runned node to iterate over the tree
     * @param i the index of the element to update
     * @param val the new value of the element at the specific index
     */
    private void RecursiveUpdate(SegmentTreeNode runner, int i, int val){
        if(runner.getStart() == runner.getEnd()) { // In case we have reached the wanted node, update all his data :
            runner.setSum(val); runner.setMax(val); runner.setMin(val);
        }
        else{
            int middle = runner.getStart() + (runner.getEnd() - runner.getStart())/2;
            if(i <= middle)  // Thus the wanted node in the left subtree
                RecursiveUpdate((SegmentTreeNode)runner.getLeft(), i, val );
            else // Thus the wanted node in the right subtree
                RecursiveUpdate((SegmentTreeNode)runner.getRight(), i, val);
            SegmentTreeNode leftChild = (SegmentTreeNode)runner.getLeft();
            SegmentTreeNode rightChild = (SegmentTreeNode)runner.getRight();
            runner.setMin(Math.min(leftChild.getMin(), rightChild.getMin()));
            runner.setMax(Math.max(leftChild.getMax(), rightChild.getMax()));
            runner.setSum(leftChild.getSum() + rightChild.getSum());
        }
    }

    /**
     * Returns the number of elements in the original array that the segment tree was built from.
     *
     * @return the size of the original array
     */
    @Override
    public int size() {
        return CountLeafsRecusively(this.root);
    }

    /**
     * Recursive helping method to help count the number of leafs (the
     * number of leafs represents the number of values in the original array)
     * @param runner root node
     * @return integer
     */
    private int CountLeafsRecusively(SegmentTreeNode runner){
        if(runner == null) return 0;
        if(runner.leftChild == null && runner.rightChild == null) return 1;
        return CountLeafsRecusively((SegmentTreeNode) runner.getLeft()) + CountLeafsRecusively((SegmentTreeNode)runner.rightChild);
    }

    /**
     * Queries the Segment Tree for the minimum value in the given range. to be implemented by subclasses.
     * @param left Start index of the query range
     * @param right End index of the query range
     * @return Minimum value in the given range
     */
    @Override
    public abstract int queryRange(int left, int right);
    /**
     * Helper method for querying the Segment Tree 
     * @param node Current node of the Segment Tree
     * @param left Start index of the query range
     * @param right End index of the query range
     * @return A SegmentTreeNode that contains the minimum, maximum and sum values for the given range
     */
    protected SegmentTreeNode queryRangeHelper(SegmentTreeNode node, int left, int right) {
        return RecursiveQueryRangeHelper(node, left, right);
    }

    /**
     * Recursive method to help retrieve the SegmentTreeNode that represents the range [left, right]
     * @param runner running node
     * @param left left range
     * @param right right range
     * @return SegmentTreeNode object
     */
    private SegmentTreeNode RecursiveQueryRangeHelper(SegmentTreeNode runner, int left, int right){
        if(runner.getStart() == right && runner.getEnd() == left) // In case the range of runner fits exactly to the given ranges
            return runner;
        else{
            int middle = runner.getStart() + (runner.getEnd() - runner.getStart())/2;
            if(right <= middle)
                return RecursiveQueryRangeHelper((SegmentTreeNode) runner.getLeft(), left, right);
            else if(left > middle)
                return RecursiveQueryRangeHelper((SegmentTreeNode)runner.getRight(), left, right);
            else{
                SegmentTreeNode leftChild = RecursiveQueryRangeHelper((SegmentTreeNode)runner.getLeft(), left, middle);
                SegmentTreeNode rightChild = RecursiveQueryRangeHelper((SegmentTreeNode)runner.getRight(), middle + 1, right);
                return HelperRangeWithCal(left, right, leftChild, rightChild);
            }
        }
    }

    /**
     * The method helps to generate SegmentTreeNode by his left+right children
     * @param s starting pos
     * @param e ending pos
     * @param leftNode left child
     * @param rightNode right child
     * @return SegmentTreeNode object
     */
    private SegmentTreeNode HelperRangeWithCal(int s, int e,SegmentTreeNode leftNode, SegmentTreeNode rightNode){
        int min, max;
        int sum = leftNode.getSum() + rightNode.getSum();
        min = Math.min(leftNode.getMin(), rightNode.getMin());
        max = Math.max(leftNode.getMax(), rightNode.getMax());
        return new SegmentTreeNode(s, e, min, max, sum, null, null);
    }
}
