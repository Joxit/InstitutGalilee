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
public class EquipesFacade extends AbstractFacade<Equipes> implements EquipesFacadeLocal {

	@PersistenceContext(unitName = "devoir_magloire-ejbPU")
	private EntityManager em;

	@Override
	protected EntityManager getEntityManager() {
		return em;
	}

	public EquipesFacade() {
		super(Equipes.class);
	}

	@Override
	public void create(Equipes e) {
		e.setEquipeId(e.getEquipeId().toUpperCase());
		super.create(e);
	}

}
