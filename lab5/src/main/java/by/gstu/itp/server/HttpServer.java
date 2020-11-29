package by.gstu.itp.server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class HttpServer {
    private static final int PORT = 8080;

    private final ServerSocket serverSocket;
    private final ExecutorService executorService = Executors.newCachedThreadPool();

    public static void main(String[] args) {
        HttpServer httpServer = new HttpServer(PORT);
        httpServer.run();
    }

    public HttpServer(int port) {
        try {
            serverSocket = new ServerSocket(port);
        } catch (IOException e) {
            throw new IllegalStateException();
        }
    }

    public void run() {
        try {
            System.out.println("server run");
            while (!serverSocket.isClosed()) {
                System.out.println("Wait new request...");
                final Socket clientSocket = serverSocket.accept();
                System.out.println("Get new request from " + clientSocket.getInetAddress());

                executorService.execute(new HttpClientHandler(clientSocket));
            }
        } catch (IOException e) {
            throw new IllegalStateException();
        }
    }
}
