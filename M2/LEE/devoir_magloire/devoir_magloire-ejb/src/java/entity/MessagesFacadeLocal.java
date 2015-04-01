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
public interface MessagesFacadeLocal {

	void create(Messages messages);

	void edit(Messages messages);

	void remove(Messages messages);

	Messages find(Object id);

	List<Messages> findAll();

	List<Messages> findRange(int[] range);

	int count();

	public void create(int auteur, String msg);

	public List<Messages> findByEtat(Boolean etat);

	public List<Messages> findByEtatSorted(Boolean etat);
}
