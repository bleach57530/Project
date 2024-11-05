import { vueFactureListe } from "../controleur/class_facture_liste.js";
vueFactureListe.init({
  divTitre: document.querySelector("[id=div_facture_liste_titre]"),
  btnAjouter: document.querySelector("[id=btn_facture_ajouter]"),
  btnModifier: document.querySelector("[id=btn_facture_modifier]"),
  btnSupprimer: document.querySelector("[id=btn_facture_details]"),
  btnDetails: document.querySelector("[id=btn_facture_details]"),
  tableFacture: document.querySelector("[id=table_facture]"),
});