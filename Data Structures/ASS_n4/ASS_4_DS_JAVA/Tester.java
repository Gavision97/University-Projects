import java.util.List;

/**
 * This is a testing framework. Use it extensively to verify that your code is working
 * properly.
 */
public class Tester {

    private static boolean testPassed = true;
    private static int testNum = 0;

    /**
     * This entry function will test all classes created in this assignment.
     *
     * @param args command line arguments
     */
    public static void main(String[] args) {

        // Each function here should test a different class. you should test here every class you created.
        testDoubleHashTable();
        testAVLTree();
        testHashAVLSpellTable();
        testSpell();

        // Notifying the user that the code have passed all tests.
        if (testPassed) {
            System.out.println("All " + testNum + " tests passed!");
        }
    }

    /**
     * This utility function will count the number of times it was invoked.
     * In addition, if a test fails the function will print the error message.
     *
     * @param exp The actual test condition
     * @param msg An error message, will be printed to the screen in case the test fails.
     */
    private static void test(boolean exp, String msg) {
        testNum++;

        if (!exp) {
            testPassed = false;
            System.out.println("Test " + testNum + " failed: " + msg);
        }
    }

    private static void testSpell() {
        Spell spell1 = new Spell("fireball", "fire", 10, "fireball!");
        Spell spell2 = new Spell("frostbolt", "ice", 7, "freeze please");
        Spell spell3 = new Spell("thunderstorm", "lightning", 9, "I`m going to shock you");
        Spell spell4 = new Spell("poison spray", "poison", 5, "sssss");
        Spell spell5 = new Spell("shockwave", "lightning", 8, "go pikachu!");

        test(spell1.getCategory().equals("fire"),"problem with getCategory()");
        test(spell2.getCategory().equals("ice"),"problem with getCategory()");
        test(spell3.getCategory().equals("lightning"),"problem with getCategory()");
        test(spell4.getCategory().equals("poison"),"problem with getCategory()");
        test(spell5.getCategory().equals("lightning"),"problem with getCategory()");

        test(spell1.getPowerLevel() == 10, "problem with getPowerLevel()");
        test(spell2.getPowerLevel() == 7, "problem with getPowerLevel()");
        test(spell3.getPowerLevel() == 9, "problem with getPowerLevel()");
        test(spell4.getPowerLevel() == 5, "problem with getPowerLevel()");
        test(spell5.getPowerLevel() == 8, "problem with getPowerLevel()");

        test(spell1.getName().equals("fireball"), "problem with getName()");
        test(spell2.getName().equals("frostbolt"), "problem with getName()");
        test(spell3.getName().equals("thunderstorm"), "problem with getName()");
        test(spell4.getName().equals("poison spray"), "problem with getName()");
        test(spell5.getName().equals("shockwave"), "problem with getName()");

    }

    private static void  testAVLTree(){

        AVLTree tree = new AVLTree(new Spell("fireball", "fire", 10, "fireball!"));
        test(tree.getSize() == 1, "problem with tree size");
        test(tree.getTreeHeight() == 0, "problem with tree height");

        tree.insert(new Spell("flamethrower min", "fire", 6, "foo"));
        tree.insert(new Spell("flamethrower", "fire", 8, "foo better"));
        tree.insert(new Spell("fireball II", "fire", 12,"fireball!!"));
        tree.insert(new Spell("flamethrower II", "fire", 15, "foooooooo!"));

        test(tree.getSize() == 5, "problem with tree size");

        test(tree.getTreeHeight() == 2, "problem with tree height");

        test(tree.search("fireball", 10) != null, "problem with spell search");
        test(tree.search("flamethrower min", 6) != null, "problem with spell search");
        test(tree.search("flamethrower min", 6) != null, "problem with spell search");
        test(tree.search("flamethrower", 8) != null, "problem with spell search");
        test(tree.search("fireball II", 12) != null ,"problem with spell search");
        test(tree.search("flamethrower II", 15) != null , "problem with spell search");

        test(tree.getCategory().equals("fire"), "problem with getCategory()");

        List<Spell> topKTest = tree.getTopK(5);

        test(topKTest.get(0).getPowerLevel() == 15, "problem with getTopK");
        test(topKTest.get(1).getPowerLevel() == 12, "problem with getTopK");
        test(topKTest.get(2).getPowerLevel() == 10, "problem with getTopK");
        test(topKTest.get(3).getPowerLevel() == 8, "problem with getTopK");
        test(topKTest.get(4).getPowerLevel() == 6, "problem with getTopK");

        AVLTree tree2 = new AVLTree(new Spell("iceball", "ice", 8, "iceball!!"));
        tree2.insert(new Spell("icewater", "ice", 4, "colddd!!"));
        tree2.insert(new Spell("iceeee", "ice", 10, "very cold"));
        tree2.insert(new Spell("ice krim", "ice",2, "ice-cream"));
        tree2.insert(new Spell("ice ice", "ice", 6, "baby"));
        tree2.insert(new Spell("cold", "ice", 5, "weather"));

        test(tree2.getTreeHeight() == 2, "problem with tree height");

    }

