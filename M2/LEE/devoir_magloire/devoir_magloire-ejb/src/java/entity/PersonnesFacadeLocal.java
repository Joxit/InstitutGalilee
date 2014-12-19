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
public interface PersonnesFacadeLocal {

	void create(Personnes personnes);

	void edit(Personnes personnes);

	void remove(Personnes personnes);

	Personnes find(Object id);

	List<Personnes> findAll();

	List<Personnes> findRange(int[] range);

	int count();

	List<Personnes> findByBureau(Bureaux bureau);

	public List<Personnes> findAllSortedByName();

	public List<Personnes> findByEquipe(Equipes equipe);
}
