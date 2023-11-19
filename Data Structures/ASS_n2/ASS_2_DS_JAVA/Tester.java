import java.util.Iterator;

/**
 * This is a testing framework. Use it extensively to verify that your code is working
 * properly.
 */
public class Tester {

    private static boolean testPassed = true;
    private static int testNum = 0;

    /**
     * This entry function will test all classes created in this assignment.
     * @param args command line arguments
     */
    public static void main(String[] args) {

        // Each function here should test a different class. you should test here every class you created.

        //SegmentTrees
        testMaximumSegmentTreeByTree();
        testMinimumSegmentTreeByTree();
        testSummationSegmentTreeByTree();
        testMaximumSegmentTreeByArray();
        testMinimumSegmentTreeByArray();
        testSummationSegmentTreeByArray();

        //NumberAnalyzers
        testNumberAnalyzerByTrees();
        testNumberAnalyzerByArrays();

        // Notifying the user that the code have passed all tests.
        if (testPassed) {
            System.out.println("All " + testNum + " tests passed!");
        }
    }

    /**
     * This utility function will count the number of times it was invoked.
     * In addition, if a test fails the function will print the error message.
     * @param exp The actual test condition
     * @param msg An error message, will be printed to the screen in case the test fails.
     */
    private static void test(boolean exp, String msg) {
        testNum++;

        if (!exp) {
            testPassed = false;
            System.out.println("Test " + testNum + " failed: "  + msg);
        }
    }

    /**
     * Checks the MaximumSegmentTreeByTree class.
     */
    private static void testMaximumSegmentTreeByTree() {

        SegmentTreeByTree mstbt = new MaximumSegmentTreeByTree(new int[]{60,10,5,15,6});

        test(mstbt.size() == 5, "Number of element in the original array should be 5");

        test(mstbt.queryRange(0,4) == 60, "The max of {60,10,5,15,6} between indexes [0:3] should be 60");

        mstbt.update(1,80);
        test(mstbt.queryRange(0,4) == 80, "After update index 1 from {60,10,5,15,6} to 80, the max between indexes [0:3] should be 80");

        test(mstbt.toString().equals(" [ 80 80 80 60 80 5 15 15 6 ] "),"The toString of {60,80,5,15} should be ' [ 80 80 80 60 80 5 15 15 6 ] ' got: '" + mstbt.toString()+ " '");
    }

    /**
     * Checks the MinimumTreeByTree class.
     */
    private static void testMinimumSegmentTreeByTree() {

        SegmentTreeByTree mstbt = new MinimumSegmentTreeByTree(new int[]{1,3,5,7,9,11});

        test(mstbt.size() == 6, "Number of element in the original array should be 6");

        test(mstbt.toString().equals(" [ 1 1 1 1 3 5 7 7 7 9 11 ] "), "The toString of {1,3,5,7,9,11} should be ' [ 1 1 1 1 3 5 7 7 7 9 11 ] ' got: '" + mstbt.toString()+ " '");
        test(mstbt.queryRange(0,0) == 1, "The min of {1,3,5,7,9,11} between indexes [0:0] should be 1");
        test(mstbt.queryRange(1,3) == 3, "The min of {1,3,5,7,9,11} between indexes [1:3] should be 3");
        test(mstbt.queryRange(5,5) == 11, "The min of {1,3,5,7,9,11} between indexes [5:5] should be 11");

        mstbt.update(3, 0);

        test(mstbt.toString().equals(" [ 0 1 1 1 3 5 0 0 0 9 11 ] "), "The toString of {1,3,5,0,9,11} should be ' [ 0 1 1 1 3 5 0 0 0 9 11 ] ' got: '" + mstbt.toString()+ " '");
        test(mstbt.queryRange(0,3) == 0,"The min of {1,3,5,0,9,11} between indexes [0:3] should be 0 ");
        test(mstbt.queryRange(4,5) == 9, "The min of {1,3,5,7,9,11} between indexes [4:5] should be 9");
        test(mstbt.queryRange(5,5) == 11, "The min of {1,3,5,0,9,11} between indexes [5:5] should be 11");
    }

