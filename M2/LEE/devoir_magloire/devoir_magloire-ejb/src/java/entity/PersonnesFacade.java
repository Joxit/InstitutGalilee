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

	public List<Personnes> findByEquipe(Equipes equipe) {
		return findAll().stream().parallel().filter(p -> {
			return p.getEquipe().equals(equipe);
		}).collect(Collectors.toList());
	}

	@Override
	public List<Personnes> findAllSortedByName() {
		return findAll().stream().sorted((p1, p2) -> {
			int c1 = p1.getNom().compareToIgnoreCase(p2.getNom());
			if (c1 == 0) {
				return p1.getPrenom().compareToIgnoreCase(p2.getPrenom());
			} else {
				return c1;
			}
		}).collect(Collectors.toList());
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
		}
		if (p.getPrenom() == null) {
			throw new IllegalArgumentException("prenom manquant");
		}
		if (p.getEquipe() == null) {
			throw new IllegalArgumentException("Equipe manquante");
		}
		if (p.getDebut() == null) {
			throw new IllegalArgumentException("Date de debut manquant");
		}
		if (p.getMail() == null) {
			throw new IllegalArgumentException("Mail manquant");
		}

		p.setNom(nameFormat(p.getNom()));
		p.setPrenom(nameFormat(p.getPrenom()));
		super.create(p);
	}
}