    private static void testDoubleHashTable() {

        DoubleHashTable table = new DoubleHashTable(7);

        // Add some spells to the table
        test(table.put(new SpellSimple("Abracadabra", "Avada Kedavra")), "should return true");
        test(table.put(new SpellSimple("Expecto Patronum", "I’m gonna stand here like a unicorn")), "should return ture");
        test(table.put(new SpellSimple("Wingardium Leviosa", "Get up, stand up")), "should return true");
        test(table.put(new SpellSimple("Shazam", "24K Magic in the air")), "should return true");

        test(table.getCastWords("Shazam").equals("24K Magic in the air"), "Should print : 24K Magic in the air, got : " + table.getCastWords("Shazam"));
        test(table.getCastWords("Abracadabra").equals("Avada Kedavra"), "Should print : Avada Kedavra, got " + table.getCastWords("Abracadabra"));

        // Get the size of the table
        test(table.getSize() == 4, "Table size should be 4, got " + table.getSize() );
    }


    private static void testHashAVLSpellTable() {

        // create a new hash AVL spell table
        HashAVLSpellTable AVLtable = new HashAVLSpellTable(10);

        // create some spells
        Spell spell1 = new Spell("fireball", "fire", 10, "fireball!");
        Spell spell2 = new Spell("frostbolt", "ice", 7, "freeze please");
        Spell spell3 = new Spell("thunderstorm", "lightning", 9, "I`m going to shock you");
        Spell spell4 = new Spell("poison spray", "poison", 5, "sssss");
        Spell spell5 = new Spell("shockwave", "lightning", 8, "go pikachu!");

        // add the spells to the hash AVL spell table
        AVLtable.addSpell(new Spell("lightning bolt", "lightning", 11, "go lightning bolt"));
        AVLtable.addSpell(spell1);
        AVLtable.addSpell(spell2);
        AVLtable.addSpell(spell3);
        AVLtable.addSpell(spell4);
        AVLtable.addSpell(spell5);

        // add more spells to an existing category
        AVLtable.addSpell(new Spell("flamethrower min", "fire", 6, "foo"));
        AVLtable.addSpell(new Spell("flamethrower", "fire", 8, "foo better"));
        AVLtable.addSpell(new Spell("fireball II", "fire", 12,"fireball!!"));
        AVLtable.addSpell(new Spell("flamethrower II", "fire", 15, "foooooooo!"));
        AVLtable.addSpell(new Spell("shockwave II", "lightning", 10,"be useful pikachu."));
        AVLtable.addSpell(new Spell("frost nova", "ice", 4, "chill dude"));

        test(AVLtable.getNumberSpells() == 12,"Should return 12, got : " + AVLtable.getNumberSpells());
        test(AVLtable.getNumberSpells("fire") == 5, "Should return 5, got : " + AVLtable.getNumberSpells("fire"));
        test(AVLtable.getNumberSpells("lightning") == 4, "Should return 4, got : " + AVLtable.getNumberSpells("lightning"));
        test(AVLtable.getNumberSpells("ice") == 2, "Should return 2, got : " + AVLtable.getNumberSpells("ice"));

        // test the top 3 spells in the "fire" category
        List<Spell> fireSpells = AVLtable.getTopK("fire", 3);
        test(fireSpells.get(0).toString().equals("flamethrower II (fire) - Power Level: 15, to cast say: foooooooo!"), "problem with toString()");
        test(fireSpells.get(1).toString().equals("fireball II (fire) - Power Level: 12, to cast say: fireball!!"), "problem with toString()");
        test(fireSpells.get(2).toString().equals("fireball (fire) - Power Level: 10, to cast say: fireball!"), "problem with toString");

        // test the top 3 spells in the "lightning" category
        List<Spell> lightningSpells = AVLtable.getTopK("lightning", 3);
        test(lightningSpells.get(0).toString().equals("lightning bolt (lightning) - Power Level: 11, to cast say: go lightning bolt"),"problem with toString()");
        test(lightningSpells.get(1).toString().equals("shockwave II (lightning) - Power Level: 10, to cast say: be useful pikachu."),"problem with toString()");
        test(lightningSpells.get(2).toString().equals("thunderstorm (lightning) - Power Level: 9, to cast say: I`m going to shock you"),"problem with toString()");

        // test spell that exists in the table
        Spell searchedSpell = AVLtable.searchSpell("fire","fireball",  10);
        test(searchedSpell != null, "problem with search spell");

        // test search for a spell that does not exist in the table
        searchedSpell = AVLtable.searchSpell("fire", "fireball", 11);
        test(searchedSpell == null, "problem with search spell");
        searchedSpell = AVLtable.searchSpell("ice", "fireball", 10);
        test(searchedSpell == null, "problem with search spell");
    }
 }