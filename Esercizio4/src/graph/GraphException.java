/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package graph;

import java.io.*;

/**
 *
 * @author Taralli Giulio & Toure Ismaila
 */
 
public class GraphException extends Exception{

  private static final long serialVersionUID = 1000000000; //to risolve the serializable warning

  public GraphException(String message){
    super(message);
  }
}
