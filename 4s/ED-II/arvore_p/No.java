/* 
 * Integrantes (04G) {
 *     Matheus Leonardo Cardoso Kroeff {
 *         RA: MAX_SIZE426434;
 *     }
 * 
 *     André Doerner Duarte {
 *         RA: MAX_SIZE427938;
 *     }
 * 
 *     Naoto Ushizaki {
 *         RA: MAX_SIZE437445;
 *     }
 * }
 */

 public class No {
    private int valor;
    private No  esquerda;
    private No  direita;

    public No() {
        this.valor = 0;
        this.esquerda = null;
        this.direita  = null;
    }

    public No(int valor) {
        this.valor = valor;
        this.esquerda = null;
        this.direita  = null;
    }

    public No(int valor, No esquerda, No direita) {
        this.valor = valor;
        this.esquerda = esquerda;
        this.direita  = direita;
    }

    public void set_valor(int valor) { this.valor = valor; }
    public void set_esquerda(No esquerda) { this.esquerda = esquerda; }
    public void set_direita(No  direita)  { this.direita  = direita; }

    public int get_valor() { return this.valor; }
    public No get_esquerda() { return this.esquerda; }
    public No get_direita()  { return this.direita; }
}