package unionfind;

/**
 *  
 * @author Giulio Taralli & Ismaila Toure
 */

public class UnionFind<T>{

    /**
    * Create a new Branch object and set the parent to itself
    * Return an Branch object that is the root of the tree
    * 
    * @param y the generic label
    * @param x the Leaf object
    * @return an generic Branch that is the root of the tree
    */
    public Branch<T> makeSet(T y, Leaf<T> x) throws UnionFindException{
        if(x == null)
            throw new UnionFindException("UnionFindException(makeSet Function):  parameter cannot be null");

        Branch<T> res;
        res = x.insert(y);
        return res;
    }

    /**
    * Create a new Branch object that is the union of the two generic Branch objects
    * Return the merged tree
    * 
    * @param x the fitst generic Branch object 
    * @param y the second generic Branch object
    * @return the new generic united tree
    */
    public Branch<T> union(Branch<T> x, Branch<T> y) throws UnionFindException{
        if(x == null || y == null)
            throw new UnionFindException("UnionFindException(union Function):  parameter cannot be null");

        Branch<T> res;
        res = link(findSet(x), findSet(y));
        return res;
    }

    private Branch<T> link(Branch<T> x, Branch<T> y) throws UnionFindException{
        if(x == null || y == null)
            throw new UnionFindException("UnionFindException(link Function):  parameter cannot be null");

        //union by rank heuristic
        Branch<T> res;
        if(x.getRank() > y.getRank()){
            y.setParent(x);
            res = y.getParent();
        }else{
            x.setParent(y);
            if(x.getRank() == y.getRank())
            y.setRank(y.getRank()+1);
            res = x.getParent();
        }
        return res;
    }

    /**
    * Return the parent of the generic tree
    * 
    * @param x the generic Branch object 
    * @return the parent of the generic tree 
    */
    public Branch<T> findSet(Branch<T> x) throws UnionFindException {
        if(x == null)
            throw new UnionFindException("UnionFindException(findSet Function):  parameter cannot be null");
        
        //path compression heuristic
        if(x != x.getParent())
            x.setParent(findSet(x.getParent()));
        return x.getParent();
    }

}