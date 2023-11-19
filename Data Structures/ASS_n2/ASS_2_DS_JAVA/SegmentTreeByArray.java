/**
 * This abstract class represents a segment tree implementation using an array
 * and provides methods to build, update, and query the tree.
 */
public abstract class SegmentTreeByArray implements SegmentTree {
	 protected int[] tree;
	 protected int size;

    /**
     * Constructor for initializing the segment tree with the given input array.
     * @param arr the input array
     */
    public SegmentTreeByArray(int[] arr) {
        int n = arr.length;
        int height = (int)Math.ceil(Math.log(n) / Math.log(2));
        this.size = 2* (int)Math.pow(2,height) - 1;
        this.tree =new int[this.size];
        for(int i = 0; i < size; i ++) // initial the values to -1000 to know in toString where switch to "-"
            this.tree[i] = -1000;
        build(arr);
    }

    /**
     * Builds the segment tree from the input array.
     * @param arr the input array
     */
    public abstract void build(int[] arr);

    /**
     * Updates the value at the specified index and updates the segment tree accordingly.
     * @param index the index of the element to update in the array
     * @param value the new value to replace the existing value
     */
    public abstract void update(int index, int value);

    /**
     * Queries the segment tree for a range of elements.
     * @param left the left index of the range
     * @param right the right index of the range
     * @return the result of the query operation
     */

    public int queryRange(int left, int right){return query(0,0, this.size() -1, left, right);}

    /**
     * Abstract method for query operation, to be implemented by subclasses.
     * @param node the current node
     * @param start the start index
     * @param end the end index
     * @param left the left index
     * @param right the right index
     * @return the result of the query operation
     */
    protected abstract int query(int node, int start, int end, int left, int right);


    /**
     * The members inside the array representing the segment tree are printed according to their indexes in the array.
	 * When the members are surrounded by "[ ]" and exactly one space between each number and between the brackets. 
	 * For example, for the tree [10,4,6,1,3,2,4] " [ 10 4 6 1 3 2 4 ] " will be returned 
     */
    @Override
    public String toString() {
        String res = " [ ";
        for(int i = 0 ; i <this.tree.length; i++) {
            if (this.tree[i] == -1000)
                res += "- ";
            else {
                res += this.tree[i];
                res += " ";
            }
        }
        res += "] ";
        return res;
    }

    /**
     * Returns the number of elements in the original array that the segment tree was built from.
     *
     * @return the size of the original array
     */
    @Override
    public int size() {
      int numOfNumbers = 0;
      for(int i = 0; i < this.size; i++)
          if(this.tree[i] != -1000)
              numOfNumbers ++;
      return (numOfNumbers + 1)/2;
    }
}