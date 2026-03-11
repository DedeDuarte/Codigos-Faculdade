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

 public class Validador {

    private int pos;

    public boolean validar(String expr) {
        expr = expr.replaceAll("\\s+", "");
        pos = 0;
        boolean ok = parseNo(expr);
        return ok && pos == expr.length();
    }

    private boolean parseNo(String s) {
        if (pos >= s.length() || s.charAt(pos) != '(') return false;
        pos++; // abre parêntese

        if (!parseNumero(s)) return false;
        if (!parseFilho(s)) return false;
        if (!parseFilho(s)) return false;

        // fecha parêntese
        if (pos >= s.length() || s.charAt(pos) != ')') return false;
        pos++;
        return true;
    }

    private boolean parseFilho(String s) {
        if (pos >= s.length()) return false;
        if (s.charAt(pos) == '*') {
            pos++;
            return true;
        } else {
            return parseNo(s);
        }
    }

    private boolean parseNumero(String s) {
        int start = pos;
        while (pos < s.length() && Character.isDigit(s.charAt(pos))) {
            pos++;
        }
        return pos > start;
    }
}