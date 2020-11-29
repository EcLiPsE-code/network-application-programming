package by.gstu.beans;

import java.util.Objects;

public class Ship extends Bean{

    private enum TypeShip{  
        CRUISER, //крейсер
        AIRCRAFT_CARRIER, //авианосец
        DESTROYER, //эсминец
    }
    private String name;
    private TypeShip typeShip;
    private double displacement; //водоизмещение
    private String country;

    public Ship(int id, String name, TypeShip typeShip, double displacement, String country){
        super(id);
        this.name = Objects.requireNonNull(name);
        this.typeShip = typeShip;
        this.displacement = displacement;
        this.country = Objects.requireNonNull(country);
    }

    public Ship(String name, TypeShip typeShip, double displacement, String country){
        this.name = Objects.requireNonNull(name);
        this.typeShip = typeShip;
        this.displacement = displacement;
        this.country = Objects.requireNonNull(country);
    }

    public Ship(){}

    public String getName(){return name;}
    public String getCountry(){return country;}
    public TypeShip getTypeShip(){return typeShip;}
    public double getDisplacement(){return displacement;}

    public void setName(String name){
        this.name = Objects.requireNonNull(name);
    }
    public void setCountry(String country){
        this.country = Objects.requireNonNull(country);
    }
    public void setTypeShip(String typeShip){
        this.typeShip = Objects.requireNonNull(TypeShip.valueOf(typeShip));
    }
    public void setDisplacement(double displacement){
        this.displacement = displacement;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Ship)) return false;
        if (!super.equals(o)) return false;
        Ship ship = (Ship) o;
        return Double.compare(ship.getDisplacement(), getDisplacement()) == 0 &&
                Objects.equals(getName(), ship.getName()) &&
                getTypeShip() == ship.getTypeShip() &&
                Objects.equals(getCountry(), ship.getCountry());
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), getName(), getTypeShip(), getDisplacement(), getCountry());
    }

    @Override
    public String toString() {
        return super.toString() + "name: " + name + ",type ship: " + typeShip +
                ",displacement: " + displacement + ",country: " + country + "}";
    }
}
