package unionfind;

import java.util.Comparator;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;

/**
 *
 * @author Giulio Taralli & Ismaila Toure
 */

public class UnionFindTest {

  private Leaf<Integer> leaf1;
  private Leaf<Integer> leaf2;
  private UnionFind<Integer> uf;

  @Before
  public void create() throws UnionFindException{
    leaf1 = new Leaf<>();
    leaf2 = new Leaf<>();
    uf = new UnionFind<>();
  }

  @Test
  public void testRank() throws UnionFindException{
      Branch<Integer> br1 = uf.makeSet(5, leaf1);
      Branch<Integer> br2 = uf.makeSet(3, leaf2);
      br1 = uf.union(br1, br2);
      Branch<Integer> br3 = uf.makeSet(1, leaf1);
      Branch<Integer> br4 = uf.makeSet(2, leaf1);
      br3 = uf.union(br3, br4);
      br2 = uf.union(br3, br1);
      assertEquals(2, br2.getRank());
  }

  @Test
  public void testFindSet() throws UnionFindException{
      Branch<Integer> br1 = uf.makeSet(5, leaf1);
      Branch<Integer> br2 = uf.makeSet(3, leaf2);
      br1 = uf.union(br1, br2);
      assertEquals(3, (int)br1.getParent().getElem());
  }

  @Test
  public void testMake() throws UnionFindException{
      Branch<Integer> br1 = uf.makeSet(5, leaf1);
      assertEquals(5, (int)br1.getParent().getElem());
  }

  @Test
  public void testUnion() throws UnionFindException{
      Branch<Integer> br1 = uf.makeSet(5, leaf1);
      Branch<Integer> br2 = uf.makeSet(3, leaf2);
      br1 = uf.union(br1, br2);
      Branch<Integer> br3 = uf.makeSet(1, leaf1);
      Branch<Integer> br4 = uf.makeSet(2, leaf1);
      br3 = uf.union(br3, br4);
      br2 = uf.union(br3, br1);
      assertEquals(3, (int)br2.getParent().getElem());
  }

  @Test
  public void testFindUniqueElement() throws UnionFindException{
      Branch<Integer> br1 = uf.makeSet(5, leaf1);
      assertEquals(5, (int)br1.getParent().getElem());
  }

  /*@Test
  public void testNull() throws UnionFindException{
      //checking the exception, keep comment
      Leaf<Integer> leaf3 = null;
      Branch br1 = uf.makeSet(5, leaf3);
      assertEquals(3, br1.getParent().getElem());
  }*/

}