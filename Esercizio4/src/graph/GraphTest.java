package graph;

import java.util.*;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;
import kruskal.*;
import unionfind.*;

/**
 *
 * @author Giulio Taralli & Ismaila Toure
 */
public class GraphTest {

  private Graph<String,Integer> graph;


  @Before
  public void create() throws GraphException{

   graph = new Graph<String, Integer>(false);
   graph.addVertex("A");
   graph.addVertex("B");
   graph.addVertex("C");
   graph.addVertex("D");
   graph.addVertex("E");

   graph.addArch("A","B",false,7);
   graph.addArch("A","C",false,4);
   graph.addArch("A","E",false,2);
   graph.addArch("B","E",false,9);
   graph.addArch("B","D",false,5);
  }

  @Test
  public void testIsOriented() throws GraphException{
    assertEquals(false, graph.isOriented());
  }

  @Test
  public void testSearchVertex() throws GraphException{
    assertEquals(true, graph.searchVertex("A"));
  }

  @Test
  public void testSearchVertexFalse() throws GraphException{
    assertEquals(false, graph.searchVertex("F"));
  }

  @Test
  public void testSearchArch() throws GraphException{
    assertEquals(true, graph.searchArch("A","B"));
  }

  @Test
  public void testSearchArchFalse() throws GraphException{
    assertEquals(false, graph.searchArch("A","D"));
  }

  @Test
  public void testDeleteVertex() throws GraphException{
    if(graph.deleteVertex("D") == 1)
      assertEquals(false, graph.searchVertex("D"));
  }

  @Test
  public void testDeleteVertexLookForArch() throws GraphException{
    if(graph.deleteVertex("D") == 1)
      assertEquals(false, graph.searchArch("B","D"));
  }

  @Test
  public void testDeleteArch() throws GraphException{
    if(graph.deleteArch("A","C") == 1)
      assertEquals(false, graph.searchArch("A","C"));
  }

  @Test
  public void testGetNumVertex() throws GraphException{
      assertEquals(5, graph.getNumV());
  }

  @Test
  public void testGetNumArch() throws GraphException{
      assertEquals(10, graph.getNumArch());
  }

  @Test
  public void testGetAllVertex() throws GraphException{
      ArrayList<String> test = new ArrayList<String>();
      test.add("A");
      test.add("B");
      test.add("C");
      test.add("D");
      test.add("E");


      assertEquals(true, graph.getAllVertex().equals(test));
  }

  @Test
  public void testGetAllArch() throws GraphException{
      ArrayList<Set<String>> test = new ArrayList<Set<String>>();
      Set<String> a,b,c,d,e;

      a = new HashSet<String>();
      b = new HashSet<String>();
      c = new HashSet<String>();
      d = new HashSet<String>();
      e = new HashSet<String>();

      a.add("B");
      a.add("C");
      a.add("E");
      test.add(a);

      b.add("A");
      b.add("D");
      b.add("E");
      test.add(b);

      c.add("A");
      test.add(c);

      d.add("B");
      test.add(d);

      e.add("A");
      e.add("B");
      test.add(e);

      assertEquals(test, graph.getAllArch());
  }

  @Test
  public void testAdjacentVertex() throws GraphException{
      ArrayList<Set<String>> test = new ArrayList<Set<String>>();
      Set<String> a = new HashSet<String>();

      a.add("B");
      a.add("C");
      a.add("E");
      test.add(a);
    
     assertEquals(test, graph.getAdjacentVertex("A"));
  }

  @Test
  public void testGetWeight() throws GraphException{

      assertEquals(7, (int)graph.getWeight("A","B"));
  }

  @Test
  public void getKruskal() throws UnionFindException, GraphException{
      Kruskal<String, Integer> k = new Kruskal<String, Integer>(graph);
      ArrayList<ArrayList<String>> solution = new ArrayList<ArrayList<String>>();
      ArrayList<ArrayList<String>> test = new ArrayList<ArrayList<String>>();
      solution.add(new ArrayList<String>());
      solution.get(0).add("A");
      solution.get(0).add("E");
      solution.add(new ArrayList<String>());
      solution.get(1).add("A");
      solution.get(1).add("C");
      solution.add(new ArrayList<String>());
      solution.get(2).add("B");
      solution.get(2).add("D");
      solution.add(new ArrayList<String>());
      solution.get(3).add("A");
      solution.get(3).add("B");

      test = k.MSTkruskal();
      assertEquals(test, solution);
  }

}