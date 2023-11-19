import java.util.LinkedList;
import java.util.List;

public class HashAVLSpellTable {
    private LinkedList<AVLTree> buckets[];
    private int tableSize;
    private int numSpells;

    public HashAVLSpellTable(int size) {
        this.tableSize = size;
        this.numSpells = 0;
        this.buckets = new LinkedList[size];
    }

    private void incrementNumSpells() {
        this.numSpells++;
    }

    /**
     * private method to generate index in the hash table
     *
     * @param category spell category
     * @return index.
     */
    private int hash(String category) {
        int index = 0;
        for (int i = 0; i < category.length(); i++)
            index = index + category.charAt(i);
        return index % this.tableSize;
    }

    /**
     * The next method adds Spell object to the hash table
     *
     * @param s the Spell object that the user sends to that method
     */
    public void addSpell(Spell s) {
        int index = hash(s.getCategory()); // get index for the hash table using hash function
        LinkedList<AVLTree> currLinkedList = this.buckets[index];
        if (currLinkedList == null) {
            this.buckets[index] = new LinkedList<>();
            this.buckets[index].add(new AVLTree(s));
            this.incrementNumSpells();
        } else {
            /*
            next search for correct category in currLinkedList full of
            AVL trees by using iterator.
            if correct AVL tree found, add the spell to it :
             */
            for (AVLTree currTree : currLinkedList) {
                if (currTree.getCategory().equals(s.getCategory())) {
                    currTree.insert(s);
                    this.incrementNumSpells();
                    return;
                }
            }
            /*
             if we get to this point, means that no AVL tree
             that holds s category exist in currLinkedList, thus
             create new AVL tree :
             */
            currLinkedList.add(new AVLTree(s));
            this.incrementNumSpells();
        }
    }

    /**
     * The next method searches for Spell object in the hash table by its
     * category, spell name and power level
     *
     * @param category   Spell category
     * @param spellName  Spell name
     * @param powerLevel Spell power level
     * @return Spell object if founded the wanted Spell in the data structure
     */
    public Spell searchSpell(String category, String spellName, int powerLevel) {
        if (category == null || spellName == null || powerLevel < 0)
            return null;

        int index = this.hash(category); // get the index by using hash function
        LinkedList<AVLTree> currLinkedList = this.buckets[index];
        for (AVLTree currTree : currLinkedList) {
            if (currTree.getCategory().equals(category))
                return currTree.search(spellName, powerLevel);
        }
        // in case the spell was not found, retrieve null :
        return null;
    }

    /**
     * method to retrieve the total amount of spells
     * in the data structure
     *
     * @return total number of spells
     */
    public int getNumberSpells() {
        return this.numSpells;
    }

    /**
     * method to retrieve the number of spell from specific category.
     *
     * @param category category the user want to know how much spell
     *                 in the data structure of it
     * @return number of spells
     */
    public int getNumberSpells(String category) {
        if (category == null) return 0;
        int index = this.hash(category);
        LinkedList<AVLTree> currLinkedList = this.buckets[index];
        try {
            for(AVLTree currTree : currLinkedList){
                if(currTree.getCategory().equals(category))
                    return currTree.getSize();
            }
        } catch (NullPointerException e) {
            return 0;
        }
        return 0;
    }

    /**
     * the method generates list of top k elements with higher
     * power level in the data structure by their category.
     * @param category the category the user wants the spells from
     * @param k number of elements the user want to retrieve in the list
     * @return list of spells
     */
    public List<Spell> getTopK(String category, int k) {
        if(category == null || k < 0) return null;
        int index = this.hash(category);
        LinkedList<AVLTree> currLinkedList = this.buckets[index];
        for(AVLTree currTree : currLinkedList)
            if(currTree.getCategory().equals(category))
                return currTree.getTopK(k);

        // in case not such category found, retrieve null:
        return null;
    }
}
