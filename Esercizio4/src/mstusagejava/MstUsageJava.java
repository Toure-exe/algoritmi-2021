package mstusagejava;

/**
 *
 * @author Giulio Taralli & Ismaila Toure
 */

import java.util.*;
import graph.*;
import kruskal.*;
import unionfind.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class MstUsageJava {

    private static final Charset ENCODING = StandardCharsets.UTF_8;

    private static double getAllWeight(ArrayList<ArrayList<String>> res, Graph<String, Double> graph) throws GraphException, UnionFindException{
        double weight = 0.0;
        for (int i = 0; i < res.size(); i++){
            weight += graph.getWeight(res.get(i).get(0), res.get(i).get(1));
        }
        return weight;
    }
    
    //load the data of the file.csv
    private static Graph<String, Double> initializationGraph(String filepath, Graph<String, Double> graph) throws IOException, GraphException{
        System.out.println("Loading the dataset...");

        Path inputFilePath = Paths.get(filepath);
        try (BufferedReader fileInputReader = Files.newBufferedReader(inputFilePath, ENCODING)){
            String line = null;
            while ((line = fileInputReader.readLine()) != null){      
                String[] lineElements = line.split(",");       
                graph.addVertex(lineElements[0]);
                graph.addVertex(lineElements[1]);
                graph.addArch(lineElements[0], lineElements[1], false, Double.parseDouble(lineElements[2]));
            }
        }
        System.out.println("Data loaded");
        return graph;
    }

    private static void wrappedFunction(String filepath) throws IOException, GraphException, UnionFindException {
        Graph<String, Double> graph = new Graph<String, Double>(false);
        graph = initializationGraph(filepath, graph);
        Kruskal<String, Double> mst = new Kruskal<String, Double>(graph);
        System.out.println("\nGraph's vertices number: " + graph.getAllVertex().size());
        System.out.println("\nGraph's arches number: " + graph.getAllArch().size());
        long startTime = System.currentTimeMillis();
        ArrayList<ArrayList<String>> minimalSpanningTree = mst.MSTkruskal();
        long stopTime = System.currentTimeMillis();
        System.out.println("\nTotal weight of the minimal spanning tree: " + getAllWeight(minimalSpanningTree, graph)/1000 + " km");
        
        System.out.println("MST-KRUSKAL TIME: "+(stopTime - startTime)/1000+" sec");
    }

    /**
    * @param args the command line arguments. It should contain only one argument
    * specifying the filepath of the data file
    */
    public static void main(String[] args) throws IOException, Exception {
        if(args.length < 1)
            throw new Exception("Error: please specify the path of the csv dataset");
    
        wrappedFunction(args[0]);
    }
}