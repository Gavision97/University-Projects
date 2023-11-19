
public class NumberAnalyzerByTrees extends  NumberAnalyzer {
    int []arr;
    SegmentTreeByTree tree;

    public NumberAnalyzerByTrees(Integer[] numbers) {
        super(numbers);
        arr = new int[numbers.length];
        for(int i = 0 ; i < numbers.length; i++)
            arr[i] = numbers[i];
    }

    @Override
    public Integer getMax(int left, int right) {
        tree = new MaximumSegmentTreeByTree(arr);
        return tree.queryRange(left, right);
    }

    @Override
    public Integer getMin(int left, int right) {
        tree = new MinimumSegmentTreeByTree(arr);
        return tree.queryRange(left, right);
    }

    @Override
    public Integer getSum(int left, int right) {
        tree = new SummationSegmentTreeByTree(arr);
        return tree.queryRange(left, right);
    }

    @Override
    public void update(int index, int value) {
        this.arr[index] = value;
    }
}
