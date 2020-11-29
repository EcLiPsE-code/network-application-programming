package by.gstu.itp.client;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class Client {

    private static final Logger logger = LogManager.getLogger();

    public static void main(String[] args) {
        Client client = new Client("127.0.0.1");
        client.connect();
    }

    private final String address;
    private final int port;

    public Client(String address, int port) {
        this.address = address;
        this.port = port;
    }

    public Client(String address) {
        this(address, 8080);
    }

    public void connect() {
        try(Socket socket = new Socket(address, port);
            Scanner in = new Scanner(new InputStreamReader(System.in));
            ObjectInputStream inServer = new ObjectInputStream(socket.getInputStream());
            ObjectOutputStream out = new ObjectOutputStream(socket.getOutputStream())) {

            System.out.println("Client connected to server.");

            while(!socket.isOutputShutdown()) {
                System.out.print("In: ");
                String command = in.nextLine();
                switch (command) {
                    case "send":
                        System.out.print("Enter password: ");
                        String password = in.nextLine(); //вводим пароль
                        out.writeObject(password); //отправляем серверу для парсинга
                        out.flush();
                        Boolean answer_server = (Boolean) inServer.readObject(); //получаем ответ сервера
                        System.out.println(answer_server); //выводим ответ в консоль
                        break;
                    case "quit":
                        System.out.println("Close connection with server");
                        socket.close();
                        break;
                    default:
                        System.out.println("This command is undefined");
                        break;
                }
            }

        } catch (IOException | ClassNotFoundException e) {
            logger.error(e);
        }

    }
}
