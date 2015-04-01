/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package entity;

import java.util.List;
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

	@Override
	public void create(Bureaux b) {
		b.setBatiment(Character.toUpperCase(b.getBatiment()));
		if (b.getNumero() < 1 || b.getNumero() > 999) {
			throw new IllegalArgumentException("Le numéro doit entre entre 1 et 999");
		} else if (b.getLimite() < 1) {
			throw new IllegalArgumentException("La limite doit etre positive");
		} else if (b.getBatiment() != 'A' && b.getBatiment() != 'B') {
			throw new IllegalArgumentException("Le batiment doit être A ou B");
		} else if (b.getEtage() > 3 || b.getEtage() < 1) {
			throw new IllegalArgumentException("Les étages sont 1 2 et 3");
		}
		super.create(b);
	}

	@Override
	public List<Bureaux> findByEquipe(Equipes equipe) {
		return em.createNamedQuery("Bureaux.findByEquipe")
				.setParameter("equipe", equipe).getResultList();
	}

	@Override
	public List<Bureaux> findAllSorted() {
		return em.createNamedQuery("Bureaux.findAllSorted").getResultList();
	}

}
