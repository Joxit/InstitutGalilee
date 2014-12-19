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
public interface BureauxFacadeLocal {

	void create(Bureaux bureaux);

	void edit(Bureaux bureaux);

	void remove(Bureaux bureaux);

	Bureaux find(Object id);

	List<Bureaux> findAll();

	List<Bureaux> findRange(int[] range);

	List<Bureaux> findByEquipe(Equipes equipe);

	public List<Bureaux> findAllSorted();

	int count();
}
