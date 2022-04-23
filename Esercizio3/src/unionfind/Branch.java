package unionfind;

/**
 *
 * @author Giulio Taralli & Ismaila Toure
 */

public class Branch<T> {
    private T elem;
    private Branch<T> parent;
    private int rank;

    //Costructor for the first element (singleton)
    public Branch(T elem, int rank){
        this.elem = elem;
        this.parent = this;
        this.rank = rank;
    }

    //getters and setters
    public int getRank(){
        return this.rank;
    }

    public void setRank(int r){
        this.rank = r;
    }

    public Branch<T> getParent(){
        return this.parent;
    }

    public void setParent(Branch<T> parent){
        this.parent = parent;
    }

    public T getElem(){
        return this.elem;
    }

    public void setElem(T r){
        this.elem = r;
    }

}

