/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package entity;

import java.util.List;
import javax.ejb.Local;

/**
 *
 * @author joxit
 */
@Local
public interface ResponsablesFacadeLocal {

    void create(Responsables responsables);

    void edit(Responsables responsables);

    void remove(Responsables responsables);

    Responsables find(Object id);

    List<Responsables> findAll();

    List<Responsables> findRange(int[] range);

    int count();

}
