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

public class ConversorArvore {
    private String[] tokens;
    private int pos;

    public ConversorArvore(String expressao) {
        expressao = expressao.replace("(", " ( ").replace(")", " ) ").trim();
        tokens = expressao.split("\\s+");
        pos = 0;
    }

    public No converter() {
        if (pos >= tokens.length) return null;

        String token = tokens[pos++];

        if (token.equals("*")) return null;
        if (token.equals("(")) {
            int valor = Integer.parseInt(tokens[pos++]);

            No esquerda = converter();
            No direita  = converter();

            pos++; // pula o ")"

            return new No(valor, esquerda, direita);
        }
        return null;
    }
}