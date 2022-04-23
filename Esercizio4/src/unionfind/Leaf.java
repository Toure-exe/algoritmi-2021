package unionfind;

/**
 *
 * @author Giulio Taralli & Ismaila Toure
 */

public class Leaf<T> {

    public Branch<T> insert(T y) { 
         Branch<T> res = new Branch<T>(y, 0);
         return res; 
    }
    
}