    /**
     * Checks the SummationTreeByTree class.
     */
    private static void testSummationSegmentTreeByTree() {

        SegmentTreeByTree sstbt = new SummationSegmentTreeByTree(new int[]{5,1,4,2,3});

        test(sstbt.toString().equals(" [ 15 10 6 5 1 4 5 2 3 ] "), "The toString of {5,1,4,2,3} should be ' [ 15 10 6 5 1 4 5 2 3] ' got: '" + sstbt.toString()+ " '");

        test(sstbt.queryRange(0,0) == 5, "The sum of {5,1,4,2,3} between indexes [0:0] should be 5");
        test(sstbt.queryRange(1,3) == 7, "The sum of {5,1,4,2,3} between indexes [1:3] should be 7");
        test(sstbt.queryRange(3,4) == 5, "The sum of {5,1,4,2,3} between indexes [3:4] should be 5");

        sstbt.update(3, 3);

        test(sstbt.toString().equals(" [ 16 10 6 5 1 4 6 3 3 ] "), "The toString of {5,1,4,3,3} should be ' [ 15 10 6 5 1 4 5 2 3] ' got: '" + sstbt.toString()+ " '");
        test(sstbt.queryRange(0,0) == 5, "The sum of {5,1,4,3,3} between indexes [0:0] should be 5");
        test(sstbt.queryRange(1,3) == 8, "The sum of {5,1,4,2,3} between indexes [1:3] should be 7");
        test(sstbt.queryRange(3,4) == 6, "The sum of {5,1,4,2,3} between indexes [3:4] should be 5");
    }

        /**
         * Checks the MaximumSegmentTreeByArray class.
         */
    private static void testMaximumSegmentTreeByArray() {

        SegmentTreeByArray mstbt = new MaximumSegmentTreeByArray(new int[]{10,15,55,15,9,12});

        test(mstbt.toString().equals(" [ 55 55 15 15 55 15 12 10 15 - - 15 9 - - ] "),"The toString of {10,15,55,15,9,12} should be ' [ 55 55 15 15 55 15 12 10 15 - - 15 9 - - ] ' got: '" + mstbt.toString()+ " '");

        test(mstbt.queryRange(0,1) == 15, "The max of {10,15,55,15,9,12} between indexes [0:1] should be 15");

        mstbt.update(0,80);
        test(mstbt.queryRange(0,0) == 80, "After update index 0 from {10,15,55,15,9,12} to 80, the max between indexes [0:0] should be 80");
    }

    /**
     * Checks the MinimumSegmentTreeByArray class
     */
    private static void  testMinimumSegmentTreeByArray() {

        SegmentTreeByArray mstbt = new MinimumSegmentTreeByArray(new int[]{5, 1, 4, 2, 3});

        test(mstbt.toString().equals(" [ 1 1 2 1 4 2 3 5 1 - - - - - - ] "), "The toString of {5,1,4,2,3} should be ' [ 1 1 2 1 4 2 3 5 1 - - - - - -] ' got: '" + mstbt.toString() + " '");

        test(mstbt.queryRange(0, 1) == 1, "The min of {5,1,4,2,3} between indexes [0:1] should be 1");
        test(mstbt.queryRange(2, 3) == 2, "The min of {5,1,4,2,3} between indexes [2:3] should be 2");
        test(mstbt.queryRange(4, 4) == 3, "The min of {5,1,4,2,3} between indexes [4:4] should be 3");

        mstbt.update(2, 1);

        test(mstbt.toString().equals(" [ 1 1 2 1 1 2 3 5 1 - - - - - - ] "), "The toString of {5,1,1,2,3} should be ' [ 1 1 2 1 1 2 3 5 1 - - - - - -] ' got: '" + mstbt.toString() + " '");

        test(mstbt.queryRange(2, 3) == 1, "The min of {5,1,1,2,3} between indexes [2:3] should be 1");
    }

