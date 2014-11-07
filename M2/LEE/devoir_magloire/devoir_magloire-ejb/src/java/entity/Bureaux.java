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
import javax.persistence.EmbeddedId;
import javax.persistence.Entity;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author 11000369
 */
@Entity
@Table(name = "BUREAUX")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Bureaux.findAll", query = "SELECT b FROM Bureaux b"),
    @NamedQuery(name = "Bureaux.findByBureauId",
            query = "SELECT b FROM Bureaux b WHERE b.bureauId = :bureauId"),
    @NamedQuery(name = "Bureaux.findByBatiment",
            query = "SELECT b FROM Bureaux b WHERE b.bureauxPK.batiment = :batiment"),
    @NamedQuery(name = "Bureaux.findByEtage",
            query = "SELECT b FROM Bureaux b WHERE b.bureauxPK.etage = :etage"),
    @NamedQuery(name = "Bureaux.findByNumero",
            query = "SELECT b FROM Bureaux b WHERE b.bureauxPK.numero = :numero")})
public class Bureaux implements Serializable {
    @Column(name = "LIMITE")
    private Integer limite;
    private static final long serialVersionUID = 1L;
    @EmbeddedId
    protected BureauxPK bureauxPK;
    @Basic(optional = false)
    @Column(name = "BUREAU_ID")
    private int bureauId;
    @OneToMany(mappedBy = "bureau")
    private Collection<Personnes> personnesCollection;

    public Bureaux() {
    }

    public Bureaux(BureauxPK bureauxPK) {
        this.bureauxPK = bureauxPK;
    }

    public Bureaux(BureauxPK bureauxPK, int bureauId) {
        this.bureauxPK = bureauxPK;
        this.bureauId = bureauId;
    }

    public Bureaux(Character batiment, int etage, int numero) {
        this.bureauxPK = new BureauxPK(batiment, etage, numero);
    }

    public BureauxPK getBureauxPK() {
        return bureauxPK;
    }

    public void setBureauxPK(BureauxPK bureauxPK) {
        this.bureauxPK = bureauxPK;
    }

    public int getBureauId() {
        return bureauId;
    }

    public void setBureauId(int bureauId) {
        this.bureauId = bureauId;
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
        hash += (bureauxPK != null ? bureauxPK.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Bureaux)) {
            return false;
        }
        Bureaux other = (Bureaux) object;
        if ((this.bureauxPK == null && other.bureauxPK != null) || (this.bureauxPK != null && !this.bureauxPK.equals(other.bureauxPK))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "entity.Bureaux[ bureauxPK=" + bureauxPK + " ]";
    }

    public Integer getLimite() {
        return limite;
    }

    public void setLimite(Integer limite) {
        this.limite = limite;
    }

}
