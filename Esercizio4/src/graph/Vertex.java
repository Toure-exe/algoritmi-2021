package graph;

/**
 *
 * @author Giulio Taralli & Ismaila Toure
 */

 import java.util.*;

 class Vertex<T,F> {

    private Map<T,F> map;
    private int numA;

    public Vertex(){
        this.map = new HashMap<T,F>();
        this.numA = 0;
    }

    public void addA(T s, F weight) {
        map.put(s,weight);
        this.numA++;
    }

    public int getNumA() {
        return this.numA;
    }

    public Map<T,F> getMap() {
        return this.map;
    }

    public void delete(T s) {
        map.remove(s);
    }
 }