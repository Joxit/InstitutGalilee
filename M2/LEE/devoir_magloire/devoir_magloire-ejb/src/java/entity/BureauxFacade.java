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
 * @author joxit
 */
@Stateless
public class BureauxFacade extends AbstractFacade<Bureaux> implements BureauxFacadeLocal {
    @PersistenceContext(unitName = "devoir_magloire-ejbPU")
    private EntityManager em;

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }

    public BureauxFacade() {
        super(Bureaux.class);
    }

}
