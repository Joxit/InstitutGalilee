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
		return em.createNamedQuery("Personnes.findByBureau")
				.setParameter("bureau", bureau).getResultList();
	}

	@Override
	public List<Personnes> findByEquipe(Equipes equipe) {
		return em.createNamedQuery("Personnes.findByEquipe")
				.setParameter("equipe", equipe).getResultList();
	}

	@Override
	public List<Personnes> findAllSortedByName() {
		return em.createNamedQuery("Personnes.findAllSortedByName")
				.getResultList();
	}

	private String nameFormat(String s) {
		StringBuilder format = new StringBuilder();
		boolean upper = true;
		for (char c : s.toCharArray()) {
			if (upper) {
				format.append(Character.toUpperCase(c));
				upper = false;
			} else {
				format.append(Character.toLowerCase(c));
			}
			if (c == '-' || c == '.' || c == '\'') {
				upper = true;
			}
		}
		return format.toString();
	}

	@Override
	public void create(Personnes p) {
		if (p.getNom() == null) {
			throw new IllegalArgumentException("Nom manquant");
		} else if (p.getPrenom() == null) {
			throw new IllegalArgumentException("Prenom manquant");
		} else if (p.getEquipe() == null) {
			throw new IllegalArgumentException("Equipe manquante");
		} else if (p.getDebut() == null) {
			throw new IllegalArgumentException("Date de debut manquant");
		} else if (p.getMail() == null) {
			throw new IllegalArgumentException("Mail manquant");
		}

		p.setNom(nameFormat(p.getNom()));
		p.setPrenom(nameFormat(p.getPrenom()));
		super.create(p);
	}
}
