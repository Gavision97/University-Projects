public class NumberAnalyzerByArrays extends NumberAnalyzer{
    int[] arr;
    SegmentTreeByArray tree;

    public NumberAnalyzerByArrays(Integer[] numbers) {
        super(numbers);
        arr = new int[numbers.length];
        for(int i = 0 ; i < numbers.length; i++)
            arr[i] = numbers[i];
    }

    @Override
    public Integer getMax(int left, int right) {
        tree = new MaximumSegmentTreeByArray(arr);
        return tree.queryRange(left, right);
    }

    @Override
    public Integer getMin(int left, int right) {
        tree = new MinimumSegmentTreeByArray(arr);
        return tree.queryRange(left, right);
    }

    @Override
    public Integer getSum(int left, int right) {
        tree = new SummationSegmentTreeByArray(arr);
        return tree.queryRange(left, right);
    }

    @Override
    public void update(int index, int value) {
       this.arr[index] = value;
    }
}
