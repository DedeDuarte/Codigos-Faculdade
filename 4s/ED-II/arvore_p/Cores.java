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

 public class Cores {
    public String red() {
        return "\033[38;2;255;000;000m";
    }

    public String cyan() {
        return "\033[38;2;000;255;255m";
    }

    public String reset() {
        return "\033[0m";
    }

    public String RGB(int R, int G, int B) {
        return String.format("\u001B[38;2;%d;%d;%dm", R, G, B);
    }
}