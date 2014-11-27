/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package entity;

import java.io.Serializable;
import java.util.Collection;
import java.util.Date;
import javax.persistence.Basic;
import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author joxit
 */
@Entity
@Table(name = "PERSONNES")
@XmlRootElement
@NamedQueries({
	@NamedQuery(name = "Personnes.findAll", query = "SELECT p FROM Personnes p"),
	@NamedQuery(name = "Personnes.findByPersonneId", query = "SELECT p FROM Personnes p WHERE p.personneId = :personneId"),
	@NamedQuery(name = "Personnes.findByNom", query = "SELECT p FROM Personnes p WHERE p.nom = :nom"),
	@NamedQuery(name = "Personnes.findByPrenom", query = "SELECT p FROM Personnes p WHERE p.prenom = :prenom"),
	@NamedQuery(name = "Personnes.findByMail", query = "SELECT p FROM Personnes p WHERE p.mail = :mail"),
	@NamedQuery(name = "Personnes.findByDebut", query = "SELECT p FROM Personnes p WHERE p.debut = :debut"),
	@NamedQuery(name = "Personnes.findByFin", query = "SELECT p FROM Personnes p WHERE p.fin = :fin")})
public class Personnes implements Serializable {
	private static final long serialVersionUID = 1L;
	@Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "PERSONNE_ID")
	private Integer personneId;
	@Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 25)
    @Column(name = "NOM")
	private String nom;
	@Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 25)
    @Column(name = "PRENOM")
	private String prenom;
	@Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 50)
    @Column(name = "MAIL")
	private String mail;
	@Basic(optional = false)
    @NotNull
    @Column(name = "DEBUT")
    @Temporal(TemporalType.DATE)
	private Date debut;
	@Column(name = "FIN")
    @Temporal(TemporalType.DATE)
	private Date fin;
	@OneToMany(cascade = CascadeType.ALL, mappedBy = "personne")
	private Collection<Responsables> responsablesCollection;
	@JoinColumn(name = "BUREAU", referencedColumnName = "BUREAU_ID")
    @ManyToOne
	private Bureaux bureau;
	@JoinColumn(name = "EQUIPE", referencedColumnName = "EQUIPE_ID")
    @ManyToOne(optional = false)
	private Equipes equipe;
	@OneToMany(cascade = CascadeType.ALL, mappedBy = "auteur")
	private Collection<Messages> messagesCollection;

	public Personnes() {
	}

	public Personnes(Integer personneId) {
		this.personneId = personneId;
	}

	public Personnes(Integer personneId, String nom, String prenom, String mail, Date debut) {
		this.personneId = personneId;
		this.nom = nom;
		this.prenom = prenom;
		this.mail = mail;
		this.debut = debut;
	}

	public Integer getPersonneId() {
		return personneId;
	}

	public void setPersonneId(Integer personneId) {
		this.personneId = personneId;
	}

	public String getNom() {
		return nom;
	}

	public void setNom(String nom) {
		this.nom = nom;
	}

	public String getPrenom() {
		return prenom;
	}

	public void setPrenom(String prenom) {
		this.prenom = prenom;
	}

	public String getMail() {
		return mail;
	}

	public void setMail(String mail) {
		this.mail = mail;
	}

	public Date getDebut() {
		return debut;
	}

	public void setDebut(Date debut) {
		this.debut = debut;
	}

	public Date getFin() {
		return fin;
	}

	public void setFin(Date fin) {
		this.fin = fin;
	}

	@XmlTransient
	public Collection<Responsables> getResponsablesCollection() {
		return responsablesCollection;
	}

	public void setResponsablesCollection(Collection<Responsables> responsablesCollection) {
		this.responsablesCollection = responsablesCollection;
	}

	public Bureaux getBureau() {
		return bureau;
	}

	public void setBureau(Bureaux bureau) {
		this.bureau = bureau;
	}

	public Equipes getEquipe() {
		return equipe;
	}

	public void setEquipe(Equipes equipe) {
		this.equipe = equipe;
	}

	@XmlTransient
	public Collection<Messages> getMessagesCollection() {
		return messagesCollection;
	}

	public void setMessagesCollection(Collection<Messages> messagesCollection) {
		this.messagesCollection = messagesCollection;
	}

	@Override
	public int hashCode() {
		int hash = 0;
		hash += (personneId != null ? personneId.hashCode() : 0);
		return hash;
	}

	@Override
	public boolean equals(Object object) {
		// TODO: Warning - this method won't work in the case the id fields are not set
		if (!(object instanceof Personnes)) {
			return false;
		}
		Personnes other = (Personnes) object;
		if ((this.personneId == null && other.personneId != null) || (this.personneId != null && !this.personneId.equals(other.personneId))) {
			return false;
		}
		return true;
	}

	@Override
	public String toString() {
		return "entity.Personnes[ personneId=" + personneId + " ]";
	}

}
