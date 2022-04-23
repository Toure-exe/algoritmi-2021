package kruskal;

/**
 *
 * @author Giulio Taralli & Ismaila Toure
 */

import java.util.*;
import graph.*;
import unionfind.*;

public class Kruskal<T,F extends Comparable <F>>{

    private ArrayList<Branch<T>> listV;
    private UnionFind<T> mst;
    private Graph<T,F> graph;

    public Kruskal(Graph<T,F> graph){
        this.listV = new ArrayList<Branch<T>>();
        this.mst = new UnionFind<T>();
        this.graph = graph;
    }

    //Merge sorting the arch list by weight 
    private ArrayList<ArrayList<T>> sort(ArrayList<ArrayList<T>> res) throws GraphException {  
        if(res.size() <= 1)
            return res;
        else {
            ArrayList<ArrayList<T>> left = new ArrayList<ArrayList<T>>();
            ArrayList<ArrayList<T>> right = new ArrayList<ArrayList<T>>();

            int mid = res.size()/2;
            for (int i = 0; i < mid; i++) { 
			    left.add(res.get(i));
		    }
            for(int i = mid; i < res.size(); i++) { 
                right.add(res.get(i));
            }

            return mergeSort(sort(left), sort(right));
        }
    }

    private ArrayList<ArrayList<T>> mergeSort(ArrayList<ArrayList<T>> a, ArrayList<ArrayList<T>> b) throws GraphException {
        ArrayList<ArrayList<T>> result = new ArrayList<ArrayList<T>>();
        int a_idx = 0; 
        int b_idx = 0;
        while (a_idx+1 <= a.size() || b_idx+1 <= b.size()) {
            if (a_idx+1 <= a.size() && b_idx+1 <= b.size()) {
                if (graph.getWeight(a.get(a_idx).get(0), a.get(a_idx).get(1)).compareTo(graph.getWeight(b.get(b_idx).get(0), b.get(b_idx).get(1))) <= 0.0) {
                    result.add(a.get(a_idx));
                    a_idx++;
                } else {
                    result.add(b.get(b_idx));
                    b_idx++;
                }
            } else if (a_idx+1 <= a.size()) {
                result.add(a.get(a_idx));
				a_idx++;
            } else if (b_idx+1 <= b.size()) {
                result.add(b.get(b_idx));
				b_idx++;
            }
        }

        return result;
    }

    private ArrayList<Branch<T>> treeInitialization(ArrayList<T> list) throws UnionFindException{
        for (int i = 0; i < list.size(); i++) {
            listV.add(mst.makeSet(list.get(i), new Leaf<T>()));
        }
        return listV;
    }

    /*By ascending order*/ 
    private ArrayList<ArrayList<T>> listSorting(ArrayList<T> listVertex, ArrayList<Set<T>> listArch) throws GraphException{
        ArrayList<ArrayList<T>> res = new ArrayList<ArrayList<T>>();
        ArrayList<T> temp = new ArrayList<T>();
        int n = 0;
        int j = 0;
        System.out.println("creating the list of ordered arcs...");
        
        //creatation of a list composed by two elements, the arch of source (first) and destination (second) vertex
        int z = 0;
        for (int i = 0; i < listVertex.size(); i++) {
            temp.clear();
            temp.addAll(listArch.get(i));
            for (int k = 0; k < listArch.get(i).size(); k++) {
                res.add(new ArrayList<T>());
                res.get(z).add(0, listVertex.get(i));
                res.get(z).add(1, temp.get(k));
                z++;
            }
        }
        System.out.println("sorting the list...");
        res = sort(res);

        //elimination of duplicates
        for (int i = 0; i < res.size()-1; i++) {
            if (res.get(i).get(0).equals(res.get(i+1).get(1)) && res.get(i).get(1).equals(res.get(i+1).get(0)))
                res.remove(i+1);
        }

        return res;
    }

    
    /**
    * Generate the minimal spamming tree of the graph
    * Each internal ArrayList is composed by two elements, the arch of source (first) and destination (second) vertex 
    * 
    * @return An ArrayList of ArrayList objects that contain the minimal spamming tree of the graph 
    */
    public ArrayList<ArrayList<T>> MSTkruskal() throws UnionFindException, GraphException{
        ArrayList<ArrayList<T>> res = new ArrayList<ArrayList<T>>();
        ArrayList<T> listVertex = graph.getAllVertex();
        ArrayList<Branch<T>> tree = treeInitialization(this.graph.getAllVertex());
        ArrayList<ArrayList<T>> listOrderedArch = listSorting(this.graph.getAllVertex(), this.graph.getAllArch());
        ArrayList<HashMap<T,T>> hp = new ArrayList<HashMap<T,T>>();
        HashMap<T,T> tempMap = new HashMap<T,T>();
        ArrayList<T> arch = new ArrayList<T>(); 
        System.out.println("Kruskal's algorithm started...");
        
        //load the vertex in a working hashmap
        for (int i = 0; i < listVertex.size(); i++){
            hp.add(new HashMap<T,T>());
            hp.get(i).put(listVertex.get(i), listVertex.get(i));
        }
       
        int i = 0;
        int j = 0;
        boolean ibool = false;
        boolean jbool = false;
        while (!listOrderedArch.isEmpty()) {       
            arch = listOrderedArch.get(0);

            //search the elements of arch in the arraylist
            i = 0;
            for (int n = 0; n < hp.size(); n++) {
                if(hp.get(n).containsKey(arch.get(0)))
                    break;
                i++;
            }
            j = 0;
            for (int m = 0; m < hp.size(); m++) {
                if(hp.get(m).containsKey(arch.get(1)))
                    break;
                j++;
            }
            
            //Kruskal's algorthm
            if (mst.findSet(tree.get(i)).equals(mst.findSet(tree.get(j))) == false) {
                res.add(arch);
                tree.set(i, mst.union(tree.get(i), tree.get(j)));
                tempMap = new HashMap<T,T>(hp.get(j));
                //tempMap = (HashMap<T,T>)hp.get(j).clone();
                for(T v : tempMap.keySet()) {
                    hp.get(i).put(v,v);
                }
                tree.remove(j);
                hp.remove(j);
            }
            listOrderedArch.remove(0);
        }

        return res;
    }
}


