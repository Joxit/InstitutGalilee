/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package entity;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;

/**
 *
 * @author 11000369
 */
@Stateless
public class PersonnesFacade extends AbstractFacade<Personnes> implements PersonnesFacadeLocal {
    @PersistenceContext(unitName = "devoir_magloire-ejbPU")
    private EntityManager em;

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }

    public PersonnesFacade() {
        super(Personnes.class);
    }

}
