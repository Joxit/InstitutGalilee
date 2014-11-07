/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package entity;

import java.io.Serializable;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Embeddable;
import javax.validation.constraints.NotNull;

/**
 *
 * @author 11000369
 */
@Embeddable
public class BureauxPK implements Serializable {
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

    public BureauxPK() {
    }

    public BureauxPK(Character batiment, int etage, int numero) {
        this.batiment = batiment;
        this.etage = etage;
        this.numero = numero;
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

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (batiment != null ? batiment.hashCode() : 0);
        hash += (int) etage;
        hash += (int) numero;
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof BureauxPK)) {
            return false;
        }
        BureauxPK other = (BureauxPK) object;
        if ((this.batiment == null && other.batiment != null) || (this.batiment != null && !this.batiment.equals(other.batiment))) {
            return false;
        }
        if (this.etage != other.etage) {
            return false;
        }
        if (this.numero != other.numero) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "entity.BureauxPK[ batiment=" + batiment + ", etage=" + etage + ", numero=" + numero + " ]";
    }

}
