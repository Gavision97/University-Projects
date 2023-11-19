import java.util.ArrayList;
import java.util.List;

public class AVLTree {

    private Node root;
    private int size;
    private String category;

    // private Node class for the AVL Tree nodes
    private class Node {
        private Spell spell;
        private Node left;
        private Node right;
        private int height;

        private Node(Spell spell) {
            this.spell = spell;
            this.left = null;
            this.right = null;
            this.height = 1; // height of lonely Node
        }

        private Node getRight(){
            if(this.right == null)
                return null;
            return this.right;
        }

        private Node getLeft(){
            if(this.left == null)
                return null;
            return this.left;
        }
    }

    // Constructor, getters, setters
    public AVLTree(Spell spell) {
        this.root = new Node(spell); // initiate root Node
        this.category = spell.getCategory(); // update the category of the AVL tree
        this.size = 1;
    }

    public int getTreeHeight() {
        return this.root.height - 1;
    }

    public int getSize() {
        return this.size;
    }

    public String getCategory() {
        return this.category;
    }

    public Spell search(String spellName, int powerLevel) {
        if (spellName == null || powerLevel < 0)
            return null;
        Spell resSpell = searchSpellRec(this.root, spellName, powerLevel);
        return resSpell;
    }

    private Spell searchSpellRec(Node runnerNode, String spellName, int powerLevel) {
        if (runnerNode.spell.getPowerLevel() == powerLevel && runnerNode.spell.getName().equals(spellName))
            return runnerNode.spell;
        if (runnerNode == null)
            return null;
        if (powerLevel < runnerNode.spell.getPowerLevel() && runnerNode.getLeft() != null)
            return searchSpellRec(runnerNode.getLeft(), spellName, powerLevel);
        else if (powerLevel > runnerNode.spell.getPowerLevel() && runnerNode.getRight() != null)
            return searchSpellRec(runnerNode.getRight(), spellName, powerLevel);
        return null;
    }

    /**
     * The next method retrieves linked list object filled with
     * the largest k element according to their power level
     *
     * @param k number of element we want to retrieve
     * @return linked list object
     */
    public List<Spell> getTopK(int k) {
        if (k < 1) return null;
        List<Spell> resList = new ArrayList<>();
        getTopK_rec(this.root, k, resList);
        return resList;
    }

    private void getTopK_rec(Node runnerNode, int k, List<Spell> resList) {
        if (runnerNode == null)
            return;
        getTopK_rec(runnerNode.right, k, resList);

        if (resList.size() < k) {
            resList.add(runnerNode.spell);
            getTopK_rec(runnerNode.left, k, resList);
        } else return;
    }

    /**
     * insert new Spell into the AVL tree data structure
     * @param spell Spell object
     */
    public void insert(Spell spell) {
        if (spell == null) return;
        this.root = insertNodeRec(this.root, spell);
        this.size++;
    }

    /*
    Few private methods so simplify the insertion oef new Node to the tree :
     */

    /**
     * recursive method to help insert new Spell object into the AVL data
     * structure
     * @param runnerNode root node
     * @param spell Spell object
     * @return pointer to the root
     */
    private Node insertNodeRec(Node runnerNode, Spell spell) {
        if (runnerNode == null)
            return new Node(spell);
        if (spell.getPowerLevel() < runnerNode.spell.getPowerLevel())
            runnerNode.left = insertNodeRec(runnerNode.left, spell);
        else if (spell.getPowerLevel() > runnerNode.spell.getPowerLevel())
            runnerNode.right = insertNodeRec(runnerNode.right, spell);
        else
            return runnerNode;

        this.updateTreeHeight(runnerNode);
        int runnerNodeBalance = this.getTreeBalance(runnerNode);

        /*
        in the next steps, the algorithm check if the tree
        is unbalanced AVL tree, and preforms rotation if
        needed :
         */
        int spellPowerLevel = spell.getPowerLevel();
        int temp = runnerNode.spell.getPowerLevel();
        // first case, left left rotation:
        if (runnerNodeBalance > 1 && spellPowerLevel < runnerNode.left.spell.getPowerLevel())
            return this.RightRotation(runnerNode);

        // second case, right right rotation :
        if (runnerNodeBalance < -1 && spellPowerLevel > runnerNode.right.spell.getPowerLevel())
            return this.LeftRotation(runnerNode);

        // third case, left right rotation :
        if (runnerNodeBalance > 1 && spellPowerLevel > runnerNode.left.spell.getPowerLevel()) {
            runnerNode.left = this.LeftRotation(runnerNode.left);
            return this.RightRotation(runnerNode);
        }

        // fourth case, right left rotation :
        if (runnerNodeBalance < -1 && spellPowerLevel < runnerNode.right.spell.getPowerLevel()) {
            runnerNode.right = this.RightRotation(runnerNode.right);
            return LeftRotation(runnerNode);
        }
        return runnerNode;
    }

    /**
     * method to retrieve tree balance to verify
     * if some joint is balanced or not
     * @param node current Node
     * @return integer
     */
    private int getTreeBalance(Node node) {
        if (node == null) return 0;
        return this.getNodeHeight(node.left) - this.getNodeHeight(node.right);
    }

    /**
     * method to retrieve current node height
     * @param node current Node
     * @return integer
     */
    private int getNodeHeight(Node node) {
        if (node == null) return 0;
        return node.height;
    }

    /**
     * method to update three height
     * @param node current Node
     */
    private void updateTreeHeight(Node node) {
        node.height = Math.max(this.getNodeHeight(node.left), this.getNodeHeight(node.right)) + 1;
    }

    /**
     * executes right rotation on current node
     * @param node current node
     * @return pointer to fixed tree node
     */
    private Node RightRotation(Node node) {
        Node leftNode = node.left;
        Node RightSubTree = leftNode.right;
        leftNode.right = node;
        node.left = RightSubTree;

        this.updateTreeHeight(node);
        this.updateTreeHeight(leftNode);
        return leftNode;
    }

    /**
     * executes left rotation on current node
     * @param node current node
     * @return pointer to fixed tree node
     */
    private Node LeftRotation(Node node) {
        Node rightNode = node.right;
        Node leftSubTree = rightNode.left;
        rightNode.left = node;
        node.right = leftSubTree;

        this.updateTreeHeight(node);
        this.updateTreeHeight(rightNode);
        return rightNode;
    }

    /**
     * private method to print the AVL tree to verify that
     * all the methods works properly
     * @param node root node
     */
    private void preOrder(Node node){
        if( node != null){
            System.out.println(node.spell);
            preOrder(node.left);
            preOrder(node.right);
        }
    }
}