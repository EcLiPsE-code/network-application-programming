package by.gstu.itp.server;

import javax.net.ssl.*;
import java.io.FileInputStream;
import java.io.IOException;
import java.security.KeyStore;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class HttpServer {
    private static final int PORT = 8080;

    private SSLServerSocket serverSocket;
    private final ExecutorService executorService = Executors.newCachedThreadPool();

    public static void main(String[] args) {
        HttpServer httpServer  = new HttpServer(PORT);
        httpServer.run();
    }

    public HttpServer(int port) {
        try {
            SSLContext ctx;
            KeyManagerFactory kmf;
            KeyStore ks;
            char[] passphrase = "changeit".toCharArray();

            ctx = SSLContext.getInstance("TLS");
            kmf = KeyManagerFactory.getInstance("SunX509");
            ks = KeyStore.getInstance("JKS");

            ks.load(new FileInputStream("keystore.jks"), passphrase);
            kmf.init(ks, passphrase);
            ctx.init(kmf.getKeyManagers(), null, null);

            SSLServerSocketFactory socketFactory = ctx.getServerSocketFactory();

            serverSocket = (SSLServerSocket) socketFactory.createServerSocket(port);

        } catch (IOException e) {
            throw new IllegalStateException(e);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void run() {
        try {
            System.out.println("server run");
            while (!serverSocket.isClosed()) {
                System.out.println("Wait new request...");
                final SSLSocket clientSocket = (SSLSocket) serverSocket.accept();
                clientSocket.startHandshake();
                System.out.println("Get new request from " + clientSocket.getInetAddress());
                executorService.execute(new HttpClientHandler(clientSocket));
            }
        } catch (IOException e) {
            throw new IllegalStateException(e);
        }
    }
}
