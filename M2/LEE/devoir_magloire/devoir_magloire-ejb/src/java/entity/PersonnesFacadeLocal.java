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
 * @author 11000369
 */
@Local
public interface PersonnesFacadeLocal {

    void create(Personnes personnes);

    void edit(Personnes personnes);

    void remove(Personnes personnes);

    Personnes find(Object id);

    List<Personnes> findAll();

    List<Personnes> findRange(int[] range);

    int count();

}
