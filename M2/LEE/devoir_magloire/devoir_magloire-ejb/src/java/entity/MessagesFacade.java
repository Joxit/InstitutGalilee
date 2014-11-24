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
public class MessagesFacade extends AbstractFacade<Messages> implements MessagesFacadeLocal {

	@PersistenceContext(unitName = "devoir_magloire-ejbPU")
	private EntityManager em;

	@Override
	protected EntityManager getEntityManager() {
		return em;
	}

	public MessagesFacade() {
		super(Messages.class);
	}

	@Override
	public void create(int auteur, String msg) {
		String s = "insert into messages(auteur,message) ";
		s = s + "values (" + auteur + ",'" + msg.replaceAll("'", "''") + "')";
		em.createNativeQuery(s).executeUpdate();
	}

}
