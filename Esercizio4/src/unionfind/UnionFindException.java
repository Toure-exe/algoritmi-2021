/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package unionfind;

import java.io.*;

/**
 *
 * @author Giulio Taralli & Ismaila Toure
 */
 
public class UnionFindException extends Exception{

  private static final long serialVersionUID = 1000000000; //to risolve the serializable warning

  public UnionFindException(String message){
    super(message);
  }
}
