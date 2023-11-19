public class SummationSegmentTreeByArray extends SegmentTreeByArray {
    public SummationSegmentTreeByArray(int[] arr) {
        super(arr);
    }

    /**
     * The method builds the summation segment tree by array using recursive helping function
     * @param arr the input array
     */
    @Override
    public void build(int[] arr) {
        RecursiveBuildArraySegmentTree(arr,0, 0, arr.length -1);
    }

    private void RecursiveBuildArraySegmentTree(int[] arr, int treeIndex, int low, int  height){
        if(low ==  height){
            this.tree[treeIndex] = arr[ height];
            return;
        }
        int middle = low + ( height - low)/2;
        RecursiveBuildArraySegmentTree(arr, 2* treeIndex + 1, low, middle);
        RecursiveBuildArraySegmentTree(arr, 2* treeIndex + 2, middle + 1,  height);
        this.tree[treeIndex] = this.tree[2 *treeIndex + 1] + this.tree[2 * treeIndex +2] ;
    }

    /**
     * Helper method to execute the query in recursion
     * @param node running index
     * @param start lower bound
     * @param end upper bound
     * @param left left range in the array
     * @param right right range in the array
     * @return integer
     */
    @Override
    protected int query(int node, int start, int end, int left, int right) {
        if(left <= start && right >=  end) return this.tree[node];
        else if (left >  end || right < start)
            return 0;
        else{
            int middle = start + (end - start) /2;
            int leftNode = query(2 * node +1, start, middle, left, right);
            int rightNode = query(2 * node +2, middle +1,  end, left, right);
            return leftNode + rightNode; // return the sum of the two nodes
        }
    }

    /**
     * The method updates the value of given element in the tree array by his index
     * @param index the index of the element to update in the array
     * @param value the new value to replace the existing value
     */
    @Override
    public void update(int index, int value) {
        RecursiveUpdateHelper(0, 0, this.size() -1, index, value);
    }

    /**
     * Recursive method to help update
     * @param treeIndex running index of the tree
     * @param low lower bound
     * @param height upper bound
     * @param index the index of the element to update in the array
     * @param value the new value to replace the existing value
     */
    private void RecursiveUpdateHelper(int treeIndex, int low, int height, int index, int value){
        if(low == height) this.tree[treeIndex] = value;
        else{
            int middle = low + (height - low) /2;
            if(index <= middle) RecursiveUpdateHelper(2 * treeIndex +1, low, middle, index, value);
            else RecursiveUpdateHelper(2 * treeIndex +2, middle +1, height, index, value);
            this.tree[treeIndex] = this.tree[2 * treeIndex + 1] + this.tree[2 * treeIndex +2];
        }
    }
}
