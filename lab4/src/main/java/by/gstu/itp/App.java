package by.gstu.itp;

import by.gstu.itp.client.Client;

/**
 * Hello world!
 *
 */
public class App {
    private static final float[][] TEMPLATE_MATRIX =  {
            new float[] {1, 4, 5, 6, 2},
            new float[] {6, 8, 2, 1, 4},
            new float[] {2, 4, 9, 7, 2},
            new float[] {7, 5, 2, 6, 4}
    };

    public static void main( String[] args ) {
        Client client = new Client("127.0.0.1");
        client.connect();
    }
}
