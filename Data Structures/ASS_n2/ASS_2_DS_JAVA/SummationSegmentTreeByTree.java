public class SummationSegmentTreeByTree extends SegmentTreeByTree {
    /**
     * Constructor for creating a Segment Tree from an input array
     *
     * @param arr Input array for which Segment Tree needs to be constructed
     */
    public SummationSegmentTreeByTree(int[] arr) {
        super(arr);
    }


    /**
     * The method generates the total sum between [left, right] and retrieves it
     * @param left Start index of the query range
     * @param right End index of the query range
     * @return integer
     */
    @Override
    public int queryRange(int left, int right) {
        SegmentTreeNode temp = this.queryRangeHelper(this.root, left, right);
        return temp.getSum();
    }

    @Override
    public String toString() {
        SegmentTreeNode runner = this.root;
        return " [ " + preorderPrint(runner).substring(0, preorderPrint(runner).length() -1) + " ] ";
    }

    /**
     * Method to help retrieve String that represents nodes sum value in preorder traversal
     * @param runner root node
     * @return string that represents the tree
     */
    private String preorderPrint(SegmentTreeNode runner){
        if(runner == null) return "";
        String res = "";
        res += runner.getSum() + " ";
        res += preorderPrint((SegmentTreeNode) runner.getLeft());
        res += preorderPrint((SegmentTreeNode) runner.getRight());
        return res;
    }
}
