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
public interface EquipesFacadeLocal {

    void create(Equipes equipes);

    void edit(Equipes equipes);

    void remove(Equipes equipes);

    Equipes find(Object id);

    List<Equipes> findAll();

    List<Equipes> findRange(int[] range);

    int count();

}
