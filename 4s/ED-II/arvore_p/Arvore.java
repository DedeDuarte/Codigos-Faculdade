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

 public class Arvore {
    private No raiz;
    private String expressao = null;
    private boolean ehArvore = true;

    public Arvore() {
        this.raiz = null;
    }
    public Arvore(No raiz) {
        this.raiz = raiz;
    }
    public Arvore(No raiz, String expressao, boolean ehArvore) {
        this.raiz = raiz;
        this.expressao = expressao;
        this.ehArvore = ehArvore;
    }

    public void set_expressao(String expressao) { this.expressao = expressao; }
    public String get_expressao() { return expressao; }

    public void set_ehArvore(boolean ehArvore) { this.ehArvore = ehArvore; }
    public boolean ehArvore() { return this.ehArvore; }

    // Função para exibir a árvore, partindo da 'raiz'.
    public  void exibirArvore() { exibirArvore_rec(this.raiz, 0); }
    private void exibirArvore_rec(No no, int nivel) {
        if (no == null) return;

        exibirArvore_rec(no.get_direita(), nivel+1);

        for (int i = 0; i < nivel; i++) System.out.print("- - ");
        System.out.println(no.get_valor());

        exibirArvore_rec(no.get_esquerda(), nivel+1);
    }

    // Função para decidir se a árvore de 'raiz' é BST ou não.
    public  boolean ehBST() { return ehBST_rec(this.raiz, Integer.MIN_VALUE, Integer.MAX_VALUE); }
    private boolean ehBST_rec(No no, int min, int max) {
        if (no == null) return true;

        if (no.get_valor() <= min || no.get_valor() >= max) return false;

        return ehBST_rec(no.get_esquerda(), min, no.get_valor()) &&
               ehBST_rec(no.get_direita(),  no.get_valor(), max);
    }

    // Função para decidir se a árvore de 'raiz' é AVL ou não.
    public  boolean ehAVL() {
        if (!ehBST()) return false;
        return ehAVL_rec(this.raiz);
    }
    private boolean ehAVL_rec(No raiz) {
        if (raiz == null) return true;

        if (!ehAVL_rec(raiz.get_esquerda()) || !ehAVL_rec(raiz.get_direita())) return false;

        int altEsq = raiz.get_esquerda() != null ? alturaArvore_rec(raiz.get_esquerda()) : 0;
        int altDir = raiz.get_direita()  != null ? alturaArvore_rec(raiz.get_direita())  : 0;
        
        int total = altDir - altEsq;

        return total > -2 && total < 2;
    }

    // Função que retorna a altura da árvore de 'raiz'.
    public  int alturaArvore() { return alturaArvore_rec(this.raiz); }
    private int alturaArvore_rec(No raiz) {
        if (raiz == null) return 0;

        int altEsq = alturaArvore_rec(raiz.get_esquerda());
        int altDir = alturaArvore_rec(raiz.get_direita());

        int max = altEsq > altDir ? altEsq : altDir;
        return max + 1;
    }

    // Função que escreve a árvore de 'raiz' no formato 'emOrdem'.
    public void preOrdem() {
        StringBuilder sb = new StringBuilder();

        sb.append("[");
        preOrdem_rec(this.raiz, sb);
        sb.deleteCharAt(sb.length() - 1);
        sb.append("]");

        System.out.println(sb.toString());
    }
    public void preOrdem_rec(No no, StringBuilder sb) {
        if (no == null) {
            // sb.append("* "); // Se for usar '*' para filhos nulos
            return;
        }

        sb.append(no.get_valor()).append(" ");
        preOrdem_rec(no.get_esquerda(), sb);
        preOrdem_rec(no.get_direita(),  sb);
    }
}
