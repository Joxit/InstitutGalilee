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
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.validation.constraints.NotNull;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author joxit
 */
@Entity
@Table(name = "BUREAUX")
@XmlRootElement
@NamedQueries({
	@NamedQuery(name = "Bureaux.findAll", query = "SELECT b FROM Bureaux b"),
	@NamedQuery(name = "Bureaux.findByBureauId", query = "SELECT b FROM Bureaux b WHERE b.bureauId = :bureauId"),
	@NamedQuery(name = "Bureaux.findByBatiment", query = "SELECT b FROM Bureaux b WHERE b.batiment = :batiment"),
	@NamedQuery(name = "Bureaux.findByEtage", query = "SELECT b FROM Bureaux b WHERE b.etage = :etage"),
	@NamedQuery(name = "Bureaux.findByNumero", query = "SELECT b FROM Bureaux b WHERE b.numero = :numero"),
	@NamedQuery(name = "Bureaux.findByLimite", query = "SELECT b FROM Bureaux b WHERE b.limite = :limite")})
public class Bureaux implements Serializable {
	private static final long serialVersionUID = 1L;
	@Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "BUREAU_ID")
	private Integer bureauId;
	@Basic(optional = false)
    @NotNull
    @Column(name = "BATIMENT")
	private Character batiment;
	@Basic(optional = false)
    @NotNull
    @Column(name = "ETAGE")
	private int etage;
	@Basic(optional = false)
    @NotNull
    @Column(name = "NUMERO")
	private int numero;
	@Basic(optional = false)
    @NotNull
    @Column(name = "LIMITE")
	private int limite;
	@OneToMany(mappedBy = "bureau")
	private Collection<Personnes> personnesCollection;

	public Bureaux() {
	}

	public Bureaux(Integer bureauId) {
		this.bureauId = bureauId;
	}

	public Bureaux(Integer bureauId, Character batiment, int etage, int numero, int limite) {
		this.bureauId = bureauId;
		this.batiment = batiment;
		this.etage = etage;
		this.numero = numero;
		this.limite = limite;
	}

	public Integer getBureauId() {
		return bureauId;
	}

	public void setBureauId(Integer bureauId) {
		this.bureauId = bureauId;
	}

	public Character getBatiment() {
		return batiment;
	}

	public void setBatiment(Character batiment) {
		this.batiment = batiment;
	}

	public int getEtage() {
		return etage;
	}

	public void setEtage(int etage) {
		this.etage = etage;
	}

	public int getNumero() {
		return numero;
	}

	public void setNumero(int numero) {
		this.numero = numero;
	}

	public int getLimite() {
		return limite;
	}

	public void setLimite(int limite) {
		this.limite = limite;
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
		hash += (bureauId != null ? bureauId.hashCode() : 0);
		return hash;
	}

	@Override
	public boolean equals(Object object) {
		// TODO: Warning - this method won't work in the case the id fields are not set
		if (!(object instanceof Bureaux)) {
			return false;
		}
		Bureaux other = (Bureaux) object;
		if ((this.bureauId == null && other.bureauId != null) || (this.bureauId != null && !this.bureauId.equals(other.bureauId))) {
			return false;
		}
		return true;
	}

	@Override
	public String toString() {
		return "entity.Bureaux[ bureauId=" + bureauId + " ]";
	}

}
