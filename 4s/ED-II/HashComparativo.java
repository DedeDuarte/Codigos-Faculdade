import java.util.Random;

public class HashComparativo {

    static class HashTable {
        private int[] table;
        private int size;
        private int collisions;

        public HashTable(int size) {
            this.size = size;
            this.table = new int[size];
            for (int i = 0; i < size; i++) {
                table[i] = Integer.MIN_VALUE; // marca posição vazia
            }
            this.collisions = 0;
        }

        // Método da divisão
        private int hash(int key) {
            return key % size;
        }

        // Inserção com sondagem linear
        public void insertLinear(int key) {
            int index = hash(key);
            int originalIndex = index;

            while (table[index] != Integer.MIN_VALUE) {
                collisions++;
                index = (index + 1) % size;
                if (index == originalIndex) { // tabela cheia
                    System.out.println("Tabela cheia!");
                    return;
                }
            }
            table[index] = key;
        }

        // Inserção com sondagem quadrática
        public void insertQuadratic(int key) {
            int index = hash(key);
            int i = 0;
            while (table[(index + i * i) % size] != Integer.MIN_VALUE) {
                collisions++;
                i++;
                if (i == size) { // tabela cheia
                    System.out.println("Tabela cheia!");
                    return;
                }
            }
            table[(index + i * i) % size] = key;
        }

        public int getCollisions() {
            return collisions;
        }

        public void printTable() {
            for (int i = 0; i < size; i++) {
                System.out.print(table[i] + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        int tableSize = 20; // tamanho da tabela hash
        int numElements = 15; // quantidade de elementos aleatórios

        Random rand = new Random(42); // seed fixa para comparação

        int[] keys = new int[numElements];
        for (int i = 0; i < numElements; i++) {
            keys[i] = rand.nextInt(100); // valores aleatórios de 0 a 99
        }

        // Hash com sondagem linear
        HashTable linearTable = new HashTable(tableSize);
        for (int key : keys) {
            linearTable.insertLinear(key);
        }
        System.out.println("Tabela Linear:");
        linearTable.printTable();
        System.out.println("Colisões com sondagem linear: " + linearTable.getCollisions());

        // Hash com sondagem quadrática
        HashTable quadraticTable = new HashTable(tableSize);
        for (int key : keys) {
            quadraticTable.insertQuadratic(key);
        }
        System.out.println("\nTabela Quadrática:");
        quadraticTable.printTable();
        System.out.println("Colisões com sondagem quadrática: " + quadraticTable.getCollisions());
    }
}
