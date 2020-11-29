package by.gstu.itp.server.api;

public class Parser {
    private static final String pattern = "(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*[ _-]).{6,}";

    private String password;

    public Parser(String password){
        setPassword(password);
    }

    public String getPassword(){return password;}
    public void setPassword(String password){
        this.password = password;
    }

    public boolean checkPassword(){
        return password.matches(pattern);
    }
}
