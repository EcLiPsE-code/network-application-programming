package by.gstu.itp.server;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

class Server {
    private static final Logger logger = LogManager.getLogger();
    private static final int PORT = 8080;

    public static void main(String[] args) {
        Server server = new Server();
        server.run();
    }

    private final ExecutorService executorService = Executors.newCachedThreadPool();
    private final ServerSocket serverSocket;


    public Server() {
        try {
            serverSocket = new ServerSocket(PORT);
        } catch (IOException e) {
            throw new IllegalStateException();
        }
    }

    public void run() {
        try {
            System.out.println("server run");
            while (!serverSocket.isClosed()) {
                System.out.println("Wait new client...");
                final Socket clientSocket = serverSocket.accept();
                System.out.println("New client connected " + clientSocket.getInetAddress());
                executorService.execute(new ClientHandler(clientSocket));
            }
        } catch (IOException e) {
            throw new IllegalStateException();
        }
    }

    public void close() {
        try {
            serverSocket.close();
        } catch (IOException e) {
            throw new IllegalStateException();
        }
        ;
    }
}
