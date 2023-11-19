import java.util.Comparator;
import java.util.Iterator;

/**
 The NumberAnalyzer class provides an abstract implementation for analyzing a collection of integers.
 It implements the Iterable interface to allow for iteration over the collection, and the Comparator interface
 to provide a default comparison method for integers.
 */
public abstract class NumberAnalyzer implements Iterable<Integer>, Comparator<Integer> {

    protected Integer[] numbers;

    /**
     * Constructs a new NumberAnalyzer object with the given array of integers.
     * @param numbers The array of integers to be analyzed.
     */
    public NumberAnalyzer(Integer[] numbers) {
        this.numbers = numbers;
    }

    private class NumberAnalyzerIterator implements Iterator{
        protected int nextIndex = 0;
        @Override
        public boolean hasNext() {
            return nextIndex < numbers.length && numbers[nextIndex] != null;
        }

        @Override
        public Object next() {
            if(!hasNext())
                return null;
            int next = numbers[nextIndex];
            nextIndex++;
            return next;
        }
    }

    @Override
    public Iterator<Integer> iterator() {
        return new NumberAnalyzerIterator();
    }

    @Override
    public int compare(Integer o1, Integer o2) {
        if(o1%2 ==0 && o2%2 ==0)
            return o1.compareTo(o2);
        else if (o1%2 == 0 && o2%2 == 1)
            return 1;
        else if(o1%2 ==1 && o2%2 ==0)
            return -1;
        else
            return o1.compareTo(o2);
    }

    public void sort(){
        for(Integer i = 0 ; i < this.numbers.length; i ++){
            Integer val = this.numbers[i];
            Integer j = i;
            while(j > 0 && this.compare(this.numbers[j -1], val) >0){
                this.numbers[j] = this.numbers[j -1];
                j = j - 1;
            }
            this.numbers[j] = val;
        }
    }

    /**
     * Returns the maximum value in the given range. This is an abstract function to be implemented by the subclasses
     * @param left The left endpoint of the range (inclusive).
     * @param right The right endpoint of the range (inclusive).
     * @return The maximum value in the range.
     */
    public abstract Integer getMax(int left, int right);

    /**
     * Returns the minimum value in the given range. This is an abstract function to be implemented by the subclasses
     * @param left The left endpoint of the range (inclusive).
     * @param right The right endpoint of the range (inclusive).
     * @return The minimum value in the range.
     */
    public abstract Integer getMin(int left, int right);

    /**
     * Returns the sum of the values in the given range. This is an abstract function to be implemented by the subclasses
     * @param left The left endpoint of the range (inclusive).
     * @param right The right endpoint of the range (inclusive).
     * @return The sum of the values in the range.
     */
    public abstract Integer getSum(int left, int right);

    /**
     * Updates the value at the given index. This is an abstract function to be implemented by the subclasses
     * @param index The index of the value to be updated.
     * @param value The new value to be set at the given index.
     */
    public abstract void update(int index, int value);
}