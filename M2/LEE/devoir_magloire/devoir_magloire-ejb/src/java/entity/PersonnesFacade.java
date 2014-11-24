/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package entity;

import java.util.List;
import java.util.stream.Collectors;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;

/**
 *
 * @author joxit
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

	@Override
	public List<Personnes> findByBureau(Bureaux bureau) {
		return findAll().stream().parallel().filter(p -> {
			return bureau.equals(p.getBureau());
		}).collect(Collectors.toList());
	}

}
