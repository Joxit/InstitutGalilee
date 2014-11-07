/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package entity;

import java.io.Serializable;
import javax.persistence.EmbeddedId;
import javax.persistence.Entity;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author 11000369
 */
@Entity
@Table(name = "RESPONSABLE")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Responsable.findAll",
            query = "SELECT r FROM Responsable r"),
    @NamedQuery(name = "Responsable.findByIdentifiant",
            query = "SELECT r FROM Responsable r WHERE r.responsablePK.identifiant = :identifiant"),
    @NamedQuery(name = "Responsable.findByMotDePasse",
            query = "SELECT r FROM Responsable r WHERE r.responsablePK.motDePasse = :motDePasse")})
public class Responsable implements Serializable {
    private static final long serialVersionUID = 1L;
    @EmbeddedId
    protected ResponsablePK responsablePK;
    @JoinColumn(name = "PERSONNE", referencedColumnName = "PERSONNE_ID")
    @ManyToOne
    private Personnes personne;

    public Responsable() {
    }

    public Responsable(ResponsablePK responsablePK) {
        this.responsablePK = responsablePK;
    }

    public Responsable(String identifiant, String motDePasse) {
        this.responsablePK = new ResponsablePK(identifiant, motDePasse);
    }

    public ResponsablePK getResponsablePK() {
        return responsablePK;
    }

    public void setResponsablePK(ResponsablePK responsablePK) {
        this.responsablePK = responsablePK;
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
        hash += (responsablePK != null ? responsablePK.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Responsable)) {
            return false;
        }
        Responsable other = (Responsable) object;
        if ((this.responsablePK == null && other.responsablePK != null) || (this.responsablePK != null && !this.responsablePK.equals(other.responsablePK))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "entity.Responsable[ responsablePK=" + responsablePK + " ]";
    }

}
