public class DoubleHashTable {
    private SpellSimple[] table;
    private int capacity;
    private int size;
    private int steps=0;

    public DoubleHashTable(int capacity) {
        this.capacity = capacity;
        table = new SpellSimple[capacity];
        this.size = 0;
    }

    private void incrementSize(){ this.size ++;}

    /**
     * method that insert new spell into the hash table
     * using double hash method
     * @param spell the spell the user want to insert
     * @return true if succeeded, else false
     */
    public boolean put(SpellSimple spell) {
        if(spell == null || this.size == this.capacity)
            return false;
        String spellName = spell.getName();
        int index, i = 0;
        while(true){
           index = (hash1(spellName) + i*hash2(spellName))% this.capacity;
           boolean isOccupiedCell = this.table[index] != null;
           if(! isOccupiedCell) {
               this.table[index] = spell;
               if(i == 0) this.steps = 0;
               else this.steps = i; // save the number of steps
               incrementSize();
               return true;
           }
           i ++;
        }
    }

    /**
     * method to retrieve the cast words of the spell in the
     * hash table
     * @param name the spell name
     * @return String that represents the cast word of the spell
     */
    public String getCastWords(String name) {
        int index, i =0;
        index = (hash1(name))% this.capacity; // first step when i=0
        /*
        we iterate until we get the wanted SpellSimple object that holds
        the wanted name, or until we hit null, which means the object is not
        in the hash table:
         */
        while (this.table[index].getName() != null && i < this.getSize()){
            if(this.table[index].getName().equals(name))
                return this.table[index].getWords();
            i++;
            index = (hash1(name) + i*hash2(name))% this.capacity;
        }
        // in case no such name exist, retrieve null :
        return null;
    }

    public int getSize() {return this.size;}

    public int getLastSteps() { return this.steps; }

    /**
     * first hash function in the double hash method
     * @param name spell name
     * @return index
     */
    private int hash1(String name) {
        int res = 0;
        for(int i = 0; i < name.length(); i++)
            res = res + name.charAt(i)*31;
        return (res % this.capacity);
    }

    /**
     * second hash function in the double hash method
     * @param name spell name
     * @return index
     */
    private int hash2(String name) {
        int res = 0;
        for(int i = 0; i < name.length(); i++)
            res = res + name.charAt(i)*13;
        return (1 + res % (this.capacity - 2));
    }
}