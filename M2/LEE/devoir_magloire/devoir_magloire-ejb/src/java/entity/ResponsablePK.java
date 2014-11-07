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
import javax.validation.constraints.Size;

/**
 *
 * @author 11000369
 */
@Embeddable
public class ResponsablePK implements Serializable {
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

    public ResponsablePK() {
    }

    public ResponsablePK(String identifiant, String motDePasse) {
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

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (identifiant != null ? identifiant.hashCode() : 0);
        hash += (motDePasse != null ? motDePasse.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof ResponsablePK)) {
            return false;
        }
        ResponsablePK other = (ResponsablePK) object;
        if ((this.identifiant == null && other.identifiant != null) || (this.identifiant != null && !this.identifiant.equals(other.identifiant))) {
            return false;
        }
        if ((this.motDePasse == null && other.motDePasse != null) || (this.motDePasse != null && !this.motDePasse.equals(other.motDePasse))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "entity.ResponsablePK[ identifiant=" + identifiant + ", motDePasse=" + motDePasse + " ]";
    }

}
