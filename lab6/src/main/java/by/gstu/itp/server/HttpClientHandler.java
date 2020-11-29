package by.gstu.itp.server;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.IOException;
import java.net.Socket;

public class HttpClientHandler implements Runnable {
    private static final Logger logger = LogManager.getLogger();
    private final Socket clientSocket;

    public HttpClientHandler(Socket clientSocket) {
        this.clientSocket = clientSocket;
    }
    @Override
    public void run() {
        boolean flag = true;
        while(flag){
            try (HttpRequest in = new HttpRequest(clientSocket.getInputStream());
                 HttpResponse out = new HttpResponse(clientSocket.getOutputStream())
            ) {
                switch (in.getUrlContextPath()) {
                    case "/":
                        String builder = "";
                        if (in.getMethod().equals("GET")) {
                            builder = "<p>Проверка введенного пароля на корректность</p>" +
                                    "<form action='/' method='POST'>" +
                                    "<p>" +
                                    "<label>Введите пароль: </label>" +
                                    "<input name='password' type='password'>" +
                                    "<button>Отправить</button>" +
                                    "</p>" +
                                    "</form>";
                        } else if (in.getMethod().equals("POST")) {
                            String password = in.getRawData().split("=")[1];
                            boolean checkPassword = new Parser(password).checkPassword();
                            builder = "<p>Введенный пароль:</p>" +
                                    "<p>" +
                                    password +
                                    "</p>" +
                                    "<hr>" +
                                    "<p>Результат проверки пароля на корректность:</p>" +
                                    "<p>" +
                                    checkPassword+
                                    "</p>"
                            ;
                        }
                        out.sendText(builder);
                        break;
                    case "/exit":
                        clientSocket.close();
                        flag = false;
                        break;
                    default:
                        out.sendNotFound();
                }
                // по окончанию выполнения блока try-with-resources потоки,
                // а вместе с ними и соединение будут закрыты
                System.out.println("Client disconnected!");
            } catch (IOException e) {
                logger.error(e);
            }
        }
    }
}