    /**
     * Checks the SummationSegmentTreeByArray class
     */
    private static void testSummationSegmentTreeByArray(){

        SegmentTreeByArray mstbt = new SummationSegmentTreeByArray(new int[]{5,1,4,2,3});

        test(mstbt.toString().equals(" [ 15 10 5 6 4 2 3 5 1 - - - - - - ] "), "The toString of {5,1,4,2,3} should be ' [ 15 10 5 6 4 2 3 5 1 - - - - - - ] ' got: '" + mstbt.toString() + " '");

        test(mstbt.queryRange(0, 1) == 6, "The sum of {5,1,4,2,3} between indexes [0:1] should be 6");
        test(mstbt.queryRange(2, 3) == 6, "The sum of {5,1,4,2,3} between indexes [2:3] should be 6");
        test(mstbt.queryRange(4, 4) == 3, "The sum of {5,1,4,2,3} between indexes [4:4] should be 3");

        mstbt.update(0,0);

        test(mstbt.toString().equals(" [ 10 5 5 1 4 2 3 0 1 - - - - - - ] "), "The toString of {0,1,4,2,3} should be ' [ 10 5 5 1 4 2 3 0 1 - - - - - - ] ' got: '" + mstbt.toString() + " '");

        test(mstbt.queryRange(0, 1) == 1, "The sum of {0,1,4,2,3} between indexes [0:1] should be 1");
        test(mstbt.queryRange(2, 3) == 6, "The sum of {0,1,4,2,3} between indexes [2:3] should be 6");
        test(mstbt.queryRange(0, 4) == 10, "The sum of {0,1,4,2,3} between indexes [0:4] should be 10");
    }
    /**
     * Checks the NumberAnalyzerByTrees class.
     */
    private static void testNumberAnalyzerByTrees() {

        Integer[] arr = {10,30,50};
        NumberAnalyzerByTrees nabt = new NumberAnalyzerByTrees(arr);

        test(nabt.getMax(0,1) == 30, "The max of {10,30,50} between indexes [0:1] should be 30");
        test(nabt.getMin(0,1) == 10, "The min of {10,30,50} between indexes [0:1] should be 10");
        test(nabt.getSum(0,1) == 40, "The sum of {10,30,50} between indexes [0:1] should be 40");

        Integer[] arr2 = {1,5,2,0,4,3,4,1,50,0,1,4,7};
        NumberAnalyzer nabt2 = new NumberAnalyzerByTrees(arr2);

        test(nabt2.getMax(0,12) == 50, "The max of {1,5,2,0,4,3,4,1,50,0,1,4,7} between indexes [0:12] should be 50");
        test(nabt2.getMin(0,11) == 0, "The min of {1,5,2,0,4,3,4,1,50,0,1,4,7} between indexes [0:11] should be 0");
        test(nabt2.getSum(7,10) == 52, "The sum of {1,5,2,0,4,3,4,1,50,0,1,4,7} between indexes [7:10] should be 52");

        nabt2.update(5,100);

        test(nabt2.getMax(0,12) == 100, "The max of {1,5,2,0,4,100,4,1,50,0,1,4,7} between indexes [0:12] should be 100");
        test(nabt2.getMin(5,5) == 100, "The min of {1,5,2,0,4,100,4,1,50,0,1,4,7} between indexes [0:11] should be 100");
        test(nabt2.getSum(5,7) == 105, "The sum of {1,5,2,0,4,100,4,1,50,0,1,4,7} between indexes [7:10] should be 105");

    }
    private static void testNumberAnalyzerByArrays(){

        Integer[] arr = {1,2,3,4};
        NumberAnalyzerByArrays naba = new NumberAnalyzerByArrays(arr);

        test(naba.getMax(0,3) == 4, "The max of {1,2,3,4} between indexes [0:3] should be 4");
        test(naba.getMin(0,3) == 1,"The min of {1,2,3,4} between indexes [0:3]d should be 1");
        test(naba.getSum(0,3) == 10,"The sum of {1,2,3,4} between indexes [0:3] should be 10");

        // check the iterator :
        Iterator<Integer> iter = naba.iterator();
        Integer temp = 1;
        while (iter.hasNext()){
            Integer it = iter.next();
            test(it.equals(temp), "The value of iter should be : " + arr[temp -1] + " and its : " + it );
            temp ++;
        }
    }
}
