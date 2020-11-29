package by.gstu.itp.server;

import by.gstu.itp.Parser;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.*;
import java.net.Socket;

public class ClientHandler implements Runnable {
    private static final Logger logger = LogManager.getLogger();
    private final Socket clientSocket;

    public ClientHandler(Socket clientSocket) {
        this.clientSocket = clientSocket;
    }

    @Override
    public void run() {
        try {
            if (clientSocket.isClosed()) throw new IllegalStateException();
            ObjectOutputStream out = new ObjectOutputStream(clientSocket.getOutputStream());

            // канал чтения из сокета
            ObjectInputStream in = new ObjectInputStream(clientSocket.getInputStream());
            while (!clientSocket.isClosed()) {
                String password = (String) in.readObject();
                boolean result = new Parser(password).checkPassword();
                out.writeObject(result);
            }
        } catch (IOException | ClassNotFoundException e) {
            logger.error(e);
        }
    }
}
