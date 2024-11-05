import { APIsql, connexion } from "../modele/connexion.js";
class UnProduit {
  private _codeProd: string;
  private _libProd: string;
  private _type: string;
  private _pays: string;
  private _conditionnement: string;
  private _tarifHt: string;
  constructor(code_prod = "", lib_prod = "", type = "",
  pays = "", conditionnement = "", tarif_ht = ""
  ) { // initialisation à l’instanciation
    this._codeProd = code_prod;
    this._libProd = lib_prod;
    this._type = type;
    this._pays = pays;
    this._conditionnement = conditionnement;
    this._tarifHt = tarif_ht;
  }
  // définition des « getters » et des « setters » pour les attributs privés de la classe
  get codeProd(): string {
    return this._codeProd;
  }
  set codeProd(code_prod: string) {
    this._codeProd = code_prod;
  }
  get libProd(): string {
    return this._libProd;
  }
  set libProd(lib_prod: string) {
    this._libProd = lib_prod;
  }
  get type(): string {
    return this._type;
  }
  set type(type: string) {
    this._type = type;
  }
  get pays(): string {
    return this._pays;
  }
  set pays(pays: string) {
    this._pays = pays;
  }
  get conditionnement(): string {
    return this._conditionnement;
  }
  set conditionnement(conditionnement: string) {
    this._conditionnement = conditionnement;
  }
  get tarifHt(): string {
    return this._tarifHt;
  }
  set tarifHt(tarif_ht: string) {
    this._tarifHt = tarif_ht;
  }
  toArray(): APIsql.TtabAsso {
    // renvoie l’objet sous la forme d’un tableau associatif
    // pour un affichage dans une ligne d’un tableau HTML
    let tableau: APIsql.TtabAsso = {
      "codeProd": this._codeProd,
      "libProd": this._libProd,
      "type": this._type,
      "pays": this._pays,
      "conditionnement": this._conditionnement,
      "tarifHt": this._tarifHt
    };
    return tableau;
  }
}
type TProduits = { [key: string]: UnProduit }; // tableau d’objets UnProduit
// eslint-disable-next-line @typescript-eslint/no-unused-vars
class LesProduits {
  static byCodeProd(arg0: string) {
    throw new Error("Method not implemented.");
  } // définition de la classe gérant les données de la table PRODUIT
  constructor() {
    // rien
  }
  private load(result: APIsql.TdataSet): TProduits {
    // à partir d’un TdataSet, conversion en tableau d’objets UnProduit
    let produits: TProduits = {};
    for (let i = 0; i < result.length; i++) {
      const item: APIsql.TtabAsso = result[i];
      const produit = new UnProduit(
        item["code_prod"],
        item["lib_prod"],
        item["type"],
        item["pays"],
        item["conditionnement"],
        item["tarif_ht"],
      );
      produits[produit.codeProd] = produit; // clé d’un élément du tableau : code prod
    }
    return produits;
  }
  private prepare(where: string): string { // préparation de la requête avec ou sans restriction (WHERE)
    let sql: string;
    sql = "SELECT code_prod, lib_prod, type, pays, conditionnement, tarif_ht";
    sql += " FROM PRODUIT";
    if (where.trim() !== "") {
      sql += " WHERE " + where;
    }
    sql += " ORDER BY lib_prod ASC ";
    return sql;
  }
  all(): TProduits { // renvoie le tableau d’objets contenant tous les produits
    return this.load(APIsql.sqlWeb.SQLloadData(this.prepare(""), []));
  }
  byCodeProd(code_prod: string): UnProduit { // renvoie l’objet correspondant à l’équipement code_prod
    let produit = new UnProduit();
    const produits: TProduits = this.load(
      APIsql.sqlWeb.SQLloadData(this.prepare("code_prod = ?"), [code_prod]),
    );
    const lesCles: string[] = Object.keys(produits);
    // affecte les clés du tableau associatif « typEquipts » dans le tableau de chaines « lesCles »
    if (lesCles.length > 0) {
      produit = produits[lesCles[0]]; // récupérer le 1er élément du tableau associatif « produits »
    }
    return produit;
  }
  toArray(produits: TProduits): APIsql.TdataSet { // renvoie le tableau d’objets sous la forme
    // d’un tableau de tableaux associatifs pour un affichage dans un tableau HTML
    let T: APIsql.TdataSet = [];
    for (let id in produits) {
      T.push(produits[id].toArray());
    }
    return T;
  }
}
class UnProduitByFacture {
  private _qteProd: number;
  private _unProduit: UnProduit;
  constructor(unProduit: UnProduit = null, qte_prod = 0) {
    // attributs de PRODUIT auxquelles on ajoute l’attribut « qte_prod » de la relation « LIGNE »
    this._unProduit = unProduit;
    this._qteProd = qte_prod;
  }
  // définition des « getters » et des « setters » pour les attributs privés de la classe
  get qteProd(): number {
    return this._qteProd;
  }
  set qteProd(qte_prod: number) {
    this._qteProd = qte_prod;
  }
  get unProduit(): UnProduit {
    return this._unProduit;
  }
  set unProduit(unProduit: UnProduit) {
    this._unProduit = unProduit;
  }
  toArray(): APIsql.TtabAsso {
    // renvoie l’objet sous la forme d’un tableau associatif
    // pour un affichage dans une ligne d’un tableau HTML
    let tableau = this.unProduit.toArray(); // appel de la méthode « toArray » de « UnProduit »
    tableau["qte_prod"] = this.qteProd.toFixed(0);
    return tableau;
  }
}
type TProduitsByFacture = { [key: string]: UnProduitByFacture };
// eslint-disable-next-line @typescript-eslint/no-unused-vars
class LesProduitsByFacture {
  constructor() {
    // rien
  }
  private load(result: APIsql.TdataSet): TProduitsByFacture {
    // à partir d’un TdataSet, conversion en tableau d’objets UnProduitByFacture
    const produitsByFacture: TProduitsByFacture = {};
    const lesProduits = new LesProduits();
    for (let i = 0; i < result.length; i++) {
      const item: APIsql.TtabAsso = result[i];
      const unProduit = LesProduits.byCodeProd(item["code_prod"]);
      const produitsByFacture = new UnProduitByFacture(unProduit,parseInt(item["qte_prod"]),
      );
      produitsByFacture[produitsByFacture.unProduit.codeProd] = produitsByFacture;}
    return produitsByFacture;
  }
  private prepare(where: string): string {
    let sql: string;
    sql = "SELECT code_prod, qte_prod";
    sql += " FROM LIGNE";
    if (where.trim() !== "") {
      sql += " WHERE " + where;
    }
    return sql;
  }
  byNumFact(num_fact: string): TProduitsByFacture {
    // renvoie le tableau d’objets contenant toutes les informations de la facture num_fact
    return this.load(
      APIsql.sqlWeb.SQLloadData(this.prepare("num_fact = ?"), [num_fact]),
    );
  }
  byNumFactCodeProd(num_fact: string, code_prod: string): UnProduitByFacture {
    // renvoie l’objet du produit code_prod contenu dans la facture num_fact
    let produitByFacture = new UnProduitByFacture();
    let produitsByFacture: TProduitsByFacture = this.load(
      APIsql.sqlWeb.SQLloadData(
        this.prepare("num_fact = ? and code_prod = ?"),
        [num_fact, code_prod],
      ),
    );
    if (!produitsByFacture[0] === undefined) {
      produitByFacture = produitsByFacture[0];
    }
    return produitByFacture;
  }
  toArray(produits: TProduitsByFacture): APIsql.TdataSet {
    let T: APIsql.TdataSet = [];
    for (let id in produits) {
      T.push(produits[id].toArray());
    }
    return T;
  }
  getTotalNbProduits(produits: TProduitsByFacture): number {
    // renvoie la quantité totale de produits d'une facture
    let total = 0;
    for (let id in produits) {
      total += produits[id].qteProd;
    }
    return total;
  }
  delete(num_fact: string): boolean { // requête de suppression des produits d’une facture dans « LIGNE »
    let sql: string;
    sql = "DELETE FROM LIGNE WHERE num_fact = ?";
    return APIsql.sqlWeb.SQLexec(sql, [num_fact]); // requête de manipulation : utiliser SQLexec
  }
  insert(num_fact: string, produits: TProduitsByFacture): boolean {
    // requête d’ajout des produits avec une quantité dans « LIGNE » installé dans « num_fact »
    let sql: string;
    let separateur = "";
    sql = "INSERT INTO LIGNE(num_fact,code_prod, qte_prod) VALUES ";
    for (let cle in produits) {
      sql += separateur + "('" + num_fact + "','" +
        produits[cle].unProduit.codeProd + "','" +
        produits[cle].qteProd + "')";
      separateur = ",";
    }
    return APIsql.sqlWeb.SQLexec(sql, []);
  }
}
export { connexion };
export { UnProduit };
export { LesProduits };
export { TProduits };
export { UnProduitByFacture };
export { LesProduitsByFacture };
export { TProduitsByFacture };