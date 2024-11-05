// importation des classes de gestion des données d’une facture et de ses produits et clients
import { LesFactures, TFactures, UneFacture } from "../modele/data_facture.js";
import { LesForfaits } from "../modele/data_forfait.js";
import { LesClients, UnClient } from "../modele/data_client.js";
import { LesProduitsByFacture, LesProduits, UnProduit } from "../modele/data_produit_ligne.js";
// déclaration de l’ensemble des zones de saisie et d’affichage nécessaires à la gestion du formulaire type
type TFactureListeForm = {
  divTitre: HTMLElement;
  btnAjouter: HTMLInputElement;
  btnModifier: HTMLInputElement;
  btnSupprimer: HTMLInputElement;
  btnDetails: HTMLInputElement;
  tableFacture: HTMLTableElement;
};
class VueFactureListe {
  private _form: TFactureListeForm;
  get form(): TFactureListeForm {
    return this._form;
  }
  init(form: TFactureListeForm): void {
    this._form = form;
    const lesFactures = new LesFactures();
    const lesForfaits = new LesForfaits();
    const lesClients = new LesClients();
    const lesProduitsByFacture = new LesProduitsByFacture();
    const lesProduits = new LesProduits();
    const unProduit = new UnProduit();
    const data = lesFactures.all();
    this.form.divTitre.textContent = "Liste des factures"; // construction du titre
    for (let num in data) {
      const uneFacture: UneFacture = data[num];
      const tr = this.form.tableFacture.insertRow(); // création nlle ligne dans tableau
      tr.insertCell().textContent = uneFacture.numFact;
      tr.insertCell().textContent = uneFacture.dateFact;
      tr.insertCell().textContent =
        lesClients.byIdCli(uneFacture.idCli).idCli;
      tr.insertCell().textContent =
        lesClients.byIdCli(uneFacture.idCli).nomCli;
        tr.insertCell().textContent =
        lesClients.byIdCli(uneFacture.idCli).communeCli;
      tr.insertCell().textContent = (lesProduitsByFacture.getTotalNbProduits(
        lesProduitsByFacture.byNumFact(num),
      ) * Number(lesProduits.byCodeProd(unProduit.codeProd).tarifHt)).toFixed(0);
      tr.insertCell().textContent = ((lesProduitsByFacture.getTotalNbProduits(
        lesProduitsByFacture.byNumFact(num),
      ) * Number(lesProduits.byCodeProd(unProduit.codeProd).tarifHt))-(Number(uneFacture.tauxRemiseFact))).toFixed(0);


    this.form.btnModifier.onclick = function (): void {
      vueFactureListe.modifierFactureClick(num);
    };
    this.form.btnSupprimer.onclick = function (): void {
      vueFactureListe.supprimerFactureClick(num);
    };
    this.form.btnDetails.onclick = function (): void {
      vueFactureListe.detailsFactureClick(num);
    };
    }
    // définition événement onclick sur bouton "ajouter"
    this.form.btnAjouter.onclick = function (): void {
      vueFactureListe.ajouterFactureClick();
    };
  }
  detailsFactureClick(num: string): void {
    // redirection vers « facture_edit.html »avec indication du statut « affi » et du numéro de facture
    location.href = "facture_edit.html?affi&" + encodeURIComponent(num);
  }
  modifierFactureClick(num: string): void {
    // redirection vers « facture_edit.html »avec indication du statut « modif » et du numéro de facture
    location.href = "facture_edit.html?modif&" + encodeURIComponent(num);
  }
  supprimerFactureClick(num: string): void {
    // redirection vers « facture_edit.html »avec indication du statut »suppr » et du numéro de facture
    location.href = "facture_edit.html?suppr&" + encodeURIComponent(num);
  }
  ajouterFactureClick(): void {
    // redirection vers « facture_edit.html »avec indication du statut « ajout »
    location.href = "facture_edit.html?ajout";
  }
}
let vueFactureListe = new VueFactureListe();
export { vueFactureListe };