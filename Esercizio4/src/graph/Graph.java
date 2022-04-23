package graph;

/**
 *
 * @author Giulio Taralli & Ismaila Toure
 */

 import java.util.*;

 public class Graph<T,F> {

    private Map<T, Vertex<T,F>> map;
    private int numV;
    private boolean oriented;

    public Graph(boolean oriented) {
        this.map = new HashMap<T, Vertex<T,F>>();
        this.numV = 0;
        this.oriented = oriented;
    }

    /**
    * Add an new arch in the graph
    * The complexity is O(1)
    * 
    * @param source the generic label of the source vertex
    * @param destination the generic label of the destination vertex
    * @param oriented describe if the arch is oriented or not 
    * @param weight the weight of the arch
    * @return 1 if success, 0 otherwise 
    */
    public int addArch(T source, T destination, boolean oriented, F weight) throws GraphException {
        if (source == null || destination == null || weight == null)
            throw new GraphException("GraphExecption(addArch) Parameters cannot be null.");
        if(!map.containsKey(source) || !map.containsKey(destination))
            return 0;

        map.get(source).addA(destination,weight);
        if(!oriented){
            map.get(destination).addA(source,weight);
        }

        return 1;
    }

    /**
    * Add an new vertex in the graph
    * The complexity is O(1)
    * 
    * @param s the generic label of the new vertex 
    */
    public void addVertex(T s) throws GraphException {
        if (s == null)
            throw new GraphException("GraphExecption(addVertex) Parameters cannot be null.");
        if(!map.containsKey(s)){
            map.put(s, new Vertex<T,F>());
            this.numV++;
        }
    }

    /**
    * Determinate the number of vertices
    * The complexity is O(1)
    * 
    * @return the number of verteces 
    */
    public int getNumV() {
        return this.numV;
    }

    /**
    * Determinate the number of arches
    * The complexity is O(n)
    * 
    * @return the number of arches 
    */
    public int getNumArch() {
        int count = 0;
        for(T v : map.keySet()) {
            count += map.get(v).getNumA();
        }
        return count;
    }

    /**
    * Check if the graph is oriented
    * The complexity is O(1)
    * 
    * @return true if it is oriented, 0 otherwise
    */
    public boolean isOriented() {
        return this.oriented;
    }

    /**
    * Search a generic vertex
    * The complexity is O(1)
    * 
    * @return true if it is present, 0 otherwise
    */
    public boolean searchVertex(T s) throws GraphException {
        if (s == null)
            throw new GraphException("GraphExecption(searchVertex) Parameters cannot be null.");
        return map.containsKey(s);
    }

    /**
    * Search a generic arch
    * The complexity is O(1)
    * 
    * @param source the generic label of the source vertex
    * @param destination the generic label of the destination vertex
    * @return true if it is present, 0 otherwise
    */
    public boolean searchArch(T source, T destination) throws GraphException {
        if (source == null || destination == null)
            throw new GraphException("GraphExecption(searchArch) Parameters cannot be null.");
        if(!map.containsKey(source) || !map.containsKey(destination))
            return false;

        return map.get(source).getMap().containsKey(destination);
    }

    /**
    * Delete a generic vertex
    * The complexity is O(n)
    * 
    * @param s the generic label of the vertex
    * @return 1 if success, 0 otherwise
    */
    public int deleteVertex(T s) throws GraphException {
        if (s == null)
            throw new GraphException("GraphExecption(deleteVertex) Parameters cannot be null.");
        if(!map.containsKey(s))
            return 0;

        map.remove(s);
        for(T v : map.keySet()) {
            if(map.get(v).getMap().containsKey(s))
                map.get(v).delete(s);
        }
        return 1;
    }

    /**
    * Delete a generic arch
    * The complexity is O(1)
    * 
    * @param source the generic label of the source vertex
    * @param destination the generic label of the destination vertex
    * @return 1 if success, 0 otherwise
    */
    public int deleteArch(T source, T destination) throws GraphException {
        if (source == null || destination == null)
            throw new GraphException("GraphExecption(deleteArch) Parameters cannot be null.");
        if(!map.containsKey(source) || !map.containsKey(destination))
            return 0; 

        map.get(source).delete(destination);
        if(!oriented)
            map.get(destination).delete(source);
        return 1;
    }

    /**
    * Generate an list of all vertices
    * The complexity is O(n)
    * 
    * @return an ArratList object of the vertices' label
    */
    public ArrayList<T> getAllVertex() {
        ArrayList<T> list = new ArrayList<T>();

        for(T v : map.keySet()) {
            list.add(v);
        }
        return list;
    }

    /**
    * Generate an list of all arches
    * The complexity is O(n)
    * 
    * @return an ArratList object of Set objects that contain a pair of vertices' label that rappresent the arch
    */
    public ArrayList<Set<T>> getAllArch() {
        ArrayList<Set<T>> list = new ArrayList<Set<T>>();
        for(T v : map.keySet()) {
            list.add(map.get(v).getMap().keySet());
        }
        return list;
    }

    /**
    * Generate an list of all adiancent vertices of a specific vertex
    * The complexity is O(1)
    * 
    * @param s the generic label of the vertex 
    * @return an ArratList object of Set objects that contain a pair of vertices' label that rappresent all the adiacent arches of the input label
    */
    public ArrayList<Set<T>> getAdjacentVertex(T s) throws GraphException {
        if (s == null)
            throw new GraphException("GraphExecption(getAdjacentVertex) Parameters cannot be null.");
        if(!map.containsKey(s))
            return null;

        ArrayList<Set<T>> list = new ArrayList<Set<T>>();
        list.add(map.get(s).getMap().keySet());

        return list;
    }

    /**
    * Obtain the weight of the specific arch
    * The complexity is O(1)
    * 
    * @param v1 the generic label of the source vertex
    * @param v2 the generic label of the destination vertex
    * @return the weight of the arch
    */  
    public F getWeight(T v1, T v2) throws GraphException {
        if(!map.containsKey(v1) || !map.containsKey(v2))
            throw new GraphException("GraphExecption(getWeight) Vertex not found.");

        if(searchArch(v1,v2)){
            return map.get(v1).getMap().get(v2);
        }else if(searchArch(v2,v1)){
            return map.get(v2).getMap().get(v1);
        }else{
            throw new GraphException("GraphExecption(getWeight) arch doesn't exist.");
        }
    }

 }