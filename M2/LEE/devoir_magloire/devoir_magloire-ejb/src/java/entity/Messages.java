/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package entity;

import java.io.Serializable;
import java.util.Date;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author joxit
 */
@Entity
@Table(name = "MESSAGES")
@XmlRootElement
@NamedQueries({
	@NamedQuery(name = "Messages.findAll", query = "SELECT m FROM Messages m"),
	@NamedQuery(name = "Messages.findByMessageId", query = "SELECT m FROM Messages m WHERE m.messageId = :messageId"),
	@NamedQuery(name = "Messages.findByMessage", query = "SELECT m FROM Messages m WHERE m.message = :message"),
	@NamedQuery(name = "Messages.findByEtat", query = "SELECT m FROM Messages m WHERE m.etat = :etat"),
	@NamedQuery(name = "Messages.findByEnvoie", query = "SELECT m FROM Messages m WHERE m.envoie = :envoie"),
	@NamedQuery(name = "Messages.findByEtatSorted", query = "SELECT m FROM Messages m WHERE m.etat = :etat ORDER BY m.envoie DESC")})
public class Messages implements Serializable {

	private static final long serialVersionUID = 1L;
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	@Basic(optional = false)
	@Column(name = "MESSAGE_ID")
	private Integer messageId;
	@Basic(optional = false)
	@NotNull
	@Size(min = 1, max = 2000)
	@Column(name = "MESSAGE")
	private String message;
	@Basic(optional = false)
	@NotNull
	@Column(name = "ETAT")
	private Boolean etat;
	@Column(name = "ENVOIE")
	@Temporal(TemporalType.TIMESTAMP)
	private Date envoie;
	@JoinColumn(name = "AUTEUR", referencedColumnName = "PERSONNE_ID")
	@ManyToOne(optional = false)
	private Personnes auteur;

	public Messages() {
	}

	public Messages(Integer messageId) {
		this.messageId = messageId;
	}

	public Messages(Integer messageId, String message, Boolean etat) {
		this.messageId = messageId;
		this.message = message;
		this.etat = etat;
	}

	public Integer getMessageId() {
		return messageId;
	}

	public void setMessageId(Integer messageId) {
		this.messageId = messageId;
	}

	public String getMessage() {
		return message;
	}

	public void setMessage(String message) {
		this.message = message;
	}

	public Boolean getEtat() {
		return etat;
	}

	public void setEtat(Boolean etat) {
		this.etat = etat;
	}

	public Date getEnvoie() {
		return envoie;
	}

	public void setEnvoie(Date envoie) {
		this.envoie = envoie;
	}

	public Personnes getAuteur() {
		return auteur;
	}

	public void setAuteur(Personnes auteur) {
		this.auteur = auteur;
	}

	@Override
	public int hashCode() {
		int hash = 0;
		hash += (messageId != null ? messageId.hashCode() : 0);
		return hash;
	}

	@Override
	public boolean equals(Object object) {
		// TODO: Warning - this method won't work in the case the id fields are not set
		if (!(object instanceof Messages)) {
			return false;
		}
		Messages other = (Messages) object;
		if ((this.messageId == null && other.messageId != null) || (this.messageId != null && !this.messageId.equals(other.messageId))) {
			return false;
		}
		return true;
	}

	@Override
	public String toString() {
		return "entity.Messages[ messageId=" + messageId + " ]";
	}

}
