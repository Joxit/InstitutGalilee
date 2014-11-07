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
import javax.persistence.JoinColumn;
import javax.persistence.JoinColumns;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author 11000369
 */
@Entity
@Table(name = "PERSONNES")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Personnes.findAll", query = "SELECT p FROM Personnes p"),
    @NamedQuery(name = "Personnes.findByPersonneId",
            query = "SELECT p FROM Personnes p WHERE p.personneId = :personneId"),
    @NamedQuery(name = "Personnes.findByNom",
            query = "SELECT p FROM Personnes p WHERE p.nom = :nom"),
    @NamedQuery(name = "Personnes.findByPrenom",
            query = "SELECT p FROM Personnes p WHERE p.prenom = :prenom"),
    @NamedQuery(name = "Personnes.findByMail",
            query = "SELECT p FROM Personnes p WHERE p.mail = :mail")})
public class Personnes implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "PERSONNE_ID")
    private Integer personneId;
    @Size(max = 25)
    @Column(name = "NOM")
    private String nom;
    @Size(max = 25)
    @Column(name = "PRENOM")
    private String prenom;
    @Size(max = 50)
    @Column(name = "MAIL")
    private String mail;
    @OneToMany(mappedBy = "auteur")
    private Collection<Message> messageCollection;
    /* zone changé pour referencer toutes les cles primaires de bureaux au lieu
     * du champs que j'ai créé pour facilité la lecture de la DB */
    @JoinColumns({@JoinColumn(name = "BUREAU", referencedColumnName = "BATIMENT"),
        @JoinColumn(name = "BUREAU", referencedColumnName = "ETAGE"),
        @JoinColumn(name = "BUREAU", referencedColumnName = "NUMERO")})
    @ManyToOne
    private Bureaux bureau;
    @JoinColumn(name = "EQUIPE", referencedColumnName = "EQUIPE_ID")
    @ManyToOne
    private Equipe equipe;
    @OneToMany(mappedBy = "personne")
    private Collection<Responsable> responsableCollection;

    public Personnes() {
    }

    public Personnes(Integer personneId) {
        this.personneId = personneId;
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

    @XmlTransient
    public Collection<Message> getMessageCollection() {
        return messageCollection;
    }

    public void setMessageCollection(Collection<Message> messageCollection) {
        this.messageCollection = messageCollection;
    }

    public Bureaux getBureau() {
        return bureau;
    }

    public void setBureau(Bureaux bureau) {
        this.bureau = bureau;
    }

    public Equipe getEquipe() {
        return equipe;
    }

    public void setEquipe(Equipe equipe) {
        this.equipe = equipe;
    }

    @XmlTransient
    public Collection<Responsable> getResponsableCollection() {
        return responsableCollection;
    }

    public void setResponsableCollection(
            Collection<Responsable> responsableCollection) {
        this.responsableCollection = responsableCollection;
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
