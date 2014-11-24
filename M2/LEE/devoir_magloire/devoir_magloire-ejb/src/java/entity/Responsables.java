/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package entity;

import java.io.Serializable;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author joxit
 */
@Entity
@Table(name = "RESPONSABLES")
@XmlRootElement
@NamedQueries({
	@NamedQuery(name = "Responsables.findAll", query = "SELECT r FROM Responsables r"),
	@NamedQuery(name = "Responsables.findByIdentifiant", query = "SELECT r FROM Responsables r WHERE r.identifiant = :identifiant"),
	@NamedQuery(name = "Responsables.findByMotDePasse", query = "SELECT r FROM Responsables r WHERE r.motDePasse = :motDePasse")})
public class Responsables implements Serializable {
	private static final long serialVersionUID = 1L;
	@Id
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 20)
    @Column(name = "IDENTIFIANT")
	private String identifiant;
	@Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 20)
    @Column(name = "MOT_DE_PASSE")
	private String motDePasse;
	@JoinColumn(name = "PERSONNE", referencedColumnName = "PERSONNE_ID")
    @ManyToOne(optional = false)
	private Personnes personne;

	public Responsables() {
	}

	public Responsables(String identifiant) {
		this.identifiant = identifiant;
	}

	public Responsables(String identifiant, String motDePasse) {
		this.identifiant = identifiant;
		this.motDePasse = motDePasse;
	}

	public String getIdentifiant() {
		return identifiant;
	}

	public void setIdentifiant(String identifiant) {
		this.identifiant = identifiant;
	}

	public String getMotDePasse() {
		return motDePasse;
	}

	public void setMotDePasse(String motDePasse) {
		this.motDePasse = motDePasse;
	}

	public Personnes getPersonne() {
		return personne;
	}

	public void setPersonne(Personnes personne) {
		this.personne = personne;
	}

	@Override
	public int hashCode() {
		int hash = 0;
		hash += (identifiant != null ? identifiant.hashCode() : 0);
		return hash;
	}

	@Override
	public boolean equals(Object object) {
		// TODO: Warning - this method won't work in the case the id fields are not set
		if (!(object instanceof Responsables)) {
			return false;
		}
		Responsables other = (Responsables) object;
		if ((this.identifiant == null && other.identifiant != null) || (this.identifiant != null && !this.identifiant.equals(other.identifiant))) {
			return false;
		}
		return true;
	}

	@Override
	public String toString() {
		return "entity.Responsables[ identifiant=" + identifiant + " ]";
	}

}
