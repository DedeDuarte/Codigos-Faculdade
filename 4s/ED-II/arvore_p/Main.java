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

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Arvore[] arvs = get_file("entrada.txt");
        Scanner sc = new Scanner(System.in);
        Cores c = new Cores();
        
        for (int i = 0; i < arvs.length; i++) {
            System.out.printf(c.red() + "===== Arvore %d =====\n" + c.reset(), i+1);
            stats_arvore(arvs[i]);

            boolean op = (i != arvs.length-1) ? opcao(sc) : false;
            
            if (!op) {
                System.out.println("Finalizando...");
                return;
            }
        }

        sc.close();
    }

    private static boolean opcao(Scanner sc) {
        System.out.println();

        while (true) {
            System.out.print("Digite 'S' para continuar ou 'N' para finalizar: ");
            String op = sc.nextLine().trim().toLowerCase();

            if (op.equals("n")) {
                System.out.println();
                return false;
            }
            if (op.equals("s")) {
                System.out.println();
                return true;
            }
            System.out.println("\nOpção inválida! Digite apenas 'S' ou 'N'.");
        }
    }

    private static Arvore nova_arvore(String input, boolean ehArvore) {
        No raiz = null;

        if (ehArvore) raiz = new ConversorArvore(input).converter();

        return new Arvore(raiz, input, ehArvore);
    }

    private static void stats_arvore(Arvore arv) {
        Cores c = new Cores();

        if (arv.ehArvore()) {
            System.out.println(c.reset() + "Entrada:" + c.cyan() + arv.get_expressao());

            System.out.println(c.reset() + "\nArvore:" + c.cyan());
            arv.exibirArvore();

            System.out.println(
                c.reset() + "\nAltura: " + c.cyan() + arv.alturaArvore() +
                c.reset() + "\nArvore: " + c.cyan() + arv.ehArvore() +
                c.reset() + "\n   BST: " + c.cyan() + arv.ehBST() +
                c.reset() + "\n   ALV: " + c.cyan() + arv.ehAVL()
            );

            System.out.println(c.reset() + "\nArvore em preOrdem:" + c.cyan());
            arv.preOrdem();
            System.out.print(c.reset());
        }
        else System.out.printf("A entrada '%s' nao é valida!\n", arv.get_expressao());
    }

    private static Arvore[] get_file(String arquivo_nome) {
        Scanner sc;
        Validador v = new Validador();

        try {
                File arquivo = new File(arquivo_nome);

                // Conta quantas linhas tem
                sc = new Scanner(arquivo);
                int linhas = 0;
                while (sc.hasNextLine()) {
                    sc.nextLine();
                    linhas++;
                }
                sc.close();

                // Cria um array com a quantidade exatas de linhas
                Arvore[] arvs = new Arvore[linhas];

                // Preenche o array com a árvore de cada linha
                sc = new Scanner(arquivo);
                int index = 0;
                while (sc.hasNextLine()) {
                    String linha = sc.nextLine();
                    if (v.validar(linha)) arvs[index++] = nova_arvore(linha, true);
                    else arvs[index++] = nova_arvore(linha, false);
                }
                sc.close();

                return arvs;
        }
        
        catch (FileNotFoundException e) {
            throw new RuntimeException("\nArquivo não encontrado: " + arquivo_nome);
        }
    }
}