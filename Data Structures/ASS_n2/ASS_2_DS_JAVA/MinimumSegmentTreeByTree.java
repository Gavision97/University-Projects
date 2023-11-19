public class MinimumSegmentTreeByTree extends SegmentTreeByTree {
    public MinimumSegmentTreeByTree(int[] arr) {
        super(arr);
    }

    @Override
    public int queryRange(int left, int right) {
        SegmentTreeNode temp = this.queryRangeHelper(this.root, left, right);
        return temp.getMin();
    }

    @Override
    public String toString() {
        SegmentTreeNode runner = this.root;
        return " [ " + preorderPrint(runner).substring(0, preorderPrint(runner).length() -1) + " ] ";
    }

    /**
     * Method to help retrieve String that represents nodes max value in preorder traversal
     * @param runner root node
     * @return string that represents the tree
     */
    private String preorderPrint(SegmentTreeNode runner){
        if(runner == null) return "";
        String res = "";
        res += runner.getMin() + " ";
        res += preorderPrint((SegmentTreeNode) runner.getLeft());
        res += preorderPrint((SegmentTreeNode) runner.getRight());
        return res;
    }
}
