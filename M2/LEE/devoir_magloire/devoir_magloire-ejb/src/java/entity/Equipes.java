/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package entity;

import java.io.Serializable;
import java.util.Collection;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author joxit
 */
@Entity
@Table(name = "EQUIPES")
@XmlRootElement
@NamedQueries({
	@NamedQuery(name = "Equipes.findAll", query = "SELECT e FROM Equipes e"),
	@NamedQuery(name = "Equipes.findByEquipeId", query = "SELECT e FROM Equipes e WHERE e.equipeId = :equipeId")})
public class Equipes implements Serializable {
	private static final long serialVersionUID = 1L;
	@Id
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 10)
    @Column(name = "EQUIPE_ID")
	private String equipeId;
	@OneToMany(mappedBy = "equipe")
	private Collection<Personnes> personnesCollection;

	public Equipes() {
	}

	public Equipes(String equipeId) {
		this.equipeId = equipeId;
	}

	public String getEquipeId() {
		return equipeId;
	}

	public void setEquipeId(String equipeId) {
		this.equipeId = equipeId;
	}

	@XmlTransient
	public Collection<Personnes> getPersonnesCollection() {
		return personnesCollection;
	}

	public void setPersonnesCollection(Collection<Personnes> personnesCollection) {
		this.personnesCollection = personnesCollection;
	}

	@Override
	public int hashCode() {
		int hash = 0;
		hash += (equipeId != null ? equipeId.hashCode() : 0);
		return hash;
	}

	@Override
	public boolean equals(Object object) {
		// TODO: Warning - this method won't work in the case the id fields are not set
		if (!(object instanceof Equipes)) {
			return false;
		}
		Equipes other = (Equipes) object;
		if ((this.equipeId == null && other.equipeId != null) || (this.equipeId != null && !this.equipeId.equals(other.equipeId))) {
			return false;
		}
		return true;
	}

	@Override
	public String toString() {
		return "entity.Equipes[ equipeId=" + equipeId + " ]";
	}

}
